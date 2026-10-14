void tx(unsigned char);
//void rx(unsigned char);
void uartstr_tx(unsigned char *);
void uart_init(){
	PINSEL0|=0x5;
	U0LCR=0x83;
	U0DLL=97;
	U0DLM=0;
	U0LCR=0x03;
}
void tx(unsigned char ch){
	while(((U0LSR>>5)&1)==0);
	U0THR=ch;
}
void uart_str_tx(unsigned char *s){
	while(*s){
		tx(*s++);
	}
}
 