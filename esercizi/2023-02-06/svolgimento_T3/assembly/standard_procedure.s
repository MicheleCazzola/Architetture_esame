	AREA	|.text|, CODE, READONLY
	EXPORT 	differenza_media_positivi_negativi
		; R0: vector
		; R1: vector size
		; R2: overflow flag pointer

differenza_media_positivi_negativi		
					MOV R12, SP
					STMFD SP!, {R4-R8, R10, R11, LR}
					
					MOV R3, #0	; index
					MOV R5, #0	; pos sum
					MOV R6, #0	; neg sum
					MOV R7, #0	; pos cnt
					MOV R8, #0	; neg cnt
					MOV R10, #1	; overflow flag
loop				CMP R3, R1
					BEQ result
					
					LDR R4, [R0], #4
					
					CMP R4, #0
					ADDGE R7, R7, #1
					ADDLT R8, R8, #1
					ADDGES R5, R5, R4
					STRBVS R10, [R2]
					CMP R4, #0
					ADDLTS R6, R6, R4
					STRBVS R10, [R2]
					
					
					ADD R3, R3, #1
					B loop
					
result				SDIV R5, R5, R7
					SDIV R6, R6, R8
					SUB R0, R5, R6	; store result	
					LDMFD SP!, {R4-R8, R10, R11, LR}
					
					BX LR
	
	END