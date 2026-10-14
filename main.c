#include<lpc21xx.h>
#include"LCD_header.h"
#include"ir_sensor.h"
#include"UART.h"

#define MOTORON 1<<27
#define MOTOROFF 1<<28
#define LED 1<<25

volatile unsigned int stop=0;
	  
void EINT0_SW1_ISR(void) __irq;
void EINT0_init(void);
int main(){
	   unsigned int ls=2,s;
	   IODIR1|=LED|MOTORON|MOTOROFF;
	   IOCLR1|=MOTOROFF;
	   LCD_INIT();
	   uart_init();
	   EINT0_init();
	   uart_str_tx("Industry Safety Monitoring and emergency shutdown sytem");
	   //lcd_title("Industry Safety Monitoring and"); 
	   //lcd_title("emergency shutdown sytem");
	   while(1){
	  	 if(stop){
			 	 stop=0;
		 		 IOCLR1|=MOTORON;
				 uart_str_tx(" MOTOR OFF");
				 IOCLR1|=LED;
				 ls=2;
				 LCD_CMD(0X01);
				 LCD_CMD(0Xc0);
				 LCD_STR("MOTOR OFF");
				 delay(3000);
		 }
		 else{
		 		s=ir_sense();
				if(s!=ls){
					LCD_CMD(0X01);
				    LCD_CMD(0Xc0);
					if(s){
					  IOCLR1|=MOTORON;
					  uart_str_tx(" MOTOR OFF");
					  LCD_STR("MOTOR OFF");
					  IOCLR1|=LED;
					}
				
					else{
						IOSET1|=MOTORON;
						uart_str_tx(" MOTOR ON");
				 		LCD_STR("MOTOR ON");
				 		IOSET1|=LED;
					}
					ls=s;
				}
		 }
}
	   	/*	LCD_CMD(0X01);
			LCD_CMD(0X80);
	   		if(ir_sense()){
				 IOCLR0|=MOTORON;
				 LCD_STR("MOTOR OFF");
				 IOSET0|=LED;
			}
			else{
				 IOSET0|=MOTORON;
				 LCD_STR("MOTOR ON");
				 IOCLR0|=LED;
			}
	   }*/
}
void EINT0_init(){
	  PINSEL1|=0x01;//EINT0 P0.16

	  VICIntSelect=0;
	  VICVectAddr0=(unsigned long)EINT0_SW1_ISR;
	  VICVectCntl0=(0x20)|14;

	  EXTMODE=0x01;//edge trigger mode
	  EXTPOLAR=0;///falling edge	
	  								  
	  VICIntEnable=1<<14;
}
void EINT0_SW1_ISR(void) __irq{
	EXTINT=0x01;
	/*IOCLR0=MOTORON;
	LCD_CMD(0X01);
	LCD_CMD(0X80);
	LCD_STR("MOTOR OFF"); */
	stop=1;
	VICVectAddr=0;
}
