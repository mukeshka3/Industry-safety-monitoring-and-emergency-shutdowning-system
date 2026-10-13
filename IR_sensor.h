#define I2_SENSOR 1<<13;

int ir_sense(){
	if(((IOPIN0>>13)&1)==1) return 1;
	return 0;
	
}
