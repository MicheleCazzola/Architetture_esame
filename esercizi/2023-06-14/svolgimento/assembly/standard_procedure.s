	AREA	|.text|, CODE, READONLY
	EXPORT 	DIFF_MAX_MIN
		; R0: vector
		; R1: last pos used

DIFF_MAX_MIN		
					MOV R12, SP
					STMFD SP!, {R4-R8, R10, R11, LR}
					
					STMFD SP!, {R0-R3}
					
					IMPORT sort_integers
					
					ADD R1, R1, #1
					BL sort_integers
					
					LDMFD SP!, {R0-R3}
					
					LDR R2, [R0]
					LDR R3, [R0, R1, LSL #2]
					
					
result				SUB R0, R2, R3							; store result
					LDMFD SP!, {R4-R8, R10, R11, LR}
					
					BX LR
	
	END