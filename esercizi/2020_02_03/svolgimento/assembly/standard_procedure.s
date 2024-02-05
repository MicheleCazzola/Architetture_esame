	AREA	|.text|, CODE, READONLY
	EXPORT 	proc_name
		; R0: data/result
		; R1: data/result
		; R2: data
		; R3: data

proc_name		
					MOV R12, SP
					STMFD SP!, {R4-R8, R10, R11, LR}
					
					
result				MOV R0, R4							; store result
					LDMFD SP!, {R4-R8, R10, R11, LR}
					
					BX LR
	
	END