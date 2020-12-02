#include<avr/io.h>

#include"../services.h"
#include"Timer_driver.h"

void timer0_init(unsigned char mode)
{   
    TCCR0 = 0;              //resets all bits
    TCCR0 |= mode;          //timer mode

    if (mode == NORMAL || mode == CTC)
    {
        SET_BIT(TCCR0, FOC0);   //force output compare non-PWM
    }
    else
    {
        CLR_BIT(TCCR0, FOC0);
    }

    SET_BIT(TIMSK, TOIE0);      //overflow interrupt enable
    SET_BIT(SREG, PIN7);        //global interrupt enable
}

void timer0_start(unsigned char clk)
{
    TCCR0 &= ~(0X07);           //timer off
    if (clk)
    {
        TCCR0 |= clk & 0X07;    //clock source set-up
    }
}

void timer0_compare_out_mode(unsigned char mode)
{
    if (mode)
    {
        SET_BIT(PORTB, PIN3);
        TCCR0 |= mode & 0X30;
    }
    
    else
    {
        CLR_BIT(PORTB, PIN3);
        TCCR0 |= mode & 0X30;
    }
}