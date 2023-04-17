;1	m!s

;************** Макроопределения форирования двух битовой матрицы  для 32 разядного слова -  dd ****************
;		МАКРОС  1  - формирования одной строки с разделителем "+"
macro m!s arg
{
common match a,arg
\{					\arg1	equ	\`a
\NMRuu	equ	1
match aww=+ww,\arg1
\\{	\\NMRuu	equ	0\\}
if	\NMRuu	eq	1
					;Print!afall   \NMRuu
		db	a,0,0,0		; xor 0FFh		;одно поле
end if
\}
;************************
common match a=+b,arg
  \{					\arg1	equ	\`a#\`b		;#\`c#\`d#`b
\NMRuu	equ	1
match aww=+ww,\arg1
\\{	\\NMRuu	equ	0\\}
if	\NMRuu	eq	1
					;Print!afall   \NMRuu
	 	db	a shl 2 or b,0,0,0		; xor 0FFh				;2 поле
end if
     \}
;**************************
common match a=+b=+c,arg
  \{					\arg1	equ	\`a#\`b#\`c
\NMRuu	equ	1
match aww=+ww,\arg1
\\{	\\NMRuu	equ	0\\}
if	\NMRuu	eq	1
							;Print!afall   \NMRuu
 	 	db	a shl 4 or b shl 2 or c,0,0,0 		;xor 0FFh		;3 поля
end if
     \}
;*************************************
match a=+b=+c=+d,arg
  \{					\arg1	equ	\`a#\`b#\`c#\`d
\NMRuu	equ	1
match aww=+ww,\arg1
\\{	\\NMRuu	equ	0\\}
if	\NMRuu	eq	1
							;Print!afall   \NMRuu
	 	db	a shl 6 or b shl 4 or c shl 2 or d,0,0,0	 ;xor 0FFh	;4 поля
end if
     \}
;**************************
match a=+b=+c=+d=+ e,arg
  \{					\arg1	equ	\`a#\`b#\`c#\`d#\`e
\NMRuu	equ	1
match aww=+ww,\arg1
\\{	\\NMRuu	equ	0\\}
if	\NMRuu	eq	1
							;Print!afall   \NMRuu
    db	b shl 6 or c shl 4 or d shl 2 or e,\
	a,\
	0,0				; xor 0FFh	;5
end if
     \}
;**************************
match a=+b=+c=+d=+ e=+f,arg
  \{					\arg1	equ	a#\`b#\`c#\`d#\`e#\`f
\NMRuu	equ	1
match aww=+ww,\arg1
\\{	\\NMRuu	equ	0\\}
if	\NMRuu	eq	1
   db	c shl 6 or d shl 4 or e shl 2 or f,\
	a shl 2 or b	,\
	0,0		;6
end if
     \}
;**************************
match a=+b=+c=+d=+ e=+f=+g,arg
  \{					\arg1	equ	\`a#\`b#\`c#\`d#\`e#\`f#\`g
\NMRuu	equ	1
match aww=+ww,\arg1
\\{	\\NMRuu	equ	0\\}
if	\NMRuu	eq	1
									;Print!afall   \NMRuu
   db	d shl 6 or e shl 4 or f shl 2 or g,\
	a shl 4 or b shl 2 or c,\
	0,0				;7
end if
     \}
;***********************
match a=+b=+c=+d=+ e=+f=+g=+ h,arg
  \{					\arg1	equ	\`a#\`b#\`c#\`d#\`e#\`f#\`g#\`h
\NMRuu	equ	1
match aww=+ww,\arg1
\\{	\\NMRuu	equ	0\\}
if	\NMRuu	eq	1
									;Print!afall   \NMRuu
	 	db	e shl 6 or f shl 4 or g shl 2 or h,\
			a shl 6 or b shl 4 or c shl 2 or d,0,0	;8
end if
     \}
;***********************
match a=+b=+c=+d=+ e=+f=+g=+ h=+i,arg
  \{					\arg1	equ	\`a#\`b#\`c#\`d#\`e#\`f#\`g#\`h#\`i
\NMRuu	equ	1
match aww=+ww,\arg1
\\{	\\NMRuu	equ	0\\}
if	\NMRuu	eq	1
    db	f shl 6 or g shl 4 or h shl 2 or i,\
	b shl 6 or c shl 4 or d shl 2 or e,\
	a,\
	0		;9
end if
     \}
;***********************
match a=+b=+c=+d=+ e=+f=+g=+ h=+i=+ j,arg
  \{						\arg1	equ	\`a#\`b#\`c#\`d#\`e#\`f#\`g#\`h#\`i#\`j
\NMRuu	equ	1
match aww=+ww,\arg1
\\{	\\NMRuu	equ	0\\}
if	\NMRuu	eq	1
									;Print!afall   \NMRuu
   db	g shl 6 or h shl 4 or i shl 2 or j,\
	c shl 6 or d shl 4 or e shl 2 or f,\
	a shl 2 or b	,\
	0		;10
end if
     \}
;****************************
;***********************
match a=+b=+c=+d=+ e=+f=+g=+ h=+i=+ j=+ k,arg
  \{\arg1	equ	\`a#\`b#\`c#\`d#\`e#\`f#\`g#\`h#\`i#\`j#\`k
\NMRuu	equ	1
match aww=+ww,\arg1
\\{	\\NMRuu	equ	0\\}
if	\NMRuu	eq	1
									;Print!afall   \NMRuu
 db	h shl 6 or i shl 4 or j shl 2 or k,\
	d shl 6 or e shl 4 or f shl 2 or g,\
	a shl 4 or b shl 2 or c,\
	0			;11
end if
     \}
;****************************
;***********************
match a=+b=+c=+d=+ e=+f=+g=+ h=+i=+ j=+ k=+ l,arg
  \{						\arg1	equ	\`a#\`b#\`c#\`d#\`e#\`f#\`g#\`h#\`i#\`j#\`k#\`l
\NMRuu	equ	1
match aww=+ww,\arg1
\\{	\\NMRuu	equ	0\\}
if	\NMRuu	eq	1
									;Print!afall   \NMRuu
 db	i shl 6 or j shl 4 or k shl 2 or l,\
	e shl 6 or f shl 4 or g shl 2 or h,\
	a shl 6 or b shl 4 or c shl 2 or d,\
	0			;12
end if
     \}
;****************************
;***********************
match a=+b=+c=+d=+ e=+f=+g=+ h=+i=+ j=+ k=+ l=+ m,arg
  \{				\arg1	equ	\`a#\`b#\`c#\`d#\`e#\`f#\`g#\`h#\`i#\`j#\`k#\`l#\`m
\NMRuu	equ	1
match aww=+ww,\arg1
\\{	\\NMRuu	equ	0\\}
if	\NMRuu	eq	1
									;Print!afall   \NMRuu
 db	j shl 6 or k shl 4 or l shl 2 or m,\
	f shl 6 or g shl 4 or h shl 2 or i,\
	b shl 6 or c shl 4 or d shl 2 or e,\
	a			; shl 6 or b shl 4 or c shl 2 or d		;13
end if
     \}
;****************************
match a=+b=+c=+d=+ e=+f=+g=+ h=+i=+ j=+ k=+ l=+ m=+ n,arg
  \{					\arg1	equ	\`a#\`b#\`c#\`d#\`e#\`f#\`g#\`h#\`i#\`j#\`k#\`l#\`m#\`n
\NMRuu	equ	1
match aww=+ww,\arg1
\\{	\\NMRuu	equ	0\\}
if	\NMRuu	eq	1
									;Print!afall   \NMRuu
 db	k shl 6 or l shl 4 or m shl 2 or n,\
	g shl 6 or h shl 4 or i shl 2 or j,\
	c shl 6 or d shl 4 or e shl 2 or f,\
	a shl 2 or b			;14
end if
     \}
;****************************
match a=+b=+c=+d=+ e=+f=+g=+ h=+i=+ j=+ k=+ l=+ m=+ n=+ o,arg
  \{				\arg1	equ	\`a#\`b#\`c#\`d#\`e#\`f#\`g#\`h#\`i#\`j#\`k#\`l#\`m#\`n#\`o
\NMRuu	equ	1
match aww=+ww,\arg1
\\{	\\NMRuu	equ	0\\}
if	\NMRuu	eq	1
									;Print!afall   \NMRuu
 db	l shl 6 or m shl 4 or n shl 2 or o,\
	h shl 6 or i shl 4 or j shl 2 or k,\
	d shl 6 or e shl 4 or f shl 2 or g,\
	a shl 4 or b shl 2 or c				;15
end if
     \}
;****************************
match a=+b=+c=+d=+ e=+f=+g=+ h=+i=+ j=+ k=+ l=+ m=+ n=+ o=+ p,arg
  \{			\arg1	equ	\`a#\`b#\`c#\`d#\`e#\`f#\`g#\`h#\`i#\`j#\`k#\`l#\`m#\`n#\`o#\`p
\NMRuu	equ	1
match aww=+ww,\arg1
\\{	\\NMRuu	equ	0\\}
if	\NMRuu	eq	1
									;Print!afall   \NMRuu
     db  	m shl 6 or n shl 4 or o shl 2 or p,\
	i shl 6 or j shl 4 or k shl 2 or l,\
	e shl 6 or f shl 4 or g shl 2 or h,\
	a shl 6 or b shl 4 or c shl 2 or d 				;16
end if
     \}
}
;******************для 32 разрядов и 16 полей*****m!s**
;		МАКРОС  2  - формирование массива (матрицы) отношений, используя МАКРОС  1
;				но возможно записать 16 отношений для 17 точек
;			после массива байт длины массива (кол-во строк)
;************
;		ОБРАЩЕНИЕ:
;	m!sd  NICK,3+3+3+2+1+0+3+3,\
;		       3+3+3+2+1+0+3,\
;		           3+3+2+1+0+3,\
;		               3+2+1+0+3,\
;		                   2+2+1+0,\
;		                       3+1+0,\
;		                           2+1,\
;		            	             3
;		РЕЗУЛЬТАТ:
;		NICK	dd  ????????
;			. . . . .
;			dd   ?
;		NICK.pole	db  N	- кол-во строк
;		NICK.dlina=число занятых байт
;************m!sd  массив двойное слово******
macro m!sd metms,[arg]	;получение массива с меткой
 { common
Rswtch=0				;'0'  для печати   счетчик по числу строк
metms	db	'N'		;скобка N - обычный, D - 2-ая диагональ с > (2), O -2-ая диагональ с < (1)
forward
Rswtch = Rswtch+1   				;В зависимости от кол-ва переменных(строк) накапл.счетчик
	m!s arg
common				;display   Rswtch
        if	Rswtch >16
display 'NE:Number poley > 16',13,10
      else				;display 'Nn:';display 13,10
      end if
metms#.pole	db	Rswtch	;длина массива
	db	16		;количество точек, для которых устанавл. отношения
	dw	0		;порядковый номер в группе из 16 элементов
metms#.N	db	'N'
metms#.dlina=metms#.N-metms		;общая длина матрицы
metms#.dlinm=metms#.pole-metms	;длина матрицы

}
;************КОНЕЦ	m!sd  массив двойное слово  ***********
;		МАКРОС  3  - формирование массива (матрицы) отношений, используя МАКРОС  1
;			но возможно записать 17 отношений для 18 точек, мнимая диагональ начинается <
;			после массива байт длины массива (кол-во строк)+ "<"shl 6
;***
;		ОБРАЩЕНИЕ:
;	m!sd1 NICK,3+3+3+2+1+0+3+3,\
;		       3+3+3+2+1+0+3,\
;		           3+3+2+1+0+3,\
;		               3+2+1+0+3,\
;		                   2+2+1+0,\
;		                       3+1+0,\
;		                           2+1,\
;		            	             3
;		РЕЗУЛЬТАТ:
;		NICK	dd  ????????
;			. . . . .
;			dd   ?
;		NICK.pole	db  N	- кол-во строк +2 shl 6
;		NICK.dlina=число занятых байт
;************m!sd1  массив двойное слово******
macro m!sd1 metms,[arg]		;получение массива с меткой
 { common
Rswtch=0				;'0'  для печати   счетчик по числу строк
metms	db	'O'		;скобка N - обычный, D - 2-ая диагональ с > (2), O -2-ая диагональ с < (1)
forward
Rswtch = Rswtch+1   				;В зависимости от кол-ва переменных накапл.счетчик
	m!s arg
common
        if	Rswtch >16
		display 'NE:Number poley > 16',13,10
      else
      end if
metms#.pole	db	1 shl 7 or Rswtch	;длина массива
	db	16		;количество точек, для которых устанавл. отношения
	dw	0		;порядковый номер в группе из 16 элементов
metms#.N	db	'O'
metms#.dlina=metms#.N-metms		;общая длина матрицы
metms#.dlinm=metms#.pole-metms	;длина матрицы

}
;************m!sd1  массив двойное слово***********
;************m!sd2 массив двойное слово******
;		МАКРОС  4  - формирование массива (матрицы) отношений c меткой , используя МАКРОС  1
;			но возможно записать 17 отношений для 18 точек, мнимая диагональ начинается >
;			после массива байт длины массива (кол-во строк)+ ">"shl 6
;***
;		ОБРАЩЕНИЕ:
;	m!sd2 NICK,3+3+3+2+1+0+3+3,\
;		       3+3+3+2+1+0+3,\
;		           3+3+2+1+0+3,\
;		               3+2+1+0+3,\
;		                   2+2+1+0,\
;		                       3+1+0,\
;		                           2+1,\
;		            	             3
;		РЕЗУЛЬТАТ:
;NICK	db	'D'	скобка  закрывающая
;			dd  ????????	|		  1
;			. . . . . 		|  матрица отношений  i
;			dd   	  ?	|		   N - размерность матрицы
;NICK.pole	db	N	;- кол-во строк +0 shl 6
;	db	K		;количество точек, для которых устанавл. отношения K=N+1
;	dw	JJ		;порядковый номер в группе из 16 элементов
;		NICK.dlina=число занятых байт
;NICK.kon	db	'D'	скобка  закрывающая
;NICK.dlina=1(0 байт)+N+1(NICK.pole)+1(K)+2(JJ)+1(NICK.kon)
;***********************************
	MACRO	ТреугольнаяМатрица	[arg]
{m!sd2 metms,[arg]}
;**************************
macro m!sd2 metms,[arg]		;получение массива с меткой
 { common
Rswtch=0				;'0'  для печати   счетчик по числу строк
metms	db	'D'		;скобка N - обычный, D - 2-ая диагональ с > (2), O -2-ая диагональ с < (1)
forward
Rswtch = Rswtch+1   			;В зависимости от кол-ва переменных накапл.счетчик
	m!s arg
common
        if	Rswtch >16
display 'NE:Number poley > 16!!',13,10
      else
      end if
metms#.pole	db	1 shl 7 or Rswtch	;длина массива
	db	16		;количество точек, для которых устанавл. отношения
	dw	0		;порядковый номер в группе из 16 элементов
metms#.N	db	'D'
metms#.dlina=metms#.N-metms		;общая длина матрицы
metms#.dlinm=metms#.pole-metms	;длина матрицы
}
;************m!sd1  массив двойное слово***********


