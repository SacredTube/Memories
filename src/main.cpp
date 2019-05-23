/*----------------------------------------------------------------------------
LAB EXERCISE - Analog input and PWM
 ----------------------------------------
	Use two potentiometers to adjust the volume and pitch of the output sound wave.

	Inputs: potentiometers 1 and 2
	Output: speaker, PC

	GOOD LUCK!
 *----------------------------------------------------------------------------*/

#include "mbed.h"
#include "pindef.h"
#include <vector>
#include <cstdlib>
/*
*/
//buttons
DigitalIn button1(PA_9);
DigitalIn	button2(PA_8);
DigitalIn button3(PB_10);
DigitalIn button4(PB_4);

//leds
DigitalOut redLed(PB_5);
DigitalOut greenLed(PB_3);
DigitalOut blueLed(PA_10);

//speaker
PwmOut speaker(PC_7);

//diagnostic
Serial computer(UART_TX, UART_RX);

 unsigned int rand_seed_global = 0;

/*----------------------------------------------------------------------------
 MAIN function
 *----------------------------------------------------------------------------*/
void start();
void increment_sequence(vector<int> &sequence);
void display_sequence(vector<int> &sequence);
bool user_turn(vector<int> sequence);
void toggle_led(int led);

int main(){
	computer.baud(9600);
	
	while(1){
	if(!button4)
	{
		while(button4)
		{
			wait(.25);
		}
		start();
	}
	wait(.1);
	rand_seed_global++;
	}
}

void start()
{
	srand(rand_seed_global);
	//TODO
	vector<int> sequence;
	while(1)
	{
	  increment_sequence(sequence);
		display_sequence(sequence);
		computer.printf("Current Sequence: ");
		for(int i = 0; i < sequence.size(); i++)
		{
			if(sequence[i] == 0)
				computer.printf("Red ");
			else if(sequence[i] == 1)
				computer.printf("Blue ");
			else
				computer.printf("Green ");
		}
		computer.printf("\n\r");
		wait(.5);
		if(!user_turn(sequence))
		{
			computer.printf("Error\n\r Final sequence length: %i \n\r", sequence.size()-1);
			toggle_led(3);
			break;
		}
	}
}

void increment_sequence(vector<int> &sequence)
{
	sequence.push_back(rand() % 3);
	//TODO
	
}

void display_sequence(vector<int> &sequence)
{
	for(int i = 0; i < sequence.size(); i++)
	{
		switch(sequence[i])
		{
			case 0:
				//toggle red led
			toggle_led(sequence[i]);
				//play 'red' sound
				break;
			case 1:
				//toggle green led
			toggle_led(sequence[i]);
				//play 'blue' sound
				break; 
			case 2:
				//toggle blue led
			toggle_led(sequence[i]);
				//play 'green' sound
				break;
			default:
				//do nothing i guess
				break;
		}
		wait(.25);
	}
	//TODO
}

bool user_turn(vector<int> sequence)
{
	bool pressed[3];
	for(int i = 0; i < 3; i++)
	{
		pressed[i] = 0;
	}
	//TODO
	for(int i = 0; i < sequence.size(); i++)
	{
		while(button1 && button2 && button3 && button4)
		{
		}
		if(!button4)
		{
			return false;
		}
		for(int i = 0; i < 3; i++)
		{
			pressed[i] = false;
		}
		while(!button1 || !button2 || !button3)
		{
			if(!button1)
				pressed[0] = true;
			if(!button2)
				pressed[1] = true;
			if(!button3)
				pressed[2] = true;
			wait(.01);
		}
		if(pressed[0])
			computer.printf("user pushed Red Button ");
		if(pressed[1])
			computer.printf("user pushed Blue Button ");
		if(pressed[2])
			computer.printf("user pushed Green Button ");
		computer.printf("\n\r");
		if((pressed[0] && pressed[1]) || (pressed[0] && pressed[2]) || (pressed[1] && pressed[2]))
		{
			return false;
		}
		
		if(pressed[0])
		{
			toggle_led(0);
		}
		if(pressed[1])
		{
			toggle_led(1);
		}
		if(pressed[2])
		{
			toggle_led(2);
		}
		
		
		else
		{
			if(sequence[i] == 0 && pressed[0])
			{
				continue;
			}
			else if(sequence[i] == 1 && pressed[1])
			{
				continue;
			}
			else if(sequence[i] == 2 && pressed[2])
			{
				continue;
			}
			return false;
		}
		while(!button1 || !button2 || !button3)
		{
			wait(.20);
		}
		
	}
			wait(.25);
			return true;
}

void toggle_led(int led)
{
	switch(led)
	{
		case 0:
			redLed = 1;
			speaker.period(.02);
			speaker = 0.5;
			wait(1);
			speaker = 0.0;
			redLed = 0;
			break;
		case 1:
			greenLed = 1;
			speaker.period(.001);
			speaker = 0.5;
			wait(1);
			speaker = 0.0;
			greenLed = 0;
			break;
		case 2:
			blueLed = 1;
			speaker.period(.005);
			speaker = 0.5;
			wait(1);
			speaker = 0.0;
			blueLed = 0;
			break;
		default:
			redLed = 1;
			blueLed = 1;
			greenLed = 1;
			speaker.period(.01);
			speaker = 0.5;
			wait(1);
			speaker = 0.0;
			redLed = 0;
			blueLed = 0;
			greenLed = 0;
			break;
	}
}

// *******************************ARM University Program Copyright © ARM Ltd 2016*************************************
