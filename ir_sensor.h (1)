
#define ir_sensor 1<<26
int ir_sense(){
	//IODIR0|=1<<1;

		if((IOPIN1 & ir_sensor)==0){
			//IOSET0=1<<1;
			return 1;
		}
		else{
		//	IOCLR0=1<<1;
			return 0;
		}			  
	
}
