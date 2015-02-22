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
class sodoku  {
	
	
public:
	sodoku(string);
	//~sodoku();
	
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
	vector<T> tempVec;
	while(!inFile.eof()){ //While the file is not at the end
		for(int i = 0 ; i < sizeOfBoard ; i++){    //Read in a line into a temporary vector
			inFile >> tempVar; //Put just read value into temporary vector
			tempVec.push_back(tempVar);
			cout << tempVar;
			cout << endl;
		}
		cout << endl;
		puzzle.push_back(tempVec);   //Push back the line just read)
		tempVec.clear(); //Clear/recycle temporary vector
	}
}
	
	
	




#endif /* defined(____sodoku__) */
