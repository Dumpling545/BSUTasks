.386
.MODEL FLAT
.DATA?
 _a			REAL4		?
 _b			REAL4		?
 _c			REAL4		?
 _x			REAL4		?
 c_x		REAL4		?
 f_x		REAL4		?
 left		REAL4		?
 right		REAL4		?
.DATA
 precision	REAL4		0.000001
 half		REAL4		0.5
 _null		REAL4		0.0
.CODE
;-----------Function definitions--------------------
_compute_func PROC
	fadd _a
	fmul c_x
	fadd _b
	fmul c_x
	fadd _c
	ret
_compute_func ENDP
_find_root PROC
	push ebp
	mov ebp, esp
	fld real4 ptr[ebp+8]
	fstp left
	fld real4 ptr[ebp+12]
	fstp right
	fld	real4 ptr[ebp+16]
	fstp _a
	fld	real4 ptr[ebp+20]
	fstp _b
	fld	real4 ptr[ebp+24]
	fstp _c
	loop_begin:
		fld left
		fadd right
		fmul half
		fst _x
		fst c_x
		call _compute_func
		fstp f_x
		fld left
		fst c_x
		call _compute_func
		fmul f_x
		fcom _null
		fstsw ax
		sahf
		fstp c_x
		je loop_end
		jnc change_left_begin
		jmp change_right_begin
		change_left_begin:
			fld _x
			fstp left
			jmp change_right_end
		change_left_end:
		change_right_begin:
			fld _x
			fstp right
		change_right_end:
		fld right
		fsub left
		fabs
		fcom precision
		fstsw ax
		sahf
		fstp f_x
		jnc loop_begin
	loop_end:
	fld _x
	pop ebp
	ret
_find_root ENDP
END
 