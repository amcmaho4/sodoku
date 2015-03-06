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
	bool singleton();
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
	void printuntakenValues();
	
	
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
	bool spotTaken= false;
//	for(int l=0; l< 9 ; l++){
//		invalid.push_back(*(squareValuesPtr[squareVal[X][Y]][l]));
//		invalid.push_back(*(verticalValuesPtr[l][Y]));
//		invalid.push_back(*(horizontalValuesPtr[l][X]));
//	}
	for (int loopCol=0; loopCol<9; loopCol++) { // same num in row?
		if (puzzle[X][loopCol] != 0 )
			invalid.push_back(puzzle[X][loopCol]);
	}
	
	for (int loopRow=0; loopRow<9; loopRow++) { // same num in col?
		if (puzzle[loopRow][Y] != 0) 
			invalid.push_back(puzzle[loopRow][Y]);
	}
	
	int minigridRow = X/3;
	int minigridCol = Y/3;
	for (int loopRow = minigridRow*3; loopRow < minigridRow*3+3; loopRow++) { // same num in mini grid?
		for (int loopCol = minigridCol*3; loopCol < minigridCol*3+3; loopCol++) {
			if(puzzle[loopRow][loopCol] != 0)
				invalid.push_back(puzzle[loopRow][loopCol]);
		}
	}
	std::sort(invalid.begin(), invalid.end());
	invalid.erase(std::unique(invalid.begin(), invalid.end()), invalid.end());
	
	
	if(puzzle[X][Y]!=0){
		spotTaken=true;
	}
	vector<T> untakenValues;
	for(int i=1; i<=9; i++){
		//cout<< invalid[i-1];
		if((std::find(invalid.begin(), invalid.end(), i) != invalid.end())||spotTaken){
			untakenValues.push_back(0);
		}
		else{
			untakenValues.push_back(1);
		}
		
	}
	//cout<<endl;
	return untakenValues;
}




template<typename T>
void sodoku<T>::updateUntakenValues(){
	vector<T> untakenValuesSegment;
	vector< vector<T> > untakenValues2Segment;
	for(int i= 0; i< 9; i++){
		for(int j=0; j< 9 ; j++){
				untakenValuesSegment= getValidArray(i,j);
				untakenValues2Segment.push_back(untakenValuesSegment);
				untakenValuesSegment.clear();
		}
		untakenValues.push_back(untakenValues2Segment);
		untakenValues2Segment.clear();
	}
	for(int i= 0; i< 9; i++){
		for(int j=0; j< 9 ; j++){
			for (int k=0; k<9; k++) {
				cout<< untakenValues[i][j][k];
			}
			cout<< " ";
		}
		cout<< endl;
	}
}

//template<typename T>
//vector<T> sodoku<T>::getValidArray(int X, int Y){
//	vector<T> invalid;
//	for(int l=0; l< 9 ; l++){
//		invalid.push_back(*(squareValuesPtr[l][squareVal[X][Y]]));
//		invalid.push_back(*(verticalValuesPtr[l][Y]));
//		invalid.push_back(*(horizontalValuesPtr[l][X]));
//	}
//	// fix it up into a nice vector with only one copy of each invalid element
//	//erase all of the 0's
//	invalid.erase(std::remove(invalid.begin(), invalid.end(), 0), invalid.end());
//	std::sort(invalid.begin(), invalid.end());
//	invalid.erase(std::unique(invalid.begin(), invalid.end()), invalid.end());
//	
//	vector<T> untakenValues;
//	for(int i=0; i<9; i++){
//		if(!(std::find(invalid.begin(), invalid.end(), i) != invalid.end())){
//			untakenValues.push_back(1);
//		}
//		else{
//			untakenValues.push_back(0);
//		}
//	}
//	return untakenValues;
//}
//
//template<typename T>
//void sodoku<T>::updateUntakenValues(){
//	cout<< "updateUntakenValues"<< endl;
//	//vector<T> untakenValuesSegment;
//	vector<int> untakenValuesSegment(9, 0);
//	vector< vector<T> > untakenValues2Segment;
//	//vector<vector<int> > untakenValuesSegment(9, vector<int>(9, 0));
//	//untakenValues.clear();
//	for(int i= 0; i< 9; i++){
//		for(int j=0; j< 9 ; j++){
//			cout<<i<<j<<" "<<puzzle[i][j] <<"   ";
//			if(puzzle[i][j] != 0){
//				untakenValuesSegment= getValidArray(i,j);
//				untakenValues2Segment.push_back(untakenValuesSegment);
//				untakenValuesSegment.clear();
//			}
//		}
//		cout<<endl;
//		untakenValues.push_back(untakenValues2Segment);
//		untakenValues2Segment.clear();
//	}
//
////	vector<T> vec;
////	for(int i= 0; i< 9; i++){
////		for(int j=0; j< 9 ; j++){
////			for(int k=0; k< 9 ; k++){
////				vec.push_back(untakenValues[j][i][k]);
////			}
////		}
////	}
//	
//		for(int i= 0; i< 9; i++){
//				for(int j=0; j< 9 ; j++){
//						for (int k=0; k<9; k++) {
//								cout<< untakenValues[i][j][k];
//						}
//						cout<< " ";
//					}
//				cout<< endl;
//		}
//	
//	
//}



//template<typename T>
//bool sodoku <T>:: singleton(){
//	
//}




//template<typename T>
//bool sodoku <T>:: singleton(){
//	cout<< "singleton"<< endl;
//
//	//cout<<endl;
//	//cout<<endl;
//	//cout<<endl;
//	int memspoti=-1, memspotj =-1;
//	int inv[9]={0};
//	for(int i= 0; i< 9; i++){
//		for(int j=0; j< 9 ; j++){
//			if(puzzle[i][j]==0)
//				for(int k=0; k<(untakenValues[i][j]).size(); k++){
//					cout<< untakenValues[i][j][k];
//					inv[untakenValues[i][j][k]]++;
//					if(inv[untakenValues[i][j][k]] == 1){
//						memspoti =i;
//						memspotj=j;
//					}
//				}
//			cout<< " ";
//		}
//		cout<<endl;
//		for(int i= 8; i> 0; i--){
//			if (inv[i] == 1){
//				puzzle[memspoti][memspotj]=i;
//				print();
//				//break;
//			}
//		}
//		updateUntakenValues();
//	}
//	cout<< memspoti <<" "<<memspotj<<"  " << puzzle[memspoti][memspotj];
//	
//	
//	cout<<"checking the rows"<< endl;
//	for(int i= 0; i< 9; i++){
//		for(int z= 0; z< 9; z++){
//			inv[z]=0;
//		}
//		for(int j=0; j< 9 ; j++){
//			if(puzzle[i][j]==0)
//				for(int k=0; k<(untakenValues[j][i]).size(); k++){
//					//cout<< untakenValues[j][i][k];
//					inv[untakenValues[j][i][k]]++;
//					if(inv[untakenValues[j][i][k]] == 1){
//						memspoti =i;
//						memspotj=j;
//						cout<< "found singleton"<<endl;
//					}
//				}
//			cout<< "i and j: "<< i<<j<< endl;
//		}
//		//cout<<endl;
//		for(int i= 8; i> 0; i--){
//			if (inv[i] == 1){
//				puzzle[memspotj][memspoti]=i;
//				print();
//				//break;
//			}
//		}
//			updateUntakenValues();
//	}
//	cout<<" i: "<< memspoti <<" j: "<<memspotj<<"  " << puzzle[memspoti][memspotj];
//	
//	return false;
//
//}

template<typename T>
void sodoku<T>:: solve(){
	cout<< "solve"<< endl;

	int sum=0;
	int place =0;
	int puzzleIterations=0;
	bool foundSimple= true;
	
	//while(singleton() == false){
//		if((foundSimple)== false) {
//			singleton();
//			foundSimple= true;
//		}
//		else{
	updateUntakenValues();
	while(!Won()){
		cout<< "solve1"<< endl;
		for(int i= 0; i< 9; i++){
			for(int j=0; j< 9 ; j++){
				sum=0;
				for(int k=0; k< 9 ; k++){
					if (untakenValues[i][j][k] == 1) {
						sum +=1;
					}
				}
					if(sum==1){
						cout<< "solvesolve"<< endl;

						for(int k=0; k< 9 ; k++){
							if (untakenValues[i][j][k] == 1) {
								cout<< "FOUND"<<endl;
								puzzle[i][j]=k+1;
								for(int z=0; z< 9 ; z++){
								untakenValues[i][j][z]=0;
									}
								for(int h=0; h< 9 ; h++){
									untakenValues[i][h][k]=0;
									untakenValues[h][j][k]=0;
								}
								int minigridRow = i/3;
								int minigridCol = j/3;
								for (int loopRow = minigridRow*3; loopRow < minigridRow*3+3; loopRow++) { // same num in mini grid?
									for (int loopCol = minigridCol*3; loopCol < minigridCol*3+3; loopCol++)
										untakenValues[loopRow][loopCol][k]=0;
								}
							}
					}
						print();
						j=0;

				}
			
		}
		}
	}
}



#endif /* defined(____sodoku2__) */



