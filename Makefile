build: 
	bison -d src/parser.y -o parser.tab.cpp
	flex src/lexer.l
	g++ src/main.cpp lex.yy.c  -o bin/interpreter -lm -g
	rm lex.yy.c
	rm parser.tab.cpp
	rm parser.tab.hpp

build-unit-test: 
	bison -d src/parser.y -o parser.tab.cpp
	flex src/lexer.l
	g++ src/main-unti-test-1.cpp lex.yy.c  -o bin/interpreter-test-1 -lm -g
	rm lex.yy.c
	rm parser.tab.cpp
	rm parser.tab.hpp

release: 
	bison -d src/parser.y -o parser.tab.cpp
	flex src/lexer.l
	g++ src/main.cpp lex.yy.c  -o bin/interpreter -lm -O3
	rm lex.yy.c
	rm parser.tab.cpp
	rm parser.tab.hpp


test-memory-leaks:
	valgrind bin/interpreter-test-1 tests/test.kk
	valgrind bin/interpreter        tests/test.kk

run:
	@ bin/./interpreter test.kk

clean:
	rm  lex.yy.c 
	rm  parser.tab.cpp
	rm  parser.tab.hpp
