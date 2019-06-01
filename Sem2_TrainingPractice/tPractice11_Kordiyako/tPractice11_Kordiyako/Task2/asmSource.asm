.386
.MODEL FLAT
.DATA?
.CODE
;-----------Function definitions--------------------
@deleteTextBetweenBrackets@8 PROC
	xor esi, esi
	begin_external_loop:
		;compare character and open bracket
		cmp byte ptr[ecx + esi], '('
		jne if_open_bracket_end
		;if character is open bracket, push index into stack
		if_open_bracket_begin:
			push esi
		if_open_bracket_end:
		;compare character and close bracket
		cmp byte ptr[ecx + esi], ')'
		jne if_close_bracket_end
		;if character is close brace, do the following:
		if_close_bracket_begin:
			;pop index of last open bracket into eax
			pop eax
			;compute and save into edi 'delta' = difference in size between original string and shifted
			;'delta' = <current index> - <last open bracket index> + 1
			mov edi, esi
			sub edi, eax
			inc edi
			;shrink to fit counter(esi) and size of string(edx) by subtracting 'delta'
			sub edx, edi
			sub esi, edi
			;shift array 'delta' positions to the left 
			begin_internal_loop:
				;compute index of 'source' character and push it into ebx
				;'source' = 'destination' + 'delta'
				mov ebx, eax
				add ebx, edi
				;get 'source' character and push it to the address of 'destination' character
				mov bl, byte ptr[ecx + ebx]
				mov byte ptr[ecx + eax], bl
				inc eax
				cmp eax, edx
				jle begin_internal_loop
			end_internal_loop:
		if_close_bracket_end:
		;repeat until counter not equal to the string size
		inc esi
		cmp esi, edx
		jle begin_external_loop
	end_external_loop:
	ret
@deleteTextBetweenBrackets@8 ENDP
END 