.ORG	0x0
		JMP MAIN
.ORG	0x02
		JMP EX0_ISR


MAIN:	LDI R16,0xFF 
		OUT DDRB,R16		//set all portB as output
		LDI R16,0x30
		OUT PORTB,R16		//Set the initial value of port B

		LDI R16,0x00
		OUT DDRD,R16		//set all portD as input

		LDI R17,0x01		//enable external interrupt INT0
		STS 0x3D,R17		//0x3D is the address of EIMSK
		LDI R17,0x02		//it is beyond the range of the OUT instruction, so the STS instruction is used here
		STS 0x69,R17		//0x69 is the address of EICRA
		SEI					//enable the global interrupt


OFF:	LDI  R19,0x00
		OUT  PORTB,R19
		RJMP OFF			//Keep the full LED off until the interrupt

L1:		LDI  R19,0x01
		OUT  PORTB,R19		//light first LED
		RJMP DELAY			//entry delay

L2:		LDI  R19,0x02
		OUT  PORTB,R19
		RJMP DELAY	
	
L3:		LDI  R19,0x04
		OUT  PORTB,R19
		RJMP DELAY	


		
DELAY:  ldi  r20, 2
		ldi  r21, 158
		ldi  r22, 245
		ldi  r23, 241
COUNT:	dec  r23
		brne COUNT
		dec  r22
	    brne COUNT
		dec  r21
	    brne COUNT
		dec  r20
	    brne COUNT		//my delay time is 5100ms, quite a long time

		CPI	 R19,0x01
		BREQ L2			//jump back to light the seconed LED
		CPI	 R19,0x02
		BREQ L3
		CPI	 R19,0x04
		BREQ MAIN		//end, return to the begin



EX0_ISR:
		IN  R18,PIND
		CPI R18,0x04
		BREQ DEBOUNCE	//check whether the button is pressed

DEBOUNCE:   ldi  r24, 104
			ldi  r25, 229
BE_DELAY:	dec  r25
			brne BE_DELAY
			dec  r24
			brne BE_DELAY

		IN	 R18,PIND
		CPI	 R18,0x04
		BRNE L1			//Button debounce 