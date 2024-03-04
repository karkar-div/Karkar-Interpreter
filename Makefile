build: 
	bison -d src/parser.y -o parser.tab.cpp
	flex src/lexer.l
	g++ src/main.cpp lex.yy.c  -o bin/interpreter -lm -g

build-unit-test: 
	bison -d src/parser.y -o parser.tab.cpp
	flex src/lexer.l
	g++ src/main-unti-test-1.cpp lex.yy.c  -o bin/interpreter-test-1 -lm -g

release: 
	bison -d src/parser.y -o parser.tab.cpp
	flex src/lexer.l
	g++ src/main.cpp lex.yy.c  -o bin/interpreter -lm -O3

test-memory-leaks:
	valgrind bin/interpreter-test-1 tests/test.kk
	valgrind bin/interpreter        tests/test.kk

run:
	@ bin/./interpreter tests/test.kk

clean:
	rm  lex.yy.c 
	rm  parser.tab.cpp
	rm  parser.tab.hpp
