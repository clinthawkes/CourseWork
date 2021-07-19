CXX = g++
CXXFLAGS = -std=c++11

lab9: main.o Simulation.o menu.o validation.o
	${CXX} ${CXXFLAGS} main.o Simulation.o menu.o validation.o -o lab9

main.o: main.cpp
	${CXX} ${CXXFLAGS} -c main.cpp

Simulation.o: Simulation.cpp
	${CXX} ${CXXFLAGS} -c Simulation.cpp
	
menu.o:	menu.cpp
	${CXX} ${CXXFLAGS} -c menu.cpp
	
validation.o: validation.cpp
	${CXX} ${CXXFLAGS} -c validation.cpp
	
clean:
	rm *.o lab9
