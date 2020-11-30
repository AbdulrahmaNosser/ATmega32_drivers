#include <avr/io.h>
#define F_CPU 8000000UL
#include <util/delay.h>

#include "LCD_LMB162ABC_driver.h"
#include "../services.h"

void LCD_init(void)
{
    LCD_DDR = 0xff;
    LCD_CTR_DDR |= ((1<<RS) | (1<<E));

    LCD_command(RETURN_HOME);
    LCD_command(FUNCTION_SET);
    LCD_command(CLEAR_DISPLAY);
    LCD_command(DIS_ON_CRS_ON_BLNK_ON);
}

void LCD_command(char cmd)
{
    CLR_BIT(LCD_CTR_REG, RS);
    SET_BIT(LCD_CTR_REG, E);
    _delay_ms(1);
    LCD_REG = cmd;
    CLR_BIT(LCD_CTR_REG, E);
    _delay_ms(1);
}

void LCD_send_char(char byte)
{
    SET_BIT(LCD_CTR_REG, RS);
    SET_BIT(LCD_CTR_REG, E);

    #if BIT_MODE == 8
        LCD_REG = byte;
    #elif BIT_MODE == 4
        LCD_REG = byte; 
    #endif
    CLR_BIT(LCD_CTR_REG, E);
    _delay_ms(1);
}

void LCD_send_string(char *string)
{
    unsigned char i = 0;
    while (string[i] != '\0')
    {
        LCD_send_char(string[i]);
        i++;
    }
}

extern void LCD_cursor_location(char row, char col)
{
    unsigned char address = 0;

    switch (row)
    {
    case 0: address = (col & 0x7f);break;
    case 1: address = (0x40 + (col & 0x7f));break;
    #if LINES_NUMBER == 4
    case 2: address = (0x10 + (col & 0x7f));break;
    case 3: address = (0x50 + (col & 0x7f));break;
    #endif
    }

    LCD_command(DDRAM_ADDRESS | address);
}