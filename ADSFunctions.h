#include<cstdlib>
#include<iostream>
#include<vector>
#include<map>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<fstream>
#include<string>
#include<string.h>
using namespace std;


extern int deg;
extern ofstream outfile;

// Main struct of the bPTreeNode.
struct bPTreeNode{
	
  bPTreeNode* parentPtr;
  bPTreeNode* lftSiblPtr;
  bPTreeNode* rgtSiblPtr;
  double *data;
  bPTreeNode** childPtr;
  bool leaf;
  vector<string> valPair;
  int n;
  
};

extern bPTreeNode *root, *np,*x;
bPTreeNode* init();

void splitNode(bPTreeNode* x);
void insertElem(double val, string s);
void searchInt(bPTreeNode* temp1, double val);
void printManip(double val, string s);
void rangeSearch(bPTreeNode * temp1, double begin, double end);

