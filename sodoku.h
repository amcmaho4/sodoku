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
#include <Array>
#include <iterator>
#include <fstream>
#include <ctype.h>
#include <typeinfo>
#include <map>

template <typename T>
class sodoku  {
	
	
public:
	sodoku(string);
	//~sodoku();
	void print();

private:
	
	vector<vector <T> > puzzle;
	T *ptr; // pointer to first element of pointer-based array	
};



// Data members
template<typename T>
sodoku<T>::sodoku(string fileName){
	ifstream inFile;
	inFile.open (fileName.c_str());
	int sizeOfBoard = 9;
	T vectorVar;
	string line;
	int index =0;
	while ( getline (inFile,line) ){
		puzzle.push_back( vector<T> ());
		for(int i = 0 ; i < line.size() ; i++){    //Read in a line into a temporary vector
			if(!isspace(line[i])){			//check to see if it is not a space
					puzzle[index].push_back(line[i]-'0');
			}
			
			// do diiferent things depending on whether it is a char or int typeid
		}
		
		index++;
	}

}

template<typename T>

void sodoku<T>::print(){
	for(int i= 0; i< puzzle.size(); i++){
		for(int j=0; j< puzzle.size() ; j++){
			cout<< puzzle[i][j];
		}
		cout<< endl;
	}
	//puzzle [down][over]
	int X=0;
	int Y=0;
	
	

	
////int allVerticalValues[];
//vector <T> *ptrs =&(puzzle[0]);
//vector <T> *ptrs2 =&(puzzle[1]);
//	
////cout<< (*ptrs)[1] << endl;
////	cout<< (*ptrs2)[1] << endl;
////	vector<int> copyV (9,0);
////	remove_copy()
//
//	
//cout<< (*ptrs)[1] << endl;
cout<<endl;

	cout<< "vertical : "<<endl;
int *verticalValuesPtr[9][9];
//vector<vector <T> > verticalValuesPtr;
	//verticalValuesPtr = &(puzzle[1][1]);
for (int v=0; v<puzzle.size(); v++) {
	for(int l=0; l< 9 ; l++){
		verticalValuesPtr[l][v]= &(puzzle[l][v]);
		//verticalValuesPtr[l].push_back(&(puzzle[l][v]));
		//cout<< l<<v;
		
	}
	}

	for (int v=0; v<puzzle.size(); v++) {
		for(int l=0; l< 9 ; l++){
			cout<<*(verticalValuesPtr[l][v]);
		}
		cout<<endl;
	}
	
	cout<<endl;
	
cout<< "horizontal: "<< endl;
	int *horizontalValuesPtr[9][9];

	for (int v=0; v<puzzle.size(); v++) {
		for(int l=0; l< 9 ; l++){
			horizontalValuesPtr[v][l]= &(puzzle[l][v]);
			
		}
	}
	for (int v=0; v<puzzle.size(); v++) {
		for(int l=0; l< 9 ; l++){
			cout<<*(horizontalValuesPtr[l][v]);
		}
		cout<<endl;
	}
	
	
	cout<<endl;
	
	cout<< "square : "<< endl;
	
	int *squareValuesPtr[9][9];
	int *allValuesPtr[9][9];
	
	int squareVal[9][9];
	int squareCenters[9][2] = {
						{1,1},
						{1,4},
						{1,7},
						{4,1},
						{4,4},
						{4,7},
						{7,1},
						{7,4},
						{7,7}
	};
	
	int locations[9][2] =
					{{1, -1},
					{-1, 1},
					{-1, -1},
					{1, 1},
					{0,0},
					{0, -1},
					{0, 1},
					{1, 0},
					{-1, 0}
	};
	cout<<endl;
	
	for (int c =0; c<9; c++) {    // loops through all the different square centers
		X=squareCenters[c][0], Y= squareCenters[c][1];
		
		for(int l=0; l< 9; l++){      // loops throught locations around a square center
			int i=X+locations[l][0], j=Y+locations[l][1];
			squareValuesPtr[c][l]= &(puzzle[i][j]);
			squareVal[i][j]=c;
		}
	}

	
	for (int v=0; v<puzzle.size(); v++) {
		for(int l=0; l< 9 ; l++){
			cout<<*(squareValuesPtr[v][l]);
		}
		cout<<endl;
	}
		cout<<endl;
		cout<<endl;
	for (int v=0; v<puzzle.size(); v++) {
		for(int l=0; l< 9 ; l++){
			cout<<(squareVal[v][l]);
		}
		cout<<endl;
	}
	
	
	
	X=3, Y=2;
	cout<<endl;
	for(int l=0; l< 9 ; l++){
		cout<<*(verticalValuesPtr[l][Y]);
	}
	cout<<endl;
	for(int l=0; l< 9 ; l++){
		cout<<*(horizontalValuesPtr[l][X]);
	}
	cout<<endl;
	for(int l=0; l< 9 ; l++){
		cout<<*(squareValuesPtr[squareVal[X][Y]][l]);
	}
	
	vector<T> invalid;
	X=3, Y=2;
	for(int l=0; l< 9 ; l++){
		invalid.push_back(*(squareValuesPtr[squareVal[X][Y]][l]));
		invalid.push_back(*(verticalValuesPtr[l][Y]));
		invalid.push_back(*(horizontalValuesPtr[l][X]));
	}
	invalid.erase(std::remove(invalid.begin(), invalid.end(), 0), invalid.end());
	
	
	std::sort(invalid.begin(), invalid.end());
	invalid.erase(std::unique(invalid.begin(), invalid.end()), invalid.end());
	cout<<endl;
	for(int j=0; j< invalid.size() ; j++){
		cout<< invalid[j];
	}
	
	
	
	//elementsPlaced
	//emptylocations
	//gameOver if they enter in a bad location
	
	
	
}



//vector1.insert( vector1.end(), vector2.begin(), vector2.end() );

//
//template<typename T>
//void sodoku<T>::play(){
//	 make taken locations
//	shareSquareLocations nxn vector of vectors
//	for each location on the board have a vector of pointers to the cells that it is dependent on
//	int n[8][2] = {{1, -1}
//					{-1, 1},
//					{-1, -1},
//					{1, 1},
//					{0, -1},
//					{0, 1},
//					{1, 0},
//					{-1, 0}
//					};
//	
//	int numberInARow=0;
//	// loops through the rows of the n (neighbors) matrix and checks how many markers are "inARow" in either direction around the current marker
//	// so the for loop is checking the four different alignments around the chip.
//	// there are two points in each alignment around the chip, which is why there are two "inARow" calls with every iteration of the for loop
//	for(int i=0;i<=3;i++){
//		numberInARow=inARow(X,Y,n[i][0],n[i][1])+inARow(X,Y,n[i][2],n[i][3])+1;
//		if(numberInARow>=4){
//			cout<<"GAMEOVER the winner is :"<< ((board[X].getDisc(board[X].getNumDiscs()-1)=='X')? " Player 1.":"Player 2") <<endl;
//			exit(1);
//		}
//		numberInARow=0;
//	}
//
//	for(int i= 0; i< puzzle.size(); i++){
//		for(int j=0; j< puzzle.size() ; j++){
//			
//			if (puzzle[i][j] == 0) {
//				cout<< "value for location: "<<endl;
//				cin>> value;
//				for(int i=0; i< shareSquareLocations();)
//			}
//
//		}
//}





#endif /* defined(____sodoku__) */
