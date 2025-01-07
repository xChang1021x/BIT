.386
.model flat, stdcall
option casemap:none

includelib msvcrt.lib
includelib ucrt.lib
includelib legacy_stdio_definitions.lib

scanf proto C :dword, :vararg
printf proto C :ptr sbyte, :vararg

.stack 512
.data
    szInMsg db '%s %s', 0
    szOutMsg db 'Ans: %s', 0ah, 0
    First db 105 dup(0)
    Second db 105 dup(0)
    Ans db 205 dup(0)
    Digits db 1
    AnsEnd dd ?
    AnsStart dd ?
.code
start:
    invoke scanf, offset szInMsg, offset First, offset Second
    mov edi, offset First
    mov esi, offset Second
    mov AnsEnd, offset Ans + 200
findEndFirst:
    inc edi
    mov bl, [edi]
    cmp bl, 0
    jne findEndFirst
    push edi
findEndSecond:
    inc esi
    mov bl, [esi]
    cmp bl, 0
    jne findEndSecond
    push esi
Count_Loop_Second:
    pop esi
    pop edi
    dec esi
    cmp esi, offset Second
    jl EndCount
    mov cl, Digits
    inc cl
    mov Digits, cl
    push edi
    push esi
    mov bl, [esi]
    sub bl, 30H ;与字符0的ASCII相减，获取真正数值
    mov esi, AnsEnd
    dec esi
    mov AnsEnd, esi
Count_Loop_First:
    dec esi
    dec edi
    cmp edi, offset First
    jl Count_Loop_Second
    mov al, [edi]
    sub al, 30H
Multiple:
    mul bl ; al * bl -> ax
    mov cl, 10
    div cl ; ax / cl -> ah(余), al（商）
    add [esi], ah
    mov cl, [esi]
    cmp cl, 10
    jl NoCarry
    sub cl, 10
    mov [esi], cl
    mov cl, [esi - 1]
    add cl, 1
    mov [esi - 1], cl
NoCarry:
    mov cl, [esi - 1]
    add cl, al
    mov [esi - 1], cl
    sub esi, 1
    mov AnsStart, esi
    add esi, 1
    cmp cl, 10
    jl NoCarry2
    sub cl, 10
    mov [esi - 1], cl
    mov cl, [esi - 2]
    add cl, 1
    mov [esi - 2], cl
    sub esi, 2
    mov AnsStart, esi
    add esi, 2
NoCarry2:
    jmp Count_Loop_First
EndCount:
    mov esi, AnsStart
    mov cl, [esi]
    cmp cl, 0
    jne Save
    inc esi
Save:
    push esi
TurnString:
    mov cl, [esi]
    add cl, 30H
    mov [esi], cl
    inc esi
    cmp esi, offset Ans+198
    jle TurnString
Print:
    pop esi
    invoke printf, offset szOutMsg, esi
end start
