.386
.MODEL FLAT
.DATA?
factor		dd		?
.CODE
;-----------Function definitions--------------------
@maxNotOversized@4 PROC
	mov eax, 1
	mov factor, ecx
	mov ecx, 0
	loop_start:
		mul factor
		jo loop_end
		add ecx, 1
		jmp loop_start
	loop_end:
	mov eax, ecx
	ret 
@maxNotOversized@4 ENDP
END
 