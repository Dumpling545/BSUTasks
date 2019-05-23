.386
.MODEL FLAT
.DATA?
var1		dd		?
.DATA
var2		dd		?
.CODE
;-----------Function definitions--------------------
@swapWords_fastcall@8 PROC
	;move value from address ecx[first word] into eax 
	mov eax,[ecx]
	;exchange values between eax and value at adress edx[second word]
	xchg eax,[edx]    
	;move value from eax to adress ecx[first word]
	mov [ecx],eax
	ret
@swapWords_fastcall@8 ENDP

_swapWords_stdcall@8 PROC
	push ebp  
	mov ebp,esp  
	mov esi,[ebp+8] 
	mov edi,[ebp+12] 
	mov eax,[esi]  
	xchg eax,[edi]    
	mov [esi],eax  
	pop ebp  
	ret 8
_swapWords_stdcall@8 ENDP

_swapWords_cdecl PROC
	push ebp  
	mov ebp,esp  
	mov esi,[ebp+8] 
	mov edi,[ebp+12] 
	mov eax,[esi]  
	xchg eax,[edi]    
	mov [esi],eax  
	pop ebp  
	ret 
_swapWords_cdecl ENDP
END
 