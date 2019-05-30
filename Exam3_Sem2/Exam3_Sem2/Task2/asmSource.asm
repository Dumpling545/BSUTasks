.386
.MODEL FLAT
.DATA?
mtrx		dd		?
n			dd		?
m			dd		?
k			dd		?
temp		dd		?
.CODE
_shift PROC
	push ebp
	mov ebp, esp
	;init values into memory variables
	mov esi, [ebp+8]
	mov mtrx, esi
	mov esi, [ebp+12]
	mov n, esi
	mov esi, [ebp+16]
	mov m, esi
	mov esi, [ebp+20]
	mov k, esi
	xor esi, esi
	; compute n x m
	mov eax, n
	mul m
	mov ebx, eax
	; normalize k (if k >= n x m)
	xchg eax, k
	cdq
	div k
	mov k, edx
	;check if k = 0 (no shift)
	cmp k, 0
	je loop_end
	;push last k values in matrix into stack
	mov ecx, mtrx
	save_loop_begin:
		;compute single index of '(k - i)-th last' element as s = n x m - k + i (and move result in eax, i stored in esi)
		mov eax, ebx
		sub eax, k 
		add eax, esi
		;transform single index s (in eax) into double index [i][j] (and move <i, j> in <eax, edx>)
		cdq
		div m
		;get value of [i][j] element  (i in eax, j in edx)
		mov edi, [ecx + eax*4]
		mov edi, [edi + edx*4]
		;push [i][j] element in stack
		push edi
		;repeat k times for last k elements
		inc esi
		cmp esi, k
		jl save_loop_begin
	save_loop_end:
	;set esi as counter for new loop: esi = n x m - 1. esi is a single index of 'destination element'
	mov esi, ebx
	dec esi
	;shift elements
	loop_begin:
		;compute ADDRESS of element with single index esi (and put ADDRESS in temp variable)
		mov eax, esi
		cdq
		div m
		mov ecx, mtrx
		mov ecx, [ecx + eax*4]
		lea ecx, [ecx + edx*4]
		mov temp, ecx
		;compute single index edi of 'source element': edi = esi - k
		mov edi, esi
		sub edi, k
		;two cases: edi < 0 and edi >= 0
		cmp edi, 0
		jl if_negative_begin
		jmp if_positive_begin
		;case if edi < 0: put top of the stack in element with single index esi ('destination element')
		if_negative_begin:
			pop eax
			mov [ecx], eax
			jmp if_positive_end
		if_negative_end:
		;case if edi >= 0: put element with single index edi ('source element')
		;in element with single index esi ('destination element')
		if_positive_begin:
			;compute ADDRESS of element with single index edi ('source element')(and put ADDRESS in ecx)
			mov eax, edi
			cdq
			div m
			mov ecx, mtrx
			mov ecx, [ecx + eax*4]
			lea ecx, [ecx + edx*4]
			;put ADDRESS of element with single index 'esi' ('destination element') in edx 
			mov edx, temp
			;swap [ecx] and [edx]
			mov eax, [ecx]
			xchg eax, [ecx]
			mov [edx], eax
		if_positive_end:
		dec esi
		cmp esi, 0
		jnl loop_begin
	loop_end:
	pop ebp
	ret
_shift ENDP
END
 