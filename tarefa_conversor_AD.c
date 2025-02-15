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

#define I2C_PORT i2c1
#define I2C_SDA 14
#define I2C_SCL 15
#define endereco 0x3C
#define WIDTH 128
#define HEIGHT 64

static volatile uint32_t last_time = 0;
ssd1306_t ssd;
int PIN;
bool cor = true;
bool led_ON = false;
bool status = true;
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

static void interrupcao(uint gpio, uint32_t events);

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

int main()
{

    // #########################################################################      // Para ser utilizado o modo BOOTSEL com botão B
    // #######################################################################
    gpio_set_irq_enabled_with_callback(BT_J, GPIO_IRQ_EDGE_FALL, true, &interrupcao);
    gpio_set_irq_enabled_with_callback(BT_A, GPIO_IRQ_EDGE_FALL, true, &interrupcao);
    gpio_set_irq_enabled_with_callback(BT_B, GPIO_IRQ_EDGE_FALL, true, &interrupcao);
    config_display();
    adc_init();

    stdio_init_all();
    inicializacao_gpio();
    config_pwm(LED_B, status);
        config_pwm(LED_R, status);
    while (true)
    {
        ssd1306_rect(&ssd, 3, 3, 122, 60, cor, !cor); // Desenha um retângulo
        ssd1306_send_data(&ssd); // Atualiza o display
        adc_config();
        gpio_put(LED_G, led_ON);
        
       
        if ((eixo_x_valor < 1500) || (eixo_x_valor > 2200))
        {

            pwm_set_gpio_level(LED_R, eixo_x_valor);
        }
        else
        {
            pwm_set_gpio_level(LED_R, 0);
        }
        if ((eixo_y_valor < 1500) || (eixo_y_valor > 2200))
        {
            pwm_set_gpio_level(LED_B, eixo_y_valor);
        }
        else
        {
            pwm_set_gpio_level(LED_B, 0);
        }

        printf("eixo x:%d\n", eixo_x_valor);
        printf("eixo y:%d\n", eixo_y_valor);
        sleep_ms(200);
    }
}
void interrupcao(uint gpio, uint32_t events)
{
    // Obtém o tempo atual em microssegundos
    uint32_t current_time = to_us_since_boot(get_absolute_time());
    // Verifica se passou tempo suficiente desde o último evento
    if (current_time - last_time > 500000) // 500 ms de debouncing
    {
        last_time = current_time; // Atualiza o tempo do último evento

        if (gpio == BT_J)
        {
            if (led_ON == false)
            {
                led_ON = true;
                ssd1306_fill(&ssd, !cor); // Limpa o display
                ssd1306_rect(&ssd, 3, 3, 122, 60, cor, !cor); // Desenha um retângulo
                ssd1306_send_data(&ssd); // Atualiza o display
            }
            else
            {
                led_ON = false;
                ssd1306_fill(&ssd, !cor); // Limpa o display
                ssd1306_rect(&ssd, 6, 6, 116, 54, cor, !cor); // Desenha um retângulo
                ssd1306_rect(&ssd, 9, 9, 110, 48, cor, !cor); // Desenha um retângulo
                ssd1306_send_data(&ssd); // Atualiza o display
            }
        }
        if (gpio == BT_B)
        {
            reset_usb_boot(0, 0);
        }
        if(gpio == BT_A){
            if(status == true){
                status = false;
            }else{
                status = true;
                            }
            pwm_set_enabled(slice, status);

        }
    }
}
