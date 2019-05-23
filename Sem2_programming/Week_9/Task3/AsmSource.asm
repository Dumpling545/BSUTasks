.386
.MODEL FLAT
.DATA?
res		dd		?
factor	dd		?
.CODE
;-----------Function definitions--------------------
@isSolution@8 PROC
	mov eax, ecx
	mov ecx, edx
	mov factor, 2
	imul factor
	mov res, eax
	mov eax, ecx
	mov factor, 3
	imul factor
	add eax, res
	cmp eax, 50
	jne _else
	mov eax, 1
	jmp _end
	_else:
	mov eax, 0
	_end:
	ret 
@isSolution@8 ENDP
END
 