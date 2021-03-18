#include <stdio.h>
#include <strdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/fcntl.h>
#include <wiringPi.h>

#define LED_ID 25
#define tth 28
// cfbb0e4

double read(void)
{
	unsigned char i = 0;
	FILE *ft;
	char text[100];
	ft = fopen("/sys/bus/w1/devices/28-00000cfbb0e4/w1_slave","r");
	if(ft==NULL) return 0;
	
	for(i=0;i<22;i++) fscanf(ft,"%s", text);
	fclose(ft);
	
	for(i=0;i<10;i++) text[i]=text[i+2]; 
	int temp = atoi(tekst);  
	double tem = (double)temp/1000;
	return tem;
};

int main(void)
{
	wiringPiSetup();
	pinMode(LED_ID, OUTPUT);
	 double temperature;
	 while(1)
	 {
	 	if( read() >= tth )
	 	{
	 		digitalWrite(LED_ID, HIGH);
	 		delay(500);
	 		digitalWrite(LED_ID, LOW);
	 		delay(500);
	 	}
 	}
 }
	 	
	 
	 
