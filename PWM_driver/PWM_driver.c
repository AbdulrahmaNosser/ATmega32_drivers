#include <avr/io.h>

#include"PWM_driver.h"
#include"../services.h"

void pwm0_init(unsigned char generation_mode, unsigned char compare_mode)
{
    //clear registers
    PWM_CTRL_REG = 0;
    COUNTER_REG = 0;
    DUTY_CYCLE = 0;

    //set PWM
    PWM_CTRL_REG |= generation_mode | compare_mode;
    //set output pin
    SET_BIT(OUTPUT_DDRREG, OUPUT_PIN);
}

void pwm0_duty(unsigned char duty)
{
    DUTY_CYCLE = duty;
}