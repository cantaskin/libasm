section .text
    global ft_strcmp
    extern __errno_location

ft_strcmp:
    ; Null pointer kontrolü
    test rdi, rdi
    jz error
    test rsi, rsi
    jz error

.loop:
    ; İki stringden karakterleri oku ve karşılaştır
    mov al, byte [rdi]    ; İlk stringden karakter
    mov bl, byte [rsi]    ; İkinci stringden karakter
    
    ; Karakterler farklı ise çık
    cmp al, bl
    jne .end
    
    ; Stringin sonuna gelindi mi?
    test al, al
    jz .end
    
    ; Sonraki karakterlere geç
    inc rdi
    inc rsi
    jmp .loop

.end: 
    sub al, bl         ; Calculate difference
    ret                  ; Return full 64-bit value in rax
    

error:
    call __errno_location
    mov dword [rax], 14  ; EFAULT
    mov eax, -1         ; -1 döndür
    ret