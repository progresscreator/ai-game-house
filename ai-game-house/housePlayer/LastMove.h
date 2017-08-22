#ifndef _LASTMOVE_H
#define _LASTMOVE_H

#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <vector>
#include <cmath>
#include <string>

using namespace std;

// Methods for recording and recalling the previous input move
class LastMove {
	
	private:
		int x, y, z;
		int color;
	public:
	// Constructors
		LastMove();
		LastMove(int color, int x, int y, int z);
	// Record Input
		void recordColor(int color);
		void recordMove(int color, int x, int y, int z);
	// Recall Input
		int returnX();
		int returnY();
		int returnZ();
		int returnColor();
	// Print Input
		void dispMove();
	
};

#endif