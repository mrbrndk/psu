.486
.model tiny
Code SEGMENT use16
	ASSUME cs:Code,	ds:Code, ss:Code
	org 100h
start:
	mov ax, 0b800h 			;Загрузка в AX адреса сегмента видеобуфера
	mov ds, ax				;Установка es на видеобуфер
	xor ax, ax				;Очистка AX
	mov si, ax				;Запись начала видеобуфера в SI
	mov dx, ax				;Инициализация счетчика

	xor dx, dx
	mov cx, 25
findrow:
    push cx
	mov cx, 80
	next_char: lodsw
		sub al, 58				;Отнимает код символа '9'
		or al, al				;Операция для выставления флагов
		jns	next0				;Прыгаем если флаг пред. операции FLAG_ZERO = 0, т.е если не число
		mov al, al				;Помещаем в bl код символа
		add al, 10				;Прибавляем количество чисел = 10
		or al, al				;Операция для выставления флагов
		js next0				;Прыгаем если флаг пред. операции FLAG_SING = 1, т.е если число
		sub cx, 1				;перемещаем указатель на след строку
		mov ax, 2
		mul cl					
		add si, ax				;добавдяем символы к пройденным
		inc dx					;добавляем кол-во строк с числами
		jmp next_row
	next0:
	loop next_char
next_row:
	pop cx
loop findrow

	push ds 				;Установка регистра ES на адрес видеобуфера 
	pop es 					;из регистра DS 
	xor di, di 				;Очиска DI 
	push cs 				;Установка сегмента данных DS 
	pop ds 					;на сегмент кода CS 
	lea si, Strk 			;В SI загружаем смещение Strk 
	add si, 6 				;Переход в конец строки 
	mov cx, 10 				;В регистр CX  записываем 10 
	mov ax, dx 				;В AX  заносим количество символов ‘ A ’ из DX 
next1: xor dx, dx 			;Очистка DX 
	div cx 					;Делим DX : AX  на CX 
	add dl, 48 				;Прибавляем к остатку код 0 
	mov ds:[si],dl 			;Записываем в строку символ числа 
	or ax, ax 				;Проверка AX  на ноль 
jz next2 					;Если AX =0, то переход на next 2 
	dec si 					;Декремент SI 
	jmp next1 				;Переход на следующую итерацию 
next2: 
	mov ah, 0Fh 			;Загрузка в AH  цвет символов 
next4: 
	lodsb 					;В AL  из DS : SI 
	or al, al 				;Проверка AL  на ноль 
	jz next3 				;Если ноль, то переход на next 3 
	stosw 					;Запись в ES :[ DI ] из AX 
	jmp next4 				;Переход на next 4 
next3: in al, 60h 			;Чтение в AL  из порта 60 h 
	cmp al, 1 				;Проверка на 1 ( ESC ) 
	jnz next3 				;Если неравно, то переход на next 3 
	int 20h 				;Завершение программы 
Strk db 7 dup(0), 0			;Резервирование под строку 
Code ENDS 
end start