#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/timer.h"
#include "hardware/clocks.h"
#include "funcoes.h"

#include <stdlib.h>
#include <time.h>

#define LED_G 11
#define LED_R 13
#define LED_B 12
#define BT_A 5
#define BT_J 23

// Prototipos

void inicializacao_gpio();

// GPIO-----------------------------------------------------------------
void inicializacao_gpio()
{
	// gpio_init(BT);
	gpio_init(BT_A);
	gpio_set_dir(BT_A, GPIO_IN);
	gpio_pull_up(BT_A);
	gpio_init(BT_J);
	gpio_set_dir(BT_J, GPIO_IN);
	gpio_pull_up(BT_J);
	// gpio_init(LED);
	gpio_init(LED_G);
	gpio_set_dir(LED_G, GPIO_OUT);
	gpio_init(LED_R);
	gpio_set_dir(LED_R, GPIO_OUT);
	gpio_init(LED_B);
	gpio_set_dir(LED_B, GPIO_OUT);
}

// inicializacao da maquina PIO-------------------------------------------------

// ADC---------------------------------------------------------
