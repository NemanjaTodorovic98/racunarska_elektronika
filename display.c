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

double read_temp(void)
{
	unsigned char i = 0;
	FILE *ft;
	char text[100];
	ft = fopen("/sys/bus/w1/devices/28-00000cfbb0e4/w1_slave","r");
	if(ft==NULL) return 0;
	
	for(i=0;i<22;i++) fscanf(ft,"%s", text);
	fclose(ft);
	
	for(i=0;i<10;i++) text[i]=text[i+2]; 
	int temp = atoi(text);  
	double tem = (double)temp/1000;
	return tem;
};
 

int main(void){

	int lcd_h;
	if (wiringPiSetup() < 0){     
		fprintf (stderr, "Greška pri inicijalizaciji: %s\n",strerror(errno));
	return 1;
	}
	lcd_h = lcdInit(2, 16, 4, RS, EN, D0, D1, D2, D3, D0, D1, D2, D3);
	while(1){
		lcdPosition(lcd_h, 0,0);
		lcdPrintf(lcd_h,"%.2ld 'C",read_temp());
		delay(2000);
		lcdClear(lcd_h);
	}
	return 0;
}
