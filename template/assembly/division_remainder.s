	AREA	|.text|, CODE, READONLY
	EXPORT 	remainder		; r = a % b, a >= 0, b > 0; if b == 0, then r = -1
		; R0: a
		; R1: b

remainder		
					MOV R12, SP
					STMFD SP!, {R4-R8, R10, R11, LR}
					
check_div			CMP R1, #0
					MOVEQ R4, #-1			; r = -1 (undefined)
					UDIVNE R2, R0, R1		; c = a / b
					MULNE R2, R1, R2		; d = b * c
					SUBNE R3, R1, R2		; r = a - d
					
result				MOV R0, R3							; store result
					LDMFD SP!, {R4-R8, R10, R11, LR}
					
					BX LR
	
	END