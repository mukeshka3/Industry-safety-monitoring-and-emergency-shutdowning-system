#include <lpc21xx.h>
#include "IR_sensor.h"
#include "lcd_interface_numeric.h"
#include "EINT_Interrupt.h"

#define MOTOR 1<< 11
#define LED   1<< 14

int main()
{
    unsigned int last_state = 2;
    unsigned int state;

    IODIR0 |= MOTOR | LED;

    lcd_init();
    EINT0_init();

    lcd_cmd(0x80);
    lcd_title("Industrial safety monitoring and emergency shutdown system");

    while (1)
    {
        if (stop_request)
        {
            stop_request = 0;

            IOSET0 = MOTOR;   // Motor OFF
            IOCLR0 = LED;     // LED ON
				//IOSET0= 1<<11;
				//IOCLR0=1<<14;
            lcd_cmd(0x01);
            lcd_cmd(0x80);
            lcd_str("MOTOR STOP");
            delay(1000);    
            last_state = 2;   
        }
        else
        {
            state = ir_sense();
            if (state != last_state)
            {
                lcd_cmd(0x01);
                lcd_cmd(0x80);

                if (state)
                {
						  lcd_str("MOTOR OFF");
                    IOSET0 = MOTOR;
                    IOCLR0 = LED;
                }
                else
                {
						  lcd_str("MOTOR ON");
                    IOCLR0 = MOTOR;
                    IOSET0 = LED;
                }

                last_state = state;
            }
        }
    }
}