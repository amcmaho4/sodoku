#include <iostream>
using namespace std;

#include <vector>
#include <fstream>
#include "sodoku.h"
#include <cstdlib>
#include <cstring>
#include <string>

int main(){

sodoku<int> puzzle;
string fileName;
cout << "Please enter file name: ";
cin >> fileName;

ifstream inFile;
inFile.open (fileName.c_str());
 string line;
	
 if (inFile.is_open())
 {
	 while ( getline (inFile,line) )
	 {
		 cout << line << '\n';
	 }
	 inFile.close();
 }
	
 else{
	 cout << "Unable to open file";
 }
	
//	if(inFile.is_open()){
//		cin >> inFile;
//		cout<<"opened file"<< endl;}
//else
//	cout<<"unable to open file"<< endl;


}