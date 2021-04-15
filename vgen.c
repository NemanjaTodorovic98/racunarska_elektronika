#include <wiringPiI2C.h>
#include <wiringPi.h>
#include <stdlib.h>
#include <stdio.h>

const char PCF8591 = 0x48; // adresa
int fd;
unsigned char output = 0;
int main()   
{  
	if (wiringPiSetup () == -1) exit (1);
	  
	fd = wiringPiI2CSetup(PCF8591);  
	
	while (1)   { 
		output += 20;   
		wiringPiI2CWriteReg8 (fd, PCF8591 + 4, output) ;    
		delay(300);  
		}  
	return 0;
}
