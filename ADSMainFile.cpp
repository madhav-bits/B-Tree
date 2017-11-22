/*

Author: Sai Madhav Kasam
Date:11/21/2017.
Course: Advanced Data Structures- Coding Assignment.
Unversity of Florida, Gainesville.

This code uses primtive data types to implement a B Plus Tree which implements various functionalities such as: Insert, Search, RangeSearch.

*/

#include<cstdlib>
#include<iostream>
#include<vector>
#include<map>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<fstream>
#include<string.h>
#include<string>
#include "ADSFunctions.h"

using namespace std;

//Global Varibale Declarations.
int deg;
ofstream outfile;
bPTreeNode *root=NULL;
bPTreeNode* np=NULL;
bPTreeNode *x=NULL;// Declaring the Global bPTreeNode pointers.


// Creating a new node and initializing all it's components to zero/NULL.
bPTreeNode* init(){
	
    int i;
    np = new bPTreeNode;
    np->data = new double[deg];
    np->childPtr = new bPTreeNode *[deg+1];
    np->leaf = true;
    np->n = 0;
    np->parentPtr=NULL;
    np->lftSiblPtr=NULL;
    np->rgtSiblPtr=NULL;
    for( i=0;i<deg;i++)
      np->valPair.push_back("");
    for (i = 0; i < (deg+1); i++)
        np->childPtr[i] = NULL;
    return np;
	
}


int main(int argc, char* argv{}){
  
  ifstream myfile;																		//To read te input.txt file.
  myfile.open(argv[1]);
  outfile.open("output3.txt");
  
  myfile>>deg;																			//Reads the first line and saves the degree of the tree value. 
																						//cout<<"Degree val is: "<<deg<<endl;
  string t;
  myfile>>t;
  int d=0,len;
  while(!myfile.eof()){
    double num1=0, num2=0;
    string valPair;
    len=t.length();
    
    if(t.compare(0,1,"I")==0){															// Case when Insert function is required.
      d=7;
      while(t.compare(d,1,",")!=0)
        d++;
	  char* c=new char[d-7];															//num1=stod(t.substr(7,d-7));
      t.copy(c,d-7,7);																	// Extracts the data value from the string.
      num1=atof(c);
      valPair=t.substr(d+1, len-1-d-1);													//Extracts the valPair from the string.
      insertElem(num1, valPair);														//Calling the insertElem Fn with the above extracted values.
	  
    }
	
    else if(t.compare(0,1,"S")==0){
      d=7;
      while(t.compare(d,1,",")!=0 && d<len)
        d++;
      if(d==len){																		//THIS CASE IS OF SEARCHING FOR A DATA VALUE.
	  
        char* c=new char[len-7];														//num1=stod(t.substr(7, len-7));
        t.copy(c,len-7,7);
        num1=atof(c);
        searchInt(root, num1);																//Calling the serachInt Fn with the above extracted value.
		
      }
	  
      else{																				//THIS CASE IS OF SEARCHING FOR A RANGE OF DATA VALUES.
	  
		char* c=new char[d-7];															//num1=stod(t.substr(7,d-7));
        t.copy(c,d-7,7);
        num1=atof(c);
		char* e=new char[len-2-d];														//num2=stod(t.substr(d+1, len-2-d));//Another way of extracting double from a string.
        t.copy(e,len-2-d,d+1);
        num2=atof(e);
        rangeSearch(root, num1, num2);														//Calling the rangeSearch Fn with the above extracted key values.
      }
      
    }
    
    myfile>>t;																			//Loading the next string to the string variable.
	
  }
  
  return 0;
}