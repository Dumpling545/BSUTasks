.386
.MODEL FLAT
.DATA?
n		dd		?
.CODE
;-----------Function definitions--------------------
@isPalindrome@8 PROC
	mov n, edx
	mov eax, 1
	mov esi, 0
	mov edi, n
	dec edi
	begin_loop:
		mov ebx, [ecx + esi*4]
		mov edx, [ecx + edi*4]
		cmp ebx, edx
		je if_equal_start
		jmp if_not_equal_start
		if_equal_start:
			inc esi
			dec edi
			cmp esi, edi
			jg end_loop
			jmp begin_loop
		if_equal_end:
		if_not_equal_start:
			mov eax, 0
		if_not_equal_end:
	end_loop:
	ret
@isPalindrome@8 ENDP
END
 