;1	E!ntryDll
;2  	ExDll							Макрос
;3	E!xDllC
;4	E!ntCDLL
;5	Ex!СDll
;*********************4*********
;Обращение:EntryDLL (ECX=[EBP+16]),(ESI=[EBP+12]),(EDI=[EBP+8])
				;Структурное преобразование ECX, PMem ==> PMemz, ECX длина
				;invoke	MOM,EDI,ESI,ECX
;*********************************
macro E!ntryDll	[arg]			;ВХОДНЫЕ ПАРАМЕТРЫ С++(pMmz,pMm,RSize)
	{		common					;EntryDLL
		PUSH	EBP
		mov	EBP,ESP
CrPUSH   EAX,EBX ,ECX,EDX,ESI,EDI	;cooтветствует	CrPOP
forward
	ReadOne	arg							;WriteOne
	}
;********************1*********************
;Обращение:E!xDllC	EAX,([EBP+16]=ECX),([EBP+12]=[pMm]), ([EBP+8]=[pMmz])  ;(EAX -значение - длина для C++)
;						               ExitDLL соответствует EntryDLL
;********************1*********************
MACRO ExDll	[arg]
	{
	forward
	WriteOne	arg
common
			CrPOP   EAX,EBX ,ECX,EDX,ESI,EDI	;cooтветствует  CrPUSH
		mov	ESP,EBP
		POP	EBP
	}
;*******************2**  конец ExDLL	для procDLL   pMmz,pMm,FlSizpMmz
;Обращение:Ex!DllC	EAX,([EBP+16]=ECX),([EBP+12]=[pMm]), ([EBP+8]=[pMmz])  ;(EAX -значение - длина для C++)
;						               ExitDLL соответствует EntryDLL
MACRO Ex!DllC	SRC,REAX,[arg]
	{
	forward
	WriteOne	arg
common
			CrPOP   EAX,EBX,ECX,EDX,ESI,EDI	;cooтветствует  CrPUSH
	mov	REAX,SRC		;[EBP+8]	;Длина [pMmz] для C++ т.к. ЕAX - значение,   ESI - адрес
		mov	ESP,EBP
		POP	EBP
	}
;**********************************
;4	E!ntCDLL
;++++++++++++++
MACRO E!ntCDLL	[arg]		;ВХОДНЫЕ ПАРАМЕТРЫ как С++(pMmz,pMm,RSize)
	{		common					;EntryDLL
		PUSH	EBP
		mov	EBP,ESP
 CrPUSH   EBX,ECX,EDX,ESI,EDI		;EAX  не упрятываем cooтветствует	CrPOP
forward
	ReadOne	arg						;WriteOne
	}
;**********************************
;5	Ex!СDll
;++++++++++++++
MACRO Ex!CDll	[arg]
	{
forward
	WriteOne	arg
common
			CrPOP   EBX,ECX,EDX,ESI,EDI		;cooтветствует  CrPUSH
							;mov	REAX,SRC;[EBP+8];Длина [pMmz] для C++ т.к. ЕAX - значение,   ESI - адрес
		mov	ESP,EBP
		POP	EBP
	}
