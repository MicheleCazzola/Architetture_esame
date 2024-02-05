	AREA	|.text|, CODE, READONLY
	EXPORT 	duty_cycle
		; R0: initial value
		; R1: tot time
		; R2: var times
		; R3: num vars

duty_cycle		
					MOV R12, SP
					STMFD SP!, {R4-R8, R10, R11, LR}
					
					MOV R4, R0	; prev value
					MOV R5, #0	; index
					MOV R11, #0	; 1-state time
loop				CMP R5, R3
					BEQ result
					
					LDR R6, [R2], #4	; current var time
					TST R4, #1
					MOVEQ R8, R6	; start of 1-state
					MOVEQ R4, #1	; prev value high
					MOVNE R10, R6	; end of 1-state
					MOVNE R4, #0	; prev value low
					
					ADDNE R11, R11, R10
					SUBNE R11, R11, R8	; cumulate duty cycle
					
					ADD R5, R5, #1
					B loop
				
result				TST R4, #1
					ADDNE R11, R11, R2
					SUBNE R11, R11, R8	; cumulate duty cycle if final state is 1
					
					MOV R4, #100
					MUL R0, R11, R4
					UDIV R0, R0, R1							; store result
					LDMFD SP!, {R4-R8, R10, R11, LR}
					
					BX LR
	
	END