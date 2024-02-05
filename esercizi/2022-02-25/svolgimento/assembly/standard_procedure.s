	AREA	|.text|, CODE, READONLY
	EXPORT 	traduzione_morse
		; R0: input vector
		; R1: output_vector

traduzione_morse		
					MOV R12, SP
					STMFD SP!, {R4-R8, R10, R11, LR}
					
					MOV R2, #0	;index
					MOV R3, #0	;decoded
					MOV R4, #4	; end
					LDREQ R7, =START1	; root
					
loop				LDRB R5, [R0], #1
					CMP R5, R4		; check end message
					
					LDREQ R6, [R7]			; store last symbol
					STRBEQ R6, [R1], #1
					ADDEQ R3, R3, #1
					
					LDREQ R6, =END_STRING	; store end of string
					LDRBEQ R6, [R6]
					STRBEQ R6, [R1], #1
					BEQ result
					
					CMP R5, #3		; check space
					LDREQ R6, [R7]
					STRBEQ R6, [R1], #1	; store symbol
					
					LDREQ R6, =SPAZIO
					LDRBEQ R6, [R6]
					STRBEQ R6, [R1], #1	; store space
					ADDEQ R3, R3, #2	
					LDREQ R7, =START1	; return to root
					
					CMP R5, #2	; check end of symbol
					LDREQ R6, [R7]
					STRBEQ R6, [R1], #1
					LDREQ R7, =START1	; return to root
					ADDEQ R3, R3, #1
					
					CMP R5, #0
					LDREQ R7, [R7, #4]	; if 0, down left
					CMP R5, #1
					LDREQ R7, [R7, #8]	; if 1, down right
					
					ADD R2, R2, #1
					B loop
					
result				MOV R0, R3							; store result
					LDMFD SP!, {R4-R8, R10, R11, LR}
					
					BX LR
	LTORG
		
START1		DCD 0,	E, T
A			DCD 65,	R, W
BB			DCD 66,	N6, DEFAULT
C			DCD 67,	DEFAULT, DEFAULT
D			DCD 68, BB, X
E			DCD 69, I, A
F			DCD 70,	DEFAULT, DEFAULT
G			DCD 71, Z, Q
H			DCD 72,	N5, N4
I			DCD 73, S, U
J			DCD 74, DEFAULT, N1
K			DCD 75, C, Y
L			DCD 76, DEFAULT , DEFAULT
M			DCD 77, G, O
N			DCD 78, D, K
O			DCD 79, OL, OR
OL			DCD 0,	N8, DEFAULT
OR			DCD 0, 	N9, N0
P			DCD 80, DEFAULT, DEFAULT
Q			DCD 81, DEFAULT, DEFAULT
R			DCD 82, L, DEFAULT
S			DCD 83, H, V
T			DCD 84, N, M
U			DCD 85, F, UR
UR			DCD 0, 	DEFAULT, N2
V			DCD 86, DEFAULT, N3
W			DCD 87, P, J
X			DCD 88, DEFAULT, DEFAULT
Y			DCD 89, DEFAULT, DEFAULT
Z			DCD 90, N7, DEFAULT
N0			DCD 48, DEFAULT, DEFAULT
N1			DCD 49, DEFAULT, DEFAULT
N2			DCD 50, DEFAULT, DEFAULT
N3			DCD 51, DEFAULT, DEFAULT
N4			DCD 52, DEFAULT, DEFAULT
N5			DCD 53, DEFAULT, DEFAULT
N6			DCD 54, DEFAULT, DEFAULT
N7			DCD 55, DEFAULT, DEFAULT
N8			DCD 56, DEFAULT, DEFAULT
N9			DCD 57, DEFAULT, DEFAULT
DEFAULT		DCD -1
SPAZIO		DCB ' '
END_STRING  DCB '\0'

	END