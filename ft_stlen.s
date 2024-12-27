section .text
global ft_strlen

ft_strlen:
    xor rax, rax        ; rax = 0, string uzunluğunu tutacak
.loop:
    cmp byte [rdi + rax], 0  ; string sonuna (null terminator) ulaştık mı?
    je .end             ; Eğer ulaşıldıysa döngüden çık
    inc rax             ; rax'i artır (bir sonraki karaktere geç)
    jmp .loop           ; döngünün başına dön
.end:
    ret                 ; string uzunluğunu döndür
