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


int deg;
ofstream outfile;

/* //Functions declarations.
bPTreeNode* init();
void splitNode(bPTreeNode* x);
void insertElem(double val, string s);
void traverse(bPTreeNode *p);
bool searchInt(bPTreeNode* temp1, double val);
bool rangeSearch(bPTreeNode * temp1, double begin, double end);
*/
void printManip(double val, string s);// Function Declaration.

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


// Struct of Listnode through which all elements are joined.
struct ListNode {
  int val;
  ListNode *next;
  ListNode(int x) : val(x), next(NULL) {}
};


// Creating a new node. Making it a leaf.
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

//Traversing the B Plus Tree.
void traverse(bPTreeNode *p){
    //cout<<"Length of node is: "<<p->n<<endl;
    cout<<endl;
    int i;
    for (i = 0; i < p->n; i++)
    {
        if (p->leaf == false)
        {
            traverse(p->childPtr[i]);
        }
        cout << " " << p->data[i]<<":"<<p->valPair[i]<<" ";
    } 
    if (p->leaf == false)
    {
        traverse(p->childPtr[i]);
    }
    cout<<endl;
}


// SPlitting the leaf node into two elements and one parent pointer.
void splitNode(bPTreeNode* x){
  cout<<" Call to split function with val: "<<endl;
  double mid;
  string u;
  int left_child=ceil(float(deg)/2);
  int left_elem= left_child-1;
  bPTreeNode* temp1, *temp2;
  if(x->leaf==true){//*****************************************Splitting a Leaf Node.
    mid=x->data[left_elem];
    u=x->valPair[left_elem];
    
    temp2=init();
    temp2->leaf=true;
    if(x->parentPtr==NULL){// Creating a parentPtr if needed.
      temp1=init();
      temp1->leaf=false;
      cout<<"yooooooooooo"<<endl;
      x->parentPtr=temp1;
      root=temp1;
    }
    else
      temp1=x->parentPtr;// Copying the parentPtr.
    //x->leaf=true;
    cout<<"root vall is: "<<temp1->data[1]<<endl;
    int len=x->n;
    for(int j=left_elem;j<len;j++){//Copying elem. following mid. to newly created sibling.
      temp2->data[j-left_elem]=x->data[j];
      temp2->valPair[j-left_elem]=x->valPair[j];// Passing the valPair to the newly created sibling.
      cout<<"Passed string is: "<<x->valPair[j]<<endl;
      temp2->childPtr[j-left_elem]=x->childPtr[j];//This childPtr will be NUll, as they-leaves.
      //temp2->childPtr[j-2]->parentPtr=temp2;// Not Applicable, as childs are NULL.
      temp2->n++;
      x->data[j]=0;
      x->valPair[j]="";
      x->childPtr[j]=NULL;//This childPtr will be NUll, as they-leaves.
      x->n--;
    }// End of for loop.
    cout<<"the final length is: "<<x->n<<endl;
    // Copy values and child ptr. to parent pointer if present or assign new values.
    int a=0;
    cout<<"root val is: "<<temp1->data[0]<<endl;
    while(temp1->data[a]<=mid && a<temp1->n)// Calc. the psn of new element in parent node.
      a++;
    //temp1->n++;
    cout<<"temp1 elements is: "<<temp1->n<<endl;
    for(int b=(temp1->n); b>a;b--){// Moving the array and childPtr contents.
      temp1->data[b]=temp1->data[b-1];
      temp1->valPair[b]=temp1->valPair[b-1];
      temp1->childPtr[b+1]=temp1->childPtr[b];
    }
    temp1->data[a]=mid;
    //temp1->valPair[a]=u;//Copying the vaPair to the Branch Node.
    temp1->n++;
    temp1->childPtr[a]=x;// re-assigning already existing child.
    temp1->childPtr[a+1]=temp2;//Assigning newly created child.
    //x->parentPtr=temp1;// Declaring the parent pointer to the child nodes.
    temp2->parentPtr=temp1;// Declaring the parent pointer to the child nodes.
    if(x->rgtSiblPtr!=NULL){
      x->rgtSiblPtr->lftSiblPtr=temp2;//Why temp2->rgtSiblPtr=x->rgtSiblPtr; //not working.?
      temp2->rgtSiblPtr=x->rgtSiblPtr;// Why temp=x->rgtSiblPtr->lftSiblPtr; //not working.?
      x->rgtSiblPtr=temp2;//Linking Left and newly created right sibling.
      temp2->lftSiblPtr=x;//Linking Left and newly created right sibling.
    }
    else{
      x->rgtSiblPtr=temp2;//Linking Left and newly created right sibling.
      temp2->lftSiblPtr=x;//Linking Left and newly created right sibling.
    }
    cout<<"The root length is: "<<temp1->n<<endl;
    if(temp1->n==deg)
      splitNode(temp1);// If the parent is full. Calling the fn. once again recursively.
  }
  
//*********************************************************************************************
//***
  else{//Splitting a Branch Node.
    //cout<<"beign elem. is: "<<x->data[0]<<endl;
    mid=x->data[left_elem];
    u=x->valPair[left_elem];
    temp2=init();
    temp2->leaf=false;
    if(x->parentPtr==NULL){// Creating a parentPtr if needed.
      temp1=init();
      temp1->leaf=false;
      x->parentPtr=temp1;
      root=temp1;
    }
    else
      temp1=x->parentPtr;// Copying the parentPtr.
    int len2=x->n;
    for(int j=left_child;j<len2;j++){//Copying elem. following mid. to newly created sibling.
      temp2->data[j-left_child]=x->data[j];
      temp2->valPair[j-left_child]=x->valPair[j];// Passing the valPair to the newly created sibling.
      temp2->childPtr[j-left_child]=x->childPtr[j];//This childPtr will be NUll, as they-leaves.
      temp2->childPtr[j-left_child]->parentPtr=temp2;//Changing the parentPtr of the children newly attached to temp2.
      temp2->n++;
      x->data[j]=0;
      x->valPair[j]="";
      x->childPtr[j]=NULL;// As they are getting moved into new sibling,so NULL.
      x->n--;
    }// End of for loop.
    temp2->childPtr[len2-left_child]=x->childPtr[len2];//Copying the last child to new sibling.
    temp2->childPtr[len2-left_child]->parentPtr=temp2;//Changing the parentPtr of the children newly attached to temp2.
    x->childPtr[len2]=NULL;// As they are getting moved into new sibling,so NULL.
    x->n--;// As mid value is moved to Parent Node.
    // Copy values and child ptr. to parent pointer if present or assign new values.
    int a=0;
    while(temp1->data[a]<=mid && a<temp1->n)// Calc. the psn of new element in parent node.
      a++;
    //temp1->n++;
    cout<<"root elem. are: "<<temp1->n<<" "<<a<<endl;
    for(int b=(temp1->n); b>a;b--){// Moving the array and childPtr contents.
      temp1->data[b]=temp1->data[b-1];
	  temp1->valPair[b]=temp1->valPair[b-1];
      temp1->childPtr[b+1]=temp1->childPtr[b];
    }
    temp1->data[a]=mid;
    //temp1->valPair[a]=u;//Copying the vaPair to the Branch Node.
    temp1->n++;
    temp1->childPtr[a]=x;// re-assigning already existing child.
    //cout<<"temp2 elem. are: "<<temp2->childPtr[1]->data[0]<<endl;
    temp1->childPtr[a+1]=temp2;//Assigning newly created child.
    //x->parentPtr=temp1;// Declaring the parent pointer to the child nodes.
    temp2->parentPtr=temp1;// Declaring the parent pointer to the child nodes.
    if(x->rgtSiblPtr!=NULL){
      x->rgtSiblPtr->lftSiblPtr=temp2;//Why temp2->rgtSiblPtr=x->rgtSiblPtr; //not working.?
      temp2->rgtSiblPtr=x->rgtSiblPtr;// Why temp=x->rgtSiblPtr->lftSiblPtr; //not working.?
      x->rgtSiblPtr=temp2;//Linking Left and newly created right sibling.
      temp2->lftSiblPtr=x;//Linking Left and newly created right sibling.
    }
    else{
    x->rgtSiblPtr=temp2;//Linking Left and newly created right sibling.
    temp2->lftSiblPtr=x;//Linking Left and newly created right sibling.
    }
    cout<<"root elem. are: "<<x->n<<" "<<a<<endl;
    if(temp1->n==deg)
      splitNode(temp1);// If the parent is full. Calling the fn. once again recursively.
  }
}


// Inserting elements into the node.
void insertElem(double val, string s){
  cout<<" Call to insert function with insert val:"<<val<<endl;
    int i;// temp;
    x=root;
    if(root==NULL){
      root=init();
      x=root;
      x->data[0]=val;//First value.
      x->valPair[0]+=s;//Inserting the value contents to the valPair array.
      x->n++;
    }
    else{//Not a NULL Tree.
      cout<<"no. of elem. are: "<<x->n<<endl;
      while(x->leaf==false){//Iterating through the tree to the leaf node.
        //cout<<"root"<<endl;
        for(i=0;i<x->n;i++){
          cout<<"To be compared branch node val is: "<<x->data[i]<<endl;
          if(x->data[i]>val)
            break;
        }
        x=x->childPtr[i];// Passing to the child.
      }
      if(x->leaf==true){// When the leaf is filled after entering new elem.
        cout<<"full node with begin is: "<<x->data[0]<<endl;
        int a=0;
        //cout<<"Num. of elements is: "<<x->n<<endl;
        while(x->data[a]<val && a<x->n)// Calc. the psn of new element.
          a++;
        //cout<<" a is: "<<a<<" "<<x->n<<endl;
        cout<<"The present data val is: "<<x->data[a]<<endl;
        if(x->data[a]==val)
          x->valPair[a]+=","+s;
        else{  
          for(int b=(x->n); b>a;b--){// Moving the array contents.
            x->data[b]=x->data[b-1];
            x->valPair[b]=x->valPair[b-1];
            //x->valPair[b-1]
          }
          x->data[a]=val;// Inserting the val. in it's psn in leaf node.
          x->valPair[a]=s;//Insrting the value contents to the valPair array.
          x->n++;
          //cout<<x->n<<" "<<x->parentPtr->data[0]<<endl;
          if(x->n==deg)// If the leaf node if full, then split.
            splitNode(x);
          //x=root;
        }
      }// End of if condition.
    }
}


bool searchInt(bPTreeNode* temp1, double val){// Standard Search Algorithm.
  int i;
  while(temp1!=NULL){
    for(i=0;i<temp1->n;i++){
      cout<<"To be compared branch node val is: "<<temp1->data[i]<<endl;
      if(temp1->data[i]==val && temp1->leaf==true){
          //cout<<temp1->valPair[i]<<endl;
          outfile<<temp1->valPair[i]<<endl;
          return true;
      }
      if(temp1->data[i]>val)
        break;
    }
    temp1=temp1->childPtr[i];
  }
  outfile<<"Null"<<endl;//cout<<"NULL"<<endl;
  return false;
}


bool rangeSearch(bPTreeNode * temp1, double begin, double end){
  int i,b=0;
  while(temp1->leaf==false){//Iterating so as to reach the leaf node.
    for(i=0;i<temp1->n;i++){
      cout<<"Elem. under scanner is: "<<temp1->data[i]<<endl;
      if(temp1->data[i]>begin)
        break;
    }
    temp1=temp1->childPtr[i];
  }
  
  if(temp1->leaf==true){//Iterating through the leaf node, so as to reach the val. psn.
    bPTreeNode * temp2;
    cout<<" the level is leaf."<<endl;
    int a=0;
    while(temp1->data[a]<begin && a<temp1->n)
      a++;
    cout<<"current val is: "<<temp1->data[a]<<endl;
    //if(temp1->data[a]==begin)
    //  cout<<"Matched range elem. is: "<<temp1->data[a]<<endl;
    while(temp1!=NULL && temp1->data[a]>=begin && temp1->data[a]<=end && a<temp1->n){
      if(b!=0)
        outfile<<",";//cout<<",";
      //cout<<"Matched range elem. is: "<<temp1->data[a]<<" : "<<temp1->valPair[a]<<endl;
      printManip(temp1->data[a], temp1->valPair[a]);
      b=1;
      a++;
      if(a==temp1->n && temp1->rgtSiblPtr !=NULL){
        temp1=temp1->rgtSiblPtr;
        a=0;
      }
    }  
  }
  outfile<<endl;//cout<<endl;
  if(b==0){
    outfile<<"Null"<<endl;//cout<<"NULL"<<endl;
    return false;
  }
  else
    return true;
}

void printManip(double val, string s){
  //cout<<"Passed value is: "<<val<<" passed valpair is: "<<s<<endl;
  string t="",u;
  int i;
  for(int i=0;i<s.length();i++){
    if(i!=0)
      outfile<<",";//cout<<",";
    u="";
    while(s.compare(i,1,",")!=0 && i<s.length()){
      u+=s[i];
      i++;
    }
    //cout<<"Extracted value is: "<<u<<endl;
    cout<<"("<<val<<","<<u<<")";
    outfile<<"("<<val<<","<<u<<")";
  }
  //cout<<endl;
}

int main(){
  cout<<"Give the degree value."<<endl;
  //cin>>deg;
  ifstream myfile;
  myfile.open("input.txt");
  outfile.open("output3.txt");
  myfile>>deg;
  cout<<"Degree val is: "<<deg<<endl;
  string t;
  //cin>>t;
  myfile>>t;
  cout<<"String is: "<<t<<endl;
  int d=0,len;
  while(!myfile.eof()){
    //cout<<" string is: "<<t<<endl;
    double num1=0, num2=0;
    string valPair;
    len=t.length();
    //cout<<"The length is: "<<len<<endl;
    
    if(t.compare(0,1,"I")==0){// Case when Insert function is required.
      d=7;
      //cout<<"Insert function required."<<endl;
      while(t.compare(d,1,",")!=0)
        d++;
      //num1=stod(t.substr(7,d-7));
	  char* c=new char[d-7];
      t.copy(c,d-7,7);
      num1=atof(c);
      valPair=t.substr(d+1, len-1-d-1);
      cout<<"num is: "<<num1<<" and the vlaue is: "<<valPair<<endl;
      insertElem(num1, valPair);
    }
    else if(t.compare(0,1,"S")==0){
      d=7;
      while(t.compare(d,1,",")!=0 && d<len)
        d++;
      if(d==len){
		char* c=new char[len-7];//num1=stod(t.substr(7, len-7));
        t.copy(c,len-7,7);
        num1=atof(c);
        cout<<"num1 is: "<<num1<<endl;
        bool result=searchInt(root, num1);
        if(result)
          cout<<"Element present in btree."<<endl;
        else
          cout<<"Null"<<endl;
      }
      else{
		char* c=new char[d-7];//num1=stod(t.substr(7,d-7));
        t.copy(c,d-7,7);
        num1=atof(c);
		char* e=new char[len-2-d];//num2=stod(t.substr(d+1, len-2-d));
        t.copy(e,len-2-d,d+1);
        num2=atof(e);
        cout<<"num1 is: "<<num1<<" and the num2 is: "<<num2<<endl;
        bool results= rangeSearch(root, num1, num2);
        if(results)
          cout<<"Range Present in btree."<<endl;
        else
          cout<<"Null"<<endl;
      }
      
    }
    
    //cin>>t;//Loading the next string to the string variable.
    myfile>>t;
  }
  /*
  //cout<<"mid val is: "<<ceil(float(5)/2)<<endl;
  //bPTreeNode* root;
  insertElem(4, "Value91");
  insertElem(7, "Value92");
  insertElem(5, "Value93");
  insertElem(5, "Value94");
  insertElem(9, "Value95");
  insertElem(8, "Value96");
  insertElem(6, "Value97");
  cout<<"Done withhhhhhhhhhhhhhhhhhhhhhhhh: "<<6<<endl;
  insertElem(16, "Value98");
  insertElem(17, "Value99");//**
  insertElem(18, "Value100");//**
  insertElem(6, "Value101");//**
  insertElem(6, "Value102");//**
  insertElem(6, "Value103");//**
  insertElem(6, "Value104");//**
  insertElem(6, "Value105");//**
  insertElem(16, "Value106");//**
  insertElem(19.5, "Value107");//**
  //cout<<"Properly working till now."<<endl;
  //insertElem(6);//**Two-to three layer.
  //insertElem(6);//**
  //insertElem(6);//**
  cout<<"root no. elements are: "<<root->n<<endl;
  //cout<<"Desired val is: "<<root->childPtr[1]->childPtr[3]->data[1]<<endl;
  //insertElem(6);
  //insertElem(21);
  cout<<"Properly working till now."<<endl;
  //insertElem(22);
  //insertElem(23);
  //insertElem(24);
  //insertElem(25);
  //insertElem(26);
  /*
  insertElem(4);//Testig today. Trying to split the first elem. in the second level.
  insertElem(4);
  insertElem(4);
  insertElem(4);
  insertElem(4);
  insertElem(4);
  insertElem(4);
  insertElem(4);
  insertElem(4);
  insertElem(4);
  insertElem(6);//Trying the mid elem. in the second level.
  insertElem(6);
  insertElem(6);
  insertElem(6);
  insertElem(6);
  insertElem(6);
  insertElem(6);
  insertElem(17);
  insertElem(22);
  insertElem(22);
  insertElem(22);
  */
  //*/
  
  
  /*
  traverse(root);
  bool result=searchInt(root, 6);//Searching for an integer.
  if(result)
    cout<<"Element present in btree."<<endl;
  else
    cout<<"Not present."<<endl;
    */
  
  //cout<<"Child's right sibling's first val is: "<<root->childPtr[1]->rgtSiblPtr->data[0]<<endl;
  //cout<<"root val 0 is: "<<root->data[1]<<endl;
  /*
  cout<<"Range search begins."<<endl;
  bool results=rangeSearch(root, -2, 16);
  if(results)
    cout<<"Range present in btree."<<endl;
  else
    cout<<"Not present."<<endl;
  */
  return 0;
}