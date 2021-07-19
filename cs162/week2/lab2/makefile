CXX = g++
CXXFLAGS = -std=c++11

lab2: main.o count_letters.o output_letters.o
	${CXX} ${CXXFLAGS} main.o count_letters.o output_letters.o -o lab2

main.o: main.cpp
	${CXX} ${CXXFLAGS} -c main.cpp

count_letters.o: count_letters.cpp
	${CXX} ${CXXFLAGS} -c count_letters.cpp

output_letters.o: output_letters.cpp
	${CXX} ${CXXFLAGS} -c output_letters.cpp

clean:
	rm *.o lab2
