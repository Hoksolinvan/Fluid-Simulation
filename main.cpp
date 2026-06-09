#include <iostream>
#include <cstring>


#define IX(i,j) ((i)+(N+2)*j)

const int N = 16;
float grid[(N+2)*(N+2)];

void printout(){

  for(int i=0; i<((N+2)*(N+2));i++){

    
    std::cout << grid[i] << " ";
    if(i%N==N-1){
    std::cout << "\n";
    }
  }
  
  return;
}

int main(){

   memset(grid,0,(N+2)*(N+2));

  grid[7]=1;
  grid[22]=1;
  grid[37]=1;

  printout();

  

  



return 0;
}
