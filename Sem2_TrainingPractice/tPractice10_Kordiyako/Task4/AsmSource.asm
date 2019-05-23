.386
.MODEL FLAT
.DATA?
m_left		dd		?
m_right		dd		?
m_result	dd		?
n			dd		?
m			dd		?
k			dd		?
.CODE
;-----------Function definitions--------------------

_multiplyMatrices PROC
	push ebp
	mov ebp, esp
	mov m_left, [ebp+8] 
	mov m_right, [ebp+12]
	mov m_left, [ebp+16]
	mov n, [ebp+20]
	mov m, [ebp+24]
	mov k, [ebp+28]

	pop ebp
	ret
_multiplyMatrices ENDP
END
 