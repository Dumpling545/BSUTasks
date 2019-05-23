.386
.MODEL FLAT
.DATA?
a_1		dd		?
a_2		dd		?
.CODE
;-----------Function definitions--------------------
@Compute@4 PROC
	mov eax, ecx
	mov a_1, eax
	imul a_1
	mov a_2, eax
	imul a_2
	add eax, a_2
	add eax, 1
	imul a_1
	ret 
@Compute@4 ENDP
END
 