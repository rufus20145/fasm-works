;	l!strlen				1+	'C:\FASM\BIBLMCN\lstrlen.inc'
;	УстановитьДлинуСтроки	2*	'C:\FASM\BIBLMCN\lstrlen.inc'
;****************************************************************************************
;	Синтаксическая конструкция
macro 	УстановитьДлинуСтроки	arg
{	common match	!adr==MAS  !len==CALC,arg
	\{
			l!strlen	MAS,CALC
	\}
		common match	!bl==  !bh==,arg
		\{
					l!strlen	ESI,EAX
		\}
		common match	,arg
		\{
					l!strlen	ESI,EAX
		\}
}
;*********************************************
macro l!strlen	arg1, arg2	; D!LString
{
if	~arg2	in 	<EAX>		;Если это не EAX то ничего не делаем
				push	EAX
else
end if
		xor	EAX,EAX
@@:
	if	~arg1	in   <ESI>			;Если это не ESI то
			xor	[arg1+EAX],0		;lodsb
			inc	EAX					;and	al,-1
		jnz	@b
	else
		xor	[ESI+EAX],0				;lodsb
		inc	EAX						;and	al,-1
	jnz	@b
	end if
if	~arg2	in 	<EAX>				;Если это EAX то ничего не делаем
			mov	arg2, EAX			; arg2= EAX
				pop	EAX
else
end if
}
;*********************  24 строки  4 команды минимум  7 команд максимум
