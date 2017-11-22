#include "ADSFunctions.h"


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


