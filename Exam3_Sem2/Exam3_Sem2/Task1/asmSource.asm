.386
.MODEL FLAT
.DATA?
gcd_val		dd		?
lcmft_val	dd		?
.CODE
@gcd@8 PROC
	pushad
	loop_begin:
		cmp ecx, edx
		jg if_ecx_greater_begin
		sub edx, ecx
		jmp if_ecx_greater_end
		if_ecx_greater_begin:
		sub ecx, edx
		if_ecx_greater_end:
		cmp ecx, edx
		jne loop_begin
	mov gcd_val, ecx
	popad
	mov eax, gcd_val
	ret
@gcd@8 ENDP
@lcm_for_two@8 PROC
	pushad
		call @gcd@8
		xchg eax, ecx
		mov ebx, edx
		cdq
		idiv ecx
		imul ebx
		mov lcmft_val, eax
	popad
		mov eax, lcmft_val
	ret
@lcm_for_two@8 ENDP
@lcm@8 PROC
	mov ebx, ecx
	mov edi, edx
	mov esi, 1
	mov ecx, [ebx]
	cmp esi, edi
	je loop_end
	loop_begin:
		mov edx, [ebx + esi*4]
		call @lcm_for_two@8
		mov ecx, eax
		inc esi
		cmp esi, edi
		jl loop_begin
	loop_end:
	mov eax, ecx
	ret
@lcm@8 ENDP

END
 