	AREA	|.text|, CODE, READONLY
	EXPORT 	calcola_somma_prodotto
		; R0: vector
		; R1: vector size
		; R2: alarm pointer

calcola_somma_prodotto		
					MOV R12, SP
					STMFD SP!, {R4-R8, R10, R11, LR}
					
					MOV R3, #0
					MOV R4, #1
					MOV R7, #0	; result
loop				CMP R3, R1
					BEQ result
					
					LDR R5, [R0, R3, LSL #2]
					LDR R6, [R0, R4, LSL #2]
					
					MLA R7, R5, R6, R7
					
					ADD R3, R3, #2
					ADD R4, R4, #2
					B loop
					
					
result				MOV R0, R7							; store result
					CMP R0, #255						; store alarm
					MOVLT R8, #-1
					STRLT R8, [R2]
					MOVGE R8, #1
					STRGE R8, [R2]
					LDMFD SP!, {R4-R8, R10, R11, LR}
					
					BX LR
	
	END