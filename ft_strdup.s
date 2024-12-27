section .text
    extern malloc
    extern __errno_location
    global ft_strdup
    extern ft_strlen
    extern ft_strcpy

ft_strdup:
    push rdi                ; Kaynak stringi sakla
    call ft_strlen         ; Uzunluğu hesapla

    inc rax                ; Null byte için +1
    push rax               ; Uzunluğu sakla
    mov rdi, rax          ; Malloc için parametre
    call malloc           ; Bellek ayır

    test rax, rax         ; Malloc başarılı mı?
    jz error              ; Başarısızsa error'a git

    mov rdi, rax          ; Hedef adres
    pop rcx               ; Uzunluğu geri al
    pop rsi               ; Kaynak stringi geri al
    push rax              ; Malloc adresini sakla
    
    call ft_strcpy        ; Stringi kopyala
    pop rax               ; Return değerini ayarla
    ret

error:
    call __errno_location
    mov dword [rax], 12   ; ENOMEM
    pop rcx               ; Stack cleanup
    pop rdi               ; Stack cleanup
    xor rax, rax          ; NULL return
    ret