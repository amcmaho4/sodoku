//
//  sodoku.h
//  
//
//  Created by Anna Jo McMahon on 2/22/15.
//
//

#ifndef ____sodoku__
#define ____sodoku__

#include <stdio.h>
#include <iostream>
using namespace std;

#include <vector>
#include <algorithm>
#include <iterator>
#include <fstream>

template <typename T>
class sodoku {
public:
	
	makeBoard(ifstream );
	
	
private:
	
	vector<vector <T> > puzzle;

	
	
	
};



// Data members



vector<T> tempVec;
while(!sudoku.eof()){ //While the file is not at the end
	for(i = 0 ; i < sizeOfBoard ; i++){    //Read in a line into a temporary vector
		sudoku >> tempVar; //Put just read value into temporary vector
		tempVec.push_back(tempVar);
	}
	puzzle.push_back(tempVec);   //Push back the line just read)
	tempVec.clear(); //Clear/recycle temporary vector
}




for (int i = 0; i < 9; i++)
for (int j = 0; j < 9; j++) {
	infile >> value;
	Puzzle[i][j] = value;
}





#endif /* defined(____sodoku__) */
