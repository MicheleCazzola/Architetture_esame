	AREA	check_divisible, CODE, READONLY
	EXPORT 	divisible

divisible		
					MOV R12, SP
					STMFD SP!, {R4-R8, R10, R11, LR}
					
check_div			UDIV R2, R0, R1
					MUL R3, R2, R1
					SUB R4, R0, R3
					
result				MOV R0, R4							; store result
					LDMFD SP!, {R4-R8, R10, R11, LR}
					
					BX LR
	
	END