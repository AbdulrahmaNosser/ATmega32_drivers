#include <avr/io.h>
#include "../services.h"

#ifndef LCD_driver_
#define LCD_driver_


#define BIT_MODE (8)  //4 | 8 Bit mode
#if BIT_MODE == 4
    #define NIBBLE_SELECT 'H'   //'L' | 'H' for low | high nibble
#endif
#define LINES_NUMBER (2)  // 1, 2

#define LCD_DDR DDRC
#define LCD_REG PORTC
#define LCD_CTR_DDR DDRD
#define LCD_CTR_REG PORTD


#define D0 PIN0
#define D1 PIN1
#define D2 PIN2
#define D3 PIN3
#define D4 PIN4
#define D5 PIN5
#define D6 PIN6
#define D7 PIN7

#define RS PIN0
#define E  PIN1

#if BIT_MODE == 8
    #if LINES_NUMBER == 2
        #define FUNCTION_SET   (0X38)
    #elif LINES_NUMBER == 1
        #define FUNCTION_SET   (0X30)
    #endif
    
#elif BIT_MODE == 4
    #if LINES_NUMBER == 2
        #define FUNCTION_SET   (0X28)
    #elif LINES_NUMBER == 1
        #define FUNCTION_SET   (0X20)
    #endif
#endif

#define CLEAR_DISPLAY  (0X01)
#define RETURN_HOME    (0X02)
#define CGRAM_ADDRESS  (0x40)
#define DDRAM_ADDRESS  (0x80)
#define DIS_ON_CRS_ON_BLNK_ON    (0X0F)
#define DIS_ON_CRS_ON_BLNK_OF    (0X0E)
#define DIS_OF_CRS_OF_BLNK_OF    (0X08)


extern void LCD_init(void);
extern void LCD_command(char cmd);
extern void LCD_send_char(char byte);
extern void LCD_send_string(char *string);
extern void LCD_cursor_location(char row, char col);
extern void low_bit(char byte, char mode);
extern void high_bit(char byte, char mode);

#endif