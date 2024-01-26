  .intel_syntax noprefix

  .text
  .global my_memcpy

my_memcpy:
  mov r10, rsi            ; 
  mov r9d, edx            ;
  shr r9d, 3              ;

  je less_8               ;

  xor eax, eax            ;
  lea r8, [0 + r9 * 8]    ;

  jmp start_loop_8byte    ;

loop_8byte:
  mov rcx, QWORD PTR [r10 + rax]   ;
  mov QWORD PTR [rdi + rax], rcx   ;

  add rax, 8             ;
  cmp rax, r8            ;
  jb loop_8byte          ;

  mov r8d, edx           ;
  and r8d, -8            ;

  cmp r8d, edx           ;
  je return              ;

  mov rax, r8            ;
  lea r9, [rdi + rax]    ;
  add r10, rax           ;

  xor eax, eax           ;

loop_1byte:
  movzx rcx, BYTE PTR [r10 + rax]   ;
  mov BYTE PTR [r9 + rax], cl       ;

  add rax, 1             ;

  lea ecx, [r8 + rax]    ;
  cmp ecx, edx           ;
  jb loop_1byte          ;

  return:
    mov rax, rdi         ;
    ret                  ;

  less_8:
    cmp edx, 0           ;
    je return            ; 

    mov r9, rdi          ; 
    xor r8d, r8d         ;
    xor eax, eax         ;
    jmp loop_1byte       ; 

start_loop_8byte:         ;
  jmp loop_8byte           ;
