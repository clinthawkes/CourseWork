CXX = g++
CXXFLAGS = -std=c++11

lab4: main.o University.o Building.o Person.o Student.o Instructor.o menu.o validation.o
	${CXX} ${CXXFLAGS} main.o University.o Building.o Person.o Student.o Instructor.o menu.o validation.o -o lab4

main.o: main.cpp
	${CXX} ${CXXFLAGS} -c main.cpp

University.o: University.cpp
	${CXX} ${CXXFLAGS} -c University.cpp

Building.o: Building.cpp
	${CXX} ${CXXFLAGS} -c Building.cpp
	
Person.o: Person.cpp
	${CXX} ${CXXFLAGS} -c Person.cpp

Student.o: Student.cpp
	${CXX} ${CXXFLAGS} -c Student.cpp
	
Instructor.o: Instructor.cpp
	${CXX} ${CXXFLAGS} -c Instructor.cpp
	
menu.o:	menu.cpp
	${CXX} ${CXXFLAGS} -c menu.cpp
	
validation.o: validation.cpp
	${CXX} ${CXXFLAGS} -c validation.cpp
	
clean:
	rm *.o lab4 
