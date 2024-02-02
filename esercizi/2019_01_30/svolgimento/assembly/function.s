	AREA	count_ones, CODE, READONLY
	EXPORT 	count_bits_to_1

count_bits_to_1		
					MOV R12, SP
					STMFD SP!, {R4-R8, R10, R11, LR}
					
					MOV R1, #0							; accumulator
					MOV R2, #32							; number of bits
					MOV R3, #0							; index
count_loop			CMP R3, R2
                    BEQ result
					
					AND R4, R0, #1
					ADD R1, R1, R4
					
					LSR R0, R0, #1
					ADD R3, R3, #1
					
					B count_loop
					
result				MOV R0, R1							; store result
					LDMFD SP!, {R4-R8, R10, R11, LR}
					
					BX LR
	
	END