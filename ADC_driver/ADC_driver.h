#include "STD_Types.h"

#ifndef DRIVER_ADC_H_
#define DRIVER_ADC_H_

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
