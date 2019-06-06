.386
.MODEL FLAT
.DATA?
 k		dd			?
 sum	REAL4		?
 addend	REAL4		?
.DATA
four	REAL4		4.0
one		REAL4		1.0
half	REAL4		0.5
.CODE
;-----------Function definitions--------------------
_compute_addend PROC
	fild k
	fimul k
	fmul four
	fsub one
	fimul k
	fdivr one
	fstp addend
	ret
_compute_addend  ENDP

@compute_sum@4 PROC
	mov k, 1
	fldz
	fstp sum
	loop_begin:
		call _compute_addend
		fld sum
		fadd addend
		fstp sum
		inc k
		cmp k, ecx
		jle loop_begin
	ret
@compute_sum@4  ENDP
@compute_ln_2@4 PROC
	call @compute_sum@4
	fld sum
	fadd one
	fmul half
	ret
@compute_ln_2@4 ENDP
@const_ln_2@0 PROC
	fldln2
	ret
@const_ln_2@0 ENDP
END
 