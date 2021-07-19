CXX = g++
CXXFLAGS = -std=c++11

Project4: main.o Game.o Lineup.o Losers.o Node.o Barbarian.o BlueMen.o Character.o HarryPotter.o Medusa.o rollDie.o Vampire.o Menu.o validation.o
	${CXX} ${CXXFLAGS} main.o Game.o Lineup.o Losers.o Node.o Barbarian.o BlueMen.o Character.o HarryPotter.o Medusa.o rollDie.o Vampire.o Menu.o validation.o -o Project4

main.o: main.cpp
	${CXX} ${CXXFLAGS} -c main.cpp

Game.o: Game.cpp
	${CXX} ${CXXFLAGS} -c Game.cpp
	
Lineup.o: Lineup.cpp
	${CXX} ${CXXFLAGS} -c Lineup.cpp
	
Losers.o: Losers.cpp
	${CXX} ${CXXFLAGS} -c Losers.cpp
	
Node.o: Node.cpp
	${CXX} ${CXXFLAGS} -c Node.cpp
	
Barbarian.o: Barbarian.cpp
	${CXX} ${CXXFLAGS} -c Barbarian.cpp

BlueMen.o: BlueMen.cpp
	${CXX} ${CXXFLAGS} -c BlueMen.cpp
	
Character.o: Character.cpp
	${CXX} ${CXXFLAGS} -c Character.cpp

HarryPotter.o: HarryPotter.cpp
	${CXX} ${CXXFLAGS} -c HarryPotter.cpp
	
Medusa.o: Medusa.cpp
	${CXX} ${CXXFLAGS} -c Medusa.cpp
	
rollDie.o: rollDie.cpp
	${CXX} ${CXXFLAGS} -c rollDie.cpp
	
Vampire.o: Vampire.cpp
	${CXX} ${CXXFLAGS} -c Vampire.cpp
	
Menu.o:	Menu.cpp
	${CXX} ${CXXFLAGS} -c Menu.cpp
	
validation.o: validation.cpp
	${CXX} ${CXXFLAGS} -c validation.cpp
	
clean:
	rm *.o Project4
