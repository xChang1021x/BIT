.386
.model flat,stdcall
option casemap:none

includelib  shell32.lib
includelib  user32.lib
includelib  masm32.lib
includelib  comctl32.lib
includelib  kernel32.lib
includelib  msvcrt.lib
includelib gdi32.lib

include  windows.inc
include  masm32.inc
include  shell32.inc
include  user32.inc
include  comctl32.inc
include  kernel32.inc
include	msvcrt.inc
include gdi32.inc

strcat   PROTO C :ptr sbyte,:ptr sbyte

;���泣��
handleButton0	EQU		0
handleButton1	EQU		1
handleButton2	EQU		2
handleButton3	EQU		3
handleButton4	EQU		4
handleButton5	EQU		5
handleButton6	EQU		6
handleButton7	EQU		7
handleButton8	EQU		8
handleButton9	EQU		9
handleButtonEqu	EQU		10
handleButtonPlus	EQU		11
handleButtonSub		EQU		12
handleButtonMul		EQU		13
handleButtonDiv		EQU		14
handleButtonRight	EQU		15
handleButtonNeg		EQU		16
handleButtonAC		EQU		17
handleButtonSin		EQU		18
handleButtonCos		EQU		19
handleButtonTan		EQU		20
handleButtonLeft	EQU		21
handleButtonDot		EQU		22
handleTextExpression	EQU		23
handleTextResult		EQU		24

.data
     
_windowHandle   DD   ?		            ;���������ھ��
_processHandle  DD   ?                  ;EXE���
screenHandle	DD	?					;��Ļ��������ڻ�ͼ

isLeft			DD	0 ;�Ƿ��ǵ�ǰ���������
isStartNum		DB	0;�Ƿ�ʼ��������
isStart			DB 0 ;�Ƿ�ʼ��ʾ
isFloat			DD	0 ;�Ƿ��Ǹ�����
isNeg			DD 0 ;�Ƿ��Ǹ���
curNum			DD	0;��ǰ�����������
tempNum			DD 0
curOp			DD 0 ;��ǰ�����

optStack		DD 200 dup(0)			;����ջ
opIndex			DD 0					;����ջ�±�
numStack		REAL4 50 DUP(0.)		;����ջ   
numIndex		DD 0;����ջ�±�

numStrExpression	DB 40 DUP(0) 
numStrResult		DB "0",0,40 DUP(0)

ProgramName     DB  'gxy�ļ�����',0     ;������
_appClassName   DB  'Calculate',0       ;��������
Button			DB	'button',0
Static			DB	'static',0

expressionText	DB	'0',0
resultText		DB	'0',0
equText			DB	'=',0
button0Text		DB	'0',0
button1Text		DB	'1',0
button2Text		DB	'2',0
button3Text		DB	'3',0
button4Text		DB	'4',0
button5Text		DB	'5',0
button6Text		DB	'6',0
button7Text		DB	'7',0
button8Text		DB	'8',0
button9Text		DB	'9',0
buttonPlusText		DB	'+',0
buttonSubText		DB	'-',0
buttonMulText		DB	'*',0
buttonDivText		DB	'/',0
buttonDotText		DB	'.',0
buttonNegText		DB	'+/ -',0
buttonSinText		DB	'sin',0
buttonCosText		DB	'cos',0
buttonTanText		DB	'tan',0
buttonACText		DB	'AC',0
buttonLeftText		DB	'(',0
buttonRightText		DB	')',0
sinText         DB  'sin(',0
cosText         DB  'cos(',0
tanText         DB  'tan(',0

ten				QWORD	10.
dot				QWORD	0.1
tempDot			QWORD	1.			;��ǰ�������ֵĽ�
initDot			QWORD	1.
res				real8	?			;��ʱ�洢������
op1				real8 ?;��ʱ�洢������
op2				real8 ?;��ʱ�洢������
.code
;-----------------�������ּ�0-9����---------------------
pressNum	proc	hWnd:HWND,num:DWORD
	XOR		EAX,EAX
	MOV		isLeft,1
	.if	isStartNum == 0
			fldz
			MOV		isStartNum,1
			MOV		EAX,curNum
			INC		EAX
			MOV		curNum,EAX				;���ּ���+1
	.endif
	.if	isFloat == 0
			fld		ten						;st[0] = 10
			fmul							;st[0] = st[1]*10
			fild	num						;st[0] = num
			MOV		tempNum,handleButton0
			fisub	tempNum					;st[0] = ��ǰ��
			;fmul							;st[0]=st[0]*��ǰС����
			.if		isNeg == 1
				fchs						;����ǰ��Ϊ������st[0]=-st[0]
			.endif
			fadd							;st[0]=st[1]+st[0]
	.else
			fld		tempDot
			fmul	dot
			fst		tempDot
			fild	num
			MOV		tempNum,handleButton0
			fisub	tempNum
			fmul
			.if		isNeg == 1
					fchs
			.endif
			fadd
	.endif
	MOV		EAX,num							;��ǰ���ַ���ʾ
	SUB		EAX,handleButton0
	ADD		EAX,'0'
	LEA		ESI,numStrResult
	.if		isStart == 1
			.while	BYTE	PTR[ESI] != 0
					INC		ESI
			.endw
	.else
			MOV		isStart,1
	.endif
	MOV		[ESI],AL
	MOV		BYTE	PTR[ESI+1],0
	invoke	SetDlgItemText,hWnd,handleTextResult,addr numStrResult
	ret
pressNum	endp
;-----------------�������ּ�0-9����---------------------


;-----------------����AC����---------------------
initAC	proc	
	MOV		isStart,0
	MOV		isLeft,0
	MOV		isStartNum,0
	MOV		opIndex,0
	MOV		numIndex,0
	MOV		curNum,0

	MOV		[optStack],0
	MOV		ESI,199
	.while	ESI != 1
			MOV		[optStack+ESI*4],0
			DEC		ESI
	.endw
	MOV		[optStack+ESI*4],0

	MOV		ESI,49
	.while	ESI != 1
			MOV		[numStack+ESI*4],0
			DEC		ESI
	.endw
	MOV		[numStack+ESI*4],0
	
	XOR		ESI,ESI
	XOR		EAX,EAX
	XOR		EDI,EDI
	fld		initDot
	fstp	tempDot
	finit
	MOV		[numStrExpression],0
	MOV		[numStrResult],0
	MOV		isNeg,0
	MOV		isFloat,0
	fldz
	ret
initAC	endp
;-----------------����AC����---------------------

;-----------------���¼Ӽ��˳����ں������ŵĴ���---------------------
pressOp	proc	hWnd:HWND,num:DWORD
	LOCAL	flag:Byte

	MOV		flag,0
	invoke	strcat,addr	numStrExpression,addr numStrResult
	MOV		isFloat,0
	MOV		isNeg,0
	MOV		isStartNum,0
	MOV		ESI,opIndex
	MOV		EAX,[optStack+ESI*4]
	MOV		curOp,EAX							;��ȡ��һ�������
	.if		curOp == 0							;ǰ��û�����������ǰ��ȡ���Ŵ������ջ
			XOR		EAX,EAX
			.if		num == handleButtonPlus
					MOV		EAX,'+'
					MOV		ESI,opIndex
					MOV		[optStack+ESI*4],1
			.elseif	num == handleButtonSub
					MOV		EAX,'-'
					MOV		ESI,opIndex
					MOV		[optStack+ESI*4],2
			.elseif	num == handleButtonMul
					MOV		EAX,'*'
					MOV		ESI,opIndex
					MOV		[optStack+ESI*4],3
			.elseif	num == handleButtonDiv
					MOV		EAX,'/'
					MOV		ESI,opIndex
					MOV		[optStack+ESI*4],4
			.endif
			LEA		ESI,numStrExpression		;������ӵ��ı���
			.if		isStart == 1
					.while	BYTE	PTR[ESI] != 0
							INC		ESI
					.endw
			.else
					MOV		isStart,1
			.endif
			MOV		[ESI],AL
			MOV		BYTE	PTR[ESI+1],0
			MOV		isStart,0
	.elseif	(curOp == 1)||(curOp == 2)			;�Ӽ�
			.if	(num == handleButtonPlus)||(num == handleButtonSub)
				.if		num == handleButtonPlus
					MOV		EAX,'+'
					MOV		ESI,opIndex
					MOV		[optStack+ESI*4],1
				.elseif	num == handleButtonSub
					MOV		EAX,'-'
					MOV		ESI,opIndex
					MOV		[optStack+ESI*4],2
				.endif
				LEA		ESI,numStrExpression
				.if		isStart == 1
						.while	BYTE	PTR[ESI] != 0
								INC		ESI
						.endw
				.else
						MOV		isStart,1
				.endif
				MOV		[ESI],AL
				MOV		BYTE	PTR[ESI+1],0
				fst		res						;ִ�в���
				.if		curOp == 1
						fadd
				.else
						fsub
				.endif
				MOV		EAX,curNum
				DEC		EAX
				MOV		curNum,EAX
				fst		res
				invoke	FloatToStr,res,addr	numStrResult
				invoke	SetDlgItemText,hWnd,handleTextResult,addr numStrResult
				MOV		isStart,0
			.elseif	(num == handleButtonMul)||(num == handleButtonDiv)
				.if		num == handleButtonMul
					MOV		EAX,'*'
					MOV		ESI,opIndex
					INC		ESI
					MOV		opIndex,ESI
					MOV		[optStack+ESI*4],3
				.elseif	num == handleButtonDiv
					MOV		EAX,'/'
					MOV		ESI,opIndex
					INC		ESI
					MOV		opIndex,ESI
					MOV		[optStack+ESI*4],4
				.endif				
				LEA		ESI,numStrExpression
				.if		isStart == 1
						.while	BYTE	PTR[ESI] != 0
								INC		ESI
						.endw
				.else
						MOV		isStart,1
				.endif
				MOV		[ESI],AL
				MOV		BYTE	PTR[ESI+1],0
				MOV		isStart,0
			.elseif	num == handleButtonEqu
				.if		curOp == 1
					fadd
				.else
					fsub
				.endif
				MOV		EAX,curNum
				DEC		EAX
				MOV		curNum,EAX
				fst		res
				invoke	FloatToStr,res,addr	numStrResult
				invoke	SetDlgItemText,hWnd,handleTextResult,addr numStrResult
				invoke	SetDlgItemText,hWnd,handleTextExpression,addr numStrExpression
				invoke	initAC
				MOV		flag,1
			.elseif	num == handleButtonRight
				.if		curOp ==1
						fadd
				.else
						fsub
				.endif
				MOV		EAX,curNum
				DEC		EAX
				MOV		curNum,EAX
				fst		res
				invoke	FloatToStr,res,addr	numStrResult
				invoke	SetDlgItemText,hWnd,handleTextResult,addr numStrResult
				MOV		ESI,opIndex
				DEC		ESI
				MOV		EAX,[optStack+ESI*4]
				MOV		curNum,EAX			
				.if		EAX == 2
						MOV		EDI,numIndex
						fstp	res
						DEC		EDI
						fld		[numStack+EDI*4]
						fst		op1
						DEC		EDI
						fld		[numStack+EDI*4]
						fst		op1
						fld		res
						MOV		numIndex,EDI
				.elseif	EAX == 1
						MOV		EDI,opIndex
						DEC		EDI
						fstp	res
						fld		[numStack+EDI*4]
						fst		op1
						fld		res
						MOV		numIndex,EDI
				.endif
				INC		EAX
				MOV		curNum,EAX
				DEC		ESI
				MOV		opIndex,ESI
				invoke	strcat,addr	numStrExpression,addr	buttonRightText
				MOV		[numStrResult],0
			.endif
		.elseif	(curOp == 3)||(curOp == 4)
			.if	(num == handleButtonMul)||(num == handleButtonDiv)
				.if		num == handleButtonMul
					MOV		EAX,'*'
					MOV		ESI,opIndex
					MOV		[optStack+ESI*4],3
				.elseif	num == handleButtonDiv
					MOV		EAX,'/'
					MOV		ESI,opIndex
					MOV		[optStack+ESI*4],4
				.endif
				LEA		ESI,numStrExpression
				.if		isStart == 1
						.while	BYTE	PTR[ESI] != 0
								INC		ESI
						.endw
				.else
						MOV		isStart,1
				.endif
				MOV		[ESI],AL
				MOV		BYTE	PTR[ESI+1],0
				fst		res
				.if		curOp == 3
					fmul
				.else
					fdiv
				.endif
				MOV		EAX,curNum
				DEC		EAX
				MOV		curNum,EAX
				fst		res
				invoke	FloatToStr,res,addr	numStrResult
				invoke	SetDlgItemText,hWnd,handleTextResult,addr numStrResult
				MOV		isStart,0
			.elseif	(num == handleButtonPlus)||(num == handleButtonSub)
				.if		curOp == 3
					fmul
				.else
					fdiv
				.endif
				MOV		EAX,curNum
				DEC		EAX
				MOV		curNum,EAX
				MOV		ESI,opIndex
				.if		curNum != 1
						DEC		ESI
						MOV		opIndex,ESI
						MOV		EAX,[optStack+ESI*4]
						MOV		curOp,EAX
						.if		curOp == 1
								fadd
						.else
								fsub
						.endif
						MOV		EAX,curNum
						DEC		EAX
						MOV		curNum,EAX
				.endif
				.if		num == handleButtonPlus
					MOV		EAX,'+'
					MOV		ESI,opIndex
					MOV		[optStack+ESI*4],1
				.elseif	num == handleButtonSub
					MOV		EAX,'-'
					MOV		ESI,opIndex
					MOV		[optStack+ESI*4],2
				.endif
				LEA		ESI,numStrExpression
				.if		isStart == 1
						.while	BYTE	PTR[ESI] != 0
								INC		ESI
						.endw
				.else
						MOV		isStart,1
				.endif
				MOV		[ESI],AL
				MOV		BYTE	PTR[ESI+1],0
				fst		res
				invoke	FloatToStr,res,addr	numStrResult
				invoke	SetDlgItemText,hWnd,handleTextResult,addr numStrResult
				MOV		isStart,0
			.elseif	(num == handleButtonEqu) ||(num == handleButtonRight)
				fst		res
				.if		curOp == 3
						fmul
				.else
						fdiv
				.endif
				MOV		EAX,curNum
				DEC		EAX
				MOV		curNum,EAX
				MOV		ESI,opIndex
				.if		curNum != 1
						DEC		ESI
						MOV		opIndex,ESI
						MOV		EAX,[optStack+ESI*4]
						MOV		curOp,EAX
						.if		curOp == 1
								fadd
						.else
								fsub
						.endif
						MOV		EAX,curNum
						DEC		EAX
						MOV		curNum,EAX
				.endif
				fst		res
				invoke	FloatToStr,res,addr	numStrResult
				invoke	SetDlgItemText,hWnd,handleTextResult,addr numStrResult
				.if		num == handleButtonEqu
						invoke	SetDlgItemText,hWnd,handleTextExpression,addr numStrExpression
						MOV		flag,1
						invoke	initAC
				.else
						MOV		ESI,opIndex
						DEC		ESI
						MOV		EAX,[optStack+ESI*4]
						MOV		curNum,EAX
						.if		EAX == 2
								MOV		EDI,numIndex
								fstp	res
								DEC		EDI
								fld		[numStack+EDI*4]
								fst		op1
								DEC		EDI
								fld		[numStack+EDI*4]
								fst		op1
								fld		res
								MOV		numIndex,EDI
						.elseif	EAX == 1
								MOV		EDI,opIndex
								DEC		EDI
								fstp	res
								fld		[numStack+EDI*4]
								fst		op1
								fld		res
								MOV		numIndex,EDI
						.endif
						INC		EAX
						MOV		curNum,EAX
						DEC		ESI
						MOV		opIndex,ESI
						invoke	strcat,addr	numStrExpression,addr	buttonRightText
						MOV		[numStrResult],0
				.endif
			.endif
		.endif
		.if flag == 0
			invoke	SetDlgItemText,hWnd,handleTextExpression,addr numStrExpression
		.endif
		ret
pressOp	endp
;-----------------���¼Ӽ��˳����ں������ŵĴ���---------------------

;-----------------���������ŵĴ���---------------------
pressLeft	proc	hWnd:HWND
	MOV		isStartNum,0
	MOV		ESI,opIndex
	INC		ESI
	MOV		EAX,curNum
	MOV		[optStack+ESI*4],EAX
	.if		EAX == 2
			MOV		EDI,numIndex
			fstp	[numStack+EDI*4]
			INC		EDI
			fstp	[numStack+EDI*4]
			INC		EDI
			MOV		numIndex,EDI
	.elseif EAX == 1
			MOV		EDI,numIndex
			.if isLeft == 0
				fldz
			.endif  
			fstp	[numStack+EDI*4]
			INC		EDI
			MOV		isLeft,0
			MOV		numIndex,EDI
	.endif
	INC		ESI
	MOV		opIndex,ESI
	MOV		curNum,0
	finit
	invoke	strcat,addr numStrExpression,addr buttonLeftText
	invoke	SetDlgItemText,hWnd,handleTextExpression,addr numStrExpression
	ret
pressLeft	endp
;-----------------���������ŵĴ���---------------------

;-----------------�������Ǻ����Ĵ���---------------------
pressTri	proc	hWnd:HWND,msgLeft:DWORD,msgRight:DWORD
	;������ʾ�����ݼ���sin������ӵ�����ʾ���ַ�����
    invoke	strcat,addr numStrExpression,msgLeft
    invoke	strcat,addr numStrExpression,addr numStrResult
    invoke	strcat,addr numStrExpression,msgRight
    ;��ȡ���Ǻ���������
    fst		res
    invoke	FloatToStr,res,addr numStrResult
    invoke	SetDlgItemText,hWnd,handleTextExpression,addr numStrExpression
    invoke	SetDlgItemText,hWnd,handleTextResult,addr numStrResult
	MOV		[numStrResult],0
    ret
pressTri	endp
;-----------------�������Ǻ����Ĵ���---------------------


;-----------------����.�Ĵ���---------------------
pressDot	proc	hWnd:HWND
	;���ֵ�ţ���Ϊ������
    MOV		isFloat,1
    ;����1.0���ڸ��µ�ǰ���Ľ�tempdot
    fld		initDot
    fstp	tempDot
    MOV		EAX,'.'
    LEA		ESI,numStrResult
    .if		isStart == 1
			.while BYTE PTR[ESI]!=0
				INC ESI
			.endw
    .else
			MOV		isStart,1
    .endif
    MOV		[ESI],AL
    MOV		BYTE PTR [ESI+1],0
    ;��������ʾ��
    invoke	SetDlgItemText,hWnd,handleTextResult,addr numStrResult
    ret
pressDot	endp
;-----------------����.�Ĵ���---------------------


;-----------------���������ڵ���Ϣ�����ڹ��̺���---------------------
_ProcWinMain proc uses ebx edi esi,hWnd:HWND,uMsg:UINT,wParam:WPARAM,lParam:LPARAM
    LOCAL	PaintInfo:	PAINTSTRUCT
	LOCAL	hDc:		HDC
									
	.if		uMsg == WM_PAINT						;uMsg��Ϣ����
		invoke	BeginPaint,hWnd,addr PaintInfo		;���ƴ���
		MOV		hDc,EAX
		MOV		screenHandle,EAX
		invoke	TextOut,hDc,470,100,addr equText,1
		invoke	EndPaint,hWnd,addr PaintInfo
	.elseif	uMsg == WM_CLOSE
		invoke	DestroyWindow,_windowHandle			;�رմ���
		invoke	PostQuitMessage,NULL
	.elseif	uMsg == WM_CREATE						;�������ڣ���ť�����
		invoke CreateWindowEx,NULL,offset Static,offset	expressionText,\
			WS_CHILD or WS_VISIBLE or ES_RIGHT,20,40,460,40,\
			hWnd,handleTextExpression,_processHandle,NULL
		invoke CreateWindowEx,NULL,offset Static,offset	resultText,\
			WS_CHILD or WS_VISIBLE or ES_RIGHT,20,140,460,40,\
			hWnd,handleTextResult,_processHandle,NULL
		invoke CreateWindowEx,NULL,offset Button,offset button1Text,\
			WS_CHILD or WS_VISIBLE,20,200,60,60,\ 
			hWnd,handleButton1,_processHandle,NULL				
		invoke CreateWindowEx,NULL,offset Button,offset button2Text,\
			WS_CHILD or WS_VISIBLE,100,200,60,60,\  
			hWnd,handleButton2,_processHandle,NULL
		invoke CreateWindowEx,NULL,offset Button,offset button3Text,\
			WS_CHILD or WS_VISIBLE,180,200,60,60,\ 
			hWnd,handleButton3,_processHandle,NULL
		invoke CreateWindowEx,NULL,offset Button,offset buttonPlusText,\
			WS_CHILD or WS_VISIBLE,260,200,60,60,\ 
			hWnd,handleButtonPlus,_processHandle,NULL
		invoke CreateWindowEx,NULL,offset Button,offset buttonSinText,\
			WS_CHILD or WS_VISIBLE,340,200,60,60,\ 
			hWnd,handleButtonSin,_processHandle,NULL
		invoke CreateWindowEx,NULL,offset Button,offset button4Text,\
			WS_CHILD or WS_VISIBLE,20,280,60,60,\ 
			hWnd,handleButton4,_processHandle,NULL				
		invoke CreateWindowEx,NULL,offset Button,offset button5Text,\
			WS_CHILD or WS_VISIBLE,100,280,60,60,\  
			hWnd,handleButton5,_processHandle,NULL
		invoke CreateWindowEx,NULL,offset Button,offset button6Text,\
			WS_CHILD or WS_VISIBLE,180,280,60,60,\ 
			hWnd,handleButton6,_processHandle,NULL
		invoke CreateWindowEx,NULL,offset Button,offset buttonSubText,\
			WS_CHILD or WS_VISIBLE,260,280,60,60,\ 
			hWnd,handleButtonSub,_processHandle,NULL
		invoke CreateWindowEx,NULL,offset Button,offset buttonCosText,\
			WS_CHILD or WS_VISIBLE,340,280,60,60,\ 
			hWnd,handleButtonCos,_processHandle,NULL
		invoke CreateWindowEx,NULL,offset Button,offset buttonACText,\
			WS_CHILD or WS_VISIBLE,420,280,60,60,\ 
			hWnd,handleButtonAC,_processHandle,NULL
		invoke CreateWindowEx,NULL,offset Button,offset button7Text,\
			WS_CHILD or WS_VISIBLE,20,360,60,60,\ 
			hWnd,handleButton7,_processHandle,NULL				
		invoke CreateWindowEx,NULL,offset Button,offset button8Text,\
			WS_CHILD or WS_VISIBLE,100,360,60,60,\  
			hWnd,handleButton8,_processHandle,NULL
		invoke CreateWindowEx,NULL,offset Button,offset button9Text,\
			WS_CHILD or WS_VISIBLE,180,360,60,60,\ 
			hWnd,handleButton9,_processHandle,NULL
		invoke CreateWindowEx,NULL,offset Button,offset buttonMulText,\
			WS_CHILD or WS_VISIBLE,260,360,60,60,\ 
			hWnd,handleButtonMul,_processHandle,NULL
		invoke CreateWindowEx,NULL,offset Button,offset buttonTanText,\
			WS_CHILD or WS_VISIBLE,340,360,60,60,\ 
			hWnd,handleButtonTan,_processHandle,NULL
		invoke CreateWindowEx,NULL,offset Button,offset equText,\
			WS_CHILD or WS_VISIBLE,420,360,60,60,\ 
			hWnd,handleButtonEqu,_processHandle,NULL
		invoke CreateWindowEx,NULL,offset Button,offset buttonNegText,\
			WS_CHILD or WS_VISIBLE,20,440,60,60,\ 
			hWnd,handleButtonNeg,_processHandle,NULL				
		invoke CreateWindowEx,NULL,offset Button,offset button0Text,\
			WS_CHILD or WS_VISIBLE,100,440,60,60,\  
			hWnd,handleButton0,_processHandle,NULL
		invoke CreateWindowEx,NULL,offset Button,offset buttonDotText,\
			WS_CHILD or WS_VISIBLE,180,440,60,60,\ 
			hWnd,handleButtonDot,_processHandle,NULL
		invoke CreateWindowEx,NULL,offset Button,offset buttonDivText,\
			WS_CHILD or WS_VISIBLE,260,440,60,60,\ 
			hWnd,handleButtonDiv,_processHandle,NULL
		invoke CreateWindowEx,NULL,offset Button,offset buttonLeftText,\
			WS_CHILD or WS_VISIBLE,340,440,60,60,\ 
			hWnd,handleButtonLeft,_processHandle,NULL
		invoke CreateWindowEx,NULL,offset Button,offset buttonRightText,\
			WS_CHILD or WS_VISIBLE,420,440,60,60,\ 
			hWnd,handleButtonRight,_processHandle,NULL
	.elseif	uMsg == WM_COMMAND						;����¼� ��������ť��wParam�ǰ�ť���	
		.if		((wParam >= handleButton0) && (wParam<= handleButton9))
			invoke	pressNum,hWnd,wParam
		.elseif	((wParam >= handleButtonEqu) && (wParam<= handleButtonRight))
			invoke	pressOp,hWnd,wParam
		.elseif	wParam == handleButtonAC			
			invoke	initAC
			invoke	SetDlgItemText,hWnd,handleTextExpression,addr numStrExpression
			invoke	SetDlgItemText,hWnd,handleTextResult,addr numStrResult
		.elseif	wParam == handleButtonLeft
			invoke	pressLeft,hWnd
		.elseif	wParam == handleButtonSin
			fsin
			invoke	pressTri,hWnd,addr sinText,addr	buttonRightText
		.elseif	wParam == handleButtonCos
			fcos
			invoke	pressTri,hWnd,addr cosText,addr	buttonRightText
		.elseif	wParam == handleButtonTan
			fst		res
			fsin
			fld		res
			fcos
			fdiv
			invoke	pressTri,hWnd,addr tanText,addr	buttonRightText
		.elseif	wParam == handleButtonNeg
			fchs
			.if		isNeg == 0
					MOV		isNeg,1
			.else
					MOV		isNeg,0
			.endif
			fst		res
			invoke	FloatToStr,res,addr	numStrResult
			invoke	SetDlgItemText,hWnd,handleTextResult,addr numStrResult	
		.elseif	wParam == handleButtonDot
			invoke	pressDot,hWnd
		.endif
	.else											;Ĭ�Ϸ�ʽ����
		invoke DefWindowProc,hWnd,uMsg,wParam,lParam
		ret
	.endif
	XOR	EAX,EAX
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
	MOV		_windowsClass.lpfnWndProc,offset	_ProcWinMain    ;SengMessage(hWnd,uMsg,wParam,lParam)
	MOV		_windowsClass.hbrBackground,COLOR_WINDOW+1
	MOV		_windowsClass.lpszClassName,offset	_appClassName
    MOV     _windowsClass.cbClsExtra,0              ;������ṹ��ĸ����ֽ����������ڴ�
    MOV     _windowsClass.cbWndExtra,DLGWINDOWEXTRA ;����ʵ����ĸ����ֽ���
	invoke  LoadCursor,NULL,IDC_ARROW    
    MOV     _windowsClass.hCursor,EAX               ;���
    MOV     _windowsClass.lpszMenuName,NULL         ;�˵�����ָ��
    MOV     _windowsClass.hIconSm,0                 ;����Сͼ����
    invoke	RegisterClassEx,addr	_windowsClass	;ע�ᴰ����  

    invoke	CreateWindowEx,WS_EX_CLIENTEDGE,\		;�½����ڣ������eax
			offset _appClassName,offset ProgramName,\  ;ע����  ��������/button����ť��
			WS_OVERLAPPEDWINDOW,100,100,520,570,\	;���Ͻ�xy����+��+��
			NULL,NULL,_processHandle,NULL
    ;invoke  CreateDialogParam,_processHandle,addr _appClassName,0,addr _ProcWinMain,0  ;���öԻ��򴰿�      	
	MOV		_windowHandle,EAX
	invoke	ShowWindow,_windowHandle,SW_SHOWDEFAULT	;��ʾ����
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
	finit  
    MOV     isLeft,0
    CALL	_WinMain
	invoke	ExitProcess,NULL
	ret
main	endp
end	main
;----------------------������------------------------------
