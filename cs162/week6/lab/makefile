CXX = g++
CXXFLAGS = -std=c++11

lab6: main.o LinkedList.o Node.o menu.o validation.o
	${CXX} ${CXXFLAGS} main.o LinkedList.o Node.o menu.o validation.o -o lab6

main.o: main.cpp
	${CXX} ${CXXFLAGS} -c main.cpp

LinkedList.o: LinkedList.cpp
	${CXX} ${CXXFLAGS} -c LinkedList.cpp

Node.o: Node.cpp
	${CXX} ${CXXFLAGS} -c Node.cpp
	
menu.o:	menu.cpp
	${CXX} ${CXXFLAGS} -c menu.cpp
	
validation.o: validation.cpp
	${CXX} ${CXXFLAGS} -c validation.cpp
	
clean:
	rm *.o lab6 
