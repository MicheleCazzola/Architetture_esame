	AREA	|.text|, CODE, READONLY
	EXPORT 	sopra_la_media
		; R0: vett
		; R1: number of elements

sopra_la_media		
					MOV R12, SP
					STMFD SP!, {R4-R8, R10, R11, LR}
					
					MOV R4, #0	; index
					MOV R6, #0	; sum
loop_sum			CMP R4, R1
					BEQ check_above
					
					LDRB R5, [R0, R4]
					ADD R6, R6, R5
					
					ADD R4, R4, #1
					B loop_sum
					
check_above			UDIV R6, R6, R1	; truncate average
					MOV R4, #0	;index
					MOV R7, #0	;counter
loop_above			CMP R4, R1
					BEQ result
					
					LDRB R5, [R0, R4]
					CMP R5, R6
					ADDGT R7, R7, #1
					
					ADD R4, R4, #1
					B loop_above
					
result				MOV R0, R7							; store result
					LDMFD SP!, {R4-R8, R10, R11, LR}
					
					BX LR
	
	END