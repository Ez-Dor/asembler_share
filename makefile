assembler : input_collector.o main.o parser.o text_validation_func.o
	gcc -g -ansi -Wall input_collector.o main.o parser.o text_validation_func.o -lm -pedantic -o assembler

input_collector.o : input_collector.c asembler.h
	gcc -c -g -ansi input_collector.c -lm -Wall -pedantic -o input_collector.o 

text_validation_func.o : text_validation_func.c asembler.h
	gcc -c  -g -ansi text_validation_func.c -lm -Wall -pedantic -o text_validation_func.o 

parser.o : parser.c asembler.h
	gcc -c -g -ansi parser.c -lm -Wall -pedantic -o parser.o 

main.o : main.c asembler.h
	gcc -c  -g -ansi main.c -lm -Wall -pedantic -o main.o 
