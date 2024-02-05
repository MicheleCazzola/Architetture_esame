	AREA	|.text|, CODE, READONLY
	EXPORT 	get_and_sort
		; R0: vector
		; R1: value
		; R2: number of elements (1 at first step)
		; R3: data

get_and_sort		
					MOV R12, SP
					STMFD SP!, {R4-R8, R10, R11, LR}
					
					MOV R5, #0		; index
					SUB R6, R2, #1	; limit
find_pos			CMP R5, R6
                    BEQ insert

					LDRB R4, [R0, R5]
                    CMP R1, R4
					BHI insert
					
					ADD R5, R5, #1
					B find_pos
					
insert				MOV R7, R2	; reverse index
loop				CMP R7, R5
					BLT insert_elem
					
					SUB R3, R7, #1
					LDRB R8, [R0, R3]
					STRB R8, [R0, R7]
					
					SUB R7, R7, #1
					B loop
					
insert_elem			STRB R1, [R0, R5]
					
result				MOV R0, R1							; store result
					LDMFD SP!, {R4-R8, R10, R11, LR}
					
					BX LR
	
	END