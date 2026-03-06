main:
	g++ -std=c++23 -O3 -ffast-math -march=native -flto -Wall -Wextra -Wshadow -Wconversion -Wpedantic -Werror -IstrukturosFailai programaVektoriai.cpp pagalbinesFunkcijos/*.cpp -o main
run: main
	./main
clean:
	rm -f main