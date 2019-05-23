.386
.MODEL FLAT
.DATA?
temp		dd		?
short_temp	word	?
.CODE
;-----------Function definitions--------------------
@computeX_fastcall@8 PROC
	;compare a(ecx) and b(edx)
	cmp ecx, edx
	jl less
	je equal
	jg greater
	jmp return
	;if a < b
	less:
		; compute result of <b / (a + 1)> in eax
		mov eax, edx
		add ecx, 1
		cdq
		idiv ecx
		jmp return
	;if a = b
	equal:
		; move 4 in eax
		mov eax, 4
		jmp return
	;if a > b
	greater:
		; compute result of <(a^3 - 5) / b> in eax
		mov temp, edx
		mov eax, ecx
		imul ecx
		imul ecx
		sub eax, 5
		cdq
		idiv temp
	return:
	ret
@computeX_fastcall@8 ENDP

_computeX_stdcall@8 PROC
	push ebp
	mov ebp, esp
	mov ecx, [ebp + 8]
	mov edx, [ebp + 12]
	cmp ecx, edx
	jl less
	je equal
	jg greater
	jmp return
	less:
		mov eax, edx
		add ecx, 1
		cdq
		idiv ecx
		jmp return
	equal:
		mov eax, 4
		jmp return
	greater:
		mov temp, edx
		mov eax, ecx
		imul ecx
		imul ecx
		sub eax, 5
		cdq
		idiv temp
	return:
	pop ebp
	ret 8
_computeX_stdcall@8 ENDP

_computeX_cdecl PROC
	push ebp
	mov ebp, esp
	mov ecx, [ebp + 8]
	mov edx, [ebp + 12]
	cmp ecx, edx
	jl less
	je equal
	jg greater
	jmp return
	less:
		mov eax, edx
		add ecx, 1
		cdq
		idiv ecx
		jmp return
	equal:
		mov eax, 4
		jmp return
	greater:
		mov temp, edx
		mov eax, ecx
		imul ecx
		imul ecx
		sub eax, 5
		cdq
		idiv temp
	return:
	pop ebp
	ret
_computeX_cdecl ENDP

@short_computeX_fastcall@8 PROC
	cmp cx, dx
	jl less
	je equal
	jg greater
	jmp return
	less:
		mov ax, dx
		add cx, 1
		cwd
		idiv cx
		jmp return
	equal:
		mov ax, 4
		jmp return
	greater:
		mov short_temp, dx
		mov ax, cx
		imul cx
		imul cx
		sub ax, 5
		cwd
		idiv short_temp
	return:
	ret
@short_computeX_fastcall@8 ENDP
END
 