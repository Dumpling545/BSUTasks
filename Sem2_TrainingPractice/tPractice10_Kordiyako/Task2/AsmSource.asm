.386
.MODEL FLAT
.DATA?
n		dd		?
.CODE
;-----------Function definitions--------------------
@isPalindrome@8 PROC
	;init n - size of array
	mov n, edx
	;init result = 1(true)
	mov eax, 1
	;esi = index of first element
	;edi = index of last element
	xor esi, esi
	mov edi, n
	dec edi
	begin_loop:
		mov ebx, [ecx + esi*4]
		mov edx, [ecx + edi*4]
		cmp ebx, edx
		jne if_not_equal_start
		;if elements are equal
		if_equal_start:
			;move to next pair of elems
			inc esi
			dec edi
			cmp esi, edi
			jg end_loop
			jmp begin_loop
		if_equal_end:
		;if elements are not equal
		if_not_equal_start:
			;set result to 0(false) and exit loop
			xor eax, eax
		if_not_equal_end:
	end_loop:
	ret
@isPalindrome@8 ENDP
END
 