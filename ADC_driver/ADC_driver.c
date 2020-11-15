#include <avr/io.h>
#include "ADC_driver.h"
#include "STD_Types.h"

void ADC_init(void)
{
#ifdef AREF
    ADMUX &= ~((1 << REFS0) | (1 << REFS1));

#elif AVCC
    ADMUX |= (1 << REFS0);
    ADMUX &= ~(1 << REFS1);

#elif INTRN
    ADMUX |= (1 << REFS0) | (1 << REFS1);

#endif

//resutl justification
#ifdef RITJUST
    ADMUX &= ~(1 << ADLAR);

#elif LFTJUST
    ADMUX |= (1 << ADLAR);

#endif

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
