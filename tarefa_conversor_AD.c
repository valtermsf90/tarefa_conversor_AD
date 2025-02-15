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

#define I2C_PORT i2c1
#define I2C_SDA 14
#define I2C_SCL 15
#define endereco 0x3C
#define WIDTH 128
#define HEIGHT 64

ssd1306_t ssd;
int PIN;
bool cor = true;
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
#include "pico/bootrom.h"
void gpio_irq_handler(uint gpio, uint32_t events)
{
    reset_usb_boot(0, 0);
}
// #######################################################

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
    gpio_set_irq_enabled_with_callback(BT_B, GPIO_IRQ_EDGE_FALL, true, &gpio_irq_handler);
    // #######################################################################

    config_display();
    adc_init();

    stdio_init_all();
    inicializacao_gpio();
    while (true)
    {
        adc_config();
        config_pwm(LED_B);
        config_pwm(LED_R);
        if((eixo_x_valor < 1200) || (eixo_x_valor > 2500)){

            pwm_set_gpio_level(LED_R, eixo_x_valor);
        }else{
            pwm_set_gpio_level(LED_R, 0);

        }
        if((eixo_y_valor < 1200) || (eixo_y_valor > 2500)){

            pwm_set_gpio_level(LED_B, eixo_y_valor);
        }else{
            pwm_set_gpio_level(LED_B, 0);

        }
        
        
        printf("eixo x:%d\n", eixo_x_valor);
        printf("eixo y:%d\n", eixo_y_valor);
        sleep_ms(400);
    }
}
