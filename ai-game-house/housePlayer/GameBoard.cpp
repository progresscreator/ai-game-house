#include "GameBoard.h"

GameBoard::GameBoard(string gboardState, int size){
	
	this->xdim = size + 3;
	this->ydim = size + 2;
	this->size = size;
	this->gboardState = gboardState;
	
	int offset = 48;
	int aCol = 0;
	int aRow = -1;
	int num = 0;
	char dummyChar = this->gboardState[0];
	
	this->gboard = new int*[this->ydim];
	
	for(int i=0;i<this->ydim;i++)
		this->gboard[i] = new int[this->xdim];
	
	// 0 = empty
	// -1 = null move
	for(int i=0;i<this->ydim;i++)
		for(int j=0;j<this->xdim;j++){
			
			if(j < i + 1) 
				this->gboard[i][j] = 0;
			
			else 
				this->gboard[i][j] = -1;
		}
	
	// Setup atropos game borders
	this->gboard[this->ydim - 1][0] = -1;
	
	for(int i=0;i<this->ydim;i++){
		
		if((i%2 == 1) && (i < this->ydim - 1)){
			
			this->gboard[i][0] = 3;
			this->gboard[i][i+1] = 2;
		}
		
		else if((i%2 == 0) && (i < this->ydim - 1)){
			
			this->gboard[i][0] = 1;
			this->gboard[i][i+1] = 3;
		}
		
		else{
			
			for(int j=0;j<this->xdim;j++){
				
				if((j > 0) && (j < this->xdim - 1)){
					
					if(j%2 == 1) this->gboard[i][j] = 1;
					
					else this->gboard[i][j] = 2;
				}
			}
		}
	}
	
	// Get board values from state string
	while(dummyChar != 'L'){
		
		if(dummyChar == '['){
			
			aRow++;
			if(aRow < this->ydim - 1)
				aCol = 0;
			
			else 
				aCol = 1;
		}
		
		else if(dummyChar != ']'){
			
			this->gboard[aRow][aCol] = (int)dummyChar - offset;
			aCol++;
		}
		
		num++;
		dummyChar = this->gboardState[num];
	}
	
	// Read in details of last play
	if(this->gboardState.find("null") != this->gboardState.npos)
		last = new LastMove();
	
	else{
		
		int amv = this->gboardState.find("LastPlay:");
		string PlayTheGame = gboardState.substr(amv+9,gboardState.rfind(')')-amv-8);
		
		// Get last move values, convert from chars
		string xval;
		string yval;
		string zval;
		
		// Declare delimiters
		int dd = PlayTheGame.find(',',3);
		int dd2 = PlayTheGame.find(',', (dd+1));
		
		// Get x, y, z Values
		xval = PlayTheGame.substr(3, (dd-3));
		yval = PlayTheGame.substr(dd+1, (dd2-dd-1));
		
		int dd3 = dd2;
		dd2 = PlayTheGame.find(')', (dd3+1));
		zval = PlayTheGame.substr((dd3+1), (dd2-dd3-1));
		
		// Perform Conversion
		int xint = atoi(xval.c_str());
		int yint = atoi(yval.c_str());
		int zint = atoi(zval.c_str());
		
		// Store Last Move
		last = new LastMove(((int)PlayTheGame[1]-offset), (this->ydim-1-xint), yint, zint);
	}

}


int GameBoard::ReturnSize(){
	
	int sz = this->size;
	return sz;
}


int GameBoard::ReturnAvailable(){
	
	int numAvail = 0;
	
	for(int i=1;i<this->ydim;i++)
		for(int j=1;this->xdim;j++){
			
			if(this->gboard[i][j] == -1)
				break;
			
			if(this->gboard[i][j] == 0)
				numAvail++;
		}
	
	return numAvail;
}


int GameBoard::ReturnColor(int xx, int yy, int zz){
	
	int color = this->gboard[xx][yy];
	return color;
}

bool GameBoard::SelectMove(LastMove *gMove){
	
	int xpos = gMove->returnX();
	int ypos = gMove->returnY();
	int zpos = gMove->returnZ();
	int color = gMove->returnColor();
	
	// Check that space is empty
	if(this->gboard[xpos][ypos] != 0)
		return false;
	
	else{
		
		// If space is empty, store the move
		this->gboard[xpos][ypos] = color;
		this->last->recordMove(color, xpos, ypos, zpos);
	}
	
	return true;
}


bool GameBoard::RetractMove(LastMove *gMove){
	
	int xpos = gMove->returnX();
	int ypos = gMove->returnY();
	
	// Check that space is filled
	if(this->gboard[xpos][ypos] == 0)
		return false;
	
	else if(this->gboard[xpos][ypos] == -1)
		return false;
	
	else{
		
		// If space is filled, make the space empty
		this->gboard[xpos][ypos] = 0;
	}
	
	return true;
}

int GameBoard::ScoreBoard(LastMove *gMove, GameBoard *board){
		
	int tmp = 0;
	int max = 0;
	int aColor = 0;
	int bColor = 0;
	int cColor = 0;
	
	int xpos = gMove->returnX();
	int ypos = gMove->returnY();
	aColor = this->last->returnColor();
	
	// Examine each triangle bordering previous move
	for(int i=0;i<6;i++){
		
		if(i==0){
				bColor = board->ReturnColor(xpos - 1,ypos - 1,0);
				cColor = board->ReturnColor(xpos - 1,ypos,0);
		}
		
		else if (i==1){
				bColor = board->ReturnColor(xpos - 1,ypos,0);
				cColor = board->ReturnColor(xpos,ypos + 1,0);
		}
		
		else if (i==2){
				bColor = board->ReturnColor(xpos,ypos + 1,0);
				cColor = board->ReturnColor(xpos + 1,ypos + 1,0);
		}
		
		else if (i==3){
				bColor = board->ReturnColor(xpos + 1,ypos + 1,0);
				cColor = board->ReturnColor(xpos + 1,ypos,0);
		}
				
		else if (i==4){
				bColor = board->ReturnColor(xpos + 1,ypos,0);
				cColor = board->ReturnColor(xpos,ypos - 1,0);
		}
				
		else if (i==5){
				bColor = board->ReturnColor(xpos,ypos - 1,0);
				cColor = board->ReturnColor(xpos - 1,ypos - 1,0);
		}
				
		
		// 2 blanks = low score
		if(bColor == 0 && cColor == 0){
			
			tmp = 10;
			
			if(tmp > max)
				max = tmp;
		}
		
		// 1 blank = medium score
		else if(bColor == 0){
			
			if(aColor*cColor == 2)
				tmp = 100;
			if(aColor*cColor == 3)
				tmp = 100;
			if(aColor*cColor == 6)
				tmp = 100;
			else 
				tmp = 1;
			if(tmp > max)
				max = tmp;
		}
		
		else if(cColor == 0){
			
			if(aColor*bColor == 2)
				tmp = 100;
			if(aColor*bColor == 3)
				tmp = 100;
			if(aColor*bColor == 6)
				tmp = 100;
			else 
				tmp = 1;
			if(tmp > max)
				max = tmp;
		}
		
		// If we detect a win...
		else if(aColor*bColor*cColor != 0){
			
			// Score it
			if(aColor*bColor*cColor == 6)
				tmp =  1000;
			
			else
				tmp = 1;
			
			if(tmp > max)
				max = tmp;
		}
		
		else 
			max = 0;
	}
	
	// Return highest score
	return max;
}
	

void GameBoard::GetLegalMoves(vector<LastMove> *moves, LastMove gMove, GameBoard *board){
	
	int xpos = gMove.returnX();
	int ypos = gMove.returnY();
	int zpos = gMove.returnZ();
			
	// Check W
	if(board->ReturnColor(xpos,ypos - 1,zpos + 1) == 0)
		moves->push_back(LastMove(-1,xpos,ypos - 1,zpos + 1));
	
	// Check E
	if(board->ReturnColor(xpos,ypos + 1,zpos - 1) == 0)
		moves->push_back(LastMove(-1,xpos,ypos + 1,zpos - 1));
	
	// Check N
	if(board->ReturnColor(xpos - 1,ypos, zpos - 1) == 0)
		moves->push_back(LastMove(-1,xpos - 1,ypos,zpos - 1));
	
	// Check S
	if(board->ReturnColor(xpos + 1,ypos,zpos + 1) == 0)
		moves->push_back(LastMove(-1,xpos + 1,ypos,zpos + 1));
	
	// Check NW
	if(board->ReturnColor(xpos - 1,ypos - 1,zpos) == 0)
		moves->push_back(LastMove(-1,xpos - 1,ypos - 1,zpos));
	
	// Check SE
	if(board->ReturnColor(xpos + 1,ypos + 1,zpos) == 0)
		moves->push_back(LastMove(-1,xpos + 1,ypos + 1,zpos));
	
	// Default to non-neighboring open spaces
	if(moves->empty()){
		
		for(int i=1; i<this->ydim; i++)
			for(int j=1; this->xdim; j++){
				
				if(board->ReturnColor(i, j, 0) == -1)
					break;
				
				if(board->ReturnColor(i, j, 0) == 0)
					moves->push_back( LastMove(-1, i, j, ((2 * i + 1) - i - j)) );
				
			}
	}
}

bool GameBoard::CheckmateTrigger(LastMove *gMove){
	
	int xpos = gMove->returnX();
	int ypos = gMove->returnY();

	int aColor = gMove->returnColor();
	int bColor = 0;
	int cColor = 0;
	
	// Examine each triangle to find endgame conditions
	for(int i=0;i<6;i++){
		
				
		if(i==0){
			bColor = this->ReturnColor(xpos - 1,ypos - 1,0);
			cColor = this->ReturnColor(xpos - 1,ypos,0);
		}
				
		if(i==1){
			bColor = this->ReturnColor(xpos - 1,ypos,0);
			cColor = this->ReturnColor(xpos,ypos + 1,0);
		}
				
		if(i==2){
			bColor = this->ReturnColor(xpos,ypos + 1,0);
			cColor = this->ReturnColor(xpos + 1,ypos + 1,0);
		}
				
		if(i==3){
			bColor = this->ReturnColor(xpos + 1,ypos + 1,0);
			cColor = this->ReturnColor(xpos + 1,ypos,0);
		}
				
		if(i==4){
			bColor = this->ReturnColor(xpos + 1,ypos,0);
			cColor = this->ReturnColor(xpos,ypos - 1,0);
		}
				
		if(i==5){
			bColor = this->ReturnColor(xpos,ypos - 1,0);
			cColor = this->ReturnColor(xpos - 1,ypos - 1,0);
		}
		
		
		if(aColor*bColor*cColor == 6)
			return true;
	}
	
	return false;
}


int GameBoard::AlphaBetaPruning(int depth, int alpha, int beta, int aColor, LastMove aNode, LastMove *bestMove, GameBoard *board){
	
	// Checkmate?
	if(board->CheckmateTrigger(&aNode) == true)
		return this->ScoreBoard(&aNode, board);
	
	// Depth limit reached?
	if(depth == 0)
		return this->ScoreBoard(&aNode, board);
	
	// Get list of legal moves
	vector<LastMove> *legalMoves = new vector<LastMove>;
	this->GetLegalMoves(legalMoves, aNode, board);
	
	// Run Alpha-Beta on node children
	for(int i=0; i<legalMoves->size(); i++){
		
		legalMoves->operator[](i).recordColor(aColor);
		board->SelectMove(&legalMoves->operator[](i));
		
		int tmp = -AlphaBetaPruning(depth-1, -beta, -alpha, aColor, legalMoves->operator[](i), bestMove, board);
		
		// Re-up Alpha
		if(alpha <= tmp){
			
			alpha = tmp;
			
			if(depth == this->rowlvl)
				bestMove->recordMove(aColor, legalMoves->operator[](i).returnX(), legalMoves->operator[](i).returnY(), legalMoves->operator[](i).returnZ());
		}
		
		board->RetractMove(&legalMoves->operator[](i));
		
		if(alpha >= beta)
			break;
	}
	
	return alpha;
}


void GameBoard::Reason(){
	
	bool newBoard = true;
	if(this->last->returnColor() != -1)
		newBoard = false;
	
	// Generate first move if gboard is empty
	if(newBoard){
		
		LastMove one(3,1,1,1);
		LastMove two(1,this->size, 1, this->size);
		int randomMove = rand()%3;
		
		if(randomMove == 0)
			this->SelectMove(&one);
		
		else if(randomMove == 1)
			this->SelectMove(&two);
		
		else if (randomMove == 2){
			
			int x = rand()%(this->size - 2) + 2;
			int y = 1 + this->size%4;
			int z = (2 * x + 1) - x - y;
			LastMove three(2, x, y, z);
			LastMove four(1, x, y, z);
			LastMove five(3, x, y, z);
			
			this->SelectMove(&three);
			
			if(this->CheckmateTrigger(&three)){
				
				this->RetractMove(&three);
				this->SelectMove(&four);
				
				if(this->CheckmateTrigger(&four)){
					
					this->RetractMove(&four);
					this->SelectMove(&five);
				}
			}
		}
	}
	
	if(! newBoard){
		
		LastMove *r_move = new LastMove();
		LastMove *g_move = new LastMove();
		LastMove *b_move = new LastMove();
		GameBoard *board = new GameBoard(this->OutputMove(), this->size);
		
		// Set Depth
		int depth = this->ReturnAvailable();
		if(depth%2 == 1) 
			depth--;
		
		if(depth > 12)
			depth = 12;
		
		rowlvl = depth;
		
		// Perform Alpha-Beta for each color
		int r_score = this->AlphaBetaPruning(depth, -2000, 2000, 1, *this->last, r_move,board);
		int g_score = this->AlphaBetaPruning(depth, -2000, 2000, 2, *this->last, g_move,board);
		int b_score = this->AlphaBetaPruning(depth, -2000, 2000, 3, *this->last, b_move,board);
		
		bool canMove_1 = false;
		bool canMove_2 = false;
		bool canMove_3 = false;
		
		// Examines endgame results for each possible move
		this->SelectMove(r_move);
		bool endGame = this->CheckmateTrigger(r_move);
		if(endGame) 
			canMove_1 = true;
		this->RetractMove(r_move);
		
		this->SelectMove(g_move);
		endGame = this->CheckmateTrigger(g_move);
		if(endGame) 
			canMove_2 = true;
		this->RetractMove(g_move);
		
		this->SelectMove(b_move);
		endGame = this->CheckmateTrigger(b_move);
		if(endGame) 
			canMove_3 = true;
		this->RetractMove(b_move);
		
		// Custom Reasoning
		if((canMove_1 == false) && (r_score > max(g_score,b_score))) 
			this->SelectMove(r_move);
		
		else if((canMove_2 == false) && (g_score > max(r_score,b_score)))
			this->SelectMove(g_move);
		
		else if((canMove_3 == false) && (b_score > max(r_score,g_score)))
			this->SelectMove(b_move);
		
		else if((canMove_1 == false) && (canMove_2 == true) && (canMove_3 == true))
			this->SelectMove(r_move);
		
		else if((canMove_2 == false) && (canMove_1 == true) && (canMove_3 == true))
			this->SelectMove(g_move);
		
		else if((canMove_3 == false) && (canMove_1 == true) && (canMove_2 == true))
			this->SelectMove(b_move);
		
		else if((canMove_1 == false) && (canMove_2 == false) && (canMove_3 == true)){
			
			if(r_score > g_score)
				this->SelectMove(r_move);
			
			else 
				this->SelectMove(g_move);
		}
		
		else if((canMove_1 == false) && (canMove_3 == false) && (canMove_2 == true)){
			
			if(r_score > b_score)
				this->SelectMove(r_move);
			else 
				this->SelectMove(b_move);
		}
		
		else if((canMove_2 == false) && (canMove_3 == false) && (canMove_1 == true)){
			
			if(g_score > b_score)
				this->SelectMove(g_move);
			
			else
				this->SelectMove(b_move);
		}
		
		else{
			int aColor = rand()%3;
			if(aColor == 0)
				this->SelectMove(r_move);
			
			else if(aColor == 1)
				this->SelectMove(g_move);
			
			else if (aColor == 2)
				this->SelectMove(b_move);
		}
	}
	
}


string GameBoard::OutputMove(){
	
	string out;
	
	for(int i=0; i<this->ydim; i++){
		
		out = out +'[';
		for(int j=0; j<this->ydim; j++){
			
			if((i == this->ydim - 1) && (j == 0))
				j = 1;
			
			if(this->gboard[i][j] != -1)
				out = out + (char)(this->gboard[i][j] + 48);
			
			else break;
		}
		
		out += ']';
	}
	
	char *x = new char[(int)log10((double)this->size + 1)];
	char *y = new char[(int)log10((double)this->size + 1)];
	char *z = new char[(int)log10((double)this->size + 1)];
	
	
	sprintf(x, "%d", this->ydim - 1 - last->returnX());
	sprintf(y, "%d", last->returnY());
	sprintf(z, "%d", last->returnZ());
	
	out = out + "LastPlay:(" + (char)(last->returnColor() + 48) + ',' + x + ',' + y + ',' + z + ')';
	return out;
	
}

void GameBoard::DispBoard(){
	
	printf("\nSize: %d\n\n", size);
	
	for(int i=0; i<this->ydim; i++){
		
		for(int k=0;k<this->ydim-i-1;k++)
			
			printf("\n");
		
			for(int j=0; j<this->xdim; j++){
			
				if((i == this->ydim - 1) && (j == 0))
					printf("\n");
				
				else if((i == this->ydim - 1) && (j == i + 1))
					printf("\n");
				
				else
					printf("%d ", this->gboard[i][j]);
				
				if(j == i + 1)
					break;
			}
		
		printf("\n");
	}
	
	printf("\n");
	printf("Last: %d, %d, %d\n", last->returnX(), last->returnY(), last->returnZ());
	printf("Color: %d\n", last->returnColor());
	
}
