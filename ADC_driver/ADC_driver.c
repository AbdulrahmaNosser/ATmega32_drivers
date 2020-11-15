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

//result justification
    #ifdef RITJUST
        ADMUX &= ~(1 << ADLAR);

    #elif LFTJUST
        ADMUX |= (1 << ADLAR);

    #endif

//Auto Trigger Enable
    #ifdef ADC_AUTO
        ADCSRA |= (1<<ADATE);
        SFIOR |= (1<<ADTS1); //External Interrupt Request 0
    #endif

//ADC Interrupt Enable
    #ifdef ADC_INT
        ADCSRA |= (1<<ADIE);
    #endif

//ADC Prescaler
    if ((ADC_scale == 2)|(ADC_scale == 8)|(ADC_scale == 32)|(ADC_scale == 128))
    {
        ADCSRA |= (1<<ADPS0);
    }
    if ((ADC_scale == 4)|(ADC_scale == 8)|(ADC_scale == 64)|(ADC_scale == 128))
    {
        ADCSRA |= (1<<ADPS1);
    }
    if ((ADC_scale == 16)|(ADC_scale == 32)|(ADC_scale == 64)|(ADC_scale == 128))
    {
        ADCSRA |= (1<<ADPS2);
    }
//..................   

    ADCSRA |= (1 << ADEN); //ADC enable
}

uint16 ADC_read(uint8 pin)
{
    ADMUX &= 0xE0;           //clear pin selection
    ADMUX |= ((0x1F) & pin); //select ADC pin
    ADCSRA |= (1 << ADSC);   //ADC start conversion

    while (ADCSRA & (1 << ADSC)); //polling for result

    return ADC; //read
}
