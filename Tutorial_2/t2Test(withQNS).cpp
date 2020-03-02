option casemap:none                ; case sensitive

;one way to link with printf is to include the following at the head of t2.asm
includelib legacy_stdio_definitions.lib
extrn printf:near

;declare g
.data 		; start of a data section
public g 	; export variable g
g QWORD 4 	; declare global variable g initialised to 4

.code 		; start of a code section

;_int64 min( _int64 a, _int64 b, _int64 c)
public      min               ; make sure function name is exported

			;param	a @ rcx	b @ rdx	c @ r8

min:			mov rax, rcx	 	;int v=a
	
				cmp rdx,rax			;if (b<v)
				jge notb
	
				mov rax, rdx		;v=b

notb:			cmp r8,rax			;if (b<c)
				jge notc
	
				mov rax,r8			;v=c

notc:								;return v in eax

				ret 				;return from funtion


	
;_int64 p (_int64 i, _int64 j, _int64 k, _int64 l)
public      p               ; make sure function name is exported

			;param	i @ rcx	j @ rdx	k @ r8	l @ r9

				;min(g,i,j)
p:				sub rsp, 32		;allocate shadow space
				mov  rbx, r8	;temporarily store k (so we can pass parameters)
				mov r8, rdx		;pass j
				mov rdx, rcx	;pass i
				mov rcx, g		;pass g (= 4)
				call min
				add rsp, 32		;deallocate shaow space

			;i @ rdx	j @ r8	k @ rbx		min(g,i,j)@ rax 
				
				sub rsp, 32		;allocate shadow space
				;min( min(g,i,j), k, l)
				mov r8, r9		;pass l
				mov rdx, rbx	;pass k
				mov rcx, rax 	;push ( min(g,i,j) )
				call min
				add rsp, 32		;deallocate shaow space

				ret 		;return from funtion 



public		gcd

gcd:		mov		rax, rcx
			mov		r10, rdx
			test	r10, r10	;if (b==0)
			jne		gcdelse		
			jmp		gcdendif	;return a

gcdelse:	sub		rsp, 32		;allocate shadow space
			xor		rdx, rdx	;clear destination for a%b
			idiv	r10			
			mov		rcx, r10	;param 1 = b
								;param 2 = a%b (already in rdx)
			call	gcd
			add		rsp, 32
gcdendif:		
			ret		

				

;_int64 q(_int64 a, _int64 b, _int64 c, _int64 d, _int64 e) 

public q					; make sure function name is exported

fq db 'a = %I64d b = %I64d c = %I64d d = %I64d e = %I64d sum = %I64d\n', 0AH, 00H ; ASCII format string
	
			;parameters a @ rcx	b @ rdx	c @ r8	d @ r9	e @ rsp+40 (return address, sahdow space & 8 byte boundary)

q:			

			;store parameters
			mov r11, rcx		;a @ r11
			mov r12, rdx		;b @ r12
			mov r13, r8			;c @ r13
			mov r14, r9			;d @ r14
			mov r15, [rsp+40]	;e @ r15

			;calculate sum
			mov r10, 0			;sum = 0
			add r10, r11		;sum += a
			add r10, r12		;sum += b
			add r10, r13		;sum += c
			add r10, r14		;sum += d
			add r10, r15		;sum += e

			sub rsp, 56		; allocate stack space ( 32=shadow space + 8=d + 8=e + 8=sum )

			mov [rsp+48], r10	; printf parameter 7 passed on stack (sum)
			mov [rsp+40], r15	; printf parameter 6 passed on stack (e)
			mov [rsp+32], r14	; printf parameter 5 passed on stack (d)
			mov r9, r13			; printf parameter 4 in r9 (c)
			mov r8,	r12			; printf parameter 3 in r8 (b)
			mov rdx, r11		; printf parameter 2 in rdx (a)
			lea rcx, fq			; printf parameter 1 in rcx [&str]

			mov [rsp+64], r10	; store sum in shadow space so conserved accross function call

			call printf			; preserved across call to printf

			mov rax, [rsp+64]	; result in rax = saved r10 ie sum

			add rsp, 56		; deallocate stack space


			ret

			;_int64 q(_int64 a, _int64 b, _int64 c, _int64 d, _int64 e) 

public qns					; make sure function name is exported

fqns db 'qns\n', 0AH, 00H ; ASCII format string
	
			;parameters a @ rcx	b @ rdx	c @ r8	d @ r9	e @ rsp+40 (return address, sahdow space & 8 byte boundary)

qns:			
			sub rsp, 32		; allocate stack space 

			lea rcx, fqns	; printf parameter 1 in rcx [&fqns]

			call printf		; preserved across call to printf

			add rsp, 32		; deallocate stack space

			mov rax, 0

			ret
	
end