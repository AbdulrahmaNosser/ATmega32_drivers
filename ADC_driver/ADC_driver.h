#include "STD_Types.h"

#ifndef DRIVER_ADC_H_
#define DRIVER_ADC_H_

//voltage reference
#define AREF 1
//#define AVCC 1
//#define INTRN 1
//..................

//result justification
#define RITJUST 1
//#define LFTJUST 1
//..................

//Auto Trigger Enable
//External Interrupt Request 0
//#define ADC_AUTO 1

//ADC Interrupt Enable
//#define ADC_INT

//ADC Prescaler 2,4,8,16,32,64,128
#define ADC_scale 2

#define ADC0 0
#define ADC1 1
#define ADC2 2
#define ADC3 3
#define ADC4 4
#define ADC5 5
#define ADC6 6
#define ADC7 7

void ADC_init(void);
uint16 ADC_read(uint8 bit);

#endif /* DRIVER_ADC_H_ */
