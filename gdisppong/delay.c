#include "delay.h"

void delay_mili(unsigned int ms){
    for (int i = 0; i< ms; i++){
        delay_250ns();
        delay_250ns();
        delay_250ns();
        delay_250ns();
    }
}


void delay_250ns(){
	delay_125ns();
    delay_125ns();
}

void delay_125ns(){
    *STK_CTRL = 0;
	*STK_LOAD = (168/8 );
	*STK_VAL = 0;
	*STK_CTRL = 5;
	while( (*STK_CTRL & 0x10000 )== 0 );
	*STK_CTRL = 0;
}

