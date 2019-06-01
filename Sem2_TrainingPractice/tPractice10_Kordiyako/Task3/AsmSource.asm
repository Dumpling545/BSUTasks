.386
.MODEL FLAT
.DATA?
n		dd		?
max		dd		?
i_max	dd		?
min		dd		?
i_min	dd		?
array	dd		?
index	dd		?
.CODE
;-----------Function definitions--------------------
@getColumnExtrema@8 PROC
	pushad
	;note: column value is a sum of elements in column
	;i_max, i_min - indexes of min and max column value
	mov i_max, 0
	mov i_min, 0
	;array - address of first element of given array
	mov array, ecx
	mov min, 0
	mov max, 0
	xor esi, esi
	;compute first column value
	begin_init_min_max_loop:
		mov ecx, array
		mov ecx, [ecx + esi*4]
		mov ecx, [ecx]
		add min, ecx
		inc esi
		cmp esi, edx
		jl begin_init_min_max_loop
	end_init_min_max_loop:
	;init max and min value with first column value
	mov esi, min
	mov max, esi
	xor esi, esi
	begin_external_loop:
		xor ebx, ebx
		xor edi, edi
		;compute value of i-th column
		begin_internal_loop:
			mov ecx, array
			mov ecx, [ecx + edi*4]
			mov ecx, [ecx + esi*4]
			add ebx, ecx
			inc edi
			cmp edi, edx
			jl begin_internal_loop
		end_internal_loop:
		;compare max value and value of i-th column
		mov ecx, max
		cmp ebx, ecx
		jg if_greater_than_max_begin
		;compare min value and value of i-th column
		mov ecx, min
		cmp ebx, ecx
		jl if_less_than_min_begin
		jmp if_less_than_min_end
		;if i-th column value > max
		if_greater_than_max_begin:
			;move value in max and index in i_max
			mov max, ebx
			mov i_max, esi
			jmp if_less_than_min_end
		if_greater_than_max_end:
		;if i-th column value < min
		if_less_than_min_begin:
			;move value in min and index in i_min
			mov min, ebx
			mov i_min, esi
		if_less_than_min_end:
		inc esi
		cmp esi, edx
		jl begin_external_loop
	end_external_loop:
	popad
	;move indexes af max and min, and address of array into registers
	mov ecx, i_min
	mov edx, i_max
	mov eax, array
	ret
@getColumnExtrema@8 ENDP

@switchColumnExtrema@8 PROC
	;get indexes of max and min columns
	call @getColumnExtrema@8
	mov min, ecx
	mov max, edx 
	mov esi, 0
	;swap elements of min and max columns
	begin_loop:
		cmp esi, n
		jnl end_loop

		mov ecx, [eax + esi*4]
		mov edi, min
		lea ecx, [ecx + edi*4]

		mov edx, [eax + esi*4]
		mov edi, max
		lea edx, [edx + edi*4]

		mov edi, [ecx]
		xchg edi, [edx]
		mov [ecx], edi

		inc esi
		jmp begin_loop
	end_loop:
	ret
@switchColumnExtrema@8 ENDP

_swap PROC
	push ebp
	mov ebp, esp
	;move array address into eax
	mov eax, [ebp+8]
	;move size into n variable
	mov ebx, [ebp+12]
	mov n, ebx
	;move index 'i' into index variable
	mov ebx, [ebp+16]
	mov index, ebx
	xor esi, esi
	;swap
	begin_loop:
		cmp esi, n
		jnl end_loop

		mov edi, index
		mov ecx, [eax + edi*4]
		lea ecx, [ecx + esi*4]

		mov edi, index
		mov edx, [eax + esi*4]
		lea edx, [edx + edi*4]

		mov edi, [ecx]
		xchg edi, [edx]
		mov [ecx], edi

		inc esi
		jmp begin_loop
	end_loop:
	pop ebp
	ret
_swap ENDP
END
 