#include <stdio.h>
#include <string.h> 
#include <errno.h>
#include <wiringPi.h>
#include <lcd.h>

const int RS = 3;   
const int EN = 14;  
const int D0 = 4;   
const int D1 = 12;  
const int D2 = 13;  
const int D3 = 6;  

const char character0[8] = {0b00000, 0b11111, 0b10001, 0b10001, 0b10001, 0b10001, 0b10001, 0b00000};
const char character1[8] = {0b00000, 0b11111, 0b00100, 0b00100, 0b00111, 0b00101, 0b00101, 0b00000};
const char character2[8] = {0b00000, 0b10001, 0b10001, 0b10001, 0b11111, 0b00001, 0b00001, 0b00000};


int main(void){

	int lcd_h;
	if (wiringPiSetup() < 0){     
		fprintf (stderr, "Greška pri inicijalizaciji: %s\n",strerror(errno));
	return 1;
	}
	lcd_h = lcdInit(2, 16, 4, RS, EN, D0, D1, D2, D3, D0, D1, D2, D3);
	
	lcdCharDef(lcd, 0, character0);        
	lcdCharDef(lcd, 1, character1);        
	lcdCharDef(lcd, 2, character2);
	
	for(unsigned char i = 0; i < 3; i++){                
		lcdPosition(lcd, i, 0);                
		lcdPutchar(lcd, i);                
		usleep(400000);        
	}
	return 0;
}
