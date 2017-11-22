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

using namespace std;

//Global Varibale Declarations.
int deg;
ofstream outfile;																				//To write in the output.txt file.

/* //*****************************************Functions declarations.
bPTreeNode* init();
void splitNode(bPTreeNode* x);
void insertElem(double val, string s);
void traverse(bPTreeNode *p);
void searchInt(bPTreeNode* temp1, double val);
void rangeSearch(bPTreeNode * temp1, double begin, double end);
void printManip(double val, string s);// Function Declaration.
*/


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
bPTreeNode *root=NULL, *np=NULL,*x=NULL;// Declaring the Global bPTreeNode pointers.



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

//Traverse the B Plus Tree and prints it's contents.
void traverse(bPTreeNode *x){
	
    cout<<endl;
    int i;
    for(i = 0; i < x->n; i++){
        if (x->leaf == false){
            traverse(x->childPtr[i]);
        }
        cout << " " << x->data[i]<<":"<<x->valPair[i]<<" ";
    } 
    if(x->leaf == false){
        traverse(x->childPtr[i]);
    }
    cout<<endl;
	
}

// Splits node into two Siblings and meges the mid value in the parent Node if exists if not creates a Parent Node and inserts mid value.
void splitNode(bPTreeNode* x){
	
  double mid;
  string u;
  int left_child=ceil(float(deg)/2);
  int left_elem= left_child-1;
  bPTreeNode* temp1, *temp2;
  
  if(x->leaf==true){																//Splitting a Leaf Node.
    mid=x->data[left_elem];
    u=x->valPair[left_elem];
    temp2=init();
    temp2->leaf=true;
	
    if(x->parentPtr==NULL){															// Creating a parentPtr if needed.
      temp1=init();
      temp1->leaf=false;
      x->parentPtr=temp1;
      root=temp1;
    }
    else
      temp1=x->parentPtr;															// Copying the parentPtr, if already exists.
    int len=x->n;
    for(int j=left_elem;j<len;j++){													//Copying elem. following mid. to newly created sibling.
      temp2->data[j-left_elem]=x->data[j];
      temp2->valPair[j-left_elem]=x->valPair[j];									// Passing the data, valPair to the newly created sibling.
      temp2->childPtr[j-left_elem]=x->childPtr[j];									//This childPtr will be NUll, as they-leaves.																			//temp2->childPtr[j-2]->parentPtr=temp2;// Not Applicable, as childs are NULL.
      temp2->n++;
      x->data[j]=0;																	//Making the copied values in original node to be NULL/0.
      x->valPair[j]="";
      x->childPtr[j]=NULL;															//This childPtr will be NUll, as they-leaves.
      x->n--;
    }
																					// Copy data, valPair and child ptr. to parent pointer if present or assign new values.
    int a=0;
    while(temp1->data[a]<=mid && a<temp1->n)										// Calc. the psn of new element in parent node.
      a++;
    for(int b=(temp1->n); b>a;b--){													// Moving the data, valPair and childPtr contents.
      temp1->data[b]=temp1->data[b-1];
      temp1->valPair[b]=temp1->valPair[b-1];
      temp1->childPtr[b+1]=temp1->childPtr[b];
    }
	
    temp1->data[a]=mid;																//Copying the mid value to the Parent Node.
    temp1->n++;
    temp1->childPtr[a]=x;															// re-assigning already existing child.
    temp1->childPtr[a+1]=temp2;														//Assigning an index to newly created child.
																					//x->parentPtr=temp1;// Declaring the parent pointer to the child nodes.
    temp2->parentPtr=temp1;															// Declaring the parent pointer to the child nodes.
    
	if(x->rgtSiblPtr!=NULL){														// Assigning, left & right childptr to passed, newly created sibling Nodes.
      x->rgtSiblPtr->lftSiblPtr=temp2;
      temp2->rgtSiblPtr=x->rgtSiblPtr;
      x->rgtSiblPtr=temp2;															//Linking Left and newly created right sibling.
      temp2->lftSiblPtr=x;															
    }
	
    else{																			//If there exists no right ptr to passed Node.
      x->rgtSiblPtr=temp2;
      temp2->lftSiblPtr=x;
    }
	
    if(temp1->n==deg)																// If the parent is full. Calling the fn. once again recursively.
      splitNode(temp1);
	  
  }
  

  
  

  else{																				//Splitting a Branch Node.
  
    mid=x->data[left_elem];															//Copying the mid data value of node.
    u=x->valPair[left_elem];														//Copying the mid valPair of node.
    temp2=init();
    temp2->leaf=false;
    if(x->parentPtr==NULL){															// Creating a parentPtr if no such exists.
      temp1=init();
      temp1->leaf=false;	
      x->parentPtr=temp1;															//Making the created new Node the parent node of passed node.
      root=temp1;
    }
    else
      temp1=x->parentPtr;															// Copying the parentPtr.
    int len2=x->n;
	
    for(int j=left_child;j<len2;j++){												//Copying data, valPair, childPtr following mid. to newly created sibling.
	
      temp2->data[j-left_child]=x->data[j];
      temp2->valPair[j-left_child]=x->valPair[j];
      temp2->childPtr[j-left_child]=x->childPtr[j];
      temp2->childPtr[j-left_child]->parentPtr=temp2;								//Changing the parentPtr of the children newly attached to temp2.
      temp2->n++;
      x->data[j]=0;																	//Making the data, valPair, childPtr values of passed Node to NULL/0 after copying.
      x->valPair[j]="";
      x->childPtr[j]=NULL;
      x->n--;
	  
    }
    temp2->childPtr[len2-left_child]=x->childPtr[len2];								//Copying the last child to new sibling.
    temp2->childPtr[len2-left_child]->parentPtr=temp2;								//Changing the parentPtr of the children newly attached to temp2.
    x->childPtr[len2]=NULL;															// As they are getting moved into new sibling,so NULL.
    x->n--;																			// As mid value is moved to Parent Node.
																					// Copy values and child ptr. to parent pointer if present or assign new values.
    int a=0;
    while(temp1->data[a]<=mid && a<temp1->n)										// Calc. the psn of new element in parent node.
      a++;
    for(int b=(temp1->n); b>a;b--){													// Moving the data, valPair and childPtr contents.
	
      temp1->data[b]=temp1->data[b-1];
	  temp1->valPair[b]=temp1->valPair[b-1];
      temp1->childPtr[b+1]=temp1->childPtr[b];
	  
    }
    temp1->data[a]=mid;																//Copying the mid value to the parent Node.
    temp1->n++;
    temp1->childPtr[a]=x;															// re-assigning already existing child.
    temp1->childPtr[a+1]=temp2;														//Assigning newly created child.
																					//x->parentPtr=temp1;// Declaring the parent pointer to the child nodes.
    temp2->parentPtr=temp1;															// Declaring the parent pointer to the newly created sibling.
    
	if(x->rgtSiblPtr!=NULL){														// Assigning, left & right childptr to passed, newly created sibling Nodes.
	
      x->rgtSiblPtr->lftSiblPtr=temp2;
      temp2->rgtSiblPtr=x->rgtSiblPtr;
      x->rgtSiblPtr=temp2;															//Linking Left and newly created right sibling.
      temp2->lftSiblPtr=x;
	  
    }
    else{
		
    x->rgtSiblPtr=temp2;
    temp2->lftSiblPtr=x;
	
    }
    
    if(temp1->n==deg)																// If the parent is full. Calling the fn. once again recursively.
      splitNode(temp1);
  
  }
  
}


// Inserting elements into the B Plues Tree.
void insertElem(double val, string s){

    int i;
    x=root;
    if(root==NULL){																	//Creating a new root node, if such does not exist.
	
      root=init();
      x=root;
      x->data[0]=val;																//Assigning the data value.
      x->valPair[0]+=s;																//Inserting the value contents to the valPair array.
      x->n++;
	  
    }
    else{																			//If the B+ Tree is not a NULL Tree.
      
      while(x->leaf==false){														//Iterating through the tree, so as to reach leaf node.
	  
        for(i=0;i<x->n;i++){
																					//cout<<"To be compared branch node val is: "<<x->data[i]<<endl;
          if(x->data[i]>val)
            break;
		
        }
        x=x->childPtr[i];															// Passing to the childNode, as the required value might exits in it.
      }
      if(x->leaf==true){															//Confirming that x is a leaf node.
																					//cout<<"full node with begin is: "<<x->data[0]<<endl;
        int a=0;
        while(x->data[a]<val && a<x->n)												// Calc. the psn of new element.
          a++;
		  
        if(x->data[a]==val)															//If the passed bal. is already in tree, then append it's valPair to the prev. valPair.
          x->valPair[a]+=","+s;
	  
        else{																		// If the passed data value doesn't exist in tree.
          for(int b=(x->n); b>a;b--){												// Moving the data, valPair contents.
		  
            x->data[b]=x->data[b-1];
            x->valPair[b]=x->valPair[b-1];
			
          }
          x->data[a]=val;															// Inserting the data in it's psn in leaf node.
          x->valPair[a]=s;															// Inserting the valPair in the valPair array.
          x->n++;
          if(x->n==deg)																// If the leaf node if full, then call splitNode function.
            splitNode(x);
        }
		
      }
	  
    }
}

//Searches for a passed val in the tree.
void searchInt(bPTreeNode* temp1, double val){										//Takes root, required data value as arguements.

  int i,j;
  while(temp1!=NULL){
	  
    for(i=0;i<temp1->n;i++){
		
      if(temp1->data[i]==val && temp1->leaf==true){									//If the desired value is in tree print it's valPair.
																					//outfile<<temp1->valPair[i]<<endl;
		  j=0;
		  while(j<temp1->valPair[i].length()){										//Printing the valPair into output file in a desired way.
            if(temp1->valPair[i].compare(j,1,",")==0)
              outfile<<", ";
            else
              outfile<<temp1->valPair[i][j];
            j++;
          }
          outfile<<endl;
          return;
		  
      }
	  
      if(temp1->data[i]>val)														//Moving down the tree.
        break;
	
    }
    temp1=temp1->childPtr[i];														// Indicating which childNode the value might exist.
	
  }
  outfile<<"Null"<<endl;//cout<<"NULL"<<endl;
  return ;
  
}

//Places the contents in the output file in a desired way in rangeSearch.
void printManip(double val, string s){												// Takes data and valPair as arguements.
	
  string t="",u;
  int i;
  for(int i=0;i<s.length();i++){													//Iterating through the valPair string and prints the required valPair string.
	  
    if(i!=0)
      outfile<<",";																	
    u="";
    while(s.compare(i,1,",")!=0 && i<s.length()){									//Segregating the valPair string present b/w the commas.
		
      u+=s[i];
      i++;
	  
    }
    outfile<<"("<<val<<","<<u<<")";													//cout<<"("<<val<<","<<u<<")";//Printing the valPair to the "outfile.txt" file.	
	
  }
  
}


// Prints the data and valPair values in B + Tree in the given range of values.
void rangeSearch(bPTreeNode * temp1, double begin, double end){							//Takes root, begin, end value of arguements.
																						//cout<<"isde range seach,"<<"begin is "<<begin<<"end is: "<<end<<endl;
  int i,b=0;
  while(temp1->leaf==false){															//Iterating so as to reach the leaf node.
  
    for(i=0;i<temp1->n;i++){
  
	if(begin >= temp1->data[i] && begin < temp1->data[i+1]){	
		i++;
		break;
	}	
	else if(begin < temp1->data[0])
		break;

	else
		continue;
	
    }
    temp1=temp1->childPtr[i];
	
  }
  
  int j;
  while(temp1!=NULL){																	//Reaching the leaf node which might contain the reqired begin value.
	  j=0;
	  while(j!=temp1->n && temp1->data[j]<begin){
		  j++;
		  if(temp1->data[j]==begin)
			  break;
	  }
	  
	  if(j==temp1->n)																	//Moving to the right sibling in search of beign value.
		  temp1=temp1->rgtSiblPtr;
	  else 
		  break;
		  
	  
  }
  
  if(temp1->data[j]>end){																//If the found value is more than end, then returning Null.
	  outfile<<"Null"<<endl;
	  return;
	 }
	  
  if(temp1->leaf==true){															
    bPTreeNode * temp2;
    int a=0;
    while(temp1->data[a]<begin && a<temp1->n)											//Iterating through the leaf node, so as to reach the val. psn.
      a++;	
    while(temp1!=NULL && temp1->data[a]>=begin && temp1->data[a]<=end && a<temp1->n){	// Prints values in the given range of key values.		
		cout<<"num1 is: "<<begin<<"num2 is: "<<end<<endl;
      if(b!=0)
        outfile<<",";
      printManip(temp1->data[a], temp1->valPair[a]);									// Calling the printManip Fn so as to print in the valPair in desired manner.							
      b=1;
      a++;
      if(a==temp1->n && temp1->rgtSiblPtr !=NULL){										//Traversing to right sibling, as there might be values in it in the req. range.
	  
        temp1=temp1->rgtSiblPtr;
        a=0;
		
      }
	  
    }  
	
  }
  outfile<<endl;	
  if(b==0)																				//If No data value in the given range exists in the B Plus Tree.
    outfile<<"Null"<<endl;					
	
  return ;
  
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