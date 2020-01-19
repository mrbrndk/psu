;(2*C-D+23)/(A/4-1)
.486										;Указание набора команд
.model small								;small - модель памяти EXE-программы
Data SEGMENT use16
	ASSUME ds:Data
	ValA dw -100                            ;Значение A
	ValB dw 25                              ;Значение B
	ValC dw 200                             ;Значение C
	ValD dw -150                            ;Значение D
	Sign db 0                               ;Признак отрицательного значения
	Strk db 7 dup(0), 0                     ;Резервирование памяти под строку
Data ENDS
Stk SEGMENT use16 STACK
	ASSUME ss:Stk
	dw 256 dup(0)
Stk ENDS
Code SEGMENT use16
ASSUME cs:Code
start:
	mov ax, seg ValB                        ;Запись в AX сегмента Data
	mov ds, ax                              ;Запись в DS AX
	mov ax, ValC                            ;Запись в AX значение C
	mov cx, 2                               ;Запись в CX значение 2
	imul cx                                 ;Умножение AX*CX -> DX:AX
	;=======================================
	sub ax, ValD							;вычитаем D
	add ax, 23								;прибавляем 23
	push ax									;запись в стек
	;=======================================
	mov ax, ValA                            ;Запись в AX значение A
	xor dx, dx								;очищаем dx
	or ax, ax                               ;Проверка AX на ноль
	jns next0                               ;Если число > 0, то переход на next0
	not dx                                  ;Преобразуем DX как верхнюю часть отрицательного числа DX:AX
	;=======================================
next0:
	mov cx, 4                               ;Записываем в CX делитель 4
	idiv cx                                 ;Делим DX:AX на CX
	sub ax, 1								;вычитаем 1
	mov bx, ax								;записываем правую скобку в bx
	pop ax									;записываем в ax из стека левую скобку
	xor dx, dx								;очищаем dx
	or ax, ax                               ;Проверка AX на ноль
	jns next1                               ;Если число > 0, то переход на next0
	not dx                                  ;Преобразуем DX как верхнюю часть отрицательного числа DX:AX
	;=======================================
next1:
	idiv bx									;делим ax на bx
	;=======================================; Вывод результата
	or ax, ax                               ;Проверка AX на ноль
	jns next2                               ;Если число > 0, то переход на next2
	neg ax                                  ;Преобразуем в положительное число
	mov byte ptr Sign, 1                    ;Сохраняем в Sign признак отрицательного результата
next2:
	lea si, Strk                            ;Загружаем в SI смещение Strk
	add si, 6                               ;Переходим в конец строки
	mov cx, 10                              ;Заносим в CX значение 10
next3:
	xor dx, dx								;Очистка DX
	div cx									;Деление DX:AX / CX
	add dl, 48								;Суммируем остаток с кодом ‘0’
	mov ds:[si], dl							;Записываем в строку
	or ax, ax								;Проверка AX на ноль
	jz next4								;Если ноль, то переходим на next8
	dec si									;Уменьшаем SI на 1
	jmp next3								;Переход на next7
next4:
	mov ax, 0b800h							;Заносим в AX адрес сегмента видеобуфера
	mov es, ax								;Устанавливаем ES на видеобуфер
	xor di, di								;Очистка DI
	mov ah, 0Fh								;В AH записываем код цвета
	cmp byte ptr Sign, 1					;Если результат был положительным, то
	jnz next5								;переход на next9
	mov al, '-'								;Записываем в AL код ‘-’
	stosw									;Запись AX в ES:[DI]
next5:
	lodsb									;Загрузка в AL из DS:[SI]
	or al, al								;Проверка AL на ноль
	jz nextA								;Если ноль, то переход на nextA
	stosw									;Запись AX в ES:[DI]
	jmp next5								;Переход на next9
next6:
	in al, 60h								;Чтение в AL из порта 60h
	cmp al, 1								;Сравнение с 1 (ESC)
	jnz next6								;Если не равно, то переход на nextA
	mov ax, 4c00h							;Запись в AX номер функции выхода
	int 21h									;Завершение программы
	
Code ENDS
end start