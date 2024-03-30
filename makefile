CC = gcc
CFLAGS = -Wall -Wextra



izvrsni: parser_v.o lex.yy.o
	$(CC) $(CFLAGS) -o $@ $^
lex.yy.o: lex.yy.c tokeni_v.h
	$(CC) $(CFLAGS) -c $<
lex.yy.c: lekser_v.lex
	flex $<
parser_v.o: parser_v.c tokeni_v.h
	$(CC) $(CFLAGS) -c $<


.PHONY: clean
clean:
	rm -f *.o izvrsni lex.yy.c
