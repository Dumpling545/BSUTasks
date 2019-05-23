.386
.MODEL FLAT
.DATA
.CODE
;-----------Function definitions--------------------
@Sum@8 PROC
	mov eax,ecx   
	add eax, edx
	ret
@Sum@8 ENDP

@Subtraction@8 PROC
	mov eax,ecx   
	sub eax, edx
	ret
@Subtraction@8 ENDP

@Multiplication@8 PROC
	mov eax,ecx 
	imul edx
	ret
@Multiplication@8 ENDP

@Division@8 PROC
	mov eax,ecx 
	mov ecx,edx 
	cdq
	idiv ecx   
	ret
@Division@8 ENDP

@Remainder@8 PROC
	mov eax,ecx 
	mov ecx,edx 
	cdq
	idiv ecx   
	mov eax, edx
	ret
@Remainder@8 ENDP
END
 