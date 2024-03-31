CC = gcc
CFLAGS = -Wall -Wextra



izvrsni: lex.yy.o parser_v.o
	$(CC) $(CFLAGS) -o $@ $^
lex.yy.o: lex.yy.c tokeni_v.h
	$(CC) $(CFLAGS) -c $<
lex.yy.c: lekser.lex
	flex $<
parser_v.o: parser_v.c tokeni_v.h
	$(CC) $(CLFAGS) -c $<

.PHONY: clean
clean:
	rm -f *.o izvrsni lex.yy.c
