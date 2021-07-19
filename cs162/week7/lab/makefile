CXX = g++
CXXFLAGS = -std=c++11

lab7: main.o Queue.o menu.o validation.o
	${CXX} ${CXXFLAGS} main.o Queue.o menu.o validation.o -o lab7

main.o: main.cpp
	${CXX} ${CXXFLAGS} -c main.cpp

Queue.o: Queue.cpp
	${CXX} ${CXXFLAGS} -c Queue.cpp
	
menu.o:	menu.cpp
	${CXX} ${CXXFLAGS} -c menu.cpp
	
validation.o: validation.cpp
	${CXX} ${CXXFLAGS} -c validation.cpp
	
clean:
	rm *.o lab7 
