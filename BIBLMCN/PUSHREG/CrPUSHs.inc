
;*********************7 ***PUSHе ******
;				Маркировочное упрятывание. ПРИМЕР:  PUSHе  EBP,1
;					           Появляется константа EBP1
;				Можно PUSHе  EBP,one  ==> константа EBPone
 	MACRO	PUSHе	 RE,t_t1	;упрятывание регистра и формирование константы под именем REt_t1
{	push	RE
RE#t_t1	equ	t_t1				;Появление константы
}
;********************************************
;**********************8**POPe	 RE,t_t1
;				Маркировочное восстановление из стека
 	MACRO	POPe	 RE,t_t1	;упрятали указатель на стек под именем t_t1
{	if  ~ defined	RE#t_t1			;если упрятывание с такой маркировкой не проходило
		display	"NE:  REG " # `RE
		display	`t_t1 # " not push"		;регистр не упрятывался
		Restore	RE#t_t1
		display 13,10
	else
	pop	RE
	end if
  }
;************************3********************
;**********************  9 *****Упрятывание с контролем во время трансляции**********
MACRO	CrPUSHs	[string]			;A C D B   нумерация регистров
     {
     common
	forward
Rpushpop = Rpushpop+1  			;local label
	PUSH	string
    common					; label db string,0
}
;***********************   10  ***************
MACRO	CrPOPs	[string]
     {
     common
	reverse
Rpushpop = Rpushpop-1
	POP	string
    common
}
;************************	11  CrPUSHе ******
;				Маркировочное упрятывание. ПРИМЕР:  CrPUSHе  1,EBP
;					           Появляется константа 1EBP
;				Можно CrPUSHе  one,EBP  ==> константа oneEBP
;SpisokSteka	equ
;**********************************************************
 	MACRO	CrPUSHе	prefix,[RE]	;упрятывание регистра и формирование константы под именем REt_t1
{common
 	PutSpisok	SpisokSteka,prefix#RE	;Запись упрятывающая уникальное имя регистра
forward
Rpushpop = Rpushpop+1  		;local label
	push	RE
}
;*****************************************
;********************** 12  **	CrPOPe	 t_t1,EAX  t_t1EAX
;				Маркировочное восстановление из стека
 	MACRO	CrPOPe	prefix, [RE]			;упрятали указатель на стек под именем t_t1
{
reverse
	if  ~ defined	prefix#RE		;если упрятывание с такой маркировкой не проходило
		display	"NE:  prefix" # `RE
		display	`prefix # " not push"		;регистр не упрятывался через группу
		display 13,10
	else
common
Restore	prefix#RE
	end if
Rpushpop = Rpushpop-1
	pop	RE
  }
;*******************************************