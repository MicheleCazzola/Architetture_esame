	AREA	|.text|, CODE, READONLY
	EXPORT 	concat_sum
		; R0: vector
		; R1: vector size
		; R2: alarm flag ptr

concat_sum		
					MOV R12, SP
					STMFD SP!, {R4-R8, R10, R11, LR}
					
					MOV R3, #0	; index
					MOV R4, #1	; index+1
					MOV R5, #0	; result
					MOV R8, #0	; alarm value
loop				CMP R3, R1
					BGE result
					
					LDRH R6, [R0], #2
					
					CMP R4, R1
					MOVGE R7, #0
					LDRHLT R7, [R0], #2
					
					LSL R6, R6, #16
					ORR R6, R6, R7
					
					ADDS R5, R5, R6
					MOVVS R8, #-1
					
					ADD R3, R3, #2
					ADD R4, R4, #2
					B loop
					
result				MOV R0, R5							; store result
					STRB R8, [R2]
					LDMFD SP!, {R4-R8, R10, R11, LR}
					
					BX LR
	
	END