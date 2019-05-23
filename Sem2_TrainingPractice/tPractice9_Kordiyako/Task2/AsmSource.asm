.386
.MODEL FLAT
.CODE
;-----------Function definitions--------------------
_solveEquation PROC
	push ebp
	mov ebp, esp
	; move 'state' parameter in esi
	mov esi, [ebp + 16]
	; move 'x' parameter in edi
	mov edi, [ebp + 20]
	; move 'a' parameter in eax
	mov eax, [ebp + 8]
	; move opposite number for 'b' parameter in ebx
	mov ebx, 0
	sub ebx, [ebp + 12]
	; compare a and 0
	cmp eax, 0
	je a_zero_begin
	jmp a_not_zero_begin
	; if(a == 0)
	a_zero_begin:
		; compare -b and 0
		cmp ebx, 0
		je b_zero_begin
		jmp b_not_zero_begin
		; if(-b == 0)
		b_zero_begin:
			; set state to 2 (infinitely many solutions)
			mov dword ptr [esi], 2
			jmp return
		; if(-b != 0)
		b_not_zero_begin:
			; set state to 0 (no solutions)
			mov dword ptr [esi], 0
			jmp return
	; if(a != 0)
	a_not_zero_begin:
		; set state to 1 (one solution)
		mov dword ptr [esi], 1
		; compute 'x' parameter: divide -b by a
		xchg eax, ebx
		cdq
		idiv ebx
		; write result into parameter x
		mov [edi], eax
	return:
	pop ebp
	ret
_solveEquation ENDP
END
 