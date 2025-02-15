#include "hardware/pwm.h"

#define WRAP 4500
const float DIVISOR_PWN = 555;
uint slice;
uint pino;
bool flag;
uint16_t step = 100;
uint16_t level = 100;

void config_pwm(pino, flag)
{

  gpio_set_function(pino, GPIO_FUNC_PWM);
  slice = pwm_gpio_to_slice_num(pino);
  pwm_set_clkdiv(slice, DIVISOR_PWN);
  pwm_set_wrap(slice, WRAP);
  pwm_set_gpio_level(pino, level);
  pwm_set_enabled(slice, flag);
}