CFLAGS = -Wall -g -pthread -pedantic

all: i-banco

i-banco: commandlinereader.o contas.o i-banco.o
	gcc $(CFLAGS) -o i-banco i-banco.o commandlinereader.o contas.o

terminal: i-banco-terminal.o commandlinereader.o contas.o
	gcc $(CFLAGS) -o i-banco-terminal i-banco-terminal.o commandlinereader.o contas.o

i-banco.o: i-banco.c commandlinereader.h contas.h commandlinereader.c contas.c
	gcc $(CFLAGS) -c i-banco.c

i-banco-terminal.o: i-banco-terminal.c
	gcc $(CFLAGS) -c i-banco-terminal.c

contas.o: contas.c contas.h
	gcc $(CFLAGS) -c contas.c

commandlinereader.o: commandlinereader.c commandlinereader.h
	gcc $(CFLAGS) -c commandlinereader.c

clean:
	rm -f *.o i-banco i-banco-terminal *.txt

run:
	./i-banco

run-term:
	./i-banco-terminal i-banco-pipe
