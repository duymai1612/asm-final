compile:
	nasm -g -f elf encode.asm
	nasm -g -f elf decode.asm
	gcc main.c encode.o decode.o -o main.out -m32

run:
	./main.out
