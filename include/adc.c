#include "hardware/i2c.h"

// Define os pinos para os eixos X e Y do joystick
#define EIXO_Y 26 // ADC0
#define EIXO_X 27 // ADC1

// Variáveis para armazenar os valores lidos dos eixos X e Y
uint16_t eixo_x_valor;
uint16_t eixo_y_valor;

// Função para configurar e ler os valores do ADC (Analog-to-Digital Converter)
void adc_config()
{
  adc_select_input(0); // Seleciona o eixo Y
  eixo_y_valor = adc_read();// Le o valor do eixo Y
  adc_select_input(1); // Seleciona o eixo X
  eixo_x_valor = adc_read(); // Le o valor do eixo X 
}