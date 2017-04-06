start:
	ldi R16, 10
	ldi xh, $a60 //between 0a60H and 0a70H
	ldi xl, 00
	ldi yh, $a70
	ldi yl, 00

lus: 
    ld R17, X+
	ST Y+, R17
	dec R16
	brne lus



klaar:
	rjmp klaar