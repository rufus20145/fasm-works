;*******************************************
;spisadd
;stradd
;L!!EXM
;*******************************************
 macro spisadd	list,item
     {	match ane,item				
\{
       match any, list \\{ list equ list,item \\}
       match , list \\{ list equ item \\}
\}
     }
;*********************************************************
	macro stradd	list,item
     {	match ane,item				
\{	
       match any, list \\{ list equ  \\}		;Обнуляем list
       match , list \\{ list equ item \\}		;Добавляем
\}
     }
;*********************************************************
	MACRO	 L!!EXM	PP_1,P_2,P_1,P_0			;\Pk,P$k
{	P_0	equ
	P_1	equ
	P_2	equ
	match P$k =) =( S$k ==> PP_2,PP_1
\{		\spisadd	list,\P$k			;занесли 1 параметр
		\spisadd	list,\S$k			;занесли 1 параметр
	stradd	PP_1,\PP_2
\P!k	equ	
			match P!i =) =( S!i ==> P!k,\PP_2 
			\\{	stradd	P_2,\\P!k
			stradd	P_1,\\S!i
			stradd	P_0,\\P!i	\\}										
\}
}