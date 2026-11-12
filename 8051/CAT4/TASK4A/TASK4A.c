#include <reg51.h>

unsigned char key=255;
unsigned char led=0;
unsigned char alter=0;
int num=0;
int blink=0;
int row=1;

#ifdef __SDCC
__sbit __at (0xA0) a;
#else
sbit a = P2^0;
#endif
#ifdef __SDCC
__sbit __at (0xA1) b;
#else
sbit b = P2^1;
#endif
#ifdef __SDCC
__sbit __at (0xA2) c;
#else
sbit c = P2^2;
#endif
#ifdef __SDCC
__sbit __at (0xA3) d;
#else
sbit d = P2^3;
#endif
#ifdef __SDCC
__sbit __at (0xA4) e;
#else
sbit e = P2^4;
#endif
#ifdef __SDCC
__sbit __at (0xA5) f;
#else
sbit f = P2^5;
#endif
#ifdef __SDCC
__sbit __at (0xA6) g;
#else
sbit g = P2^6;
#endif
#ifdef __SDCC
__sbit __at (0xA7) h;
#else
sbit h = P2^7;
#endif

#ifdef __SDCC
__sbit __at (0x90) led1;
#else
sbit led1 = P1^0;
#endif
#ifdef __SDCC
__sbit __at (0x91) led2;
#else
sbit led2 = P1^1;
#endif
#ifdef __SDCC
__sbit __at (0x92) led3;
#else
sbit led3 = P1^2;
#endif
#ifdef __SDCC
__sbit __at (0x93) led4;
#else
sbit led4 = P1^3;
#endif

#ifdef __SDCC
__sbit __at (0x80) dis1;
#else
sbit dis1 = P0^0;
#endif
#ifdef __SDCC
__sbit __at (0x81) dis2;
#else
sbit dis2 = P0^1;
#endif
#ifdef __SDCC
__sbit __at (0x82) dis3;
#else
sbit dis3 = P0^2;
#endif
#ifdef __SDCC
__sbit __at (0x83) dis4;
#else
sbit dis4 = P0^3;
#endif
#ifdef __SDCC
__sbit __at (0x84) dis5;
#else
sbit dis5 = P0^4;
#endif
#ifdef __SDCC
__sbit __at (0x85) dis6;
#else
sbit dis6 = P0^5;
#endif
#ifdef __SDCC
__sbit __at (0x86) dis7;
#else
sbit dis7 = P0^6;
#endif
#ifdef __SDCC
__sbit __at (0x87) dis8;
#else
sbit dis8 = P0^7;
#endif


int i,j;
void delaysmall(){
    for(i=0;i<10;i++){
        for( j=0;j<512;j++){

        }
    }
}

int intr(){
    if(keypad_scan()){
        return 1;
    }
    return 0;
}

int delay(){
    for( i=0;i<10;i++){
        for( j=0;j<512;j++){
            if(intr()){
							num=0;
                return 1;
    }

        }
    }
    return 0;


}

int keypad_scan(void){

    if(row==1){
        h=0;
        if(h==b){
        delaysmall();
          if(h==b){
            key=3;
            return 1;
    }}

        else if(h==c){
        delaysmall();
            if(h==c){
               key=2;
               return 1;
    }}

        else if(h==d){
        delaysmall();
            if(h==d){
                key=1;
                return 1;

    }}
        else if(h==a){
           delaysmall();
           if(h==a){
              key=4;
              return 1;
    }}
        
    }
    
    else if(row==2){
        g=0;
        if(g==c){
           delaysmall();
           if(g==c){
              key=6;
              return 1;
    }}
        else if(g==d){
            delaysmall();
            if(g==d){
              key=5;
              return 1;
    }}
        else if(g==b){
            delaysmall();
            if(g==b){
              key=7;
              return 1;
    }}
        else if(g==a){
           delaysmall();
           if(g==a){
             key=8;
             return 1;
    }}}
    else if(row==3){
        f=0;
         if(f==d){
            delaysmall();
            if(f==d){
             key=9;
             return 1;
    }}
        else if(f==c){
           delaysmall();
           if(f==c){
             key=0;
             return 1;
    }}
}
    row++;
    if(row>3){
        row=1;
    }
    return 0;
    
    
}


void running_led(void){
        if(led==0){
            led1=1;
            led2=0;
            led3=0;
            led4=0;
            delay();
        }
        else if(led==1){
            led1=0;
            led2=1;
            led3=0;
            led4=0;
            delay();
        }
        else if(led==2){
            led1=0;
            led2=0;
            led3=1;
            led4=0;
            delay();
        }
        else if(led==3){
            led1=0;
            led2=0;
            led3=0;
            led4=1;
            delay();
        }
        led++;
        if(led>3){
            led=0;
        }

    }

void alternate_led(){
     if(alter==0){
        led1=1;
        led2=0;
        led3=1;
        led4=0;
        delay();
     }
      else if(alter==1){
        led1=0;
        led2=1;
        led3=0;
        led4=1;
        delay();
      }
      alter++;
      if(alter>1){
        alter=0;
      }
    
    }


void binary_counter(){
    int a=0;
    
        a=num;
        led1=a%2;
        a=a/2;
        led2=a%2;
        a=a/2;
        led3=a%2;
        a=a/2;
        led4=a%2;
        delay();
        num++;
        if(num>15){
            num=0;
        }

       
    }

void blink_all(){
    blink=0;
        if(blink==0){
        led1=1;
        led2=1;
        led3=1;
        led4=1;
        delay();
        }
        else{
            led1=0;
            led2=0;
            led3=0;
            led4=0;
            delay();
    }
        blink++;
        if(blink>1){
            blink=0;
        }

    }


void display_digit(unsigned char key){
    if(key==0){
        dis1=1;
        dis2=1;
        dis3=1;
        dis4=1;
        dis5=1;
        dis6=1;
        dis7=0;
        dis8=0;
    }
    else if(key==1){
        dis1=0;
        dis2=1;
        dis3=1;
        dis4=0;
        dis5=0;
        dis6=0;
        dis7=0;
        dis8=0;
    }
    else if(key==2){
        dis1=1;
        dis2=1;
        dis3=0;
        dis4=1;
        dis5=1;
        dis6=0;
        dis7=1;
        dis8=0;
    }
    else if(key==3){
        dis1=1;
        dis2=1;
        dis3=1;
        dis4=1;
        dis5=0;
        dis6=0;
        dis7=1;
        dis8=0;

    }
    else if(key==4){
        dis1=0;
        dis2=1;
        dis3=1;
        dis4=0;
        dis5=0;
        dis6=1;
        dis7=1;
        dis8=0;
    }
    else if(key==5){
        dis1=1;
        dis2=0;
        dis3=1;
        dis4=1;
        dis5=0;
        dis6=1;
        dis7=1;
        dis8=0;
    }
    else if(key==6){
        dis1=1;
        dis2=0;
        dis3=1;
        dis4=1;
        dis5=1;
        dis6=1;
        dis7=1;
        dis8=0;
    }
    else if(key==7){
        dis1=1;
        dis2=1;
        dis3=1;
        dis4=0;
        dis5=0;
        dis6=0;
        dis7=0;
        dis8=0;
    }
    else if(key==8){
        dis1=1;
        dis2=1;
        dis3=1;
        dis4=1;
        dis5=1;
        dis6=1;
        dis7=1;
        dis8=0;
    }
    else if(key==9){
        dis1=1;
        dis2=1;
        dis3=1;
        dis4=1;
        dis5=0;
        dis6=1;
        dis7=1;
        dis8=0;
    }
    else{
        dis1=0;
        dis2=0;
        dis3=0;
        dis4=0;
        dis5=0;
        dis6=0;
        dis7=0;
        dis8=0;

    }

}


void led_control(unsigned char key){
    led1=0;
    led2=0;
    led3=0;
    led4=0;
    if(key==1){
        led1=1;
        led2=0;
        led3=0; 
        led4=0;
        delay();
        
    }
    else if(key==2){
            led1=0;
            led2=1;
            led3=0;
            led4=0;
            delay();
        
        }
    
    else if(key==3){
            led1=0;
            led2=0;
            led3=1;
            led4=0;
            delay();

        }
    
    else if(key==4){
            led1=0;
            led2=0;
            led3=0;
            led4=1;
            delay();
  
    }
    else if(key==5){
        running_led();
    }
    else if(key==6){
        alternate_led();
    }
    else if(key==7){
        binary_counter();
    }
    else if(key==8){
        blink_all();
    }
    else if(key==9){
            led1=0;
            led2=0;
            led3=0;
            led4=0;
            delay();
    }
    else if(key==0){
        led=0;
        led1=0;
        led2=0;
        led3=0;
        led4=0;
    }
    }


void main(){
     while(1){
        h=1;
        g=1;
        f=1;
        keypad_scan();
        display_digit(key);
        led_control(key);
     }
}