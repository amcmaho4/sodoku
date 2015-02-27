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
#include <ctype.h>
#include <typeinfo>
#include <map>
#include<numeric>

template <typename T>
class sodoku  {
	
	
public:
	sodoku(string);
	void print();
	void play();
	bool Won();
	T *squareValuesPtr[9][9];
	int squareVal[9][9];
	T *verticalValuesPtr[9][9];
	T *horizontalValuesPtr[9][9];
	vector<T> *validverticalValuesPtr[9][9];
	vector<T> *validhorizontalValuesPtr[9][9];
	vector<T> *validsquaresValuesPtr[9][9];
	vector<T> getValidArray(int , int );
	void updateUntakenValues();
	void insertSingle();
	void solve();
	
	//T*[9][9] getsquareValuesPtr()
private:
	vector<vector <vector <T> > > untakenValues;
	vector<vector <T> > puzzle;
	T *ptr; // pointer to first element of pointer-based array
};



template<typename T>
sodoku<T>::sodoku(string fileName){
	// input the file
	ifstream inFile;
	inFile.open (fileName.c_str());
	
	
	//read the contents of te file into a vector of vectors (the puzzle) using temporary vars
	T tempVar;
	vector<T> tempVec;
	while(!inFile.eof()){ //While the file is not at the end
		for(int i = 0 ; i < 9 ; i++){    //Read in a line into a temporary vector
			inFile >> tempVar; //Put just read value into temporary vector
			tempVec.push_back(tempVar);
		}
		puzzle.push_back(tempVec);   //Push back the line just read)
		tempVec.clear(); //Clear/recycle temporary vector
	}
	
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
	
	// squareCenters holds the locations of all the centers of the 3x3 sub- squares that make up a 9 x9 grid
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
	// locations is essentially an array of increments, that when added to squared centers, will give you all the locations in a mini grid. For example, if you add locations to squareCenters[1] .. (1,1) then you would get a 9x2 matrix. This 9x2 matrix holds all the locations of the upper left mini grid in the full grid
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
			squareValuesPtr[l][c]= &(puzzle[i][j]);
			squareVal[i][j]=c;  // used to decide which square the piece is in
		}
	}
	updateUntakenValues();
	validverticalValuesPtr[1][1] =&(untakenValues[1][1]);
	cout<< (*validverticalValuesPtr) << endl;
	
	for (int v=0; v<9; v++) {
		for(int l=0; l< 9 ; l++){
			validverticalValuesPtr[l][v] =&(untakenValues[l][v]);
		}
	}
	for (int v=0; v<9; v++) {
		for(int l=0; l< 9 ; l++){
			validhorizontalValuesPtr[v][l]= &(untakenValues[l][v]);
		}
	}
	for (int c =0; c<9; c++) {    // loops through all the different square centers
		scX=squareCenters[c][0], scY= squareCenters[c][1];
		for(int l=0; l< 9; l++){      // loops throught locations around a square center
			int i=scX+locations[l][0], j=scY+locations[l][1];
			validsquaresValuesPtr[l][c]= &(untakenValues[i][j]);
		}
	}
	
	
	//**************************************************************************************************
	cout<<endl;
 	vector<T> *vectorOfPossibleValues= validhorizontalValuesPtr[0][0];
	vector<T> *vectorOfCurrentValues= validhorizontalValuesPtr[0][0];
	vector<T> *allPossibleVals ; // vals in all the row

	// need to do this for each row
	for(int l= 0; l< 9; l++){
		for(int s= 0;     s< (*validhorizontalValuesPtr[l][s]).size() ;   s++ ){
			//Use if statement to deregard the possible values at taken locations
			//cout<<"puzzle piece: "<<puzzle[l][0]<<endl;
			//if(puzzle[l][s]==0){
			(*vectorOfPossibleValues).push_back((*validhorizontalValuesPtr[0][l])[s]);
			cout<< (*validhorizontalValuesPtr[0][l])[s];
			//}
		}
		cout<<endl;
	}
	// PRINT ONUT ALL
	cout<< "All the things in the vector space:  "<<endl;
	for(int l=0; l< (*vectorOfPossibleValues).size() ; l++){
		cout<< (*vectorOfPossibleValues)[l];
	}
	// finding the unique element at the current location.
	// will traverse a vector of vectors, but right now it just looks at [0][0]
	cout<<endl;
	cout<< "unique to our current vector of vectors: "<<endl;
	vector<int> Vals;
	//for each of the vectors
	for(int i=0; i<(*vectorOfCurrentValues).size(); i++){
		if((std::count((*vectorOfPossibleValues).begin(), (*vectorOfPossibleValues).end(), (*vectorOfCurrentValues)[i]))==1){
			cout<< "ADD "<<(*vectorOfPossibleValues)[i]<< endl;
			// puzzle[X][Y] = i
			// add to puzzle it is unique
			// uppdateTakeLocations
		}
		
	}
	//**************************************************************************************************

	
	
	//	T *value= horizontalValuesPtr[1][1];
	//	value+=10;
	//	cout<<" VALLDSAD:"<<*value;
	//cout<<horizontalValuesPtr[1][1]<< endl;
	
	//	for(int l=0; l< (*vectorOfPossibleValues).size() ; l++){
	//		cout<< (*vectorOfPossibleValues)[l];
	//	}
	//	cout<< "   "<<*value;
	//
	//	*value = 5;
	//
	//	for(int X=0; X<9;X++){
	//	for(int l=0; l< 9; l++){
	//		(*vectorOfPossibleValues).push_back((*validhorizontalValuesPtr[1][X])[l]);
	//
	//	}
	//	}
	//
	

	
//	for(int l= 0; l< 9; l++){
//		cout<< *(verticalValuesPtr[l][Y]);
//
//		for(int s= 0; s<(*validverticalValuesPtr[l][Y]).size();s++ ){
//			cout<< "  "<<(*validverticalValuesPtr[l][Y])[s];
//		}
//		cout<<endl;
//	}
	
//	cout<< endl;
//	for(int l= 0; l< 9; l++){
//		cout<< *(squareValuesPtr[l][squareVal[X][Y]])<<"  ";
//
//		for(int s= 0; s<(*validsquaresValuesPtr[l][squareVal[X][Y]]).size();s++ ){
//			cout<< "  "<<(*validsquaresValuesPtr[l][squareVal[X][Y]])[s];
//		}
//		cout<<endl;
//	}
	
//	cout<< endl;
//	for(int l= 0; l< 9; l++){
//		cout<< *(horizontalValuesPtr[l][Y])<<"  ";
//		
//		for(int s= 0; s<(*validhorizontalValuesPtr[l][Y]).size();s++ ){
//			cout<< "  "<<(*validhorizontalValuesPtr[l][Y])[s];
//		}
//		cout<<endl;
//	}
	
	
	
	
	
}

template<typename T>
void sodoku<T>::print(){
	cout<< endl;
	for(int i= 0; i< 9; i++){
		for(int j=0; j< 9 ; j++){
			cout<< puzzle[i][j]<< " ";
		}
		cout<< endl;
	}
}

// checks to see if all the spaces on the board are filled
template<typename T>
bool sodoku<T>::Won(){
	bool winner= true;
	for(int i= 0; i< 9; i++){
		for(int j=0; j< 9 ; j++){
			if(puzzle[i][j]==0 || puzzle[i][j]=='0'){
				winner= false;
			}
		}
	}
	if(winner ==true){
		cout << "winner"<< endl;
	}
	return winner;
}

template<typename T>
vector<T> sodoku<T>::getValidArray(int X, int Y){
	vector<T> invalid;
	for(int l=0; l< 9 ; l++){
		invalid.push_back(*(squareValuesPtr[l][squareVal[X][Y]]));
		invalid.push_back(*(verticalValuesPtr[l][Y]));
		invalid.push_back(*(horizontalValuesPtr[l][X]));
	}
	// fix it up into a nice vector with only one copy of each invalid element
	//erase all of the 0's
	invalid.erase(std::remove(invalid.begin(), invalid.end(), 0), invalid.end());
	std::sort(invalid.begin(), invalid.end());
	invalid.erase(std::unique(invalid.begin(), invalid.end()), invalid.end());
	
	vector<T> untakenValues;
	for(int i=1; i<=9; i++){
		if(!(std::find(invalid.begin(), invalid.end(), i) != invalid.end())){
			untakenValues.push_back(i);
		}
	}
	return untakenValues;
}

template<typename T>
void sodoku<T>::updateUntakenValues(){
	vector<T> untakenValuesSegment;
	vector< vector<T> > untakenValues2Segment;
	untakenValues.clear();
	for(int i= 0; i< 9; i++){
		for(int j=0; j< 9 ; j++){
			untakenValuesSegment= getValidArray(i,j);
			for(int j=0; j< untakenValuesSegment.size() ; j++){
				cout<<untakenValuesSegment[j];
			}
			cout<< " ";
			untakenValues2Segment.push_back(untakenValuesSegment);
			untakenValuesSegment.clear();
		}
		
		
		
		cout<< endl;
		untakenValues.push_back(untakenValues2Segment);
		untakenValues2Segment.clear();
	}
}




//
// checkForSingletons
//sort
//set symmetric difference
//resize

// for each of the other sets in the row/ column/
// for each vector of possible values in a set for()

// if find(element = true)
//continue
// puzzle[i][j]== value


template<typename T>
void sodoku<T>:: solve(){
	int sum=0;
	int place =0;
	int puzzleIterations=0;
	while(!Won()){
		for(int i= 0; i< 9; i++){
			for(int j=0; j< 9 ; j++){
				sum=0;
				if(puzzle[i][j] == 0 ){
					if((untakenValues[i][j]).size()== 1){
						puzzle[i][j] = untakenValues[i][j][0];
						//i=0;
						//j=0;
						print();
						updateUntakenValues();
					}
				}
			}
		}
		
	}

}


//  for puzzle[][]

#endif /* defined(____sodoku2__) */



