#define F_CPU 8000000UL

#include <avr/io.h>
#include <util/delay.h>

#include "PWM_driver.h"

int main(void)
{
    pwm0_init(FAST, NIN_INVERTING);
    while (1)
    {
        pwm0_duty(255);
        _delay_ms(1000);

        pwm0_duty(128);
        _delay_ms(1000);

        pwm0_duty(64);
        _delay_ms(1000);

        pwm0_duty(0);
        _delay_ms(1000);
    }
}
