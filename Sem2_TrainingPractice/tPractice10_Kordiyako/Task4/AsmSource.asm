.386
.MODEL FLAT
.DATA?
m_left		dd		?
m_right		dd		?
m_result	dd		?
n			dd		?
m			dd		?
k			dd		?
.CODE
;-----------Function definitions--------------------
_computeElement PROC
	push ebp
	push edx
	push ecx
	push ebx
	mov ebp, esp
	xor ebx, ebx
	xor eax, eax
	begin_loop:
		mov ecx, m_left
		mov ecx, [ecx + esi*4]
		mov ecx, [ecx + ebx*4]

		mov edx, m_right
		mov edx, [edx + ebx*4]
		mov edx, [edx + edi*4]
		
		xchg eax, ecx
		imul edx
		add eax, ecx
		inc ebx
		cmp ebx, m
		jl begin_loop
	end_loop:
	pop ebx
	pop ecx
	pop edx
	pop ebp
	ret
_computeElement ENDP
_multiplyMatrices PROC
	push ebp
	mov ebp, esp
	mov eax, [ebp+8] 
	mov m_left, eax
	mov eax, [ebp+12]
	mov m_right, eax
	mov ebx, [ebp+16]
	mov eax, [ebp+20]
	mov n, eax
	mov eax, [ebp+24]
	mov m, eax
	mov eax, [ebp+28]
	mov k, eax
	xor esi, esi
	xor edi, edi
	begin_external_loop:
		xor edi, edi
		begin_internal_loop:
			call _computeElement
			mov ecx, [ebx+esi*4]
			xchg eax, [ecx+edi*4]
			inc edi
			cmp edi, k
		jl begin_internal_loop
		end_internal_loop:
		inc esi
		cmp esi, n
		jl begin_external_loop
	end_external_loop:
	pop ebp
	ret
_multiplyMatrices ENDP
END
 