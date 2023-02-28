#include "ascii.h"
#include "startup.h"
#include "delay.h"

void ascii_ctrl_bit_set(char x){
        char c;
        c = *GPIO_E_ODR_LOW;
        *GPIO_E_ODR_LOW = B_SELECT | x | c;
}

void ascii_ctrl_bit_clear(char x){
	char c;
	c = *GPIO_E_ODR_LOW;
	c = c & ~x;
	*GPIO_E_ODR_LOW = B_SELECT | c;
}


char  ascii_read_controller(){
        
        char c;
        ascii_ctrl_bit_set(B_E);

        delay_250ns();
        delay_250ns();


        c = *GPIO_E_IDR_HIGH;

        ascii_ctrl_bit_clear(B_E);
        
        return c;
    }
char  ascii_read_status(){
	*GPIO_E_MODER = 0x00005555;
        char c;

        // vilket kommando vil vi göra
      
        ascii_ctrl_bit_clear(B_RS);
		  ascii_ctrl_bit_set(B_RW);
        // kicka ingång det hela
        c = ascii_read_controller();
		*GPIO_E_MODER = 0x55555555;
        return c;
    }

char ascii_read_data(){
	char c;
	*GPIO_E_MODER = *GPIO_E_MODER & 0x00005555;
	ascii_ctrl_bit_set(B_RW);
    ascii_ctrl_bit_set(B_RS);
	c = ascii_read_controller();
	*GPIO_E_MODER = *GPIO_E_MODER & 0x55555555;
	return c;

}
    void ascii_write_controller(char command){
        char c;
        ascii_ctrl_bit_set(B_E);
        *GPIO_E_ODR_HIGH = command;
        delay_250ns();
        ascii_ctrl_bit_clear(B_E);
        delay_250ns();
        
        
    }
void ascii_write_cmd(char command){
	ascii_ctrl_bit_clear(B_RW);
	ascii_ctrl_bit_clear(B_RS);
	ascii_write_controller(command);
}
void ascii_write_data(char command){
		ascii_ctrl_bit_set(B_RS);
	ascii_ctrl_bit_clear(B_RW);

	ascii_write_controller(command);
}

void ascii_command(char command){
	while((ascii_read_status() & 0x80) == 0x80){
	}
	ascii_write_cmd(command);
	delay_mili(2);
}

void ascii_write_char(char command){
	while((ascii_read_status() & 0x80) == 0x80){
	}
	ascii_write_data(command);
	delay_mili(2);
}

void ascii_init(){
	// functions set
	ascii_command(0x38);
	//display init blinking cursor
	ascii_command(0xC);
	//clear display
	ascii_command(1);
	// entry mode left, no increment
	ascii_command(0x6);
}

void ascii_clear_screen(){
    ascii_command(1);
}

void ascii_gotoxy(int x, int y ){
	int adress = x-1;
	if(y == 2){
		adress = adress + 0x40;
	}
	ascii_write_cmd(0x80 | adress);

}

void ascii_write_text_at(char num, int x, int y){
	
	int moder_save = *GPIO_E_MODER;
	int otyper_save = *GPIO_E_OTYPER;
	int ospeedr_save = *GPIO_E_OSPEEDR;
	*GPIO_E_MODER = 0x55555555;
	*GPIO_E_OTYPER = 0x0;
    *GPIO_E_OSPEEDR = 0xffffffff;
	ascii_gotoxy(x,y);
	ascii_write_char(num);

	*GPIO_E_MODER = moder_save;
	*GPIO_E_OTYPER = otyper_save;
	*GPIO_E_OSPEEDR = ospeedr_save;
}