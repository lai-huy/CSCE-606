all: run

clean: 
	rm -f *.gcov *.gcda *.gcno *.out

memory_errors: clean args.h main.cpp
	g++ -std=c++17 -Wall -Wextra -Weffc++ -pedantic-errors -g -o valgrind.out main.cpp
	valgrind --leak-check=full --show-leak-kinds=all -s ./valgrind.out

run: clean args.h main.cpp
	g++ -std=c++17 -Wall -Wextra -Weffc++ -pedantic-errors -g --coverage -o main.out main.cpp
	./main.out
	mv main.out-main.gcda main.gcda
	mv main.out-main.gcno main.gcno
	gcov -mr main.cpp
