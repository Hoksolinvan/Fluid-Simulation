#include <iostream>
#include <cstring>


#define IX(i,j) ((i)+(N+2)*j)

const int N = 16;
char grid[(N+2)*(N+2)];
float dens[(N+2)*(N+2)];
float source[(N+2)*(N+2)];

void printout();
void border_initializer();
void add_source(float* x, float* s, float dt);

int main(){

   memset(grid,'.',sizeof(grid));
    float source[(N+2)*(N+2)];
    memset(source,0,sizeof(source));
    
    source[IX(8,8)]= 5.0f;
    
    add_source(dens,source,1);
    
    for(int i =0; i<(N+2)*(N+2);i++){
        printf("%.2f ",dens[i]);
        
    }
    border_initializer();
    

    grid[IX(9,6)]='#';
    grid[IX(9,7)]='#';
    grid[IX(9,8)]='#';
    grid[IX(10,7)]='#';
    grid[IX(8,7)]='#';
   

  //printout();

  

return 0;
}



void border_initializer(){
    
    for(int i=0;i<N+2;i++){
        grid[IX(i,0)]='*';
    }
    
    for(int i=0;i<N+2;i++){
        grid[IX(0,i)]='*';
    }
    
    for(int i=0;i<N+2;i++){
        grid[IX(N+1,i)]='*';
    }
    
    for(int i=0;i<N+2;i++){
        grid[IX(i,N+1)]='*';
    }
    
    
    return;
}

void printout(){

    
    for(int j=0; j<(N+2);j++){
        for(int i=0; i<(N+2);i++){
            std::cout << grid[IX(i,j)]<< " ";
        }
        std::cout << std::endl;
    }
  
  return;
}


void add_source(float* x, float* s, float dt){
    
    
    for(int i=0; i<(N+2)*(N+2);i++){
        x[i]+=s[i]*dt;
    }
    
    return;
}
