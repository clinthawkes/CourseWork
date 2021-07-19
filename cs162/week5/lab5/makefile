CXX = g++
CXXFLAGS = -std=c++11

lab5: main.o stringReverse.o sumOfArray.o triangularNumber.o menu.o validation.o
	${CXX} ${CXXFLAGS} main.o stringReverse.o sumOfArray.o triangularNumber.o menu.o validation.o -o lab5

main.o: main.cpp
	${CXX} ${CXXFLAGS} -c main.cpp

stringReverse.o: stringReverse.cpp
	${CXX} ${CXXFLAGS} -c stringReverse.cpp

sumOfArray.o: sumOfArray.cpp
	${CXX} ${CXXFLAGS} -c sumOfArray.cpp
	
triangularNumber.o: triangularNumber.cpp
	${CXX} ${CXXFLAGS} -c triangularNumber.cpp

menu.o:	menu.cpp
	${CXX} ${CXXFLAGS} -c menu.cpp
	
validation.o: validation.cpp
	${CXX} ${CXXFLAGS} -c validation.cpp
	
clean:
	rm *.o lab5 
