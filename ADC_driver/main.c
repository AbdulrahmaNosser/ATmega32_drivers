#include <avr/io.h>
#include "ADC_driver.h"
#include "STD_Types.h"

int main(void)
{
	uint16 sensor = 0;

	DDRD = 0xff;

	ADC_init();

	while (1)
	{
		sensor = ADC_read(ADC0);
		sensor *= 5 * 100;
		sensor /= 1023;

		if (sensor > 30)
		{
			PORTD |= (1 << PD7);
		}
		else
		{
			PORTD &= ~(1 << PD7);
		}
	}
}
