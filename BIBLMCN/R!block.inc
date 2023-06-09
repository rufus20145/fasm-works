;	R!block			1+				;создать блок в англ.в-те
;	W!riteRingBloc	2*
;	Запись_в_Блок	3*
;	СоздатьБлок		4*
;*******************************  1
; МАКРОС Формирования участка программы для заполнения БЛОКА памяти
;Пример обращения:
;	R!block	Nick,4,1,4		;Вызов для формирования Блока массивов байтных
;	R!block	Nick1,8,2,6		;Вызов для формирования Блока массивов словных
;	СоздатьБлок	$ИмяБлока=Nick  $ЧислоЭлементов_в_Массиве=8\
;     $РазмерностьЭлемента_число_байт=2     $КоличествоМассивов_в_Блоке=4
;+++++++++++++++++++++++++++++++
MACRO R!block Name,m,t,N
{
	dd	Name				;ХранительУказателяНаМассив=[UKNom]

	if	t=1
label	Name	byte		;Метка Блока
times N db m  dup	(0)
	else
		if	t=2
label	Name	word		;Метка Блока
times N dw m  dup	(0)
			;Print!Rfall   "Это задается блок массивов словных!"
			;display 13,10
		else
			if	t=4
label	Name	dword		;Метка Блока
times N dd m  dup	(0)
			else
			Print!Rfall  "Формируем блоки только для байтных,словных и двухсловных массивов!"
			display 13,10
			end if
		end if
	end if
;****** Формирование меток привязанныз к имени массива
Name#_m=m					;Чисдо элементов в массивк
Name#_r=t					;t - тип 0= 1equ байт2  3-слово  4 двойное слово 5- 64 разряда
Name#_N=N					;N -Число массивов в БЛОКЕ
Name#_L=m*N*t  				;число элементов в БЛОКЕ
}
;************************************* 1
;************************************ 2
;WriteRingBloc	ESI,Nick;
;++++++++++++++++++++++++++++++++++++++
			macro W!riteRingBloc Inmas,Ni			;,OutMas,NMas,UkMas,Nelem
{
		УпряталиРегистры	ECX,EDI,ESI
			mov	ESI,Inmas				;InMas -Адрес входного массива
			mov ECX,Ni#_m				;Nick_m -Число элементов в массиве
			mov	EDI,dword [Ni-4]			;\Nick-4 -изменяемый указатель на массив
			If Ni#_r=1
			rep	movsb
			else
				If Ni#_r=2
				rep	movsw
				else
					If Ni#_r=4
					rep	movsd
					else
					end if
				end if
			end if
			mov	dword [Ni-4],EDI			;Изменяемое значение указателя на массив
			mov	ECX,Ni				;\Nick - Начало массивов в блоке
			sub	EDI,ECX					;
			cmp	EDI,Ni#_L				;Nick_L-Общая длина Блока
		jl	@F
			mov	dword [Ni-4],ECX
@@:
			ВосстановилиРегистры	ECX,EDI,ESI
}
;*********************************конец 2
;***********  3	Упрощенный вариант формирования цикла записи в кольцевой массив
;Запись_в_Блок 	$ИзМассивЧтения=INMAS $В_блок_закольцованный=Nick
;*************************************	3
MACRO Запись_в_Блок	arg
{
common	match $Имя_или_регистр_ВходногоМассива==Inmas  $ИмяБлока==Ni,arg
\{
		\W!riteRingBloc \Inmas,\Ni
\}
}
;********************************* конец 3
;*********************************		4
;ПРИМЕР:	СоздатьБлок	$ИмяБлока=Nick\
;								$ЧислоЭлементов_в_Массиве=8\
;								$РазмерностьЭлемента_в_байтах=2\
;								$КоличествоМассивов_в_Block=4
;+++++++++++++++++++++++++++++++++
MACRO СоздатьБлок	arg
	{
common	match $ИмяБлока==Ni  $ЧислоЭлементов==m $Размерностьв_байтах==t $КоличествоМассивов_в_Блоке==N ,arg
		\{
		\R!block \Ni,\m,\t,\N
		\}
}
;********************************* end 4
