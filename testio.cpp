//
//  testio.cpp
//  
//
//  Created by Anna Jo McMahon on 2/22/15.
//
//

#include <stdio.h>
#include <iostream>
using namespace std;
#include <fstream>
int main()
{
	
	int i = 0;
	int array[5];
	int max_read = 5;
	int amountRead = 0;
	ifstream in("sudoku.txt",ios::in |ios::binary);
	if(!in)
	{
  
		cout<<"Could not open file"<<endl;
		return 1;
  
	}
	//this is where we are reading in the information into our array
	while(in>>array[amountRead]&& amountRead < max_read)
	{
  
		amountRead++;
  
	}
	for(i = 0; i < 5; i++)
	{
  
		cout<<array[i]<<endl;
  
	}
	
	cin.get();
	
	return 0;
}