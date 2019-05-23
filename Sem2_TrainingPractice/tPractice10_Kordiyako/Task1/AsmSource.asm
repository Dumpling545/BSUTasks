.386
.MODEL FLAT
.DATA?
n			dd		?
max_index	dd		?
max_count	dd		?
.CODE
;-----------Function definitions--------------------
@uniqueElements@8 PROC
	mov n, edx
	mov eax, 0
	mov esi, 0
	mov edi, 0
	begin_external_loop:
		mov edi, esi
		add edi, 1
		begin_internal_loop:
			mov ebx, [ecx + esi*4]
			mov edx, [ecx + edi*4]
			cmp ebx, edx
			je if_start
			jmp if_end
			if_start:
				cmp esi, edi
				je if_end
				inc eax
				jmp end_internal_loop
			if_end:
			inc edi
			cmp edi, n
			jl begin_internal_loop
		end_internal_loop:
		inc esi
		mov ebx, n
		dec ebx
		cmp esi, ebx
		jl begin_external_loop
	end_external_loop:
	sub n, eax
	mov eax, n
	ret
@uniqueElements@8 ENDP

@mostFrequentElement@8 PROC
	mov n, edx
	mov eax, 0
	mov esi, 0
	mov edi, 0
	begin_external_loop:
		mov edi, esi
		add edi, 1
		mov eax, 0
		begin_internal_loop:
			mov ebx, [ecx + esi*4]
			mov edx, [ecx + edi*4]
			cmp ebx, edx
			je if_equal_start
			jmp if_equal_end
			if_equal_start:
				inc eax
			if_equal_end:
			inc edi
			cmp edi, n
			jl begin_internal_loop
		end_internal_loop:
		cmp eax, max_count
		jg if_greater_start
		jmp if_greater_end
		if_greater_start:
			mov max_index, esi
			mov max_count, eax
		if_greater_end:
		inc esi
		mov ebx, n
		dec ebx
		cmp esi, ebx
		jl begin_external_loop
	end_external_loop:
	mov esi, max_index
	mov eax, [ecx + esi*4]
	ret
@mostFrequentElement@8 ENDP
END
 