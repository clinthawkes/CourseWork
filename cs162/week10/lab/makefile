CXX = g++
CXXFLAGS = -std=c++11

lab10: main.o fibRec.o fibNonRec.o validation.o
	${CXX} ${CXXFLAGS} main.o fibRec.o fibNonRec.o validation.o -o lab10

main.o: main.cpp
	${CXX} ${CXXFLAGS} -c main.cpp

fibRec.o: fibRec.cpp
	${CXX} ${CXXFLAGS} -c fibRec.cpp
	
fibNonRec.o: fibNonRec.cpp
	${CXX} ${CXXFLAGS} -c fibNonRec.cpp
	
validation.o: validation.cpp
	${CXX} ${CXXFLAGS} -c validation.cpp
	
clean:
	rm *.o lab10
