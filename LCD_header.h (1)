
#define LCD 0xff<<2
#define RS 1<<10
#define E 1<<11

void delay(unsigned int ms){
	T0PR=15000-1;
	T0TCR=0x01;
	while(T0TC<ms);
	T0TCR=0x03;
	T0TCR=0;
}

void LCD_CMD(unsigned char cmd);
void LCD_DATA(unsigned char data);
void LCD_INIT(){
	IODIR0=LCD|RS|E;
	LCD_CMD(0x01);
	LCD_CMD(0x02);
	LCD_CMD(0x0c);
	LCD_CMD(0x38);
}

void LCD_CMD(unsigned char cmd){
	IOCLR0=LCD;
	IOSET0=cmd;
	IOCLR0=RS;
	IOSET0=E;
	delay(2);
	IOCLR0=E;
}
void LCD_DATA(unsigned char data){
	IOCLR0=LCD;
	IOSET0=data;
	IOSET0=RS;
	IOSET0=E;
	delay(2);
	IOCLR0=E;
}
void LCD_STR(unsigned char* s){
	while(*s) LCD_DATA(*s++);	
}
void lcd_title(char *s){
	while(*s){
		LCD_CMD(0x80);
		LCD_STR(s);
		s++;
	}
}
