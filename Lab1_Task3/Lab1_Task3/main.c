#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdlib.h>
#define F_CPU 16000000UL
#include "util/delay.h"

void Delay()
{
	TCNT1= 0x124F;
	TCCR1A = 0x00;
	TCCR1B = 0x05;
	while((TIFR1&(1<<TOV1))==0)
	{}
	TCCR1B = 0;
	TIFR1 = (1<<TOV1);	//Timer1 for three second delay
}

int main(void)
{
	DDRB = 0xFF;
	DDRD = 0x00;
	EIMSK = (1<<INT0);
	sei();
	while(1);
}


void light_1()
{
	PORTB = 0x02;
}

void light_2()
{
	PORTB = 0x01;	//There are two LEDs connected to the corresponding ports
}

void light_3()
{
	PORTB = 0x03;
}

void light_4()
{
	PORTB = 0x0B;
}

void light_5()
{
	PORTB = 0x0D;	//Similarly, two LEDs are connected to the corresponding ports
}

void light_6()
{
	PORTB = 0x0F;
}

void light_OFF()
{
	PORTB = 0x00;
}

void shuffle()
{
	light_1();
	_delay_ms(100);
	light_OFF();
	_delay_ms(100);
	light_2();
	_delay_ms(100);
	light_OFF();
	_delay_ms(100);
	light_3();
	_delay_ms(100);
	light_OFF();
	_delay_ms(100);
	light_4();
	_delay_ms(100);
	light_OFF();
	_delay_ms(100);
	light_5();
	_delay_ms(100);
	light_OFF();
	_delay_ms(100);
	light_6();
	_delay_ms(100);	
	light_OFF();
	_delay_ms(100);		//Illumination in sequence				
}

ISR (INT0_vect)
{
	shuffle();
	int dice_number = rand() % 6 + 1;
	switch(dice_number)
	{
		case 1:light_1();break;
		case 2:light_2();break;
		case 3:light_3();break;
		case 4:light_4();break;
		case 5:light_5();break;
		case 6:light_6();break;
	}
	Delay();
	light_OFF();
}
