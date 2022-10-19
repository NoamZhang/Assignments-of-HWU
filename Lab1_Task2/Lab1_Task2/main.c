#include <avr/io.h> 
#include <avr/interrupt.h>

void Delay()
 {
	TCNT1 = 0x6769;
	TCCR1A = 0x00; 
	TCCR1B = 0x05; 
	while((TIFR1&(1<<TOV1))==0) 
	{}	
	TCCR1B = 0; 
	TIFR1 = (1<<TOV1); 
 } 
  
int main(void) 
{ 
	CLKPR = (1<<CLKPCE);	//Enable the system prescaler
	CLKPR = (1<<CLKPS0);	//Reduce the system frequency to 8MHz
	DDRB = 0xFF;
	DDRD = 0x00;
	EIMSK = (1<<INT0);
	sei();
	while(1);
} 


 ISR (INT0_vect)
 {
	   PORTB = 0x01;
	   Delay();
	   PORTB = 0x02;
	   Delay();
	   PORTB = 0x04;
	   Delay();
	   PORTB = 0x00;
 }