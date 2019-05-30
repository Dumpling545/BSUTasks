.386
.MODEL FLAT
.DATA?
temp		dd		?
.CODE
;-----------Function definitions--------------------
@deleteTextBetweenSpaces@8 PROC
	mov edi, ecx
	mov ecx, edx
	inc ecx
	cld
	find_open_brace:
		mov al, '('
		repne scasb
		jecxz return
		mov edx, edi
		mov al, ')'
		repne scasb
		jecxz return
		xor esi, esi
		loop_begin:
			mov bl, byte ptr[edi + esi]
			mov byte ptr[edx + esi - 1], bl
			inc esi
			cmp esi, ecx
			jl loop_begin
		loop_end:
		mov edi, edx
		jmp find_open_brace
	return:
	ret
@deleteTextBetweenSpaces@8 ENDP
END 