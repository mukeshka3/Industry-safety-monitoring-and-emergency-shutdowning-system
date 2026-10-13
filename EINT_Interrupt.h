
#define l 1<<20
volatile unsigned int stop_request = 0;

void EINT0_ISR(void) __irq{
	EXTINT=0x1;
	 stop_request = 1;
	/*IODIR0|=l;
	lcd_cmd(0x01);
	lcd_cmd(0x80);
	lcd_str("MOTOR OFF");
	IOSET0= 1<<11;
	IOCLR0=1<<14;
	IOSET0=l;
	delay(1000);
	IOCLR0=l;*/
	VICVectAddr=0;
}
void EINT0_init(){
	 PINSEL1 =0x01;
	VICIntSelect=0;
	
	VICVectCntl0=(0x20)|14;
	VICVectAddr0=(unsigned long)EINT0_ISR;
	
	EXTMODE=0x1;
	EXTPOLAR=0;
	
	VICIntEnable=1<<14;
}
