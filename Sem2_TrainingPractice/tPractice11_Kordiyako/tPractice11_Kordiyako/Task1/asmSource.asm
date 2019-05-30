.386
.MODEL FLAT
.DATA?
temp_size		dd		?
counter			dd		?
.CODE
;-----------Function definitions--------------------
@deleteLastSpaces@8 PROC
	pushad
	lea edi, [ecx + edx - 1]
	mov ecx, edx
	mov temp_size, edx
	inc ecx
	std
	mov al, ' '
	repe scasb
	jecxz end_
	mov byte ptr[edi+2], 0
	mov temp_size, ecx
	end_:
	popad
	mov edx, temp_size
	ret
@deleteLastSpaces@8 ENDP
@deleteFirstSpaces@8 PROC
	pushad
	mov edi, ecx
	mov ecx, edx
	inc ecx
	mov edx, edi
	mov ebx, edi
	cld
	mov al, ' '
	repe scasb
	jecxz end_loop
	mov esi, ecx
	inc esi
	dec edi
	begin_loop:
		mov bl, byte ptr[edi]
		mov byte ptr[edx], bl
		inc edi
		inc edx
		dec esi
		cmp esi, 0
		jg begin_loop
	end_loop:
	mov temp_size, ecx
	popad
	mov edx, temp_size
	ret
@deleteFirstSpaces@8 ENDP
@deleteOddSpaces@8 PROC
	call @deleteFirstSpaces@8
	call @deleteLastSpaces@8
	mov edi, ecx
	mov ecx, edx
	inc ecx
	cld
	mov al, ' '
	begin_:
		or al, 0
		repne scasb
		jecxz end_
		jmp replace_word_
	replace_word_:
		cmp byte ptr[edi], ' '
		jne begin_
		mov edx, edi
		mov esi, ecx
		begin_loop:
			mov bl, byte ptr[edx]
			mov byte ptr[edx - 1], bl
			inc edx
			dec esi
			cmp esi, 0
			jg begin_loop
		end_loop:
		dec edi
		jmp begin_
	end_:
	ret
@deleteOddSpaces@8 ENDP

@countWords@8 PROC
	mov counter, 0
	mov edi, ecx
	mov ecx, edx
	inc ecx
	cld
	mov al, ' '
	find_letter_begin:
		or al, 0
		repe scasb
		jecxz return
		inc counter
		or al, 0
		repne scasb
		jecxz return
		jmp find_letter_begin
	return:
	mov eax, counter
	ret
@countWords@8 ENDP
END 