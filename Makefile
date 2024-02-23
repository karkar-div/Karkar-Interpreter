build: 
	bison -d src/parser.y -o parser.tab.cpp
	flex src/lexer.l
	g++ src/main.cpp lex.yy.c  -o bin/interpreter -lm

run:
	@ bin/./interpreter test.txt

clean:
	rm  lex.yy.c 
	rm  parser.tab.cpp
	rm  parser.tab.hpp
