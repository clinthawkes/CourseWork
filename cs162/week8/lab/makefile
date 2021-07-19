CXX = g++
CXXFLAGS = -std=c++11

lab8: main.o Test.o validation.o
	${CXX} ${CXXFLAGS} main.o Test.o validation.o -o lab8

main.o: main.cpp
	${CXX} ${CXXFLAGS} -c main.cpp

Test.o:	Test.cpp
	${CXX} ${CXXFLAGS} -c Test.cpp
	
validation.o: validation.cpp
	${CXX} ${CXXFLAGS} -c validation.cpp
	
clean:
	rm *.o lab8
