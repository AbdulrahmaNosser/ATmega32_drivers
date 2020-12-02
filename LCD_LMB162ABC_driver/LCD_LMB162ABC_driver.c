#define F_CPU 8000000UL

#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>

#include "LCD_LMB162ABC_driver.h"
#include "../services.h"

void LCD_init(void)
{
    #if BIT_MODE == 8
        LCD_DDR = 0xFF;

    #elif BIT_MODE == 4
        #if NIBBLE_SELECT == 'L'
            LCD_DDR |= 0x0F;

        #elif NIBBLE_SELECT == 'H'
            LCD_DDR |= 0xF0;
        #endif
    #endif

    LCD_CTR_DDR |= ((1<<RS) | (1<<E));
    
    LCD_command(FUNCTION_SET);
    LCD_command(RETURN_HOME);
    LCD_command(CLEAR_DISPLAY);
    LCD_command(DIS_ON_CRS_ON_BLNK_ON);
}

void LCD_command(char cmd)
{
    #if BIT_MODE == 8
        CLR_BIT(LCD_CTR_REG, RS);
        SET_BIT(LCD_CTR_REG, E);
        _delay_ms(1);
        LCD_REG = cmd;
        CLR_BIT(LCD_CTR_REG, E);
        _delay_ms(1);

    #elif BIT_MODE == 4
        #if NIBBLE_SELECT == 'L'
            low_bit(cmd, 'I');

        #elif NIBBLE_SELECT == 'H'
            high_bit(cmd, 'I');
        #endif
    #endif
}

void LCD_send_char(char byte)
{
    #if BIT_MODE == 8
        SET_BIT(LCD_CTR_REG, RS);
        SET_BIT(LCD_CTR_REG, E);
        _delay_ms(1);
        LCD_REG = byte;
        CLR_BIT(LCD_CTR_REG, E);
        _delay_ms(1);

    #elif BIT_MODE == 4
        #if NIBBLE_SELECT == 'L'
            low_bit(byte, 'C');

        #elif NIBBLE_SELECT == 'H'
            high_bit(byte, 'C');

        #endif
    #endif
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

    #if LINES_NUMBER > 1
        case 1: address = (0x40 + (col & 0x7f));break;
    #endif

    #if LINES_NUMBER > 2
        case 2: address = (0x10 + (col & 0x7f));break;
    #endif

    #if LINES_NUMBER > 3
        case 3: address = (0x50 + (col & 0x7f));break;
    #endif
    }

    LCD_command(DDRAM_ADDRESS | address);
}

void low_bit(char byte, char mode)
{
    for (size_t i = 1; i >= 0; i--)
    {
        (mode == 'I') ? CLR_BIT(LCD_CTR_REG, RS):SET_BIT(LCD_CTR_REG, RS);

        SET_BIT(LCD_CTR_REG, E);
        _delay_ms(1);
        LCD_REG &= ~(0x0F);
        LCD_REG |= (byte >> (4 * i)) & (0x0F);
        CLR_BIT(LCD_CTR_REG, E);
        _delay_ms(1);
    }
}
void high_bit(char byte, char mode)
{
    for (size_t i = 0; i < 2; i++)
    {
        (mode == 'I') ? CLR_BIT(LCD_CTR_REG, RS):SET_BIT(LCD_CTR_REG, RS);

        SET_BIT(LCD_CTR_REG, E);
        _delay_ms(1);
        LCD_REG &= (0x0F);
        LCD_REG |= (byte << (4 * i)) & (0x0F0);
        CLR_BIT(LCD_CTR_REG, E);
        _delay_ms(1);
    }
}