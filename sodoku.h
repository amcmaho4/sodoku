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
	
friend istream &operator<<( istream &, const sodoku<T> & );
	
public:
	sodoku();
	~sodoku();
	
private:
	
	vector<vector <T> > puzzle;
	T *ptr; // pointer to first element of pointer-based array	
};



// Data members
template<typename T>
sodoku<T>::sodoku(){

}
template<typename T>
sodoku<T>::~sodoku(){
	
}


template<typename T>
istream &operator>> ( istream &input, sodoku<T> &puzzle ){
vector<T> tempVec;
int sizeOfBoard = 9;
T tempVar; // how can we define this as any thing?
	cout<< "out 1";
while(!input.eof()){ //While the file is not at the end
	cout<< "out 2";
	for(int i = 0 ; i < sizeOfBoard ; i++){    //Read in a line into a temporary vector
		input >> tempVar; //Put just read value into temporary vector
		cout<< input;
		tempVec.push_back(tempVar);
	}
	puzzle.push_back(tempVec);   //Push back the line just read)
	tempVec.clear(); //Clear/recycle temporary vector
}
	return input;

}




#endif /* defined(____sodoku__) */
