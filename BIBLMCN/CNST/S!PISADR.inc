;******************************* Структуризаторы массивов
;S!PISADR			1+		'C:\FASM\BIBLMCN\STRUCNST\S!PISADR.inc'
;+++++++++++++++++++++++++++++++	
;'C:\FASM\BIBLMCN\STRUCNST\S!PISADR.inc'
;Список имен массивов констант разной длины
;ѕосле списка с меткой  Metka идет массив констант с перечисленными именами
;Возможно контролировать регистр-переключатель через содержимое по адресу Metka-1 
;Metka	S!PISADR S1,S2,S3,S4,S5,S6,S7,S8,S9,S10,S11,S12,S13,S14,S15,S16,S17,S18,S19,S20\
;		S21,S22,S23,S24,S25,S26,S27,S28,S29
;для include 'C:\FASM\WATER\Nsin.inc';ТАБЛИЦы значений sin по кол-ву отсчетов
;*******************************
	struc S!!PISADR [string]				; для макроса  S!PISADR	Metka,[string]
     {     common
							;local RMet
RMet = 0					;счетчик числа переходов
offs = $-$$
	db	RMet				;Кол-во согласно списка параметров
;+++++++++++++++++
		forward				; здесь выборка string по кол-ву параметров
	dd	string				;формирование адресных констант дл¤ 32 разр¤дного адреса
RMet = RMet+1 
	common
	db	RMet				;load char byte from $$+offs1+(%-1)+1 ;db	charchar=RMet
store byte char at $$+offs-(%-1)-1		;-(4*RMet+2) количество зафиксированных меток
    }
;*******************************
;S!PISADR SALL,S1,S2,S3,S4,S5,S6,S7,S8,S9,S10,S11,S12,S13,S14,S15,S16,S17,S18,S19,S20\
;		S21,S22,S23,S24,S25,S26,S27,S28,S29
;*******************************
;************************  1 Константы  *****************
	struc S!PISADR [string]				; для макроса  S!PISADR	Metka,[string]
     {     common
	local RMet
RMet = 0								;счетчик числа переходов
offsik = $-$$
offs=offsik
	db	RMet							;исправляется store Кол-во согласно списка параметров
;+++++++++++++++++
		forward							; здесь выборка string по кол-ву параметров
	dd	string							;формирование адресных констант дл¤ 32 разр¤дного адреса
RMet = RMet+1
	common
offs1 = $-$$	
	db	RMet				;
	load char byte from $$+offs1 		;db	charchar=RMet
	store byte char at $$+offs			;-(4*RMet+2) количество зафиксированных меток
    }
;для include 'C:\FASM\WATER\Nsin.inc'	;ТАБЛИЦы значений sin по кол-ву отсчетов
;*****************************************************************************