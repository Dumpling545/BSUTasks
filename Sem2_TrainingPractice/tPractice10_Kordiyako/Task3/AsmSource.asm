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
	mov i_max, 0
	mov i_min, 0
	mov array, ecx
	mov min, 0
	mov max, 0
	mov esi, 0
	begin_init_min_max_loop:
		mov ecx, array
		mov ecx, [ecx + esi*4]
		mov ecx, [ecx]
		add min, ecx
		inc esi
		cmp esi, edx
		jl begin_init_min_max_loop
	end_init_min_max_loop:
	mov esi, min
	mov max, esi
	mov esi, 0
	begin_external_loop:
		mov ebx, 0
		mov edi, 0
		begin_internal_loop:
			mov ecx, array
			mov ecx, [ecx + edi*4]
			mov ecx, [ecx + esi*4]
			add ebx, ecx
			inc edi
			cmp edi, edx
			jl begin_internal_loop
		end_internal_loop: 
		mov ecx, max
		cmp ebx, ecx
		jg if_greater_than_max_begin
		mov ecx, min
		cmp ebx, ecx
		jl if_less_than_min_begin
		jmp if_less_than_min_end
		if_greater_than_max_begin:
			mov max, ebx
			mov i_max, esi
			jmp if_less_than_min_end
		if_greater_than_max_end:
		if_less_than_min_begin:
			mov min, ebx
			mov i_min, esi
		if_less_than_min_end:
		inc esi
		cmp esi, edx
		jl begin_external_loop
	end_external_loop:
	mov ecx, i_min
	mov edx, i_max
	mov eax, array
	ret
@getColumnExtrema@8 ENDP

@switchColumnExtrema@8 PROC
	call @getColumnExtrema@8
	mov min, ecx
	mov max, edx 
	mov esi, 0
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
	mov eax, [ebp+8] 
	mov ebx, [ebp+12]
	mov n, ebx
	mov ebx, [ebp+16]
	mov index, ebx
	mov esi, 0
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
 