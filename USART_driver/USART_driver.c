#include <AVR/io.h>
#include "USART_driver.h"

void USART_init(long BaudRate)
{
    //Double Transmission Speed
    #if DOUBLE_SPEED
        UCSRA |= (1<<U2X);
    #endif  
//_________________________________

    //Multi-processor Communication
    #if MULTI_PRC_COM
        UCSRA |= (1<<MPCM);
    #endif
//_________________________________

    UCSRC |= (1<<URSEL);    //USCRC select


    #if SYNC_MODE
        UCSRC |= (1<<UMSEL);
    
    #else SYNC_MODE
        UCSRC &= ~(1<<UMSEL);
    #endif
//_________________________________

    #if PARITY == 1         //odd parity
        UCSRC &= ~(1<<UPM0);
        UCSRC |= (1<<UPM1);

    #elif PARITY == 2       //even parity
        UCSRC |= ((1<<UPM0)|(1<<UPM1));

    #else                   //parity disabled
        UCSRC &= ~((1<<UPM0)|(1<<UPM1));
    #endif
//_________________________________

    #if STOP_BIT == 1
        UCSRC &= ~(1<<USBS);
    #elif STOP_BIT == 2
        UCSRC |= (1<<USBS);
    #endif
//_________________________________

    #if CHAR_SIZE == 5
        UCSRB &= ~(1<<UCSZ2);
        UCSRC &= ~((1<<UCSZ0)|(1<<UCSZ1));
    
    #elif CHAR_SIZE == 6
        UCSRB &= ~(1<<UCSZ2);
        UCSRC |= (1<<UCSZ0);
        UCSRC &= ~((1<<UCSZ1));

    #elif CHAR_SIZE == 7
        UCSRB &= ~(1<<UCSZ2);
        UCSRC |= (1<<UCSZ1);
        UCSRC &= ~((1<<UCSZ0));

    #elif CHAR_SIZE == 8
        UCSRB &= ~(1<<UCSZ2);
        UCSRC |= (1<<UCSZ0)|(1<<UCSZ1);

    #elif CHAR_SIZE == 9
    UCSRB |= (1<<UCSZ2);
    UCSRC |= ((1<<UCSZ0)|(1<<UCSZ1));
    #endif
//_________________________________
//baud rate setting
    unsigned int BD_Rate_calc;

//baud calculation
    #if SYNC_MODE
        BD_Rate_calc = (F_CPU/(2*BaudRate)) - 1;
    #else
        
        #if DOUBLE_SPEED == 0

        BD_Rate_calc = (F_CPU/(16*BaudRate)) - 1;

        #elif DOUBLE_SPEED == 1
        BD_Rate_calc = (F_CPU/(8*BaudRate)) - 1;
        #endif
    #endif
    
//baud assignment
    UBRRL = BD_Rate_calc;
    UBRRH &= ~(1<<URSEL);    //UBRRH select
    UBRRH &= ~(0x0F);
    UBRRH |= (BD_Rate_calc>>8) * 0x0F;
//_________________________________

    UCSRB |= (1<<RXEN)|(1<<TXEN);     //Receiver & Transmitter Enable 
}

void USART_send_byte(unsigned char data)
{
    while(!(UCSRA & (1<<UDRE)));
    UDR = data;
}

void USART_send_string(unsigned char* data)
{
    unsigned int i = 0;
    while (data[i] != '\0')
    {
        USART_send_byte(data[i++]);
    }    
}

char USART_read_byte(void)
{
    while(!(UCSRA & (1<<RXC)));
    return UDR;
}

void USART_read_string(unsigned char* data)
{
    unsigned int i = 0;
    do
    {
        data[i++] = USART_read_byte();
    } while (data[i-1] != '\0');
}