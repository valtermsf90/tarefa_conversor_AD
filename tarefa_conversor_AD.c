#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/i2c.h"
#include "hardware/adc.h"
#include "hardware/pwm.h"
#include "include/ssd1306.h"
#include "include/funcoes.c"
#include "include/led_RGB_cores.c"
#include "include/adc.c"
#include "include/pwm.c"
#include "pico/bootrom.h"

// VARIAVEIRS DISPLAY
#define I2C_PORT i2c1
#define I2C_SDA 14
#define I2C_SCL 15
#define endereco 0x3C
#define WIDTH 128
#define HEIGHT 64

// VARIAVEIS GLOBAIS
static volatile uint32_t last_time = 0;
ssd1306_t ssd;
int PIN;
bool cor = true;
bool led_ON = false;
bool status = true;
int quadro = 1;
// PROTOTIPOS
static void interrupcao(uint gpio, uint32_t events);

// FUNCOES
void config_display()
{
    // Configuração do I2C
    i2c_init(I2C_PORT, 400 * 1000);
    gpio_set_function(I2C_SDA, GPIO_FUNC_I2C);
    gpio_set_function(I2C_SCL, GPIO_FUNC_I2C);
    gpio_pull_up(I2C_SDA);
    gpio_pull_up(I2C_SCL);

    // Inicialização do display OLED
    ssd1306_init(&ssd, WIDTH, HEIGHT, false, endereco, I2C_PORT);
    ssd1306_config(&ssd);
    ssd1306_send_data(&ssd);

    // Limpa o display
    ssd1306_fill(&ssd, false);
    ssd1306_send_data(&ssd);
}
void borda_retangulo(int modo){
    if(modo == 1){
        ssd1306_rect(&ssd, 3, 3, 122, 60, cor, !cor);
    }
    if(modo == 2){        
        ssd1306_rect(&ssd, 6, 6, 116, 54, cor, !cor);
        ssd1306_rect(&ssd, 9, 9, 110, 48, cor, !cor);
    }
}

// INICIO
int main()
{
    // Configuração das interrupções
    gpio_set_irq_enabled_with_callback(BT_J, GPIO_IRQ_EDGE_FALL, true, &interrupcao);
    gpio_set_irq_enabled_with_callback(BT_A, GPIO_IRQ_EDGE_FALL, true, &interrupcao);
    gpio_set_irq_enabled_with_callback(BT_B, GPIO_IRQ_EDGE_FALL, true, &interrupcao);
    // Configuração do display
    config_display();

    // INCIALIZACAO DO ADC, GIO, PWM
    stdio_init_all();
    adc_init();
    inicializacao_gpio();
    config_pwm(LED_B, status);
    config_pwm(LED_R, status);

     // Desenha um retângulo como borda
     
    // LOOP
    while (true)
    {
        // Limpa o display com a cor inversa
        ssd1306_fill(&ssd, !cor);

        // Calcula a posição X a partir do valor do eixo X
        int posicao_x = eixo_x_valor / 31.2;
        if (posicao_x > 115) // Limita a posição máxima em X
        {
            posicao_x = 115;
        }
        if (posicao_x < 5) // Limita a posição mínima em X
        {
            posicao_x = 5;
        }

        // Calcula a posição Y invertendo o eixo (porque a tela cresce para baixo)
        int posicao_y = 60 - (eixo_y_valor / 70.2);
        if (posicao_y > 53) // Limita a posição máxima em Y
        {
            posicao_y = 53;
        }
        if (posicao_y < 5) // Limita a posição mínima em Y
        {
            posicao_y = 5;
        }

       
        borda_retangulo(quadro);
        // Desenha um quadrado na posição calculada
        ssd1306_rect(&ssd, posicao_y, posicao_x, 8, 8, 1, 1);

        // Atualiza o display
        ssd1306_send_data(&ssd);

        // Configura o ADC (provavelmente para ler sensores)
        adc_config();

        // Acende o LED verde
        gpio_put(LED_G, led_ON);

        // Controla o brilho do LED vermelho com base no eixo X
        if ((eixo_x_valor < 1500) || (eixo_x_valor > 2200))
        {
            pwm_set_gpio_level(LED_R, eixo_x_valor);
        }
        else
        {
            pwm_set_gpio_level(LED_R, 0);
        }

        // Controla o brilho do LED azul com base no eixo Y
        if ((eixo_y_valor < 1500) || (eixo_y_valor > 2200))
        {
            pwm_set_gpio_level(LED_B, eixo_y_valor);
        }
        else
        {
            pwm_set_gpio_level(LED_B, 0);
        }

        // Exibe os valores dos eixos no terminal para depuração
        printf("eixo x:%d\n", eixo_x_valor);
        printf("posicao x:%d\n", posicao_x);
        printf("eixo y:%d\n", eixo_y_valor);
        printf("posicao y:%d\n", posicao_y); // Posição Y invertida

        // Aguarda 200ms antes da próxima iteração
        sleep_ms(200);
    }
}
void interrupcao(uint gpio, uint32_t events)
{
    // Obtém o tempo atual em microssegundos
    uint32_t current_time = to_us_since_boot(get_absolute_time());

    // Implementação de debounce: só executa se passaram pelo menos 500ms desde o último evento
    if (current_time - last_time > 500000)
    {
        last_time = current_time; // Atualiza o tempo do último acionamento

        // Verifica se o botão BT_J foi pressionado
        if (gpio == BT_J)
        {
            // Alterna o estado da variável led_ON
            led_ON = !led_ON;
            quadro++;
            if(quadro > 2){
                quadro = 1;
            }
        }

        // Verifica se o botão BT_B foi pressionado e reinicia no modo bootloader
        if (gpio == BT_B)
        {
            reset_usb_boot(0, 0);
        }

        // Verifica se o botão BT_A foi pressionado e alterna o status do PWM
        if (gpio == BT_A)
        {
            status = !status;               // Alterna entre ligado e desligado
            pwm_set_enabled(slice, status); // Ativa/desativa o PWM
        }
    }
}
