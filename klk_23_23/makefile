CC = gcc
CFLAGS = -Wall -Wextra



izvrsni: potisni.o lex.yy.o
	$(CC) $(CFLAGS) -o $@ $^
lex.yy.o: lex.yy.c tokeni.h
	$(CC) $(CFLAGS) -c $<
lex.yy.c: lexer.lex
	flex $<
potisni.o: potisni.c tokeni.h
	$(CC) $(CFLAGS) -c $<


.PHONY: clean
clean:
	-rm -f *.o lex.yy.c izvrsni
