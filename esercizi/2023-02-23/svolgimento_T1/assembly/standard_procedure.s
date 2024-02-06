	AREA	|.text|, CODE, READONLY
	EXPORT 	fibonacci
		; R0: 8-bit variabile

fibonacci		
					MOV R12, SP
					STMFD SP!, {R4-R8, R10, R11, LR}
					
					MOV R1, #0	; fibo0
					MOV R2, #1	; fibo1
					
					CMP R0, R1
					MOVEQ R7, #0xFF
					BEQ result
					
					MOV R3, #0	; flag
					MOV R4, #1	; fibo2
loop				CMP R3, #1	
                    BEQ result
					
					ADD R4, R1, R2	; fibo2 = fibo0 + fibo1
					MOV R1, R2		; fibo0 = fibo1
					MOV R2, R4		; fibo1 = fibo2
					
					CMP R0, R4			; belongs to fibo
					MOVEQ R7, #0xFF
					BEQ result
					SUBGT R5, R0, R4	; d_prev = elem - fibo2
					SUBLT R6, R4, R0	; d_next = fibo2 - elem
					MOVLT R3, #1
					CMPLT R5, R6		; if(elem < fibo2)
					MOVLT R7, R1
					MOVGT R7, R4
					
					B loop
					
result				MOV R0, R7							; store result
					LDMFD SP!, {R4-R8, R10, R11, LR}
					
					BX LR
	
	END