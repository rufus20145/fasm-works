;№    ИМЯ Операт. Место файл MZERO.inc
;1.     dbr            8        -формирование русского текста в нужной кодировке для печати
;2      dbr arg        108        структура для формирования русского текста в нужной кодировке для печати
;3      struc du [args]    192
;4      Print!afall    197
;5      Print!Rfall    207        Печать в русской кодировке
;6      spibefor    271
;7      spiafter    280
;8      spiszero    289
;9      spisoutone    299
;10     spinumb        316
;11     MINC        326        MINC Nom,\an1 ***** Увеличение счетчика
;12     MINCd        336
;13     MDEC        348        Уменьшение счетчика MDEC Nom,\an1
;14     !            376        Включение/выключение макроопределения при трансляции
;15     PrList        412        PrList  ********  15  ***   Печать по одному списка в arge
;16     PrLista        422        Печать 2-х из списка в arge
;17     !_            433        Печать Полная_библиотека_Операторов с включенной, выключенной библиотеки
;18     !_v            457        !_v  ***********Включенные операторы
;10     !_n            458        Выключенные операторы
;20     !_Pr        469        Полная_библиотека_Операторов
;21     !_Pro        485        Печать библиотеки включенной по одному параметру
;22     ?_V            503        Проверка Включен ли оператор
;23     ?_N            512        Проверка Отключен ли оператор
;24     ?_Vd        518        добавление в ?_Vd
;25     ?_Nd        533        добавление в  ?_N
;26     !_!            543        добавление(включение) библиотеки
;27     !_!d        551        добавление к !_!
;28     M!ET_r0        568        Макросы установления размерности константы
;29     M!ET_t0                Макросы установления типа                        29    НАЧАЛО_Программы    500
;*********1***********
macro dbr arg                                    ;UTF-8 для русских символов в OEM866
{    offset = $-$$
    offsetw = offset                                ;$-$$
    db arg
    FLEG=0
if arg eqtype ''
offs=offset                                        ;для подсчета окончания записи основных символов
nsimv=0                                            ;Количество паразитных символов
    repeat ($-offset-$$)
    load char byte from $$+offset+(%-1)
    if char > 07Fh                            ;>127
        if ~char=0D1h                                                ;FLEG=2
            if ~char=0D0h                                                ;FLEG=1
                                    if FLEG=1                        ;Был 0D0
                if char > 090h                    ;090h=192   A  русские символы
                    if char < 0C0h                ;от 090 до 0С0  русские А,Б,...,н,о,п
                    char =char-10h
                    store byte char at $$+offsetw+(%-1)
                    offs=offs+1
                                    FLEG=0
                    else
                    Print!Rafall 'Ошибка '        ;>090h >0C0h
                    display char
                                    FLEG=0
                    end if
                else                            ;07Fh <char< 090h
                    store byte char at $$+offsetw+(%-1)
                    offs=offs+1
                                    FLEG=0
                end if
                                    else
;************************************************* char=0D0h**************
                                    if FLEG=2
                if char > 07Fh
                    if char < 090h                ;128 русские  p,с,т..,я  +060h
                                char =char+60h
                                store byte char at $$+offsetw+(%-1)
                                offs=offs+1
                                    FLEG=0
                    else
                                Print!Rafall 'Ошибка '
                                display char
                                store byte char at $$+offsetw+(%-1)
                                offs=offs+1
                                FLEG=0
                    end if
                else                            ;< = 07Fh
                                Print!Rafall 'Ошибка '
                                display char
                        store byte char at $$+offsetw+(%-1)
                        offs=offs+1
                end if
                                    else        ; ~FLEG=1     ~FLEG=2
                                    store byte char at $$+offsetw+(%-1)
                                    offs=offs+1
                                    end if        ;FLEG=2
                                    end if        ;FLEG=1
        else
            offsetw=offsetw-1                    ;char=0D0h
            FLEG=1
            nsimv=nsimv+1
        end if
        else                                    ;char=0D1h
        offsetw=offsetw-1
        nsimv=nsimv+1
        FLEG=2
        end if
    else                                        ;char<07Fh
        store byte char at $$+offsetw+(%-1)
        offs=offs+1
        FLEG=0
    end if
    end repeat
        repeat nsimv
        load char byte from $$+offs+(%-1)
        char =020h
        store byte    char at $$+offs+(%-1)
        end repeat
end if
}
;*****************        3    ****** Windows 1251 ==> OEM 866
struc dbr arg
{    offset = $-$$
    offsetw = offset                                ;$-$$
    db arg
    FLEG=0
if arg eqtype ''
offs=offset                                        ;для подсчета окончания записи основных символов
nsimv=0
    repeat ($-offset-$$)
     load char byte from $$+offset+(%-1)
      if char > 07Fh                            ;>127
        if ~char=0D1h                                                ;FLEG=2
          if ~char=0D0h                                                ;FLEG=1
                                    if FLEG=1                        ;Был 0D0
                if char > 090h                    ;090h=192   A  русские символы
                    if char < 0C0h                ;от 090 до 0С0  русские А,Б,...,н,о,п
                    char =char-10h
                            ;display char
                            ;display '\'
                    store byte char at $$+offsetw+(%-1)
                    offs=offs+1
                                    FLEG=0
                    else
                    Print!Rafall 'Ошибка '
                    display char
                                    FLEG=0
                    end if
                else                            ;07Fh <char< 090h
                    store byte char at $$+offsetw+(%-1)
                    offs=offs+1
                                    FLEG=0
                end if
                                    else
;************************************************* char=0D0h**************
                                    if FLEG=2
                if char > 07Fh
                    if char < 090h                ;128 русские  p,с,т..,я  +060h
                                char =char+60h
                                store byte char at $$+offsetw+(%-1)
                                offs=offs+1
                                    FLEG=0
                    else
                                Print!Rafall 'Ошибка '
                                display char
                                store byte char at $$+offsetw+(%-1)
                                offs=offs+1
                                FLEG=0
                    end if
                else                            ;< = 07Fh
                                Print!Rafall 'Ошибка '
                                display char
                        store byte char at $$+offsetw+(%-1)
                        offs=offs+1
                end if
                                    else        ; ~FLEG=1     ~FLEG=2
                                    store byte char at $$+offsetw+(%-1)
                                    offs=offs+1
                                    end if        ;FLEG=2
                                    end if        ;FLEG=1
          else
            offsetw=offsetw-1                    ;char=0D0h
            FLEG=1
            nsimv=nsimv+1
          end if
        else                                    ;char=0D1h
        offsetw=offsetw-1
        nsimv=nsimv+1
        FLEG=2
        end if
      else                                                    ;char<07Fh
        store byte char at $$+offsetw+(%-1)
        offs=offs+1
        FLEG=0
      end if
    end repeat
        repeat nsimv
        load char byte from $$+offs+(%-1)
        char =020h
        store byte    char at $$+offs+(%-1)
        end repeat
end if
 }
;*******************     3    ********************
struc du [args]
 { common label . word
  du args }
;***************************************
;***********************    4    ************    Print!afall    expr
    macro Print!afall nlist1
{    common match nlist,nlist1
    \{    common  irps token,nlist
    \\{
    common    display    \\`token
    \\}
    \}
}
;1**********    5    *******    Print!Rafall    expr  display  Русских текстов
    macro Print!Rfall [arg]
{virtual at 0
    o$set = $-$$
    FLEG=0                                    ;label Z_ME1
if arg eqtype ''
    db arg
else
    db    ''# `arg
end if
;if arg eqtype ''
    repeat ($-o$set-$$)
     load char byte from $$+o$set+(%-1)
    IF    char=020h
    display     char
    FLEG=0
    else
      if char > 07Fh                            ;>127
        if ~char=0D1h                            ;FLEG=2
          if ~char=0D0h                            ;FLEG=1
                                    if FLEG=1    ;Был 0D0
                if char > 08Fh                    ;192   A
                    if char < 0C0h
                    char =char-10h
                    display     char
                                    FLEG=0
                    else
                    end if
                else
                end if
                                    else
;++++++++++++++++++++++++++++++++++++++++++++++++++++++
                                    if FLEG=2
                if char > 07Fh                    ;128   p    +030h
                    if char < 090h
                                char =char+60h
                                display     char
                                    FLEG=0
                    else
                    end if
                else
                end if
                                    else
                                    end if
;++++++++++++++++++++++++++++++++++++++++++++++++++++++
                                    end if
          else
            FLEG=1                                ;~char=0D0h
          end if
        else
        FLEG=2                                    ;~char=0D1h
        end if
      else
                    if FLEG=0
                    display     char
                    else
                    end if                        ;char < 7Fh
      end if
    end if                                         ;020h
    end repeat
;end if
    end virtual
}
;******************************************************
;spibefor ********    6    ************ Дополнение списка спереди  item + List
  macro spibefor    item,list
     {
    match ane,item
\{
       match any,list \\{ list equ item,list \\}
       match ,list \\{ list equ item \\}            ;при пустом списке
\}
     }
;******************************************************
;spiafter *******    7    ***********Дополнение списка сзади  List+item
  macro spiafter    list,item
     {
    match ane,item
\{
       match any,list \\{ list equ list,item \\}
       match ,list \\{ list equ item \\}            ;Первый в списке
\}
     }
;******************************************************
;spiszero ******    8    ********* Заверщение списка 0
    macro    spiszero vlis
{
        match ,vlis
    \{            Print!afall vlis
                    Print!Rfall "  Список пустой"
                    display    0Dh,0ah
    \}
    match any,list \{ vlis equ vlis,0 \}
}
;****************    9    *********
;spisoutone **********Из listua по разделителю =, изымается 1 в tema элемент в list остаток
;Отрезаем 1-й элемент из списка  listua и укороченный список в list. А в tema 1-й элемент
macro spisoutone    tema,list,listua
    {common    match an1 =,an2,listua
                \{
                tema    equ    \an1
                list     equ    \an2
                \}
                ;match an1,listua             \{ listua equ 0,an1 \}
                ;match =0,listua             \{ Print!afall listua\}
                ;assert listua, 'File is too small.'
                                                ;Print!Rfall " СПИСОК ИСЧЕРПАН"
                                                ;display 0Dh,0ah
    }
;****************    10    *********
;spinumb **spinumb tema,list,listua **Из listua добав.в список list с фиксацией номера впереди
    macro spinumb    tema,list,listua
{        common    match an1 =,an2,listua
                \{
                MINC Nom,\an1
                list equ    Nom,\an2,tema
                \}
                match ,list             \{ list equ 1,tema \}
}
;******************** 11    *********
;MINC **   MINC Nom,\an1 ***** Увеличение счетчика _A,вначале, на 1 и фиксация N_A
    macro MINC    N_A,_A
    {
 MINCd    N_A,_A,1,2,2,3,3,4,4,5,5,6,6,7,7,8,8,9,9,10,10,11,11,12,12,13,13,14,14,15,15,16,16,\
 17,17,18,18,19,19,20, 20,21, 21,22, 22,23, 23,24, 24,25, 25,26, 26,27, 27,28, 28,29, 29,30,\
 30,31
    }
;********************* 12    *********
    macro MINCd    N_A,_A,[P1,P2]
{FORWARD
        match =P1,_A
     \{ define _PPT P2
        N_A equ    _PPT
                                ;Print!afall _A
                                ;display " _A  63",0Dh,0ah
     \}
common
                            ;Print!afall N_A
                            ;display " N_A 64",0Dh,0ah
}
;******************** 13    **********************
;MDEC **  MDEC Nom,\an1 ***** Уменьшение счетчика MDEC Nom,\an1 NOM по содержимомму \an1
    macro MDEC    N_A,_A
    {
 MDECd    N_A,_A,1,0,2,1,3,2,4,3,5,4,6,5,7,6,8,7,9,8,10,9,11,10,12,11,13,12,14,13,15,14,16,15,\
 17,16,18,17,19,18,20,19,21,20, 22,21, 23,22, 24,23, 25,24, 26,25, 27,26, 28,27, 29,28, 30,29,\
 31,30, 32,31, 33,32, 34,33, 35,34, 36,35, 37,36, 38,37, 39,38, 40,39, 41,40, 42,41, 43,42,\
 44,43
    }
;*******        MINCd    эквивалентно MDECd
    macro MDECd    N_A,_A,[P1,P2]
{FORWARD
        match =P1,_A
     \{ define _PPT P2
        N_A equ    _PPT
                                ;Print!afall _A
                                ;display " _A  63",0Dh,0ah
     \}
common
                            ;Print!afall N_A
                            ;display " N_A 64",0Dh,0ah
}
;*******************************************
_vlista    equ            ;Список включенных
_nlista    equ            ;Список включенных
_slista    equ            ;Список не требуюших подключения так уже включены через другой     ОПЕРАТОР
_lista equ            ;Весь список ОПЕРАТОРОВ
;***************************************************************
;************************* 14 *******************************************
;N имя        Способ обращения  к макросу   !                                *
;        имя     Имя макроса  n выкл/вкд  Путь к билиотеке                 *
;9  !   * !   УпряталРегистры 4   -/+    'C:\FASM\BIBLMC\Rpushpop.inc'     *
; *** Включение/выключение макроопределения при трансляции программы    *
;********************* 14 ***********************************************
MACRO ! arg
{
common match ar1 ar2 =- ar3,arg
\{
 ;match params,\ar1 \\{ \\params 0 \\}                ;маркировка для отключения
    \spiafter \_lista,\ar1
    \spiafter \_lista,"        -"
    \spiafter    \_nlista,\ar1
    \spiafter \_nlista,\ar3
\}
common match ar1 ar2 =+ ar3,arg
\{
    \spinumb \ar1,\_vlista,\_vlista        ;Запись очередного имени  с изменением номера
    \spiafter \_vlista,\ar2                ;номер библиотеки
    \spiafter \_lista,\ar1                ;В общий список всех опреаторов подключенных и не
    \spiafter \_lista,"        +"
    include \ar3
\}
common match ar1 ar2 =* ar3,arg            ;Библиотека подключена через другой оператор
\{

    \spiafter \_lista,\ar1
    \spiafter \_lista,"        *"            ;В общий список операторов
    \spiafter \_slista,\ar1                ;имя оператора в список под одним номером
    \spiafter \_slista,\ar2                ; общий номер библиотеки
    ;\spiafter    \_vlista,\ar1
    ;\spiafter \_vlista,\ar2            ;номер библиотеки
    \niki equ    ON
 \}
}
;********************   Из listua по разделителю -, изымается 1 элемент в tema в list остаток
;PrList  ********  15  ***   Печать по одному списка в arge
MACRO PrList [arge]
{
FORWARD
Print!afall    arge

display 0Dh,0ah
}
;*********************
;PrLista *********  16 ***Печать 2-х из списка в arge YN***************
MACRO PrLista [arge,YN]
{
FORWARD
Print!Rfall    ""#`arge
display    "      "
Print!afall    YN
display 0Dh,0ah
}
;*****
;*********************** 17  *******************************************
; !_    Печать Полная_библиотека_Операторов с включенной, выключенной библиотеки
    MACRO        !_
{
    display    "+*-*+-+*-*+-+*+-+*-*+-+*-*+-+*-*+-+*-+*-*+-+*-*+-+*-"
    display 0Dh,0ah
!_Pr    "     Полная библиотека Операторов" _lista
    display    "+*-*+-+*-*+-+*+-+*-*+-+*-*+-+*-*+-+*-+*-*+-+*-*+-+*-"
    display 0Dh,0ah
}
;************************** 18 *******************
;!_v  ***********Включенные операторы
    MACRO        !_v
{
tema    equ
    spisoutone    tema,_list,_vlista
    display    "+++++++++++++++++++++++++++++++++++++++++++"
    display 0Dh,0ah
    !_Pr    "        Включенные операторы"  _list
    display    "..................................."
    display 0Dh,0ah
    !_Pr    "        Уже включенные операторы" _slista
    display    "+++++++++++++++++++++++++++++++++++++++++++"
    display 0Dh,0ah
}
;*****************************
;!_n  **********        19    **    Выключенные операторы
    MACRO        !_n
{
    display    "-----------------------------------------------"
    display 0Dh,0ah
    !_Pro    "          Выключенные операторы" _nlista
    display    "-----------------------------------------------"
    display 0Dh,0ah
}
;***********************    20 **по двум параметрам******************
;                            Заголовок                    Список полной библиотеки
;  !_Pr   *****    !_Pr    <Полная_библиотека_Операторов> _lista ****************
    MACRO    !_Pr    arg                        ;служебная для печати библиотека
{
    common match  ogl Nspis,arg
    \{                            Print!Rfall \ogl
                                display 0Dh,0ah
    display    "     ~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
    display 0Dh,0ah
    common match  params,\Nspis
    \\{
                        \\PrLista \\params  ;к двум параметрам
                                \\}
    ;display    "***********************************"
    ;display 0Dh,0ah
    \}
}
;********************    21        по одному параметру******************
;16 !_Pro *****             ****************************
; Печать библиотеки включенной + , выключенной библиотеки
    MACRO    !_Pro        arg
{
    common match  ogl Nspis,arg
    \{                            Print!Rfall \ogl
                                display 0Dh,0ah
    display    "     ~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
    display 0Dh,0ah
    common match  params,\Nspis
    \\{
                        \\PrLista \\params        ;ОБРАЩЕНИЕ К ОДНОМУ ПАРАМЕТРУ
    \\}
    display    "..................................."
    display 0Dh,0ah
    \}
}
;*************************** 22 **************
; ?_V*****   ?_V        УпряталиРегистры  *******
; Проверка Включен ли оператор arg в списке Операторов  Name
;
    MACRO    ?_V            arg
{
    match _vlis,_vlista    \{?_Vd    arg,\_vlis    \}
}
;*************************** 23 **************
;18 ?_N ************?_N УпряталиРегистры************
; Проверка Отключен ли оператор
MACRO ?_N            arg
{
    match _vlis,_nlista    \{?_Nd    arg,\_vlis    \}
}
;*************************** 24 **************
;?_Vd ***добавление ?_Vd *********************
    MACRO    ?_Vd        arg,[_vlis]
    {common
                                    ;Print!afall arg
                                    ;display " arg",0Dh,0ah
FORWARD
                                    ;Print!afall _vlis
                                    ;display " _vlis",0Dh,0ah
        match =arg,_vlis
     \{                         Print!afall arg
                                display " включен",0Dh,0ah
     \}
    }
;***********
;*************************** 25 **************
;?_Nd ********довавление ?_N***********
    MACRO    ?_Nd        arg,[_vlis]
    {common
FORWARD
        match =arg,_vlis
     \{                         Print!afall arg
                                display " выключен",0Dh,0ah
     \}
    }
;*************************** 26 **************
; !_! ***************включение библиотеки соотвествующего макроса*********
;*************  !_! УпряталиРегистры   ****************
MACRO !_!            arg
{
common    match _vlis,_nlista    \{!_!d    arg,\_vlis    \}
}
;*************************** 27 **************
; !_!d *******    добавление к !_!    *****************
MACRO !_!d        arg,[_nm,_bib]
    {common
                                    ;Print!afall arg
                                    ;display " arg",0Dh,0ah
FORWARD
                                    ;Print!afall _vlis
                                    ;display " _vlis",0Dh,0ah
        match =arg,_nm
    \{
                include `_bib#'   '
                                Print!afall _bib
                                display " включили",0Dh,0ah
    \}
}
;***************************************************************************
;    Макросы установления типа и размерности константы
;************************************************************r Размерность записанных данных
    MACRO M!ET_r0    arg            ;Присвоение MET_r = 0 литеральная константа
{arg#_r=0  }
    MACRO    Литеральность arg
    {    M!ET_r0    arg}
;************
    MACRO M!ET_r3    arg            ;Присвоение MET_r = 3 через equ константа
{arg#_r=3  }
    MACRO    Эквивалентность arg
    {    M!ET_r3    arg}
;************
    MACRO M!ET_r1    arg            ;Присвоение MET_r = 1 данные в памяти байтные
{arg#_r=1  }
MACRO Байтность arg
    {    M!ET_r1    arg}
;************
    MACRO M!ET_r2    arg            ;Присвоение MET_r = 2 данные в памяти словные
{arg#_r=2  }
MACRO Словность arg
    {    M!ET_r2    arg}
;************
    MACRO M!ET_r4    arg            ;Присвоение MET_r = 4 данные в памяти двухсловные
{arg#_r=4  }
MACRO Двухсловность arg
    {    M!ET_r4    arg}
;************
;*********************************************************Тип (тег) используемых данных
MACRO M!ET_t0    arg            ;Присвоение MET_t = 0 ,битовая шкала,битовое множество
{arg#_t=0  }
MACRO Битовая arg
    {    M!ET_t0    arg}
;************
MACRO M!ET_t1    arg            ;Присвоение MET_t = 1 ,буквенная информация байт
{arg#_t=1  }
MACRO Символьная arg
    {    M!ET_t1    arg}
;************
MACRO M!ET_t2    arg            ;Присвоение MET_t = 2 ,буквенная информация 2 байта
{arg#_t=2  }
MACRO СимвольнаяРасширенная arg
    {    M!ET_t3    arg}
;************
MACRO M!ET_t3    arg            ;Присвоение MET_t = 3 ,целое число без знака (r=байт,слово,двойное слово)
{arg#_t=3  }
MACRO Числовая_без_знака arg
    {    M!ET_t3    arg}
;************
MACRO M!ET_t4    arg            ;Присвоение MET_t = 4 ,целое число со знаком (r=байт,слово,двойное слово)
{arg#_t=4  }
MACRO Числовая_со_знаком arg
    {    M!ET_t4    arg}
;************
MACRO M!ET_t5    arg            ;Присвоение MET_t = 5 ,число с плавающей запятой(r=байт,слово,двойное слово)
{arg#_t=5  }
MACRO Числовая_с_плавающей arg
    {    M!ET_t5    arg}
;************
MACRO M!ET_t6    arg            ;Присвоение MET_t = 6 ,число двоично-десятичное(r=байт,слово,двойное слово)
{arg#_t=6  }
MACRO Числовая_двоично_десятичная arg
    {    M!ET_t6    arg}
;************
; ВЫЗОВ НЕОБХОДИМЫХ БИБЛИОТЕК МАКРОСОВ
include '.\INCALL.inc'    ;Включение Библиотеки ОПЕРАТОРОВ по имени
; include '.\SYSALL.inc'    ;Включение Библиотеки системных ОПЕРАТОРОВ по имени
include '.\INCLUDE\win32a.inc'    ;Билиотека системных ОПЕРАТОРОВ
;****************************************************
