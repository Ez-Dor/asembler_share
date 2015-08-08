									;file ps.as
.entry    LOOP
.entry LENGTH
.extern L3
.extern W
MAIN:	mov2 K, W
	add1 r2,STR
LOOP:	mov1 $$,r4
	jmp1 L3
	prn1 #-5
	sub1 $$, r1
	inc1 r0
	mov2 $$,r3
	bne1 L3
END:	stop1
STR:	.string "abcdef" 
LENGTH: .data 6,-9,15
K:	.data 2

