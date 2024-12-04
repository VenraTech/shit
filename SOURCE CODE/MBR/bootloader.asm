; BY CYBERWARE
BITS 16
ORG 0x7C00

WSCREEN equ 320
HSCREEN equ 200

; Setup do vídeo e configuração inicial
setup:
    ; Configura o modo gráfico 13h (320x200, 256 cores)
    mov ah, 0x00
    mov al, 0x13
    int 0x10

    ; Configura o segmento de vídeo (0xA000)
    push 0xA000
    pop es

    ; Inicializa os registradores
    xor al, al
    xor bx, bx
    xor cx, cx
    mov dx, 0x08 
    
    fninit

    call rainbow_effect
    ret

rainbow_effect:
    ; Loop de pixels para preencher a tela
    xor cx, cx 
    xor dx, dx

pixel_loop:
    ; Verifica se a linha já terminou
    cmp cx, WSCREEN
    jae nextline

    mov al, cl
    add al, dl
    and al, 0x3F

    ; Define o pixel na posição (CX, DX) com a cor calculada
    mov ah, 0x0C 
    int 0x10

    ; Incrementa a posição X
    inc cx
    jmp pixel_loop

nextline:
    xor cx, cx
    inc dx             ; Move para a próxima linha
    cmp dx, WSCREEN
    jmp pixel_loop


; Assinatura do setor de inicialização
times 510 - ($ - $$) db 0
dw 0xAA55