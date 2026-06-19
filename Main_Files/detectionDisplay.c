#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>  

#include "lcd.h"
#include "ultrasonic.h"

char string[20];
char contactString[20] = "No Contact";

int main (void) 
{
    unsigned char i;
    
    lcd_init();
    lcd_writecommand(0x01);     // Clear the screen
    sensor_init();
    _delay_ms(2);

    lcd_moveto(0, 0);
    float dislength = distance_inches();
    sprintf(string, "%.2f inches", dislength);
    for (i = 0; i < 16; i++)
    {
        lcd_writedata(string[i]);
    }
    _delay_ms(1000);
    lcd_writecommand(0x01);

    while (1)
    {
        lcd_moveto(0, 0);
        dislength = distance_inches(); 
        sprintf(string, "%.2f inches", dislength);
        for (i = 0; i < 16; i++)
        {
            lcd_writedata(string[i]);
        }
        _delay_ms(1000);
        lcd_writecommand(0x01);

        if (dislength < 12)
        {
            strcpy(contactString, "Caution Object");
            lcd_moveto(1, 0);
            for (i = 0; i < 16; i++)
            {
                if (contactString[i] == '\0')
                {
                    break;
                }
                lcd_writedata(contactString[i]);
            }
            lcd_moveto(0, 0);
        }
        else
        {
            strcpy(contactString, "No Contact");
            lcd_moveto(1, 0);
            for (i = 0; i < 16; i++)
            {
                if (contactString[i] == '\0')
                {
                    break;
                }
                lcd_writedata(contactString[i]);
            }
             lcd_moveto(0, 0);
        }
    }

    return 0;
}