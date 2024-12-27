section .text
    global ft_write
    extern __errno_location

ft_write:
    mov rax, 1          ; write syscall numarası
    syscall             ; write çağrısını yap
    
    test rax, rax       ; hata kontrolü
    js error            ; rax negatifse hata var
    ret                 ; başarılı ise direkt dön

error:
    neg rax                     ; hata kodunu pozitife çevir
    mov rdi, rax               ; hata kodunu sakla
    call __errno_location      ; errno adresini al
    mov [rax], rdi            ; errno'yu ayarla
    mov rax, -1               ; -1 döndür
    ret