.intel_syntax noprefix
.global main
.extern printf
.data
format_str:
.asciz "%d\n"
.text
main:
  push ebp
  mov ebp, esp
  sub esp, 0x100
  mov DWORD PTR [ebp-4], 0
  mov DWORD PTR [ebp-8], 0
  mov DWORD PTR [ebp-12], 0
  mov DWORD PTR [ebp-16], 0
  mov DWORD PTR [ebp-20], 0
  mov DWORD PTR [ebp-24], 0
  mov DWORD PTR [ebp-28], 0
  mov DWORD PTR [ebp-32], 0
  mov eax, 114
  mov DWORD PTR [ebp-4], eax
  mov eax, 514
  mov DWORD PTR [ebp-8], eax
  mov eax, DWORD PTR [ebp-8]
  push eax
  mov eax, DWORD PTR [ebp-4]
  pop ebx
  cmp eax, ebx
  jle true0
  mov eax, 0
  jmp done0
true0:
  mov eax, 1
done0:
  mov DWORD PTR [ebp-12], eax
  mov eax, DWORD PTR [ebp-8]
  push eax
  mov eax, DWORD PTR [ebp-4]
  pop ebx
  cmp eax, ebx
  jl true1
  mov eax, 0
  jmp done1
true1:
  mov eax, 1
done1:
  mov DWORD PTR [ebp-16], eax
  mov eax, DWORD PTR [ebp-8]
  push eax
  mov eax, DWORD PTR [ebp-4]
  pop ebx
  cmp eax, ebx
  jge true2
  mov eax, 0
  jmp done2
true2:
  mov eax, 1
done2:
  mov DWORD PTR [ebp-20], eax
  mov eax, DWORD PTR [ebp-8]
  push eax
  mov eax, DWORD PTR [ebp-4]
  pop ebx
  cmp eax, ebx
  jg true3
  mov eax, 0
  jmp done3
true3:
  mov eax, 1
done3:
  mov DWORD PTR [ebp-24], eax
  mov eax, DWORD PTR [ebp-8]
  push eax
  mov eax, DWORD PTR [ebp-4]
  pop ebx
  cmp eax, ebx
  jne true4
  mov eax, 0
  jmp done4
true4:
  mov eax, 1
done4:
  mov DWORD PTR [ebp-28], eax
  mov eax, DWORD PTR [ebp-8]
  push eax
  mov eax, DWORD PTR [ebp-4]
  pop ebx
  cmp eax, ebx
  je true5
  mov eax, 0
  jmp done5
true5:
  mov eax, 1
done5:
  mov DWORD PTR [ebp-32], eax
  push DWORD PTR [ebp-4]
  push offset format_str
  call printf
  add esp, 8
  push DWORD PTR [ebp-8]
  push offset format_str
  call printf
  add esp, 8
  push DWORD PTR [ebp-12]
  push offset format_str
  call printf
  add esp, 8
  push DWORD PTR [ebp-16]
  push offset format_str
  call printf
  add esp, 8
  push DWORD PTR [ebp-20]
  push offset format_str
  call printf
  add esp, 8
  push DWORD PTR [ebp-24]
  push offset format_str
  call printf
  add esp, 8
  push DWORD PTR [ebp-28]
  push offset format_str
  call printf
  add esp, 8
  push DWORD PTR [ebp-32]
  push offset format_str
  call printf
  add esp, 8
  mov eax, 0
  mov eax, 0
  leave
  ret
