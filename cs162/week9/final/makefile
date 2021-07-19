CXX = g++
CXXFLAGS = -std=c++11

final: main.o Chemical.o Game.o Gear.o Ladder.o Parts.o Player.o Space.o Tools.o Workbench.o menu.o validation.o
	${CXX} ${CXXFLAGS} main.o menu.o Chemical.o Game.o Gear.o Ladder.o Parts.o Player.o Space.o Tools.o Workbench.o validation.o -o final

main.o: main.cpp
	${CXX} ${CXXFLAGS} -c main.cpp

Chemical.o: Chemical.cpp
	${CXX} ${CXXFLAGS} -c Chemical.cpp
	
Game.o: Game.cpp
	${CXX} ${CXXFLAGS} -c Game.cpp
	
Gear.o: Gear.cpp
	${CXX} ${CXXFLAGS} -c Gear.cpp
	
Ladder.o: Ladder.cpp
	${CXX} ${CXXFLAGS} -c Ladder.cpp
	
Parts.o: Parts.cpp
	${CXX} ${CXXFLAGS} -c Parts.cpp
	
Player.o: Player.cpp
	${CXX} ${CXXFLAGS} -c Player.cpp
	
Space.o: Space.cpp
	${CXX} ${CXXFLAGS} -c Space.cpp
	
Tools.o: Tools.cpp
	${CXX} ${CXXFLAGS} -c Tools.cpp
	
Workbench.o: Workbench.cpp
	${CXX} ${CXXFLAGS} -c Workbench.cpp
	
menu.o:	menu.cpp
	${CXX} ${CXXFLAGS} -c menu.cpp
	
validation.o: validation.cpp
	${CXX} ${CXXFLAGS} -c validation.cpp
	
clean:
	rm *.o final
