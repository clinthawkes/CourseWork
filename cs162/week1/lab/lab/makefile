CXX = g++
CXXFLAGS = -std=c++11

lab1: main.o readMatrix.o determinant.o
	${CXX} ${CXXFLAGS} main.o readMatrix.o determinant.o -o lab1

main.o: main.cpp
	${CXX} ${CXXFLAGS} -c main.cpp

readMatrix.o: readMatrix.cpp
	${CXX} ${CXXFLAGS} -c readMatrix.cpp

determinant.o: determinant.cpp
	${CXX} ${CXXFLAGS} -c determinant.cpp

clean:
	rm *.o lab1
