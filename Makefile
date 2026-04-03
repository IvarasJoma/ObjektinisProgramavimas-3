O3fast:
	g++ -std=c++23 -O3 -ffast-math -march=native -flto -Wall -Wextra -Wshadow -Wconversion -Wpedantic -Werror -IstrukturosFailai programaVektoriai.cpp pagalbinesFunkcijos/*.cpp Studentas.cpp -o O3fast
O3:
	g++ -std=c++23 -O3 -march=native -flto -Wall -Wextra -Wshadow -Wconversion -Wpedantic -Werror -IstrukturosFailai programaVektoriai.cpp pagalbinesFunkcijos/*.cpp Studentas.cpp -o O3
O2:
	g++ -std=c++23 -O2 -march=native -flto -Wall -Wextra -Wshadow -Wconversion -Wpedantic -Werror -IstrukturosFailai programaVektoriai.cpp pagalbinesFunkcijos/*.cpp Studentas.cpp -o O2
O1:
	g++ -std=c++23 -O1 -march=native -flto -Wall -Wextra -Wshadow -Wconversion -Wpedantic -Werror -IstrukturosFailai programaVektoriai.cpp pagalbinesFunkcijos/*.cpp Studentas.cpp -o O1
runO1: O1
	./O1
runO2: O2
	./O2
runO3: O3
	./O3
runO3fast: O3fast
	./O3fast
clean:
	rm -f O1 O2 O3