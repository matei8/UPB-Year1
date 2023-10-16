%include "utils/printf32.asm"

extern printf

section .bss:
	; structura pentru o bautura
	struc beverage_t
		id:			resd	1	; id bautura = index in v_beverages
		bvg_name:	resb	10	; char[10] - nume bautura
	endstruc

	; structura pentru un angajat
	struc emp_t
		emp_name:	resb	10	; char[10] - nume angajat
		bvg_id:		resd	1	; integer - bautura ceruta = index in v_beverages
		drinking:	resd	1	; "bool" - 1 daca va consuma alcool, 0 daca nu
	endstruc

section .data
	vanilla_text:		db "Vanilla", 0

	v_beverages_count:	dd 3
	v_emp_count:		dd 5

	v_beverages:
		istruc beverage_t
			at id,			dd 0
			at bvg_name,	db "Rum", 0
		iend

		istruc beverage_t
			at id,			dd 1
			at bvg_name,	db "Whiskey", 0
		iend

		istruc beverage_t
			at id,			dd 2
			at bvg_name,	db "Beer", 0
		iend

	v_emp:
		istruc emp_t
			at emp_name,	db "John", 0
			at bvg_id,		dd 0
			at drinking,	dd 1
		iend

		istruc emp_t
			at emp_name,	db "Mark", 0
			at bvg_id,		dd 1
			at drinking,	dd 1
		iend

		istruc emp_t
			at emp_name,	db "Maria", 0
			at bvg_id,		dd 1
			at drinking,	dd 1
		iend

		istruc emp_t
			at emp_name,	db "George", 0
			at bvg_id,		dd 2
			at drinking,	dd 1
		iend

		istruc emp_t
			at emp_name,	db "Elsa", 0
			at bvg_id,		dd 0
			at drinking,	dd 0
		iend

section .text
global main

main:
	push ebp
	mov ebp, esp

	;; Freestyle starts here

	PRINTF32 `Here comes a) and maybe c)\n\n\x0`

	; TODO a:	Print employee names from v_emp.
	xor ecx, ecx
	xor eax, eax
	xor ebx, ebx
	mov ecx, 0
	mov edi, dword [v_emp_count]
	lea ebx, v_emp

task1:
	cmp ecx, edi
	je end_task1

	mov eax, 18
	mul ecx
	lea esi, [ebx + eax + emp_t + emp_name]
	PRINTF32 `%s\n\x0`, esi
	inc ecx
	jmp task1

end_task1:
	PRINTF32 `\nHere comes b)\n\n\x0`

	; TODO b:	Print beverage names from v_beverages.
	xor eax, eax
	xor ecx, ecx
	xor ebx, ebx
	xor ecx, ecx
	xor esi, esi
	xor edi, edi

	mov ecx, 0
	mov edi, dword [v_beverages_count]
	lea ebx, v_beverages
task2:
	cmp ecx, edi
	je end_task2

	mov eax, 14
	mul ecx
	lea esi, [ebx + eax + beverage_t + bvg_name]
	PRINTF32 `%s\n\x0`, esi
	inc ecx
	jmp task2	

end_task2:

	PRINTF32 `\nHere comes c) or not xd\n\n\x0`

	; TODO c:	For each employee print their chosen drink or vanilla otherwise.
	; You can solve this task by modifying a) or below this comment.
	xor ecx, ecx
	xor eax, eax
	xor ebx, ebx
	xor edi, edi
	mov ecx, 0
	mov edi, dword [v_emp_count]
	lea ebx, v_emp

task3:
	cmp ecx, edi
	je end_task3

	mov eax, 18
	mul ecx

	lea esi, [ebx + eax + emp_t + drinking]

	mov edx, dword [esi]
	cmp edx, 0
	je print_name

	lea esi, [ebx + eax + emp_t + emp_name]
	PRINTF32 `%s \x0`, esi
	
	lea esi,  [ebx + eax + emp_t + bvg_id]
	mov edx, dword [esi]
	cmp edx, 0
	je print_rom

	cmp edx, 1
	je print_whisky

	cmp edx, 2
	je print_beer

	inc ecx
	jmp task3

print_rom:
	PRINTF32 `Rum\n\x0`
	inc ecx
	jmp task3

print_whisky:
	PRINTF32 `Whiskey\n\x0`
	inc ecx
	jmp task3
	
print_beer:
	PRINTF32 `Beer\n\x0`
	inc ecx
	jmp task3
print_name:
	lea esi, [ebx + eax + emp_t + emp_name]
	PRINTF32 `%s \x0`, esi
	PRINTF32 `%s\n\x0`, vanilla_text
	inc ecx
	jmp task3


end_task3:
	;; Freestyle ends here

	; Return 0.
	xor eax, eax
	leave
	ret
