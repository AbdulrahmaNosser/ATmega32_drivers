#include <avr/io.h>
#include <avr/interrupt.h>

#include"Timer_driver.h"
#include"../services.h"

ISR(TIMER0_OVF_vect)
{
    static volatile unsigned long long cnt = 0;

    cnt++;
    if (cnt > 152)              //5 secs delay 8MHz/(8bit * 1024 prescaller)
    {
        TOG_BIT(PORTD, PIN7);   //toggle pin7
        cnt = 0;
    }
}

int main(void)
{
    timer0_init(NORMAL);
    timer0_start(CLK1024);

    SET_BIT(DDRD, PIN7);

    while (1) 
    {
    }
}

