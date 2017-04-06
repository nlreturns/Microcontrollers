;
; Track6.asm
;
; Author : jawi
;


start:
    ; demoprogram 6_b: 16 bits setup with storage in datamemory
;
.INCLUDE "m128def.inc"
;
.CSEG
.ORG $0000
rjmp main
;
.CSEG
.ORG $0200
;
main:
; init datamemory
;
LDI YH, $04 ; Y <- $0400 address in datamemory 1 byte
LDI YL, $00 ; +1 = 2 byte
; LDI YH, HIGH(a) ;
; LDI YL, LOW(a) ;
LDD R8, Y+0 ; Get values from datamemory ++
LDD R9, Y+1 ; +1 = 4 byte
LDD R6, Y+2 ; +1 = 5 byte
LDD R7, Y+3 ; +1 = 6 byte
; 16 bits total = R5/R4 = R9/R8 + R7/R6 (23 ab + 44 98 = 68 43)
; Step 1: count the LSB's R4 = R6+R8
MOV R4, R8 ; R4 <- R8 +4 = 10 bytes
ADD R4, R6 ; R4 <- R4+R6
; Step 2: count MSB's with possible carryout LSB's
MOV R5, R9 ; R5 <- R9 +4 = 16 bytes
ADC R5, R7 ; R5 <- R5+R7+C +3 = 19 bytes
;
; Store result
;
STD Y+4,R4 ; 21 bytes
STD Y+5,R5 ; +2 23 bytes
no_end: ; unlimited loop, when done total 23 bytes
rjmp no_end
.DSEG
.ORG $0400
a: .BYTE 2
b: .BYTE 2
c: .BYTE 2