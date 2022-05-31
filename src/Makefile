CXXFLAGS = -g -Wall -Wextra -std=c++11
CXX=g++

# nom de l'executable
project=main

all: ${project}

# edition des liens
${project}: main.o caractere.o utility.o
	${CXX} $^ -o ${project}

# compilation
main.o: main.cpp
caractere.o: caractere.cpp caractere.hpp
utility.o: utility.cpp utility.hpp

clean:
	rm -f *~  *.o ${project}