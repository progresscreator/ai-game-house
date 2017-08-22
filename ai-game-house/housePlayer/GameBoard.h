#ifndef _GAMEBOARD_H
#define _GAMEBOARD_H

#include "LastMove.h"

class GameBoard {
	
	public:
	// Board dimensions and data storage
		int xdim;
		int ydim;
		int size;
		int rowlvl;
		int **gboard;
		LastMove *last;
		string gboardState;
	// Initialize Gameboard
		GameBoard(string gboardState, int size);
	// Return Gameboard States
		int ReturnSize();
		int ReturnColor(int xx, int yy, int zz);
		int ReturnAvailable();
	// Perform or Retract a Play During Reasoning Stage
		bool SelectMove(LastMove *gMove);
		bool RetractMove(LastMove *gMove);
	// Perform Scoring Routine
		int ScoreBoard(LastMove *gMove, GameBoard *board);
	// Check Legal Moves
		void GetLegalMoves(vector<LastMove> *moves, LastMove gMove, GameBoard *board);
	// Check for Endgame Scenarios
		bool CheckmateTrigger(LastMove *gMove);
	// Perform Alpha-Beta Filtering
		int AlphaBetaPruning(int depth, int alpha, int beta, int aColor, LastMove aNode, LastMove *bestMove, GameBoard *board);
	// Perform Reasoning
		void Reason();
	// Output States
		void DispBoard();
		string OutputMove();
	
};

#endif