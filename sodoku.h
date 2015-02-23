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
#include <array>
#include <iterator>
#include <fstream>
#include <ctype.h>
#include <typeinfo>

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
	int X=3;
	int Y=3;
	
	
	int verticalLocations[9][2];
 int horizontalLocations[9][2];
	cout<< "vlocs: "<<endl;
	for(int l=0; l< 9 ; l++){
		verticalLocations[l][0]= l;
		verticalLocations[l][1]= Y;
		
			cout<<  l <<" "<< Y <<" "<<puzzle[l][Y]<< endl;
	
	}
	cout<< "hlocs: "<<endl;
	for(int d=0; d< 9 ; d++){
		horizontalLocations[d][0]= X;
		horizontalLocations[d][1]= d;
		cout<<  X<<" "<< d <<" "<<puzzle[X][d]<< endl;
		
	}
	
	
	
	int shareSquareLocations[8][2];
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
	cout<< "checking for neighbors of: "<< X<<", "<<Y<<" the value here: "<< puzzle[X][Y]<<endl;
	for(int l=0; l< 9; l++){
		int i=X+locations[l][0], j=Y+locations[l][1];
		shareSquareLocations[l][0]= j;
		shareSquareLocations[l][1]= i;
		cout<<  i <<" "<< j <<" "<<puzzle[i][j]<< endl;
	}
	
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
