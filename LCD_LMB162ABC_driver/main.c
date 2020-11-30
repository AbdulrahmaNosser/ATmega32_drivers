#include <avr/io.h>
#include "LCD_LMB162ABC_driver.h"

int main(void)
{
	LCD_init();
	LCD_cursor_location(1, 3);
	LCD_send_char('a');
    while (1) 
    {
    }
}

