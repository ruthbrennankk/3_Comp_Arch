.686                                ; create 32 bit code
.model flat, C                      ; 32 bit memory model
 option casemap:none                ; case sensitive

;declare g
.data 		; start of a data section
public g 	; export variable g
g DWORD 4 	; declare global variable g initialised to 4

.code 		; start of a code section

;min( int a, int b, int c)
public      min               ; make sure function name is exported

			;function entry
min:			push ebp		;save ebp
				mov ebp, esp	;ebp -> new stack frame
	
			;param	a @ ebp+8	b @ ebp+12	c @ ebp+16
			;local	none (eax is used as v)

				mov eax, [ebp+8] 	;int v=a
	
				cmp [ebp+12],eax	;if (b<v)
				jge notb
	
				mov eax, [ebp+12]	;v=b

notb:			cmp [ebp+16],eax	;if (b<c)
				jge notc
	
				mov eax,[ebp+16]	;v=c

notc:								;return v in eax
	
			;function exit
				mov esp, ebp	;restore esp
				pop ebp 		;restore previous ebp
				ret 0			;return from funtion (add esp, 12)


	
;int p (int i, int j, int k, int l)
public      p               ; make sure function name is exported

			;function entry
p:				push ebp		;save ebp
				mov ebp, esp	;ebp -> new stack frame
	
			;param	i @ ebp+8	j @ ebp+12	k @ ebp+16	l @ ebp+20
			;local	none

				;min(g,i,j)
				push  [ebp+12]	;push j
				push [ebp+8]	;push i
				push g			;push g (= 4)
				call min
				add esp, 12		;add 12 to esp to remove the 3 parameters from the stack
	
				;min( min(g,i,j), k, l)
				push [ebp+20]	;push l
				push [ebp+16]	;push k
				push eax 		;push ( min(g,i,j) )
				call min
				add esp, 12		;add 12 to esp to remove the 3 parameters from the stack

	
			;function exit
				mov esp, ebp		;restore esp
				pop ebp 		;restore previous ebp
				ret 0		;return from funtion (add esp, 16)


;int gcd( int a, int b)
public      gcd               ; make sure function name is exported

			;function entry
gcd:			push ebp		;save ebp
				mov ebp, esp		;ebp -> new stack frame

			;parameters a @ ebp+8	b @ ebp+12
			;locals	none

				mov eax, [ebp+12] ;memory/immediate not allowed
				test eax,eax	;if (b==0)
				jne gcdelse
	
				mov eax, [ebp+8]
				jmp gcdendif
	
gcdelse:		mov eax, [ebp+8]	;eax=a
				xor edx,edx			;clear destiniation for outputs. Stops garbage remainder
				mov ecx,[ebp+12]	;ecx = b
				idiv ecx			;eax%ecx=edx

				push edx			;push a%b
				push [ebp+12]		;push b
				call gcd
				add esp,8		;add 8 to esp to remove parameters from the stack

gcdendif:

			;function exit
				mov esp, ebp		;restore esp
				pop ebp				;restore previous ebp
				ret 0

	
end