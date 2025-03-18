section .text
global FlipVertical
FlipVertical:
    ; Arguments:
    ; rcx: img1 (source)
    ; rdx: img2 (destination)
    ; r8: rows (height)
    ; r9: cols (width)

    ; Assign registers
    mov r10, rcx    ; r10 = img1
    mov r11, rdx    ; r11 = img2
    mov r12, r8     ; r12 = rows
    mov r13, r9     ; r13 = cols

    xor rbx, rbx    ; i = 0
    mov rdi, 3

flip_via_depth:
    cmp rbx, rdi
    jge end_flip_vertical

    xor r14, r14        ; j = 0

flip_via_row:
    cmp r14, r12
    jge next_depth

    xor r15, r15        ; k = 0

flip_via_col:
    cmp r15, r13
    jge next_row

    ; Flip array values based on C logic
    mov rax, [r10 + rbx*8]  ; rax = img1[i]
    mov rsi, r12
    sub rsi, r14
    dec rsi                 ; rsi = rows - j - 1
    mov rdx, [rax + rsi*8]  ; rdx = img1[i][rows - j - 1]
    movzx rax, byte [rdx + r15]  ; rax = img1[i][rows - j - 1][k]

    mov rcx, [r11 + rbx*8]  ; rcx = img2[i]
    mov rdx, [rcx + r14*8]  ; rdx = img2[i][j]
    mov [rdx + r15], al  ; img2[i][j][k] = img1[i][rows - j - 1][k]

    inc r15                 ; k++
    jmp flip_via_col

next_row:
    inc r14                 ; j++
    jmp flip_via_row

next_depth:
    inc rbx                 ; i++
    jmp flip_via_depth

end_flip_vertical:
    ret