;	1 SDfCntAdB
;	2 SDfCntAdBM
;	3 ОтладочныеГрупповыеКонстантыBПод_Именем
;************************ Специальные константы для отладки
MACRO SDfCntAdB  	SGroppa,Spis
{common
		db	'b'						;тип данных байт
match  nn (nnm == nm2),SGroppa Spis ; nma='PR'  nma1=f  nma2=0
 \{\label	\nnm	\dword			;короткая метка nnm
\nn\#\nnm\#_d	db	\nm2			;длинное имя константы	\nn\#\nnm\#_b
		db	"$"\#\`nn				;,32\nnm\#\uuu
		db	\`nnm\#"$"
		db	" = "\#\`nm2			;значение в текстовом виде
\nnm#.size=1						;размерность операнда тип=1 т.е. 1 байт
 \}
}
;************************************
MACRO SDfCntAdBM	SGroppa,[Spisok]
 {forward
	SDfCntAdB	SGroppa,Spisok
}
;************************************
;*******************	Специальные отладочные константы для отладки
MACRO ОтладочныеГрупповыеКонстантыBПод_Именем  	SGroppa,[Spisok]
{forward
	SDfCntAdB	SGroppa,Spisok
}