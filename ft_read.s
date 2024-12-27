section .text
    global ft_read
    extern __errno_location

ft_read:
    mov rax, 0          ; read syscall numarası
    syscall             ; syscall çağrısı
    
    test rax, rax       ; hata kontrolü
    js error            ; negatifse hata var
    ret                 ; başarılıysa direkt dön

error:
    neg rax                     ; hata kodunu pozitife çevir
    mov rdi, rax               ; hata kodunu sakla
    call __errno_location      ; errno adresini al
    mov [rax], rdi            ; errno'yu ayarla
    mov rax, -1               ; -1 döndür
    ret