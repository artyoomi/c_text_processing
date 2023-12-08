CC = gcc
FLAGS = -g -c

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
	 shiftingWordsInText.o \
	 textStructToString.o \
	 printUniqSymbolsInText.o \
	 printNumOfWordsOfACertainLen.o \

	$(CC) -g main.o printWelcomeMessage.o printManual.o printText.o remSentence.o remDupFromText.o safetyReallocMemToWStr.o safetyReallocMemToWordStructsArray.o safetyReallocMemToSentenceStructsArray.o readSentence.o readText.o shiftingWordsInText.o remWord.o remWordsWithLastUppercaseLetter.o freeText.o textStructToString.o printUniqSymbolsInText.o printNumOfWordsOfACertainLen.o -o cw
	rm -rf *.o

main.o: ./main.c
	$(CC) $(FLAGS) ./main.c 


printWelcomeMessage.o: ./lib/print_functions/printWelcomeMessage.c
	$(CC) $(FLAGS) ./lib/print_functions/printWelcomeMessage.c

printManual.o: ./lib/print_functions/printManual.c 
	$(CC) $(FLAGS) ./lib/print_functions/printManual.c

printUniqSymbolsInText.o: ./lib/print_functions/printUniqSymbolsInText.c
	$(CC) $(FLAGS) ./lib/print_functions/printUniqSymbolsInText.c

printNumOfWordsOfACertainLen.o: ./lib/print_functions/printNumOfWordsOfACertainLen.c
	$(CC) $(FLAGS) ./lib/print_functions/printNumOfWordsOfACertainLen.c

printText.o: ./lib/print_functions/printText.c
	$(CC) $(FLAGS) ./lib/print_functions/printText.c


safetyReallocMemToWStr.o: ./lib/safety_realloc_functions/safetyReallocMemToWStr.c
	$(CC) $(FLAGS) ./lib/safety_realloc_functions/safetyReallocMemToWStr.c

safetyReallocMemToWordStructsArray.o: ./lib/safety_realloc_functions/safetyReallocMemToWordStructsArray.c
	$(CC) $(FLAGS) ./lib/safety_realloc_functions/safetyReallocMemToWordStructsArray.c

safetyReallocMemToSentenceStructsArray.o: ./lib/safety_realloc_functions/safetyReallocMemToSentenceStructsArray.c
	$(CC) $(FLAGS) ./lib/safety_realloc_functions/safetyReallocMemToSentenceStructsArray.c


readSentence.o: ./lib/read_functions/readSentence.c
	$(CC) $(FLAGS) ./lib/read_functions/readSentence.c

readText.o: ./lib/read_functions/readText.c
	$(CC) $(FLAGS) ./lib/read_functions/readText.c


remSentence.o: ./lib/remove_functions/remSentence.c
	$(CC) $(FLAGS) ./lib/remove_functions/remSentence.c  

remDupFromText.o: ./lib/remove_functions/remDupFromText.c
	$(CC) $(FLAGS) ./lib/remove_functions/remDupFromText.c

remWord.o: ./lib/remove_functions/remWord.c
	$(CC) $(FLAGS) ./lib/remove_functions/remWord.c

remWordsWithLastUppercaseLetter.o: ./lib/remove_functions/remWordsWithLastUppercaseLetter.c
	$(CC) $(FLAGS) ./lib/remove_functions/remWordsWithLastUppercaseLetter.c


shiftingWordsInText.o: ./lib/shifting_functions/shiftingWordsInText.c
	$(CC) $(FLAGS) ./lib/shifting_functions/shiftingWordsInText.c


textStructToString.o: ./lib/textStructToString.c
	$(CC) $(FLAGS) ./lib/textStructToString.c

freeText.o: ./lib/freeText.c
	$(CC) $(FLAGS) ./lib/freeText.c

clean:
	rm -rf *.o
	rm -rf cw

rebuild: clean all
