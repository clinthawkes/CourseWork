CXX = g++
CXXFLAGS = -std=c++11

project1: main.o ant.o menu.o validation.o
	${CXX} ${CXXFLAGS} main.o ant.o menu.o validation.o -o project1

main.o: main.cpp
	${CXX} ${CXXFLAGS} -c main.cpp

ant.o: ant.cpp
	${CXX} ${CXXFLAGS} -c ant.cpp

menu.o: menu.cpp
	${CXX} ${CXXFLAGS} -c menu.cpp

validation.o: validation.cpp
	${CXX} ${CXXFLAGS} -c validation.cpp
	
clean:
	rm *.o project1
