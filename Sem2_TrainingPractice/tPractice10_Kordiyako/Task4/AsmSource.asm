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
	;save register values which will be changed
	push ebp
	push edx
	push ecx
	push ebx
	mov ebp, esp
	xor ebx, ebx
	xor eax, eax
	begin_loop:
		;get [esi][ebx] and [ebx][edi] elements
		mov ecx, m_left
		mov ecx, [ecx + esi*4]
		mov ecx, [ecx + ebx*4]

		mov edx, m_right
		mov edx, [edx + ebx*4]
		mov edx, [edx + edi*4]
		
		;multiply  [esi][ebx] and [ebx][edi]
		xchg eax, ecx
		imul edx
		;add them to sum(stored in eax)
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
	;move left matrix into m_left
	mov eax, [ebp+8] 
	mov m_left, eax
	;move right matrix into m_right
	mov eax, [ebp+12]
	mov m_right, eax
	;move result matrix into ebx
	mov ebx, [ebp+16]
	;move 1st size of left matrix into n
	mov eax, [ebp+20]
	mov n, eax
	;move 2nd size of left/1st size of right matrix into m
	mov eax, [ebp+24]
	mov m, eax
	;move 2nd size of right matrix into n
	mov eax, [ebp+28]
	mov k, eax
	xor esi, esi
	begin_external_loop:
		xor edi, edi
		begin_internal_loop:
			;compute [esi][edi] element and push it into ebx[esi][edi]
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
 