/// main.c
//this is a repo for the ascii conversion. Use the md407 sim for best results. 
//Alsooooo i recomment installing the "power moe" extension fro better coding 
#include "keyb.h"
#include "startup.h"





void activateRow(int row){

    switch (row) {
        case 1: *GPIO_E_ODR_HIGH= 0x10; break;
        case 2: *GPIO_E_ODR_HIGH = 0x20; break;
        case 3: *GPIO_E_ODR_HIGH= 0x40; break;
        case 4: *GPIO_E_ODR_HIGH = 0x80; break;
        default: *GPIO_E_ODR_HIGH = 0; break;

 }
}

int  readColumn(void){

	*GPIO_E_MODER = 0x55005555;
    char c =  *GPIO_E_IDR_HIGH;
    if(c & 8){
        return 4;
    }
    if(c & 4){
        return 3;
    }
    if(c & 2){
        return 2;
    }
    if(c & 1){
        return 1;
    }
    return 0;
}

void initKeyb(void){
        //init init pupd 
       
        *GPIO_E_PUPDR = 0x00AA0000;
        // sets otr
       
        *GPIO_E_OTYPER = 0x0;
        
        *GPIO_E_OSPEEDR = 0xffffffff;

            //starts clocks for debug board
    *((unsigned long *) 0x40023830) = 0x18;
    
	*GPIO_E_MODER = 0x55005555;
}
unsigned char returnPressedKey(void)
{

    int temp = *GPIO_E_MODER;

    initKeyb();
    char key[] = 
    {1,2,3,0xa,4,5,6,0xb,7,8,9,0xc,0xe,0,0xf,0xd};
    int column;
    for (int row = 1 ; row <= 4; row++){
        activateRow(row);
        column = readColumn();
        if (column != 0){
            activateRow(600000000);
            return key [4*(row-1)+(column-1)];
        }
    }

    *GPIO_E_MODER = temp;
    return  0xFF; 
}




void out7seg( unsigned char c){
    // siiIIick table for convertiong to 7 segment codes
    char outputTable[] = {
    0x3F, 
	0x06, 
	0x5B, 
	0x4F, 
	0x66, 
	0x6D, 
	0x7D, 
	0x07, 
	0x7F, 
	0x6F, 
    0x77, 
	0x7C, 
	0x39, 
    0x5E, 
    0x7E, 
    0x21};
 if(c < 15){
    *GPIO_E_ODR_LOW = outputTable[c];
 }
 else{ 
    *GPIO_E_ODR_LOW = 0;
 }
}




    //  0x3F, /* 0 */
	// 0x06, /* 1 */
	// 0x5B, /* 2 */
	// 0x4F, /* 3 */
	// 0x66, /* 4 */
	// 0x6D, /* 5 */
	// 0x7D, /* 6 */
	// 0x07, /* 7 */
	// 0x7F, /* 8 */
	// 0x6F, /* 9 */
    // 0x77, /* A */
	// 0x7C, /* B */
	// 0x39, /* C */
    // 0x5E, /* D */
    // 0x7E, /* # */
    // 0x21, /* * */

