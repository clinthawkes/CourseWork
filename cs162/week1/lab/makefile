lab1: main.o readMatrix.o determinant.o
	g++ main.o readMatrix.o determinant.o -o lab1

main.o: main.cpp
	g++ -c main.cpp

readMatrix.o: readMatrix.cpp
	g++ -c readMatrix.cpp

determinant.o: determinant.cpp
	g++ -c determinant.cpp

clean:
	rm *.o lab1
