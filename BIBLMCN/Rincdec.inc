;*******************1***********
;    R!inc [ADR],5    можно и ячейку в памяти Нельзя R!inc ADR,5
MACRO    R!inc    Reg,Number
    {times    Number: INC    Reg     }
;*******************1
;*******************2***********
MACRO    R!dec    Reg,Number
    {times    Number: DEC    Reg     }
;*******************2
;*******************3
;        R!incS    INMAS,1,4,2    R!incS    INMAS,1,4,2
;++++++++++++++++++++++
    MACRO    R!incS    Adr,Num,KOL,t            ;Рассылка увеличения(Num) данных по ячейкам Adr с шагом t
{
IJ=0
    repeat    KOL
        R!inc    [Adr+IJ],Num
        Print!afall   "IJ="
    display    IJ+'0'            ;+'30'
    display 13,10
IJ=IJ+t
    end repeat
}
;*******************3
;*******************4
;    УвеличилиЦелыеЗначения    $НачальныйАдрес=INMAS  $НаСколькоУвеличить=5\
;  $КолвоЯчеек=4 $ТипРазмера=2
;R_t=1 Тип размерности-байт  2 слово 4 двойное слово
;++++++++++++++++++++
    MACRO УвеличилиЦелыеЗначения    arg
{
common    match $MASS==InMas  $UK==M    $NY==N $Type==K ,arg
        \{
        R!incS    \INMAS,\M,\N,\K
        \}
}
;*******************4
