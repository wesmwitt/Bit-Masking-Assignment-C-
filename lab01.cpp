#include <iostream>
#include <bitset>

using std::cout;
using std::cin;
unsigned int getValue(unsigned int var, unsigned int k, unsigned int i);
void setValue(unsigned int & var, unsigned int k, unsigned int i, unsigned int val);

int main(){

  unsigned int var; //the unsigned int containing all the values
  unsigned int k; //the number of partitions
  unsigned int val; //the value to be placed into the var 

  //prompting user for k (number of partitions)
  cout << "Please input value of k: \n ";
  cin >> k;
  
  //populating var with values inputted by used
  for (int j=0; j < k; j++){
    cout << "Please input value at index " << j << ": ";
    cin >> val;
    setValue(var,k,j,val);
  }

  //listing out values contained within var
  cout << "Your values are : \n";

  for (int j=0; j < k; j++){
    cout << "index " << j << ": " << getValue(var,k,j) << "\n";
  }

}

void setValue(unsigned int & var, unsigned int k, unsigned int i, unsigned int val){

  unsigned int maskSize = 32/k;
  unsigned int mask = 0;

  //making the mask size                                                                                                                                                            
  for (int j=0; j < maskSize; j++){
    mask = mask|1;
    if (j==maskSize-1){
      break;
    }
    mask = mask << 1;
  }

  //shifting bit mask to proper place                                                                                                                                               
  for (int j=0; j < (32/k)*i; j++){
    mask = mask << 1;
  }
  
  //inverting mask to clear that section of var
  mask = ~mask;

  //bitwise AND with mask and given var to erase that section of var                                                                                                                
  var = var & mask;

  //adding new values to var
  unsigned int newValuesMask = val;

  //moving new values into right place in mask
  for (int j=0; j < (32/k)*i; j++){
    newValuesMask = newValuesMask << 1;
  }

  //bitwise OR to place new values in var
  var = var|newValuesMask;

}

unsigned int getValue(unsigned int var, unsigned int k, unsigned int i){
    
  unsigned int maskSize = 32/k;
  unsigned int mask = 0;

  //making the mask size                                                                                                                                                            
  for (int j=0; j < maskSize; j++){
    mask = mask|1;
    if (j==maskSize-1){
      break;
    }
    mask = mask << 1;
  }

  //shifting bit mask to proper place                                                                                                                                               
  for (int j=0; j < (32/k)*i; j++){
    mask = mask << 1;
  }
  
  //bitwise AND with mask and given var                                                                                                                                             
  unsigned int value = var & mask;
  
  //shifting bits right to give proper value                                                                                                                                        
  for (int j=0; j < (32/k)*i; j++){
    value = value >> 1;
  }
  
  return value;
}
