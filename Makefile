assTwo.o	:	main.cpp main.hpp cword.hpp
	g++ -Wall -o assTwo.o main.cpp -std=c++17
clean	: 
	rm *.o *.out
archive	:
	tar -czvf main.cpp main.h cword.h
gdb	: main.cpp main.hpp cword.hpp
	g++ -g -Wall -o assTwoGDB.o main.cpp -std=c++17
	gdb -args assTwoGDB.o foo1.txt
