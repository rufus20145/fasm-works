;  �������� CONPRN   
;****************************  3    ****************
	macro	P!rTXTNUMBER	TEXT
{	local	Adruk,spsim,Pref,DlPref,FGH,Writed,Hconsl_d
@@:
	���������������	EBP,EAX,ECX,EDX	
;		mov	EBP,@B
	jmp	FGH		;�� ��������� �� ������ � EBP:  ������ ��������� � ����. ������ ����� 
Pref 	db	" "
	PRZN	equ	0
	common match  ==TXT TXT1 TXT2 TXT3,TEXT
\{
	db	" "\#\`TXT
	db	" "\#\`TXT1
	db	" "\#\`TXT2
	db	" "\#\`TXT3
	\PRZN	equ	1
	\}
	if	\PRZN eq 0
	common match  ==TXT TXT1 TXT2,TEXT
\{
	db	" "\#\`TXT
	db	" "\#\`TXT1
	db	" "\#\`TXT2
	\PRZN	equ	1
	\}
		if	\PRZN eq 0
	common match  ==TXT TXT1,TEXT
	\{
	db	" "\#\`TXT
	db	" "\#\`TXT1
	\PRZN	equ	1
	\}
			if	\PRZN eq 0
	match  ==TXT,TEXT
	\{
	db	" "\#\`TXT
	\}
			end if
		end if
	end if
	db	" "
Adruk	db	10	dup	('!')	; ��� ����� �������� 8 16-��� �����
spsim	db	0
Hconsl_d	dd	0
DlPref=spsim-Pref
Writed	dd	21
FGH:
;[���������  N16inASCII ECX,SPSTR,NUMBER] �� �������� ECX   ������ �������� SPSTR 16-��� �����
						;a���� ����������� ����� � ECX
		N!16inASCII	EBP,Adruk,8
	invoke	GetStdHandle, STD_OUTPUT_HANDLE
		mov	[Hconsl_d],eax

		mov	EAX,[Hconsl_d]
		mov	EDX,DlPref		;����� ���������
	invoke	WriteConsole,eax,Pref,edx,Writed,0
	�������������������   EBP,EAX,ECX,EDX
}
;**********************************  4     *******************
	macro	P!rAdr	Hconsl,BufPrint,TEXT,adr		;TEXT="NE:A"
{			local	FGH,Pref
@@:
	���������������   EBP,EAX,ECX,ESI,EDI 
		if ~adrDll eq
		mov	EBP,@B			;���� �� ������ �����
		else
		mov	EBP,adr			;����� ����� ��������� � ������
		end if
	jmp	FGH					;�� ���������: ����� �� ������� ������� ��� ��� �� 10-�� �����
Pref	db	TEXT
		db	0

FGH:
DlPref=FGH-Pref
	mov	ECX,DlPref			;���-�� ��������
	mov	ESI,Pref			;����� ��������
	mov	EDI,BufPrint		;����� ������  ������� ����������� ������
@@:
	LODSB
	STOSB
	loop	@B
;[���.N16inASCII ECX,SPSTR,NUMBER] �� ���.ECX ������ �������� SPSTR 16-��� �����, ����� ��������
	N!16inASCII	EBP,BufPrint+DlPref,8
		mov	EDX,DlPref+10		;8 �����+2(LF,CR)
		mov	eax,[Hconsl]		;handle console
	invoke	WriteConsole, eax,BufPrint, edx, Writed, 0
	�������������������   EBP,EAX,ECX,ESI,EDI 
}
;**********************************<-<-<-P!rAdrInDll
