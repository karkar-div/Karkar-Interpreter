build: 
	bison -d src/parser.y -o parser.tab.cpp
	flex src/lexer.l
	g++ lex.yy.c parser.tab.cpp -o interpreter -lm -g
run:
	./interpreter test.txt

clean:
	rm  lex.yy.c 
	rm  parser.tab.cpp
	rm  parser.tab.hpp
