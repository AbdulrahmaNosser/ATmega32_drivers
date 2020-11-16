#include "USART_driver.h"
#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
    char data = 0;
    DDRC = 0xff;

    USART_init(9600UL);
    USART_send_string("Enter O or F for ON & OFF\n\r");

    while (1) 
    {
        data = USART_read_byte();
        if (data == 'O')
        {
            PORTC |= (1<<PC0);
            USART_send_string("ON\n\r");
        }
        
        else if (data == 'F')
        {
            PORTC &= ~(1<<PC0);
            USART_send_string("OFF\n\r");
        }
        
    }
}

