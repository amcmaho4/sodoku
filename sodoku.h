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
	string line;
	int index;
	while ( getline (inFile,line) ){
		puzzle.push_back( vector<T> ());
		for(int i = 0 ; i < line.size() ; i++){    //Read in a line into a temporary vector
			if(!isspace(line[i])){
				puzzle[index].push_back(line[i]-'0');
				cout<< line[i];
			}
			//check to see if it is not a space
			
			// do diiferent things depending on whether it is a char or int typeid
		}
		cout<<endl;
		index++;
	}

}

	
	
	




#endif /* defined(____sodoku__) */
