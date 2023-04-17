;Блок макросов ОБНУЛЕНИЯ   ZeroReg
;Список
;1.ОбнулитьРегистры [Список]
;2 Z!eroReg	[Список]
;3.Z!eroMas	[Список]
;ZeroReg	        ОбнулитьРегистры O!bnulR Z!eroReg
;*****************************
	MACRO	ОбнулитьРегистры [Reg]
	{forward
		XOR	Reg,Reg
	}
;************			Макро для обнуления списка регистров ZiroReg
MACRO	O!bnulR	[Reg]
	{forward
		XOR	Reg,Reg
	}
;*******************
MACRO	Z!eroReg	[Reg]
	{forward
		XOR	Reg,Reg
	}
;*************  Рбнуление массива
	MACRO	Z!eroMas	P1,P2
	{
					push	ECX
		mov 	ECX,[P2]			;[FlSizeW]
		mov		EDI,[P1]
		mov		al,0
	rep	stosb
		pop		ECX
	}