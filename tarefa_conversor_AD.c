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


ssd1306_t ssd;
char strx[5];
char stry[5];
char strnum[5];
char cores[10];

int main()
{
    adc_config();
    stdio_init_all();
    inicializacao_gpio();
    vermelho(100);
    while (true) {
        printf("Hello, world!\n");
        sleep_ms(1000);
    }
}
