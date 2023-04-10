;******************************* ˜˜˜˜˜˜˜˜˜˜˜˜˜˜˜ ˜˜˜˜˜˜˜˜
;S!PISADR			1+		'C:\FASM\BIBLMCN\STRUCNST\S!PISADR.inc'
;+++++++++++++++++++++++++++++++	
;'C:\FASM\BIBLMCN\STRUCNST\S!PISADR.inc'
;˜˜˜˜˜˜ ˜˜˜˜ ˜˜˜˜˜˜˜˜ ˜˜˜˜˜˜˜˜ ˜˜˜˜˜˜ ˜˜˜˜˜
;˜˜˜˜˜ ˜˜˜˜˜˜ ˜ ˜˜˜˜˜˜  Metka ˜˜˜˜ ˜˜˜˜˜˜ ˜˜˜˜˜˜˜˜ ˜ ˜˜˜˜˜˜˜˜˜˜˜˜˜˜ ˜˜˜˜˜˜˜
;˜˜˜˜˜˜˜˜ ˜˜˜˜˜˜˜˜˜˜˜˜˜˜ ˜˜˜˜˜˜˜-˜˜˜˜˜˜˜˜˜˜˜˜˜ ˜˜˜˜˜ ˜˜˜˜˜˜˜˜˜˜ ˜˜ ˜˜˜˜˜˜ Metka-1 
;Metka	S!PISADR S1,S2,S3,S4,S5,S6,S7,S8,S9,S10,S11,S12,S13,S14,S15,S16,S17,S18,S19,S20\
;		S21,S22,S23,S24,S25,S26,S27,S28,S29
;˜˜˜ include 'C:\FASM\WATER\Nsin.inc';˜˜˜˜˜˜˜ ˜˜˜˜˜˜˜˜ sin ˜˜ ˜˜˜-˜˜ ˜˜˜˜˜˜˜˜
;*******************************
	struc S!!PISADR [string]	; ˜˜˜ ˜˜˜˜˜˜˜  S!PISADR	Metka,[string]
     {     common
							;local RMet
RMet = 0					;˜˜˜˜˜˜˜ ˜˜˜˜˜ ˜˜˜˜˜˜˜˜˜
offs = $-$$
	db	RMet				;˜˜˜-˜˜ ˜˜˜˜˜˜˜˜ ˜˜˜˜˜˜ ˜˜˜˜˜˜˜˜˜˜
;+++++++++++++++++
		forward				; ˜˜˜˜˜ ˜˜˜˜˜˜˜ string ˜˜ ˜˜˜-˜˜ ˜˜˜˜˜˜˜˜˜˜
	dd	string				;˜˜˜˜˜˜˜˜˜˜˜˜ ˜˜˜˜˜˜˜˜ ˜˜˜˜˜˜˜˜ ˜˜˜ 32 ˜˜˜˜˜˜˜˜˜˜ ˜˜˜˜˜˜
RMet = RMet+1 
	common
	db	RMet				;load char byte from $$+offs1+(%-1)+1 ;db	charchar=RMet
store byte char at $$+offs-(%-1)-1		;-(4*RMet+2)˜˜˜˜˜˜˜˜˜˜˜ ˜˜˜˜˜˜˜˜˜˜˜˜˜˜˜ ˜˜˜˜˜
    }
;*******************************
;S!PISADR SALL,S1,S2,S3,S4,S5,S6,S7,S8,S9,S10,S11,S12,S13,S14,S15,S16,S17,S18,S19,S20\
;		S21,S22,S23,S24,S25,S26,S27,S28,S29
;*******************************
;************************  1 ˜˜˜˜˜˜˜˜˜  *****************
	struc S!PISADR [string]	; ˜˜˜ ˜˜˜˜˜˜˜  S!PISADR	Metka,[string]
     {     common
	local RMet
RMet = 0					;˜˜˜˜˜˜˜ ˜˜˜˜˜ ˜˜˜˜˜˜˜˜˜
offsik = $-$$
offs=offsik
	db	RMet				;˜˜˜˜˜˜˜˜˜˜˜˜ store ˜˜˜-˜˜ ˜˜˜˜˜˜˜˜ ˜˜˜˜˜˜ ˜˜˜˜˜˜˜˜˜˜
;+++++++++++++++++
		forward				; ˜˜˜˜˜ ˜˜˜˜˜˜˜ string ˜˜ ˜˜˜-˜˜ ˜˜˜˜˜˜˜˜˜˜
	dd	string				;˜˜˜˜˜˜˜˜˜˜˜˜ ˜˜˜˜˜˜˜˜ ˜˜˜˜˜˜˜˜ ˜˜˜ 32 ˜˜˜˜˜˜˜˜˜˜ ˜˜˜˜˜˜
RMet = RMet+1
	common
offs1 = $-$$	
	db	RMet				;
	load char byte from $$+offs1 	;db	charchar=RMet
	store byte char at $$+offs		;-(4*RMet+2)˜˜˜˜˜˜˜˜˜˜˜ ˜˜˜˜˜˜˜˜˜˜˜˜˜˜˜ ˜˜˜˜˜
    }
;˜˜˜ include 'C:\FASM\WATER\Nsin.inc';˜˜˜˜˜˜˜ ˜˜˜˜˜˜˜˜ sin ˜˜ ˜˜˜-˜˜ ˜˜˜˜˜˜˜˜
;*****************************************************************************
	