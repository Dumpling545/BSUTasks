.386
.MODEL FLAT
.DATA?
temp_size		dd		?
counter			dd		?
.CODE
;-----------Function definitions--------------------
@deleteLastSpaces@8 PROC
	;save all registers into stack not to be changed during procedure
	pushad
	;load address of last non-terminator character in string
	lea edi, [ecx + edx - 1]
	;move size of string into ecx
	mov ecx, edx
	;increment size of string (assembly language works with string including null-terminator)
	inc ecx
	;save original size into memory
	mov temp_size, edx
	;change direction flag: 'right-to-left'
	std
	;init character to be found by scasb
	mov al, ' '
	;find non-space character (last in the string)
	repe scasb
	jecxz end_
	;push null-terminator after last non-space character
	mov byte ptr[edi+2], 0
	;save new string size into memory
	mov temp_size, ecx
	end_:
	;load all registers from stack
	popad
	;change second parameter(edx) because string size may be changed
	mov edx, temp_size
	ret
@deleteLastSpaces@8 ENDP
@deleteFirstSpaces@8 PROC
	;save all registers into stack not to be changed during procedure
	pushad
	;move address of string into edi
	mov edi, ecx
	;move size of string into ecx
	mov ecx, edx
	;increment size of string (assembly language works with string including null-terminator)
	inc ecx
	;save address to the beginning of string
	mov edx, edi
	;change direction flag: 'left-to-right'
	cld
	;init character to be found by scasb
	mov al, ' '
	;find non-space character (first in the string)
	repe scasb
	jecxz end_loop
	;save value of ecx into esi
	;change address in edi to first-non space character('repe scasb' stops at second)
	mov esi, ecx
	inc esi
	dec edi
	;left shift
	begin_loop:
		mov bl, byte ptr[edi]
		mov byte ptr[edx], bl
		inc edi
		inc edx
		dec esi
		cmp esi, 0
		jg begin_loop
	end_loop:
	;save new string size into memory
	mov temp_size, ecx
	;load all registers from stack
	popad
	;change second parameter(edx) because string size may be changed
	mov edx, temp_size
	ret
@deleteFirstSpaces@8 ENDP
@deleteOddSpaces@8 PROC
	;delete spaces before first word and after last word
	call @deleteFirstSpaces@8
	call @deleteLastSpaces@8
	;mov address and counter into edi, ecx
	mov edi, ecx
	cmp byte ptr[edi], 0
	je end_
	mov ecx, edx
	inc ecx
	;chahge direction
	cld
	;init character to be used by scasb
	mov al, ' '
	begin_:
		;find space
		or al, 0
		repne scasb
		jecxz end_
		;compare character AFTER space
		cmp byte ptr[edi], ' '
		;if it is not a space, find next space
		jne begin_
		;if it is a space, shift string to the left
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
		;move edi to next character (after shift edi pointed to the character after next in source string)
		dec edi
		jmp begin_
	end_:
	ret
@deleteOddSpaces@8 ENDP

@countWords@8 PROC
	;init word counter
	mov counter, 0
	;move address of string into edi
	mov edi, ecx
	;move size of string into ecx
	mov ecx, edx
	;increment size of string (assembly language works with string including null-terminator)
	inc ecx
	;change direction flag: 'left-to-right'
	cld
	;init character to be found by scasb
	mov al, ' '
	find_letter_begin:
		;find non-space character
		or al, 0
		repe scasb
		;if string is ended, stop procedure
		jecxz return
		;move to first non-space character ('repe scasb' stops at second)
		dec edi
		inc ecx
		;increment counter of words
		inc counter
		;find space character
		or al, 0
		repne scasb
		;if string is ended, stop procedure
		jecxz return
		;move to first space character ('repe scasb' stops at second)
		dec edi
		inc ecx
		jmp find_letter_begin
	return:
	;save counter into 'return' register
	mov eax, counter
	ret
@countWords@8 ENDP
END 