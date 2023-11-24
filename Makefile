all: main.o printManual.o printWelcomeMessage.o
	gcc main.o printManual.o printWelcomeMessage.o -o main
main.o:
	gcc -c main.c
printManual.o:
	gcc -c printManual.c
printWelcomeMessage.o:
	gcc -c printWelcomeMessage.c
clean: all
	rm *.o
