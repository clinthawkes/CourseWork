CXX = g++
CXXFLAGS = -std=c++11

lab3: main.o Game.o Die.o LoadedDie.o validation.o
	${CXX} ${CXXFLAGS} main.o Game.o Die.o LoadedDie.o validation.o -o lab3

main.o: main.cpp
	${CXX} ${CXXFLAGS} -c main.cpp

Game.o: Game.cpp
	${CXX} ${CXXFLAGS} -c Game.cpp

Die.o: Die.cpp
	${CXX} ${CXXFLAGS} -c Die.cpp
	
LoadedDie.o: LoadedDie.cpp
	${CXX} ${CXXFLAGS} -c LoadedDie.cpp

validation.o: validation.cpp
	${CXX} ${CXXFLAGS} -c validation.cpp
	
clean:
	rm *.o lab3
