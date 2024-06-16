CXX = g++
CXXFLAGS = -Wall -Wextra


izvrsni: lex.yy.o parser.tab.o
		$(CXX) $(CXXFLAGS) -o $@ $^
lex.yy.o: lex.yy.c parser.tab.hpp
		$(CXX) $(CXXFLAGS) -c $<
lex.yy.c: lexer.lex
		flex $<
parser.tab.o: parser.tab.cpp
		$(CXX) $(CXXFLAGS) -c $<
parser.tab.cpp parser.tab.hpp: parser.ypp
		bison -dv $<


.PHONY: clean
clean: 
		-rm -f parser.output parser.tab* izvrsni lex.yy*