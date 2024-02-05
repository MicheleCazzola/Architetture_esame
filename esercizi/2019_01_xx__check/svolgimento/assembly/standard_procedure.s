	AREA	|.text|, CODE, READONLY
	EXPORT 	overflow
		; R0: data/result
		; R1: data/result
		; R2: data
		; R3: data

overflow		
					MOV R12, SP
					STMFD SP!, {R4-R8, R10, R11, LR}
					
					MOV R5, #2	; default result
					MOV R2, #0	; index
					MOV R3, #0	; sum
loop				CMP R2, R1
					BEQ result
					
					LDR R4, [R0], #4
					ADDS R3, R3, R4
					
					ADD R2, R2, #1
					B loop
					
result				MOV R0, R7		; store default result
					MOVVS R0, #0	; store if overflow	set
					MOVHS R0, #1	; store if carry set
					LDMFD SP!, {R4-R8, R10, R11, LR}
					
					BX LR
	
	END