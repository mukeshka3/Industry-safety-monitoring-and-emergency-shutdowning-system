#define lcd 0xff<<16
#define rs 1<<24
#define e 1<<25


void delay(unsigned int s){
	T0PR=15000-1;
	T0TCR=0x1;
	while(T0TC<s);
	T0TCR=0x3;
	T0TCR=0;

}

void lcd_init(void);
void lcd_cmd(unsigned char);
void lcd_data(unsigned char);
void lcd_str(unsigned char*);
void lcd_integer(int);
void lcd_float(float);
void lcd_title(unsigned char*);

void lcd_init(void){
	IODIR1|=lcd|rs|e;
	lcd_cmd(0x01);
	lcd_cmd(0x02);
	lcd_cmd(0x0f);
	lcd_cmd(0x38);
}
void lcd_cmd(unsigned char cmd){
	IOCLR1=lcd;
	IOSET1=cmd<<16;
	IOCLR1=rs;
	IOSET1=e;
	delay(2);
	IOCLR1=e;
}
void lcd_data(unsigned char data){
	IOCLR1=lcd;
	IOSET1=data<<16;
	IOSET1=rs;
	IOSET1=e;
	delay(2);
	IOCLR1=e;

}
void lcd_integer(int n){
	signed char arr[5],i=0;
	if(n==0) lcd_data('0');
	if(n<0) lcd_data('-');
	while(n){
		arr[i++]=n%10;
		n/=10;
	}
	for(--i;i>=0;i--) lcd_data(arr[i]+'0');
}
void lcd_float(float f){
	int t=f;
	if(f<0) lcd_data('-');
	lcd_integer(t);
	lcd_data('.');
	t=(f-t)*100;
	lcd_integer(t);
}

void lcd_str(unsigned char* str){
	while(*str){
		lcd_data(*str);
		str++;
	}
}

void lcd_title(unsigned char* p){
	while(*p){
		lcd_cmd(0x80);
		lcd_str(p++);
	}
}
