#pragma once
#include "ballandpaddle.h"
#include "debug.h"
#include "startup.h"
#include "delay.h"
#include "keyb.h"
#include "clock.h"
#include "ascii.h"
// #include "systick.h"
#include "math.h"'
#include "main.h"
int main();


void timer6_interrupt(){
	*TIM6_SR &= ~UIF;
	time.seconds++;
	if (time.seconds > 9){
		time.ten_seconds++;
		time.seconds = 0;
	}
	if (time.ten_seconds > 5){
		time.minutes++;
	}
	ascii_clear_screen();
	
	print_scores();
	ascii_gotoxy(10,1);
	ascii_write_char(48 + time.minutes);
	ascii_write_char(58);
	ascii_write_char(48 + time.ten_seconds);
	ascii_write_char(48 + time.seconds);
}

char points_player1 = 0;
char points_player2 = 0;
char winning_score = 5;
char* winner_name;
// char timer_flag = 0;

char collision(POBJECT object1, POBJECT object2){
	int deltax = abs(object1.posx - object2.posx);
	int deltay = abs(object1.posy - object2.posy);
	if(deltax<5 && deltay<9){
		return 1;
	}
	return 0;
}

void winning_routine(){

	char *s = "The epic winner is: ";
	ascii_clear_screen();
	graphic_clear_screen();
	ascii_gotoxy(1,1);
	while(*s != 0){
		ascii_write_char(*s);
		s++;
	}
	ascii_gotoxy(1,2);
	while(*winner_name != 0){
		ascii_write_char(*winner_name);
		winner_name++;
	}
	tim6_disable();
	delay_mili(500);

	ascii_clear_screen();
	// graphic_clear_screen();
	ascii_gotoxy(1,1);
	s = "Press any key to restart";
	while(*s != 0){
		ascii_write_char(*s);
		s++;
	}
	while(return_pressed_key() == 0xff);
	time.seconds = 0;
	time.ten_seconds = 0;
	time.minutes = 0;
	main();
}

void print_scores(){
	char * string_points_player1 = "P1: ";
	char * string_points_player2 = "P2: ";

	ascii_gotoxy(1,1);
	while (*string_points_player1 != 0) {
		ascii_write_char(*string_points_player1);
		string_points_player1++;
	}
	ascii_write_char(points_player1+0x30);

	ascii_gotoxy(1,2);
	while(*string_points_player2 != 0){
		ascii_write_char(*string_points_player2);
		string_points_player2++;
	}
	ascii_write_char(points_player2+0x30);

	// ascii_write_text_at(points_player1, 1, 1);
	// ascii_write_text_at(string_points_player2, 1, 7);
}

void app_init(){
	ascii_init();
	*GPIO_E_MODER = 0x55555555;
	*GPIO_E_OTYPER = 0x0;
    *GPIO_E_OSPEEDR = 0xffffffff;
	graphic_initialize();
	graphic_clear_screen();
}

void singleGame(POBJECT paddle1, POBJECT paddle2){
	unsigned char c = 0xff;
	POBJECT ball = create_ballobject(1,1);
	ball.set_speed(&ball, 4,1);
	// POBJECT paddle1 = create_paddleobject(100, 32);
	// POBJECT paddle2 = create_paddleobject(28, 32);
	print_scores();
	timer6_init();
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
			case 6: singleGame(paddle1, paddle2); break;
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
			print_scores();
			singleGame(paddle1, paddle2);
		}
		if(ball.posx <= 0){
			points_player2++;
			print_scores();
			singleGame(paddle1 ,paddle2);
		}
		if(time.seconds+time.ten_seconds*10 >= 10){
			if(points_player1 > points_player2){
				winner_name = "Player 1";
				winning_routine();
				break;
			}else if(points_player2 > points_player1){
				winner_name = "Player 2";
				winning_routine();
				break;
			}
		}
		// if(points_player1 == winning_score){
		// 	winner_name = "Player 1";
		// 	winning_routine();
		// 	break;
		// }else if(points_player2 == winning_score){
		// 	winner_name = "Player 2";
		// 	winning_routine();
		// 	break;
		// }
		// else if(get_timer_flag() == 1){
		// 	break;
		// }
		
	}		
}		






//main for singlepong
int main(void) {

	app_init();
	// benis:
	unsigned char c = 0xff;
	POBJECT ball = create_ballobject(1,1);
	ball.set_speed(&ball, 4,1);
	POBJECT paddle1 = create_paddleobject(100, 32);
	POBJECT paddle2 = create_paddleobject(28, 32);
	singleGame(paddle1, paddle2);	
	return 1;
}