#include <avr/io.h>
#include "STD_Types.h"

void ADC_init(void)
{
    ADCSRA |= (1 << ADEN); //ADC enable
}

uint16 ADC_read(uint8 pin)
{
    ADMUX &= 0xE0;           //clear pin selection
    ADMUX |= ((0x1F) & pin); //select ADC pin
    ADCSRA |= (1 << ADSC);   //ADC start conversion

    while (ADCSRA & (1 << ADSC))
        ;       //wait for read
    return ADC; //read
}
