	AREA	|.text|, CODE, READONLY
	EXPORT 	find_best_k		; finds top-K elements in a vector of 32-bit integers
		; R0: vector to analyize
		; R1: number of elements
		; R2: result vector

find_best_k		
					MOV R12, SP
					STMFD SP!, {R4-R8, R10, R11, LR}
					
					IMPORT sort_integers
						
					STMFD SP!, {R0-R3}	
					
					BL sort_integers 
					
					LDMFD SP!, {R0-R3}
					
select_best_K		MOV R3, #3	; BEST-k, k = 3
					MOV R4, #0

loop				CMP R4, R3
					BEQ result
					
					LDR R5, [R0], #4
					STR R5, [R2], #4
					
					ADD R4, R4, #1
					B loop
					
					
result				MOV R0, R1							; store result
					LDMFD SP!, {R4-R8, R10, R11, LR}
					
					BX LR
	
	END