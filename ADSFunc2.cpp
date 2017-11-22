#include "ADSFunctions.h"



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
          outfile<<endl;															//cout<<endl;
		  
		  
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
