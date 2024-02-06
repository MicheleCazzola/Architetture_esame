	AREA	|.text|, CODE, READONLY
		EXPORT 	totale_pressioni_con_filtro
		; R0: pressure vector
		; R1: vector size
		; R2: max value
		; R3: min value

totale_pressioni_con_filtro		
					MOV R12, SP
					STMFD SP!, {R4-R8, R10, R11, LR}
					
					MOV R4, #0	; index
					MOV R5, #0	; result
loop				CMP R4, R1
					BEQ result
					
					LDRB R6, [R0], #1

first_cfr			CMP R6, R3
					BMI next
second_cfr			CMP R6, R2
					BHI next
					
					ADD R5, R5, R6

next				ADD R4, R4, #1
					B loop
					
					
result				MOV R0, R5							; store result
					LDMFD SP!, {R4-R8, R10, R11, LR}
					
					BX LR
	
	END