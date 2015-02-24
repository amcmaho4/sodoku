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
	void play();
	bool checkIfInvalid(T, int , int );
	T *squareValuesPtr[9][9];
	int squareVal[9][9];
	T *verticalValuesPtr[9][9];
	T *horizontalValuesPtr[9][9];
	
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
	T tempVar;
	 string line;
	int index =0;
//	while ( getline (inFile,line) ){
//		puzzle.push_back( vector<T> ());
//		for(int i = 0 ; i < line.size() ; i++){    //Read in a line into a temporary vector
//			if(!isspace(line[i])){			//check to see if it is not a space
//				if (isdigit(line[i])){
//						puzzle[index].push_back(line[i]-'0');
//						if (puzzle[index][puzzle[index].size()-1] == char(NULL))
//							//cout << "I'm null..." << endl;
//							puzzle[index][puzzle[index].size()-1] = '0';
//					
//				}
//				else
//						puzzle[index].push_back(line[i]);
//						
//			}
//			
//			// do diiferent things depending on whether it is a char or int typeid
//		}
//		index++;
//	}
	
	

	vector<T> tempVec;

	while(!inFile.eof()){ //While the file is not at the end
		for(int i = 0 ; i < sizeOfBoard ; i++){    //Read in a line into a temporary vector
			inFile >> tempVar; //Put just read value into temporary vector
			tempVec.push_back(tempVar);
			//cout<< tempVar;
		}
		puzzle.push_back(tempVec);   //Push back the line just read)
		tempVec.clear(); //Clear/recycle temporary vector
	}
//

	
//
	// make an array of pointers to the loactions columns
	for (int v=0; v<9; v++) {
		for(int l=0; l< 9 ; l++){
			verticalValuesPtr[l][v]= &(puzzle[l][v]);
		}
	}
	// make an array of pointers to the locations in the rows
	for (int v=0; v<9; v++) {
		for(int l=0; l< 9 ; l++){
			horizontalValuesPtr[v][l]= &(puzzle[l][v]);
		}
	}
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
	//  the center X and Y locations
	int scX, scY;
	// make an array of pointers to a locations in the nine different squares on the box
	for (int c =0; c<9; c++) {    // loops through all the different square centers
		scX=squareCenters[c][0], scY= squareCenters[c][1];
		
		for(int l=0; l< 9; l++){      // loops throught locations around a square center
			int i=scX+locations[l][0], j=scY+locations[l][1];
			
			squareValuesPtr[c][l]= &(puzzle[i][j]);
			squareVal[i][j]=c;  // used to decide which square the piece is in
		}
	}

	
	
	
}
//
template<typename T>
void sodoku<T>::print(){
	for(int i= 0; i< puzzle.size(); i++){
		for(int j=0; j< puzzle.size() ; j++){
			cout<< puzzle[i][j];
		}
		cout<< endl;
	}
}
//
//
//template<typename T>
//void sodoku<T>::play(){
//	T value;
//	int X=0;
//	int Y=0;
//	int elementsPlaced = 0;
//	int emptylocations = 81; //CHANGE
//	bool gameOver = false;  //if they enter in a bad location
//	while ((elementsPlaced <= emptylocations) && !(gameOver)) {
//		
//		do{
//			cout<< "X position: " <<endl;
//			cin >> X;
//			cout << endl;
//			cout << "Y position: "<< endl;
//			cin>> Y;
//		}while(puzzle[X][Y]!=0);
//		cout << "and what's you value: "<<endl;
//		cin>> value;
//		
//		
//		
//		if (checkIfInvalid(value, X,Y)) // check the invalid array
//		{
//			gameOver= true;
//			cout<<endl;
//			cout << "sorry bad move you lose";
//		}
//		else{
//			puzzle[X][Y]=value;
//			elementsPlaced++;
//			cout<< "successfully placed, updated puzzle: "<<endl;
//			print();
//			cout<<endl;
//		}
//	}
//}
//
//
//
//// check if valid gets all the elements and pushes
//
//template<typename T>
//bool sodoku<T>::checkIfInvalid(T value, int X, int Y){
//// use push back to put all the relevant values into a vector
//// the vector has 0's and is 27 T in size
//vector<T> invalid;
//for(int l=0; l< 9 ; l++){
//	invalid.push_back(*(squareValuesPtr[squareVal[X][Y]][l]));
//	invalid.push_back(*(verticalValuesPtr[l][Y]));
//	invalid.push_back(*(horizontalValuesPtr[l][X]));
//}
//// fix it up into a nice vector with only one copy of each invalid element
//invalid.erase(std::remove(invalid.begin(), invalid.end(), 0), invalid.end());
////
//std::sort(invalid.begin(), invalid.end());
//invalid.erase(std::unique(invalid.begin(), invalid.end()), invalid.end());
//cout<<endl;
//for(int j=0; j< invalid.size() ; j++){
//	cout<< "the invalid numbers were: "<<invalid[j]<<endl;
//}
//
////returns true or false based on whether the users input was good or not
//return (std::find(invalid.begin(), invalid.end(), value) != invalid.end());
//	
//}


#endif /* defined(____sodoku__) */
