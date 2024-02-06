	AREA	|.text|, CODE, READONLY
	EXPORT 	sort_integers	; 32-bit integers, sort desc order
		; R0: vector to sort
		; R1: number of elements

sort_integers		MOV R12, SP
					STMFD SP!, {R4-R8, R10, R11, LR}
					
					MOV R2, #0	; i
loop_ext			CMP R2, R1
                    BEQ result
					
					LDR R3, [R0, R2, LSL #2]	; get v[i]
					MOV R6, R3	;	max = v[i]
					MOV R7, R2	; 	posmax = i
					
					ADD R4, R2, #1	;j = i+1
find_min			CMP R4, R1
                    BEQ next_loop_ext
					
					LDR R5, [R0, R4, LSL #2]	; get v[j]
					CMP R5, R6	; if(v[j] > max)
					
					MOVGT R6, R5	; max = v[j]
					MOVGT R7, R4	; posmax = j
					
					ADD R4, R4, #1	; j++
					B find_min
					
next_loop_ext		CMP R2, R7					; if(i != posmax)
					STRNE R3, [R0, R7, LSL #2]	; v[posmax] = v[i]
					STRNE R6, [R0, R2, LSL #2]	; v[i] = max
					ADD R2, R2, #1	; i++
					B loop_ext
					
result				LDMFD SP!, {R4-R8, R10, R11, LR}
					BX LR
	
	END