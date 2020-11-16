#ifndef USART_DRIVER_
#define USART_DRIVER_
#define F_CPU 8000000UL
#define DOUBLE_SPEED 0
#define MULTI_PRC_COM 0
#define SYNC_MODE 0
#define PARITY 0        //0 disabled, 1 odd, 2 even
#define STOP_BIT 1      //1 bit, 2 bits
#define CHAR_SIZE 8     //5, 6, 7, 8, 9 bits

extern void USART_init(long BaudRate);
extern void USART_send_byte(unsigned char data);
extern void USART_send_string(unsigned char* data);
extern char USART_read_byte(void);
extern void USART_read_string(unsigned char* data);

#endif