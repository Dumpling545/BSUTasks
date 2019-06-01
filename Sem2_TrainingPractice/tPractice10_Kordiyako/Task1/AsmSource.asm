.386
.MODEL FLAT
.DATA?
n			dd		?
max_index	dd		?
max_count	dd		?
.CODE
;-----------Function definitions--------------------
@uniqueElements@8 PROC
	;save size in n
	mov n, edx
	;make eax, esi, edi equal to null
	xor eax, eax
	xor esi, esi
	xor edi, edi
	;esi - counter of external loop
	;edi - counter of internal loop
	begin_external_loop:
		;each element of array is compared with all right-hand elements
		mov edi, esi
		inc edi
		begin_internal_loop:
			;move elements in ebx, edx
			mov ebx, [ecx + esi*4]
			mov edx, [ecx + edi*4]
			;compare elements in ebx, edx
			cmp ebx, edx
			jne if_end
			;if elements are equal, eax is incremented and loop goes to the next element
			if_start:
				inc eax
				jmp end_internal_loop
			if_end:
			;repeat untill edi is less than n
			inc edi
			cmp edi, n
			jl begin_internal_loop
		end_internal_loop:
		;repeat untill esi is less than n-1
		inc esi
		mov ebx, n
		dec ebx
		cmp esi, n
		jl begin_external_loop
	end_external_loop:
	;eax now stores sum of <repeat amount of each element> - 1
	;so if we subtract eax from n, we get amount of unique elements
	sub n, eax
	mov eax, n
	ret
@uniqueElements@8 ENDP

@mostFrequentElement@8 PROC
	;save size in n
	mov n, edx
	;make eax, esi, edi equal to null
	xor eax, eax
	xor esi, esi
	xor edi, edi
	;esi - counter of external loop
	;edi - counter of internal loop
	begin_external_loop:
		;each element of array is compared with all right-hand elements
		mov edi, esi
		inc edi
		xor eax, eax
		begin_internal_loop:
			;move elements in ebx, edx
			mov ebx, [ecx + esi*4]
			mov edx, [ecx + edi*4]
			;compare elements in ebx, edx
			cmp ebx, edx
			jne if_equal_end
			if_equal_start:
				inc eax
			if_equal_end:
			;repeat untill edi is less than n
			inc edi
			cmp edi, n
			jl begin_internal_loop
		end_internal_loop:
		;compare eax-value and max_count
		cmp eax, max_count
		jle if_greater_end
		;if eax > max_count, move eax into max_count and edi into max_index
		if_greater_start:
			mov max_index, esi
			mov max_count, eax
		if_greater_end:
		;repeat untill esi is less than n-1
		inc esi
		mov ebx, n
		dec ebx
		cmp esi, ebx
		jl begin_external_loop
	end_external_loop:
	;move element at max_index into eax
	mov esi, max_index
	mov eax, [ecx + esi*4]
	ret
@mostFrequentElement@8 ENDP
END
 