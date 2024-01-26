.intel_syntax noprefix

  .text
  .global dot_product

dot_product:
  pxor xmm0, xmm0
.big_loop:
  cmp rdi, 4
  jl .big_loop_end
  sub rdi, 4
  movups xmm1, [rsi + rdi * 4]
  movups xmm2, [rdx + rdi * 4]
  mulps xmm1, xmm2
  addps xmm0, xmm1

  jmp .big_loop
.big_loop_end:
  haddps xmm0, xmm0
  haddps xmm0, xmm0
.little_loop:
  cmp rdi, 0
  je .done
  sub rdi, 1
  movss xmm1, [rsi + rdi * 4]
  movss xmm2, [rdx + rdi * 4]
  mulss xmm1, xmm2
  addss xmm0, xmm1
  jmp .little_loop
.done:
  ret
