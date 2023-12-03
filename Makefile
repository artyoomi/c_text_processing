all: main.o \
	 printWelcomeMessage.o \
	 printManual.o \
	 printText.o \
	 remSentence.o \
	 remDupFromText.o \
	 safetyReallocMemToWStr.o \
	 safetyReallocMemToWordStructsArray.o \
	 safetyReallocMemToSentenceStructsArray.o \
	 readSentence.o \
	 readText.o \
	 remWord.o \
	 remWordsWithLastUppercaseLetter.o \
	 freeText.o \
	 printSentenceWithNumberN.o \
	 shiftingWordsInText.o

	gcc main.o printWelcomeMessage.o printManual.o printText.o remSentence.o remDupFromText.o safetyReallocMemToWStr.o safetyReallocMemToWordStructsArray.o safetyReallocMemToSentenceStructsArray.o readSentence.o readText.o shiftingWordsInText.o remWord.o remWordsWithLastUppercaseLetter.o freeText.o printSentenceWithNumberN.o -o main

main.o: ./source/main.c
	gcc -c ./source/main.c 

printWelcomeMessage.o: ./source/lib/printWelcomeMessage.c
	gcc -c ./source/lib/printWelcomeMessage.c

printManual.o: ./source/lib/printManual.c 
	gcc -c ./source/lib/printManual.c

safetyReallocMemToWStr.o: ./source/lib/safetyReallocMemToWStr.c
	gcc -c ./source/lib/safetyReallocMemToWStr.c

safetyReallocMemToWordStructsArray.o: ./source/lib/safetyReallocMemToWordStructsArray.c
	gcc -c ./source/lib/safetyReallocMemToWordStructsArray.c

safetyReallocMemToSentenceStructsArray.o: ./source/lib/safetyReallocMemToSentenceStructsArray.c
	gcc -c ./source/lib/safetyReallocMemToSentenceStructsArray.c

readSentence.o: ./source/lib/readSentence.c
	gcc -c ./source/lib/readSentence.c

readText.o: ./source/lib/readText.c
	gcc -c ./source/lib/readText.c

remSentence.o: ./source/lib/remSentence.c
	gcc -c ./source/lib/remSentence.c  

remDupFromText.o: ./source/lib/remDupFromText.c
	gcc -c ./source/lib/remDupFromText.c  

printSentenceWithNumberN.o: ./source/lib/printSentenceWithNumberN.c
	gcc -c ./source/lib/printSentenceWithNumberN.c

printText.o: ./source/lib/printText.c
	gcc -c ./source/lib/printText.c

shiftingWordsInText.o: ./source/lib/shiftingWordsInText.c
	gcc -c ./source/lib/shiftingWordsInText.c

remWord.o: ./source/lib/remWord.c
	gcc -c ./source/lib/remWord.c

remWordsWithLastUppercaseLetter.o: ./source/lib/remWordsWithLastUppercaseLetter.c
	gcc -c ./source/lib/remWordsWithLastUppercaseLetter.c

freeText.o: ./source/lib/freeText.c
	gcc -c ./source/lib/freeText.c

clean: all
	rm -rf *.o 