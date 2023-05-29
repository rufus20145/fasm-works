;БИБЛИОТЕКА ПОДКЛЮЧЕНИЯ DLL ДЛЯ ИСПОЛНЕНИЯ UMMN 11.07.2022

library kernel, 'KERNEL32.DLL',\
        UMON,		'UMON.DLL',\
        UPAK,		'UPAK.dll',\
        SLWAV,		'SLWAV.dll',\
        UNPAK,		'UNPAK.dll',\
        FENick,		'FENick.dll',\
        Spectr,		'Spectr',\
        FenSpec,	'FenSpec',\
        FenVod,		'FenVod'
    import	kernel,\
        ExitProcess,	'ExitProcess',\
        GetStdHandle,	'GetStdHandle',\
        GetLastError,	'GetLastError',\
        WriteConsole,	'WriteConsoleA',\
        ReadConsole,	'ReadConsoleA',\
        GetCurrentDirectory,	'GetCurrentDirectoryA',\
        CloseHandle,	'CloseHandle',\
        CreateFile,		'CreateFileA',\
        CreateDirectory,'CreateDirectoryA',\
        ReadFile,		'ReadFile',\
        WriteFile,		'WriteFile',\
        GetCommandLine,	'GetCommandLineA',\
        VirtualFree,	'VirtualFree',\
        VirtualAlloc,	'VirtualAlloc',\
        SetFilePointer,	'SetFilePointer',\
        SetCurrentDirectory,'SetCurrentDirectoryA',\
        GetFileSize,	'GetFileSize',\
        GlobalAlloc,    'GlobalAlloc'

    import	UMON,\
        UMON,		'UMON'
    import	SLWAV,\
        TWWAV,			'TWWAV',\
        NTWAV,			'NTWAV',\
        WNWAV,			'WNWAV',\
        LPWAV,			'LPWAV',\
        WTWAV,			'WTWAV',\
        SNWAV,			'SNWAV'
    import	FENick,\
        F@eniсk,	'F@eniсk'
    import	Spectr,\
        S@pectr,	'S@pectr'
    import	FenSpec,\
        F@enSpec,	'F@enSpec'
    import	FenVod,\
        F@enVod,	'F@enVod'
import	UPAK,\
			UPAK,		'UPAK',\
			TXTINH,		'TXTINH'
	import	UNPAK,\
			UNPAK,		'UNPAK',\
			NHASCII,		'NHASCII'