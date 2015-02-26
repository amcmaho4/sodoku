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
	bool checkIfInvalid(T, int , int );
	T *squareValuesPtr[9][9];
	int squareVal[9][9];
	T *verticalValuesPtr[9][9];
	T *horizontalValuesPtr[9][9];
	vector<T> getValidArray(int , int );
	void updateUntakenValues();
	void insertSingle();
	void trySolve();
	
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
			
			squareValuesPtr[c][l]= &(puzzle[i][j]);
			squareVal[i][j]=c;  // used to decide which square the piece is in
		}
}
}
//

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


template<typename T>
void sodoku<T>::play(){
	T value;
	int X=0;
	int Y=0;
	bool gameLost = false;  //if they enter in a bad location
	bool gameWon= false;
	while ( !(gameLost)) {
		bool badUserInput=true;
		gameWon= Won();
		if (gameWon)
			continue;
		while(badUserInput==true){ //while loop continues to read user locations until they enter a valid one
			cout<< "enter in the X and Y position: (rows/ columns go from 0-8)"<< endl;

			cout<< "X position: " <<endl;
			cin >> X;
			cout << "Y position: "<< endl;
			cin>> Y;
	
			if(X<0 |Y<0 |X>9 |Y>9) // check the user input
				cout<< "that spot is out side of the bounds";
			else if(puzzle[X][Y]!=0 && puzzle[X][Y]!='0')
				cout<< "that spot is taken";
			else
				badUserInput=false;
			cout<< endl;
		}
			cout << "and what's you value: "<<endl;
		cin>> value;
		
		
		
		if (checkIfInvalid(value, X,Y)) // check the invalid array
		{
			gameLost= true;
			cout<<endl;
			cout << "sorry bad move you lose";
			cout<<endl;

		}
		else{
			puzzle[X][Y]=value;
			cout<< "successfully placed, updated puzzle: "<<endl;
			print();
			gameWon= Won();
			cout<<endl;
			
		}
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
		exit(1);
	}
	
	return winner;
}


// check if valid gets all the elements and pushes

template<typename T>
bool sodoku<T>::checkIfInvalid(T value, int X, int Y){
	// use push back to put all the relevant values into a vector
	// the vector has 0's and is 27 T in size
	vector<T> invalid;
	for(int l=0; l< 9 ; l++){
		invalid.push_back(*(squareValuesPtr[squareVal[X][Y]][l]));
		invalid.push_back(*(verticalValuesPtr[l][Y]));
		invalid.push_back(*(horizontalValuesPtr[l][X]));
	}
	// fix it up into a nice vector with only one copy of each invalid element
	
	//erase all of the 0's
	invalid.erase(std::remove(invalid.begin(), invalid.end(), 0), invalid.end());
	// erase all the '0''s
	invalid.erase(std::remove(invalid.begin(), invalid.end(), '0'), invalid.end());

	
	std::sort(invalid.begin(), invalid.end());
	invalid.erase(std::unique(invalid.begin(), invalid.end()), invalid.end());
	cout<<endl;
//	
//	cout<< "the invalid numbers were: "<<endl;
//	for(int j=0; j< invalid.size() ; j++){
//		cout<<invalid[j];
//	}

	//returns true or false based on whether the users input was good or not
	return (std::find(invalid.begin(), invalid.end(), value) != invalid.end());
	
}



template<typename T>
vector<T> sodoku<T>::getValidArray(int X, int Y){
vector<T> invalid;
for(int l=0; l< 9 ; l++){
	invalid.push_back(*(squareValuesPtr[squareVal[X][Y]][l]));
	invalid.push_back(*(verticalValuesPtr[l][Y]));
	invalid.push_back(*(horizontalValuesPtr[l][X]));
}
// fix it up into a nice vector with only one copy of each invalid element

//erase all of the 0's
invalid.erase(std::remove(invalid.begin(), invalid.end(), 0), invalid.end());
// erase all the '0''s
invalid.erase(std::remove(invalid.begin(), invalid.end(), '0'), invalid.end());


std::sort(invalid.begin(), invalid.end());
invalid.erase(std::unique(invalid.begin(), invalid.end()), invalid.end());

vector<T> untakenValues;
for(int i=1; i<=9; i++){
	if((std::find(invalid.begin(), invalid.end(), i) != invalid.end())){
		untakenValues.push_back(0);
	}
	else{
		untakenValues.push_back(1);
	}
}
	return untakenValues;
}




template<typename T>
void sodoku<T>::updateUntakenValues(){
	vector<T> untakenValuesSegment;
	vector< vector<T> > untakenValues2Segment;
	
	//cout<< "in update untaken vals: " <<endl;
	untakenValues.clear();
	for(int i= 0; i< 9; i++){
		for(int j=0; j< 9 ; j++){
			untakenValuesSegment= getValidArray(i,j);
			//untakenValuesSegment.erase(std::remove(untakenValuesSegment.begin(), untakenValuesSegment.end(), 0), untakenValuesSegment.end());
			for(int j=0; j< untakenValuesSegment.size() ; j++){
				//cout<<untakenValuesSegment[j];
			}
			untakenValues2Segment.push_back(untakenValuesSegment);
			untakenValuesSegment.clear();
		}
		//cout<< endl;
		untakenValues.push_back(untakenValues2Segment);
		
		untakenValues2Segment.clear();
	}
}




template<typename T>
void sodoku<T>:: trySolve(){
	int sum=0;
	int place =0;
	while(!Won()){
	for(int i= 0; i< 9; i++){
		for(int j=0; j< 9 ; j++){
			sum=0;
			if(puzzle[i][j] == 0 ){
				for (int k=0; k<9; k++) {
					sum += untakenValues[i][j][k];
					if(untakenValues[i][j][k] == 1){
						place = k;
					}
				}
				if(sum == 1){
					puzzle[i][j] = place+1;
					cout<< "the number "<<place+1<< " was placed at: "<< i<<" "<<j<<endl;
					i=0;
					j=0;
					(*this).print();
					updateUntakenValues();
				}
			}
		}
		}
	}
}






//template<typename T>
//void sodoku<T>:: insertSingle(){
//	updateUntakenValues();
//	int yesContinue=0;
//	int sum =0;
//	int place;
//	
//	
//	
//
//	for(int i= 0; i< 9; i++){
//		for(int i= 0; i< 9; i++){
//			for(int j=0; j< 9 ; j++){
//				for (int k=0; k<9; k++) {
//					//cout<< untakenValues[i][j][k];
//					sum += untakenValues[i][j][k];
//				}
//				cout<< "  " << sum<< "  " ;
//				sum=0;
//			}
//			cout<< endl;
//		}
//		
//		
//		for(int j=0; j< 9 ; j++){
//			if(puzzle[i][j] == 0 ){
//				cout << 0;
//				sum= 0;
//				for(int k= 0; k< 9; k++){
//					sum += untakenValues[i][j][k];
//					if(untakenValues[i][j][k] == 1){
//						place = k;
//					}
//				}
//				cout<< sum;
//				if(sum == 1 ){
//					puzzle[i][j]= place+1; //(std::find(invalid.begin(), invalid.end(), value) != invalid.end());
//					cout<< "place"<<place;
//					updateUntakenValues();
//					i=0;
//					j=0;
//					cout<< "this is the board: "<<endl;
//					print();
//				}
//			}
//			
//		}
//		cout<< endl;
//	
//
//	}
//}




			

template<typename T>
void printVectorVectorVector(){
	cout<< endl;
	for(int i= 0; i< 9; i++){
		for(int j=0; j< 9 ; j++){
			for (int k=0; k<9; k++) {
				//cout<< puzzle[i][j][k]<< " ";
			}
			cout<<endl;
		}
		cout<< endl;
	}
}

#endif /* defined(____sodoku__) */
