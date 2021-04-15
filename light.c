#include <wiringPiI2C.h>
#include <wiringPi.h>
#include <stdlib.h>
#include <stdio.h>
#include <lcd.h>

const int RS = 3;   
const int EN = 14;  
const int D0 = 4;   
const int D1 = 12;  
const int D2 = 13;  
const int D3 = 6;

const char PCF8591 = 0x48; // adresa
enum pday{DNEVNO = "DNEVNO", SLABO = "SLABO", NOCNO = "NOCNO"};
int fd;
unsigned char input = 0;
unsigned char bright = 0;
int main()   
{  
	int lcd_h;
	pday time;
	
	if (wiringPiSetup () == -1) exit (1);
	
	lcd_h = lcdInit(2, 16, 4, RS, EN, D0, D1, D2, D3, D0, D1, D2, D3);
	  
	fd = wiringPiI2CSetup(PCF8591);  
	
	while (1)   { 
		input = wiringPiI2CReadReg8(fd, PCF8591 + 0);
		
		bright = (unsigned char)(((1.0) * input / 255 ) * 100); 
		lcdPosition(lcd_h, 0,0);
		lcdPrintf(lcd_h,"%d%",bright);
		lcdPosition(lcd_h, 0,1);
		if(bright < 20)
			time = DNEVNO;
		else if(bright > 80)
			time = NOCNO;
		else 
			time = SLABO;
		lcdPrintf(lcd_h, "%s",time); 
		
		delay(500);  
		lcdClear(lcd_h);
		}  
	return 0;
}
