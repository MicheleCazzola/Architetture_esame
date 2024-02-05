	AREA	|.text|, CODE, READONLY
	EXPORT 	search_in_pool		; search integer in literal pool
		; R0: element to search	

search_in_pool		
					MOV R12, SP
					STMFD SP!, {R4-R8, R10, R11, LR}
					
					LDR R4, =N
					LDR R4, [R4]
					LDR R1, =numbers
					
					MOV R2, #0
					
search				CMP R2, R4
					BEQ result
					
					LDR R3, [R1], #4
					CMP R3, R0
					
					BEQ result
					
					ADD R2, R2, #1
					
					B search
					
					
result				CMP R2, R4
					MOVEQ R0, #-1							; store result
					MOVNE R0, R2
					LDMFD SP!, {R4-R8, R10, R11, LR}
					
					BX LR
	LTORG
	
N			DCD 4
numbers		DCD 0x67, 0x78, 0x86, 0x13	
	
	END
		
	