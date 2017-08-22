
#include "LastMove.h"
#include "GameBoard.h"

int main(int argc, char* argv[])
{
	if(argc != 2)
	{
		cout << "Error, check your input and try again" << endl;
		return -1;
	}
	
	string gboardState;
	int index = 0;
	while(argv[1][index] != NULL){
		gboardState += argv[1][index];
		index++;
	}
	
	int parse = gboardState.rfind('[');
	index = 0;
	char dummy = gboardState[index+parse+1];
	while(dummy != ']'){
		index++;
		dummy = gboardState[index+parse+1];
	}
	
	GameBoard *newBoard = new GameBoard(gboardState, (index-1));
	newBoard->Reason();
	cout << newBoard->OutputMove() << endl;
	return 0;
}
