main:
	g++ -std=c++23 -Wall -Wextra -Wshadow -Wconversion -Wpedantic -Werror -IstrukturosFailai programaVektoriai.cpp pagalbinesFunkcijos/*.cpp -o main
run: main
	./main
clean:
	rm -f main