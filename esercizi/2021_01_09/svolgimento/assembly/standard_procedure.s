	AREA	|.text|, CODE, READONLY
	EXPORT 	count_negative_and_odd
		; R0: array
		; R1: number of elements
		; R2: data
		; R3: data

count_negative_and_odd		
					MOV R12, SP
					STMFD SP!, {R4-R8, R10, R11, LR}
					
					MOV R4, #0	; count
					MOV R5, #0	; index
loop				CMP R5, R1
					BEQ result
					
					ADD R5, R5, #1
					
					LDR R6, [R0], #4
					TST R6, #1
					BEQ loop	; =1 if even
					
					CMP R6, #0
					BGE loop	; >= 0
					
					ADD R4, R4, #1	; increment result
					
					B loop
					
					
result				MOV R0, R4							; store result
					LDMFD SP!, {R4-R8, R10, R11, LR}
					
					BX LR
	
	END