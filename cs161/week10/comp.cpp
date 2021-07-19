#include "SBoard.hpp"

#define M * 1000000;


void executeTest(SBoard* board)
{
	int squareCount = board->placeToken(6, 3);
	//cout << squareCount << endl;
	board->removeToken(6, 3);
}

int main()
{
	SBoard board;
	board.readPlacementsFromFile("numbers.txt");
	int i = 1000 M;
	while (i-- > 0)
		executeTest(&board);
	return 0;
}
