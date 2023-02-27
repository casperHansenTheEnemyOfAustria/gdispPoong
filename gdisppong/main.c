#pragma once
#include "ballandpaddle.h"
#include "debug.h"
#include "startup.h"
#include "delay.h"
#include "keyb.h"
#include "math.h"
#include "systick.h"

char points_player1 = 0;
char points_player2 = 0;
char winning_score = 5;
char timer_flag = 0;

char collision(POBJECT object1, POBJECT object2){
	int deltax = abs(object1.posx - object2.posx);
	int deltay = abs(object1.posy - object2.posy);
	if(deltax<5 && deltay<9){
		return 1;
	}
	return 0;
}


void app_init(){

	graphic_initialize();
	graphic_clear_screen();
}

void singleGame(){
	unsigned char c = 0xff;
	POBJECT ball = create_ballobject(1,1);
	ball.set_speed(&ball, 4,1);
	POBJECT paddle1 = create_paddleobject(100, 32);
	POBJECT paddle2 = create_paddleobject(28, 32);
	while(1){
		paddle1.move(&paddle1);
		paddle2.move(&paddle2);
		ball.move(&ball);
		c = return_pressed_key();
		switch(c){
			case 1: paddle2.set_speed(&paddle2, 0,-3); break;
			case 7: paddle2.set_speed(&paddle2,0,3);break;
			case 3: paddle1.set_speed(&paddle1, 0,-3); break;
			case 9: paddle1.set_speed(&paddle1,0,3);break;
			case 6: singleGame(); break;
			case 0xff: paddle1.set_speed(&paddle1, 0,0);break;
		}




		if(collision(paddle1, ball)){
				ball.dirx = -ball.dirx;
			}
		if(collision(paddle2, ball)){
				ball.dirx = -ball.dirx;
			}
		if(ball.posx >= 128){
			points_player1++;
			singleGame();
		}
		if(ball.posx <= 0){
			points_player2++;
			singleGame();
		}
		if(points_player1 == winning_score){
			break;
		}else if(points_player2 == winning_score){
			break;
		}else if(get_timer_flag() == 1){
			break;
		}
	}		
}		




//main for singlepong
void main(void) {

	app_init();
	unsigned char c = 0xff;
	POBJECT ball = create_ballobject(1,1);
	ball.set_speed(&ball, 4,1);
	POBJECT paddle1 = create_paddleobject(100, 32);
	singleGame();	
}