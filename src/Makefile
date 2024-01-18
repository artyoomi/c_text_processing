TARGET=cw
CC=gcc
LINK_FLAGS=-g
COMP_FLAGS=-g -c

OBJ=main.o \
	readSentence.o \
	readText.o \
	printWelcomeMessage.o \
	printManual.o \
	printUniqSymbolsInText.o \
	printNumOfWordsOfACertainLen.o \
	printText.o \
	safetyReallocMemToWStr.o \
	safetyReallocMemToWordStructsArray.o \
	safetyReallocMemToSentenceStructsArray.o \
	remSentence.o \
	remDupFromText.o \
	remWord.o \
	remWordsWithLastUppercaseLetter.o \
	shiftingWordsInText.o \
	textStructToString.o \
	freeText.o \
	freeSentence.o \
	addSmile.o

$(TARGET): $(OBJ)
	$(CC) $(LINK_FLAGS) $(OBJ) -o $(TARGET)
	rm -rf *.o

main.o: ./main.c
	$(CC) $(COMP_FLAGS) ./main.c 


readSentence.o: ./lib/read_functions/readSentence.c
	$(CC) $(COMP_FLAGS) ./lib/read_functions/readSentence.c
readText.o: ./lib/read_functions/readText.c
	$(CC) $(COMP_FLAGS) ./lib/read_functions/readText.c


printWelcomeMessage.o: ./lib/print_functions/printWelcomeMessage.c
	$(CC) $(COMP_FLAGS) ./lib/print_functions/printWelcomeMessage.c
printManual.o: ./lib/print_functions/printManual.c 
	$(CC) $(COMP_FLAGS) ./lib/print_functions/printManual.c
printUniqSymbolsInText.o: ./lib/print_functions/printUniqSymbolsInText.c
	$(CC) $(COMP_FLAGS) ./lib/print_functions/printUniqSymbolsInText.c
printNumOfWordsOfACertainLen.o: ./lib/print_functions/printNumOfWordsOfACertainLen.c
	$(CC) $(COMP_FLAGS) ./lib/print_functions/printNumOfWordsOfACertainLen.c
printText.o: ./lib/print_functions/printText.c
	$(CC) $(COMP_FLAGS) ./lib/print_functions/printText.c


safetyReallocMemToWStr.o: ./lib/safety_realloc_functions/safetyReallocMemToWStr.c
	$(CC) $(COMP_FLAGS) ./lib/safety_realloc_functions/safetyReallocMemToWStr.c
safetyReallocMemToWordStructsArray.o: ./lib/safety_realloc_functions/safetyReallocMemToWordStructsArray.c
	$(CC) $(COMP_FLAGS) ./lib/safety_realloc_functions/safetyReallocMemToWordStructsArray.c
safetyReallocMemToSentenceStructsArray.o: ./lib/safety_realloc_functions/safetyReallocMemToSentenceStructsArray.c
	$(CC) $(COMP_FLAGS) ./lib/safety_realloc_functions/safetyReallocMemToSentenceStructsArray.c


remSentence.o: ./lib/remove_functions/remSentence.c
	$(CC) $(COMP_FLAGS) ./lib/remove_functions/remSentence.c  
remDupFromText.o: ./lib/remove_functions/remDupFromText.c
	$(CC) $(COMP_FLAGS) ./lib/remove_functions/remDupFromText.c
remWord.o: ./lib/remove_functions/remWord.c
	$(CC) $(COMP_FLAGS) ./lib/remove_functions/remWord.c
remWordsWithLastUppercaseLetter.o: ./lib/remove_functions/remWordsWithLastUppercaseLetter.c
	$(CC) $(COMP_FLAGS) ./lib/remove_functions/remWordsWithLastUppercaseLetter.c


shiftingWordsInText.o: ./lib/shifting_functions/shiftingWordsInText.c
	$(CC) $(COMP_FLAGS) ./lib/shifting_functions/shiftingWordsInText.c


textStructToString.o: ./lib/textStructToString.c
	$(CC) $(COMP_FLAGS) ./lib/textStructToString.c

freeText.o: ./lib/free_functions/freeText.c
	$(CC) $(COMP_FLAGS) ./lib/free_functions/freeText.c
freeSentence.o: ./lib/free_functions/freeSentence.c
	$(CC) $(COMP_FLAGS) ./lib/free_functions/freeSentence.c

addSmile.o: ./lib/def_task/addSmile.c
	$(CC) $(COMP_FLAGS) ./lib/def_task/addSmile.c


clean:
	rm -rf *.o
	rm -rf $(TARGET)


rebuild: clean $(TARGET)
