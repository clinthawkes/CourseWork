CXX = g++
CXXFLAGS = -std=c++11

project2: main.o Zoo.o Animal.o Penguin.o Tiger.o Turtle.o validation.o
	${CXX} ${CXXFLAGS} main.o Zoo.o Animal.o Penguin.o Tiger.o Turtle.o validation.o -o project2

main.o: main.cpp
	${CXX} ${CXXFLAGS} -c main.cpp

Zoo.o: Zoo.cpp
	${CXX} ${CXXFLAGS} -c Zoo.cpp

Animal.o: Animal.cpp
	${CXX} ${CXXFLAGS} -c Animal.cpp
	
Penguin.o: Penguin.cpp
	${CXX} ${CXXFLAGS} -c Penguin.cpp

Tiger.o: Tiger.cpp
	${CXX} ${CXXFLAGS} -c Tiger.cpp
	
Turtle.o: Turtle.cpp
	${CXX} ${CXXFLAGS} -c Turtle.cpp
	
validation.o: validation.cpp
	${CXX} ${CXXFLAGS} -c validation.cpp
	
clean:
	rm *.o project2
