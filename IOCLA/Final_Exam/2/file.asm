section .data
    string_fmt: db "%s\n", 10, 0
    int_fmt: db "%d ", 0
    newline_fmt: db 10, 0
    cmp_string: db "AnaAreMere", 0
    test_number_true: db "12345", 0
    test_number_false: db "12b23", 0

section .bss
    ; TODO a: Reserve space for string
    my_string: resd 15

section .text
global main
extern printf
extern scanf

; TODO b: Implement `my_strcmp`
my_strcmp:
    push ebp
    mov ebp, esp

    leave
    ret

; TODO c: Implement `is_number`
is_number:
    push ebp
    mov ebp, esp

    leave
    ret

main:
    push ebp
    mov ebp, esp

    ; TODO a: Read a string from stdin then print it
    xor eax, eax
    mov eax, my_string
    xor ecx, ecx

task1:
    cmp ecx, 5
    je end_task1
    lea eax, [my_string + ecx * 4]
    push eax
    push string_fmt
    call scanf
    add esp, 8

    cmp eax, newline_fmt
    je end_task1

    inc ecx
    jmp task1

end_task1:

    ; TODO c: Call `is_number` with `test_number_true` and `test_number_false`
    ;         as parameters. Print the results, first call should print 1,
    ;         second call should print 0.

    ; TODO d: Call `my_strcmp(buffer_from_a, cmp_string)`

    ; Return 0.
    xor eax, eax
    leave
    ret
