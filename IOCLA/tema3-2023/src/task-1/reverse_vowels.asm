section .data
	; declare global vars here
	vocale dw 'aeiou', 0

section .text
	global reverse_vowels

;;	void reverse_vowels(char *string)
;	Cauta toate vocalele din string-ul `string` si afiseaza-le
;	in ordine inversa. Consoanele raman nemodificate.
;	Modificare se va face in-place
reverse_vowels:
	push ebp
	push esp
	pop ebp
	pusha

	push dword [ebp + 8]
	pop esi ; stocam stringul dat ca argument in esi

itereaza_string:
	xor eax, eax
	add al, byte [esi + ecx]

	cmp al, 0 ; verific daca am ajuns la capatul stringului
	je replace_vowels

	xor edx, edx
	jmp vector_vocale

inc_contor:
	inc ecx
	jmp itereaza_string

push_vowel:
	push eax ; pun vocala  pe stiva
	jmp inc_contor

pop_vowel:
	pop eax
	and byte [esi + ecx], 0
	add byte [esi + ecx], al
	jmp cont2

replace_vowels:
	xor ecx, ecx
	
itereaza_string2:
	xor eax, eax
	add al, byte [esi + ecx]
	cmp al, 0 ; verific daca am ajuns la capatul stringului
	je end
	xor edx, edx
	jmp vector_vocale2

cont2:
	inc ecx
	jmp itereaza_string2


vector_vocale: ; parcurg vectorul de vocale ca sa verific daca elemntul curent este una
	cmp edx, 5
	je inc_contor
	cmp al, [vocale + edx]
	je push_vowel ; daca e vocala o pun pe stiva
	inc edx
	jmp vector_vocale

vector_vocale2:
	cmp edx, 5
	je cont2
	cmp al, [vocale + edx]
	je pop_vowel ; daca este o vocala o inlocuiesc cu vocala din varful stivei
	inc edx
	jmp vector_vocale2
end:
	popa
	pop ebp
	ret