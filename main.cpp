#include <iostream>
using namespace std;

#include <vector>
#include <fstream>
#include "sodoku.h"
#include <cstdlib>
#include <cstring>
#include <string>

int main(){

	
string fileName;
cout << "Please enter file name: ";
cin >> fileName;

sodoku <int> puzzle("sodoku.txt");
	puzzle.print();

}