section .text
global ft_strcpy

ft_strcpy:
    push rdi            ; dest adresini sakla
.loop:
    mov al, byte [rsi]  ; src'deki bir baytı al
    mov byte [rdi], al  ; dest'e yaz
    inc rsi             ; src pointer'ını artır
    inc rdi             ; dest pointer'ını artır
    test al, al         ; null karaktere ulaştık mı?
    jnz .loop           ; eğer null değilse döngüye devam et
    pop rax             ; dest adresini geri yükle (return value)
    ret                 ; dest pointer'ını döndür
