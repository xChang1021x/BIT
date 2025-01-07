.386
.model flat,stdcall
option casemap:none

include masm32rt.inc
includelib masm32rt.lib
includelib user32.lib
includelib kernel32.lib
includelib gdi32.lib
includelib Comdlg32.lib
includelib msvcrt.lib

include windows.inc
include user32.inc
include kernel32.inc
include gdi32.inc
include Comdlg32.inc
include	msvcrt.inc

sprintf	PROTO C :ptr sbyte, :ptr sbyte, :VARARG

.data
_processHandle	DD	?							;EXE���
_appClassName	DB	'CompareFileClass',0		;ע�ᴰ��������
screenHandle	DD	?							;��Ļ��������ڻ�ͼ
Button			DB	'button',0
_windowHandle	DD	?							;���������ھ��
DiffNum			DD	?							;��һ����������
Difference		DB	2000 dup(0)					;��һ������
FileName1		DB	MAX_PATH	dup(?)
FileName2		DB	MAX_PATH	dup(?)
Buffer1			DB	1024 dup(?)
Buffer2			DB	1024 dup(?)
Chose1			DB	0
Chose2			DB	0
;--------------��ʾ��Ϣ-------------
AppCaption		DB	'Compare2Files!',0			;���ڱ���
Button1Text		DB	'Choose File1',0
Button2Text		DB	'Choose File2',0
Button3Text		DB	'Begin Comparation',0
CompareTitle	DB	'Comparation Result',0
SameContentHint	DB	'There is no different line between two files!', 0
MyFilter		DB	'Text Files(*.txt) ',0,'*.txt',0
				DB	'Doc Files(*.doc) ',0,'*.doc',0
				DB	'Docx Files(*.docx) ',0,'*.docx',0,0
FileChosenHint	DB	'You have chosen the file:',0
DifferenceHint	DB	'Different line: %d',0AH,0
TextNotChosen	DB	'Empty'
TextChosen		DB	'                      ',0
;--------------��ʾ��Ϣ-------------


.code
;-----------------ʹ���ļ������һ��---------------------
ReadOneLine	proc	uses EBX,filehandle:HANDLE,buffer:PTR	BYTE
	LOCAL	fileptr:		DWORD					;
	LOCAL	input_char:		BYTE					;��������

	MOV		EBX,buffer
	.while TRUE
		invoke	ReadFile,filehandle,addr	input_char,1,addr	fileptr,NULL
		.break	.if	!fileptr
		.break	.if	input_char==10

		MOV		AL,input_char						;ѭ����������ַ�����buffer
		MOV		[EBX],AL
		INC		EBX
	.endw

	MOV		AL,0									;���һλ0
	MOV		[EBX],AL
	invoke	lstrlen,buffer							;����strlen������浽eax�в�����
	ret

ReadOneLine	endp
;-----------------ʹ���ļ������һ��---------------------

;-----------------�ļ��Ƚ�---------------------
CompareFile	proc
	LOCAL	filehandle1:	HANDLE					;�ļ����
	LOCAL	filehandle2:	HANDLE
	LOCAL	ptr1:			DWORD					;�ļ�ָ��
	LOCAL	ptr2:			DWORD
	LOCAL	_line:			DWORD					;����
	LOCAL	differenceline[1000]:	BYTE			

	MOV		_line,0									;��ʼ��������ļ����
	MOV		DiffNum,0								
	invoke	CreateFile,offset	FileName1,GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL
	MOV		filehandle1,EAX
	invoke	CreateFile,offset	FileName2,GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL
	MOV		filehandle2,EAX

READ_LINE_START:
	INC		_line
	invoke	RtlZeroMemory,offset	Buffer1,sizeof	Buffer1
	invoke	ReadOneLine,filehandle1,offset	Buffer1
	MOV		ptr1,EAX								;���ȴ���EAX
	invoke	RtlZeroMemory,offset	Buffer2,sizeof	Buffer2
	invoke	ReadOneLine,filehandle2,offset	Buffer2
	MOV		ptr2,EAX								;���ȴ���EAX

	CMP		ptr1,0									;ptr1=0,�Ѷ����ļ�����
	JNE		FILE1_NOT_EMPTY
	CMP		ptr2,0									;�����ļ������꣬����ѭ��
	JE		COMPARE_END
	JMP		DIFFERENCE_LINE_EXIST

FILE1_NOT_EMPTY:									;�ļ�1 2�����Ϊ�գ�����strcmp�Ƚ�
	CMP		ptr2,0
	JNE		BOTH_NOT_EMPTY
	JMP		DIFFERENCE_LINE_EXIST

BOTH_NOT_EMPTY:
	invoke	lstrcmp,offset	Buffer1,offset Buffer2
	CMP		EAX,0
	JE		READ_LINE_START
	JMP		DIFFERENCE_LINE_EXIST

COMPARE_END:
	invoke	CloseHandle,filehandle1
	invoke	CloseHandle,filehandle2
	ret

DIFFERENCE_LINE_EXIST:								;���в�ͬ����ӡ�к�
	invoke	sprintf,addr	differenceline,offset	DifferenceHint,_line
	invoke	lstrcat,addr	Difference,addr	differenceline
	INC		DiffNum
	JMP		READ_LINE_START
CompareFile	endp
;-----------------�ļ��Ƚ�---------------------

;-----------------���ļ�ѡ�񴰿�---------------------
_OpenFile	proc	flag:dword
	LOCAL	filehandle:OPENFILENAME					;Ҫ�򿪵��ļ���

	invoke	RtlZeroMemory,addr filehandle,sizeof filehandle
	MOV		filehandle.lStructSize,sizeof filehandle;��ʼ���ļ����
	PUSH	_windowHandle
	POP		filehandle.hwndOwner
	MOV		filehandle.lpstrFilter,offset	MyFilter

	MOV		EAX,flag								;ͨ��flag��Ǵ򿪵����ļ�1/2
	CMP		EAX,1
	JNE		FILE_NOT_1
	MOV		filehandle.lpstrFile,offset	FileName1
	JMP		MARK_FILE_DONE
FILE_NOT_1:
	MOV		EAX,flag
	CMP		EAX,2
	JNE		MARK_FILE_DONE
	MOV		filehandle.lpstrFile,offset	FileName2
MARK_FILE_DONE:
	MOV		filehandle.nMaxFile,MAX_PATH
	MOV		filehandle.Flags,OFN_FILEMUSTEXIST OR OFN_PATHMUSTEXIST

	invoke	GetOpenFileName,addr filehandle			;��һ������ѡ���ļ�
	CMP		EAX,1
	JNE		OPEN_FILE_END
	MOV		EAX,flag
	CMP		EAX,1
	JNE		NOT_1
	invoke	MessageBox,_windowHandle,offset FileName1,\
			offset FileChosenHint,MB_OK
	JMP		OPEN_FILE_END
NOT_1:
	invoke	MessageBox,_windowHandle,offset FileName2,\
			offset FileChosenHint,MB_OK
OPEN_FILE_END:
	ret
_OpenFile	endp
;-----------------���ļ�ѡ�񴰿�---------------------


;-----------------���������ڵ���Ϣ�����ڹ��̺���---------------------
_ProcWinMain proc uses ebx edi esi,hWnd:HWND,uMsg:UINT,wParam:WPARAM,lParam:LPARAM
    LOCAL	PaintInfo:	PAINTSTRUCT
	LOCAL	hDc:		HDC

	MOV		EAX,uMsg								;uMsg��Ϣ����
	.if		EAX == WM_PAINT
		invoke	BeginPaint,hWnd,addr PaintInfo		;���ƴ���
		MOV		hDc,EAX
		MOV		screenHandle,EAX
		invoke	TextOut,hDc,250,15,addr TextNotChosen,5
		invoke	TextOut,hDc,250,55,addr TextNotChosen,5
		invoke	EndPaint,hWnd,addr PaintInfo
	.elseif	EAX == WM_CLOSE
		invoke	DestroyWindow,_windowHandle			;�رմ���
		invoke	PostQuitMessage,NULL
	.elseif	EAX == WM_CREATE						;�������ڣ�3����ť�����
		invoke CreateWindowEx,NULL,offset Button,offset Button1Text,\
			WS_CHILD or WS_VISIBLE,10,10,200,30,\ 
			hWnd,1,_processHandle,NULL				;1��ʾ�ð�ť�ľ����1
		invoke CreateWindowEx,NULL,offset Button,offset Button2Text,\
			WS_CHILD or WS_VISIBLE,10,50,200,30,\  
			hWnd,2,_processHandle,NULL
		invoke CreateWindowEx,NULL,offset Button,offset Button3Text,\
			WS_CHILD or WS_VISIBLE,10,90,200,30,\ 
			hWnd,3,_processHandle,NULL
	.elseif	EAX == WM_COMMAND						;����¼�
		MOV		EAX,wParam							;��������ť��wParam�ǰ�ť���
		.if	EAX == 1
			invoke	_OpenFile,1
			invoke	GetDC, hWnd
			MOV		Chose1,1
			MOV		hDc,EAX
			invoke	TextOut,hDc,250,15,addr TextChosen,13
			invoke	TextOut,hDc,250,15,addr FileName1,30
			.if		Chose2 == 1
				invoke	TextOut,hDc,250,55,addr TextChosen,13
				invoke	TextOut,hDc,250,55,addr FileName2,30
			.else
				invoke	TextOut,hDc,250,55,addr TextNotChosen,5
			.endif
			invoke	ReleaseDC, hWnd, hDc 
		.elseif	EAX == 2
			invoke	_OpenFile,2
			invoke	GetDC, hWnd
			MOV		Chose2,1
			MOV		hDc,EAX
			invoke	TextOut,hDc,250,55,addr TextChosen,13
			invoke	TextOut,hDc,250,55,addr FileName2,30
			.if		Chose1 == 1
				invoke	TextOut,hDc,250,15,addr TextChosen,13
				invoke	TextOut,hDc,250,15,addr FileName1,30
			.else
				invoke	TextOut,hDc,250,15,addr TextNotChosen,5
			.endif
			invoke	ReleaseDC, hWnd, hDc 
		.elseif	EAX == 3
			invoke	CompareFile
			.if	DiffNum == 0
				invoke	MessageBox,hWnd,offset SameContentHint,offset CompareTitle,MB_OK+MB_ICONQUESTION
			.else
				invoke	MessageBox,hWnd,offset Difference,offset CompareTitle,MB_OK+MB_ICONQUESTION
				invoke	RtlZeroMemory,addr Difference,sizeof Difference
			.endif
		.endif
	.else											;Ĭ�Ϸ�ʽ����
		invoke DefWindowProc,hWnd,uMsg,wParam,lParam
		ret
	.endif

	XOR		EAX,EAX
	ret	
_ProcWinMain endp
;-----------------���������ڵ���Ϣ�����ڹ��̺���---------------------

;-----------------��һ��windows���ĳ���������---------------------
_WinMain	proc	C
	LOCAL	_windowsClass:	WNDCLASSEX				;������ ������Ҫ���� egͼ�� ��� ����ɫ
	LOCAL	_windowsMsg:	MSG						;�����ഫ����Ϣ�Ľṹ��

	invoke	GetModuleHandle,NULL					;��ȡ��ǰexe���������eax
	MOV		_processHandle,EAX

	invoke	RtlZeroMemory,addr _windowsClass,sizeof _windowsClass  ;��ʼ��ȫ0
	invoke	LoadCursor,0,IDC_ARROW
	MOV		_windowsClass.hCursor,EAX
	PUSH	_processHandle
	POP		_windowsClass.hInstance
	MOV		_windowsClass.cbSize,sizeof	WNDCLASSEX
	MOV		_windowsClass.style,CS_HREDRAW or CS_VREDRAW
	MOV		_windowsClass.lpfnWndProc,offset	_ProcWinMain	;SengMessage(hWnd,uMsg,wParam,lParam)
	MOV		_windowsClass.hbrBackground,COLOR_WINDOW+1
	MOV		_windowsClass.lpszClassName,offset	_appClassName
	invoke	RegisterClassEx,addr	_windowsClass	;ע�ᴰ����

	invoke	CreateWindowEx,WS_EX_CLIENTEDGE,\		;�½����ڣ������eax
			offset _appClassName,offset AppCaption,\ ;ע����  ��������/button����ť��
			WS_OVERLAPPEDWINDOW,100,100,600,180,\	;���Ͻ�xy����+��+��
			NULL,NULL,_processHandle,NULL		
	MOV		_windowHandle,EAX
	invoke	ShowWindow,_windowHandle,SW_SHOWNORMAL	;��ʾ����
	invoke	UpdateWindow,_windowHandle				;ˢ�´���
		
APP_PROCESS_MESSAGE:								;ѭ����Ϣ���д�����Ϣ
	invoke	GetMessage,addr _windowsMsg,NULL,0,0	;����Ϣ������ȡ��Ϣ
	CMP		EAX,0									;�˳���Ϣ��EAX=0
	JE		APP_END
	invoke	TranslateMessage,addr _windowsMsg		;�ѻ��ڼ���ɨ����İ�����Ϣת���ɶ�Ӧ��ASCII�룬�����Ϣ����ͨ������������ⲽ��Ч
	invoke	DispatchMessage,addr _windowsMsg		;�ҵ��ô��ڳ���Ĵ��ڹ��̣�������Ϣ
	JMP		APP_PROCESS_MESSAGE
APP_END:
	ret
_WinMain endp
;-----------------��һ��windows���ĳ���������---------------------

;----------------------������------------------------------
main proc
	CALL	_WinMain
	invoke	ExitProcess,NULL
	ret
main	endp
end	main
;----------------------������------------------------------