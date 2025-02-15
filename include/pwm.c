#include "hardware/pwm.h"

// Define o valor de wrap para o PWM
#define WRAP 4500

// Define o divisor para o relógio do PWM
const float DIVISOR_PWN = 555;

// Variáveis para controlar o slice e o pino PWM
uint slice;
uint pino;

// Flag para habilitar ou desabilitar o PWM
bool flag;

// Variáveis para controlar o passo e o nível do PWM
uint16_t step = 100;
uint16_t level = 100;

// Função para configurar o PWM no pino especificado
void config_pwm(pino, flag)
{
  // Configuração do pino PWM
  gpio_set_function(pino, GPIO_FUNC_PWM);

  // Configuração do PWM
  slice = pwm_gpio_to_slice_num(pino);
  pwm_set_clkdiv(slice, DIVISOR_PWN);
  pwm_set_wrap(slice, WRAP);
  pwm_set_gpio_level(pino, level);
  
  // Habilita ou desabilita o PWM
  pwm_set_enabled(slice, flag);
}