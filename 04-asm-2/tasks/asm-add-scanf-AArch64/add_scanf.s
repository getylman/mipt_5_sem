.text
  .global add_scanf

  .macro push Xn
    sub sp, sp, 16
    str \Xn, [sp]
  .endm

  .macro pop Xn
    ldr \Xn, [sp]
    add sp, sp, 16
  .endm

add_scanf:
  sub sp, sp, 64
  stp x29, x30, [sp, -16]!
  mov x29, sp

  adr x0, scanf_format_string
  add x1, sp, 16
  add x2, sp, 24

  bl scanf

  ldr x0, [sp, 16]
  ldr x1, [sp, 24]
  add x0, x0, x1

  ldp x29, x30, [sp], 16
  add sp, sp, 64
  ret

  .section .rodata

scanf_format_string:
  .string "%lld %lld"