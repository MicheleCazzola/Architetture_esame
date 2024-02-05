	AREA	|.text|, CODE, READONLY
	EXPORT 	stat_satisfaction
		; R0: S
		; R1: N
		; R2: I
		; R3: &PS

stat_satisfaction		
					MOV R12, SP
					STMFD SP!, {R4-R8, R10, R11, LR}
					
					LDR R4, [R12]	; &PN
					LDR R5, [R12, #4]	; &PI
					
					MOV R7, R0
					ADD R7, R7, R1
					ADD R7, R7, R2	; tot clienti
					
					MOV R8, #100
					
					MUL R11, R0, R8
					UDIV R11, R11, R7
					STRB R11, [R3]	; calc PS
					
					MUL R11, R1, R8
					UDIV R11, R11, R7
					STRB R11, [R4]	; calc PN
					
					MUL R11, R2, R8
					UDIV R11, R11, R7
					STRB R11, [R5]	; calc PI 
					
					
result				MOV R0, R7							; store result
					LDMFD SP!, {R4-R8, R10, R11, LR}
					
					BX LR
	
	END