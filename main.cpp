#include <iostream>
using namespace std;

#include <vector>
#include <fstream>
#include "sodoku2.h"
#include <cstdlib>
#include <cstring>
#include <string>

int main(){

	
//string fileName;
//cout << "Please enter file name: ";
//cin >> fileName;
	
	
//int userChoice;
//// lets the user play the two versions of the game
//cout<< "would you like to play sodoku(1) or wordoku(2)? "<< endl;
//	cin>> userChoice;
	
	//if(userChoice==1){  // playing actual sodoku
		sodoku <int> puzzle("mediumPuzzle.txt");

		puzzle.print();

	puzzle.updateUntakenValues();
	puzzle.singleton();

	//puzzle.solve();
	
	//	puzzle.insertSingle();
		//puzzle.solve();
	//}
//	else if(userChoice==2){ // palying wordoku
//		sodoku <char> puzzle("wordoku.txt");
//		puzzle.print();
//		puzzle.play();
//	}
//	else{
//		cout<< "that wasnt an option"<< endl;
//	}
}