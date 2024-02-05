				
			
			
				AREA asm_functions, CODE, READONLY				
                EXPORT  get_and_sort
get_and_sort
				; save current SP for a faster access 
				; to parameters in the stack
				MOV   r12, sp
				; save volatile registers
				STMFD sp!,{r4-r8,r10-r11,lr}				
				
				; CODE HERE
				; r0 = indirizzo del vettore VETT
				; r1 = il valore di VAL (8 bit)
				; r2 = n (valore attualmente acquisito)
				
				; r1= 7
				; n = 4
				; 	[r3][r2]
				; 10, 8, 7,   6, X, X, X
				
				; r1 = 7
				; n = 1
				; 	[r3][r2]
				; 		7,0,0,0,0,0,0
				
				add r2, r0, r2

loop			sub r2, r2, #1  ; indirizzo della prima posizione libera
				sub r3, r2, #1 ; indirizzo dell'ultima posizione occupata
						
				cmp r0, r3   ; aggiorna i FLAGS
				bhi fine
				
				ldrb r4, [r3]  ; il valore dell'ultimo elemento inserito
				cmp r4, r1; 	
				bhi fine 		; MAGGIORE
				strb r4, [r2]
				b loop
				
				
fine			strb r1, [r2]
				mov r0, r1
				

				; restore volatile registers
				LDMFD sp!,{r4-r8,r10-r11,pc}
				
                END
					
					
					
					
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			; CODE HERE
				; r0 = indirizzo di VETT
				; r1 = VAL (8 bit unsigned)
				; r2 = n 
				
;				add r2, r0, r2 ; ind elemento da inserire + 1
;loop			sub r2, r2, #1
;				sub r3, r2, #1
;				cmp r0, r3
;				bhi fine
;				ldrb r4, [r3]  ; 7
;				cmp r4, r1
;				bhi fine
;				strb r4, [r2]
;				b loop
;fine			strb r1, [r2]
;				mov r0, r1