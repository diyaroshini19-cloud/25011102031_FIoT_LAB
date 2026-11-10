#include <reg51.h>

void main() {
	char received;
	PCON=0;
	SM0=0;
	SM1=1;
	REN=1;
	TH1=0xFD;
	TMOD=0x20;
	TR1=1;
	
	while(1) {
		while(RI==0);
		received=SBUF;
		RI=0;
		SBUF=received;
		while(TI==0);
		TI=0;
	}
}