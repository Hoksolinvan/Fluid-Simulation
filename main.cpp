#include <iostream>
#include <cstring>


#define IX(i,j) ((i)+(N+2)*(j))

const int N = 16;
char grid[(N+2)*(N+2)];
float dens[(N+2)*(N+2)];
float dens_prev[(N+2)*(N+2)];
float source[(N+2)*(N+2)];
float dt =1;

void printout();
void border_initializer(float* dens);
void add_source(float* x, float* s, float dt);
void diffuse(float* x=dens, float* x0=dens_prev, float diff=0.001f, float dt=1);


int main(){
    memset(dens, 0, sizeof(dens));
    memset(dens_prev, 0, sizeof(dens_prev));
    
    dens_prev[IX(8,8)] = 100.0f;
    
   for(int step = 0; step < 10; step++){
    diffuse(dens, dens_prev, 0.002f, 1.0f);
    printout();
    std::cout << "--- step " << step << " ---" << std::endl;
    memcpy(dens_prev, dens, sizeof(dens));
}
    return 0;

}



void border_initializer(float* dens){
    
    for(int i=0;i<N+2;i++){
        dens[IX(i,0)]=-1;
    }
    
    for(int i=0;i<N+2;i++){
        dens[IX(0,i)]=-1;
    }
    
    for(int i=0;i<N+2;i++){
        dens[IX(N+1,i)]=-1;
    }
    
    
    for(int i=0;i<N+2;i++){
        dens[IX(i,N+1)]=-1;
    }
    
    
    return;
}

void printout(){

    
    for(int j=0; j<(N+2);j++){
        for(int i=0; i<(N+2);i++){
            
            if(dens[IX(i,j)]>1.0f){
                std::cout << "# " ; 
            }
            else if(dens[IX(i,j)]==0){
                std::cout << ". ";
            }
            else{
                std::cout << ". ";
                //std::cout << "* ";
            }
            
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


void diffuse(float* x, float* x0, float diff, float dt){
    
    
    float a = dt * diff * N * N;
    
    
    for(int k =0; k<20;k++){
    for(int j=1; j<N+1;j++){
        for(int i=1; i<N+1;i++){
    
            x[IX(i,j)]=(x0[IX(i,j)]+a*(x[IX(i-1,j)]+x[IX(i+1,j)]+x[IX(i,j-1)]+x[IX(i,j+1)])) / (1+4*a);
        }
    }
    }
    
    return;
}

