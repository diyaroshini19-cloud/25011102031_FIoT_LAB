#include <reg51.h>
sbit led0 = P1^1;
sbit led1 = P1^2;
sbit led2 = P1^3;
sbit led3 = P1^4;

sbit ROW1 = P2^3;
sbit col1 = P2^7;
int mode = 0;



void delay( ){
	int i,j;
	for ( i = 0; i <500; i++) {
		for ( j = 0; j < 500; j++){
     }
   }
 }

 void delay2( ){
	int i,j;
	for ( i = 0; i <10; i++) {
		for ( j = 0; j < 100; j++){
     }
   }
 }


 
  



int keypress(){
	ROW1= 0;

	if (col1 == 0){
		delay2();

		if (col1 == 0){
			
			return 1;
		
		}


	}

	return 0;


 }

 void counter(){
	int i,a;
	for (i = 0 ; i <= 15 ; i++){
		a = i;
		if (a%2){
			led0 = 1;
		} else {
			led0 = 0;
		}
		a = a / 2;

		if (a%2){
			led1 = 1;
		} else {
			led1 = 0;
		}
		a = a / 2;

		if (a%2){
			led2 = 1;
		} else {
			led2 = 0;
		}
		a = a / 2;

		if (a%2){
			led3 = 1;
		} else {
			led3 = 0;
		}
		a = a / 2;

		delay();


	}
 }

 void seq(){
	led0 = 1;
	delay();
	led0 = 0;
	led1 = 1;
	delay();
	led1 = 0;
	led2 = 1;
	delay();
	led2 = 0;
	led3 = 1;
	delay();
	led3 = 0;
	}

	void pattern1(){
		led0 = 1;
		led1 = 0;
		led2 = 1;
		led3 = 0;

		delay();

		led0 = 0;
		led1 = 1;
		led2 = 0;
		led3 = 1;

		delay();


	}

	void pattern2(){
		led0 = 1;
		led1 = 1;
		led2 = 1;
		led3 = 1;

		delay();

		led0 = 0;
		led1 = 0;
		led2 = 0;
		led3 = 0;

		delay();


	}

	void main(){
 while(1){
	if (keypress()){
		mode = (mode+1)%4;
	}

	switch(mode){

	case 0:
		seq();
		break;

	case 1:
	    counter();	
		break;
	
	case 2:
		pattern1();
		break;

	case 3:
	   pattern2();
	   break;



	
	}
}
	
 
 }
 