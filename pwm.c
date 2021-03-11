#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*#include <wiringPi.h>
#include <softPwm.h>*/

#define PWM_MAX 100
#define PWM_MIN 0
#define LED_first 25
#define ASCII_ZERO 48

int main (int argc, char **argv)
{
	if(argc == 2 && strlen(argv[1]) == 4)
	{
		unsigned char duty_cycle = 0;
		unsigned char desired_dc = 0;
		unsigned char led = 0;
		unsigned char desired_led = 0;
		unsigned char i = 0;
		char* arg = argv[1];
		char input_string[10];
		desired_led = arg[3] - ASCII_ZERO;
		arg[3] = '\0';
		if( strcmp(arg, "LED") == 0 && ( desired_led >= 0 || desired_led <= 3 ))
		{
			//wiringPiSetup();
			led = desired_led + LED_first;
			//if(softPwmCreate(led, PWM_MIN, PWM_MAX) != 0) printf("Error occured!\n");
			while(1){
				printf("Duty cycle: %d . Add value to current duty cycle: ", duty_cycle);
				scanf("%s", input_string);
				if(*input_string == 'q') break;
				while( *(input_string + i) != '\0' ){
					if(input_string[i] == '%') {
						input_string[i] = '\0';
						break;
					}
					i++;
				}
				i = 0;
				desired_dc = (unsigned char) atoi( (input_string + 1) );
				if(input_string[0] == '+')
				{
					if(desired_dc + duty_cycle > PWM_MAX)
						printf("Desired value exceeds PWM_MAX limit\n");
					else
						duty_cycle += desired_dc;
				}	
				else if(input_string[0] == '-')
				{
					if(duty_cycle - desired_dc < PWM_MIN)
						printf("Desired value is under PWM_MIN limit\n");
					else
						duty_cycle -= desired_dc;
				}
				//softPwmWrite(led, duty_cycle);
				printf("Use 'q' for exit\n");
				
			}
		}
		else
			printf("Wrong function call, use ./pwm LED<led_id> ( <led_id> is number 0 - 3 )\n");
	}
	else
		printf("Invalid function call, use ./pwm LED<led_id> ( <led_id> is number 0 - 3 )\n");
	return 0;
}

