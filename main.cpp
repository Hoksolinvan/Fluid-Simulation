#include <iostream>
#include <cstring>


#define IX(i,j) ((i)+(N+2)*(j))

// Misc
const int N = 16;
char grid[(N+2)*(N+2)];
float dt =1;

// density field
float dens[(N+2)*(N+2)];
float dens_prev[(N+2)*(N+2)];

// input field
float source[(N+2)*(N+2)];


// velocity field
float u[(N+2)*(N+2)];
float v[(N+2)*(N+2)];
float u_prev[(N+2)*(N+2)];
float v_prev[(N+2)*(N+2)];


void printout();
void border_initializer(float* dens);
void add_source(float* x, float* s, float dt);
void diffuse(float* x=dens, float* x0=dens_prev, float diff=0.001f, float dt=1);
void advect(float* d, float* d0, float* u, float* v, float dt);
void dens_step(float* x=dens, float* x0=dens_prev, float* current_u=u, float* current_v=v, float diff=0.002f, float dt=1);
void set_bnd(int b, float* x);
void project(float* u, float* v, float* p, float* div);

void advect_tester(){
    for(int i = 0; i < (N+2)*(N+2); i++){
    u[i] = 0.05f;
    v[i] = 0.05f;
}
    
    return;
}

int main(){
    memset(dens, 0, sizeof(dens));
    memset(dens_prev, 0, sizeof(dens_prev));
    
    dens_prev[IX(8,8)] = 100.0f;
    
    advect_tester();
    
   for(int step = 0; step < 10; step++){
    dens_step();
    printout();
    std::cout << "--- step " << step << " ---" << std::endl;
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


void advect(float* d, float* d0, float* u, float* v, float dt){
    
   
        for(int j=1; j<N+1;j++){
             for(int i=1; i<N+1;i++){
                
                 float x = i - dt * N * u[IX(i,j)];
                 float y = j - dt * N * v[IX(i,j)];
                 
                 if(x < 0.5f) x = 0.5f;
                 else if(x> N + 0.5f) x = N + 0.5f;
                 
                 if(y < 0.5f) y = 0.5f;
                 else if(y > N+0.5f) y = N + 0.5f;
                 
                 int i0= (int)x;
                 int j0 = (int)y;
                 int i1= i0+1;
                 int j1 = j0+1;
                 
                 
                 float s1 = x - i0;
                 float s0 = 1 - s1;
                 float t1 = y - j0;
                 float t0 = 1 - t1;
                 
                 d[IX(i,j)] = s0 * (t0*d0[IX(i0,j0)] + t1*d0[(IX(i0,j1))]) + s1 * (t0 * d0[IX(i1,j0)] + t1*d0[IX(i1,j1)]);
        }
    }
    
    return;
}

void dens_step(float* x, float* x0, float* current_u, float* current_v, float diff, float dt){
    
    add_source(x, source, dt);
    
    memcpy(x0, x, (N+2)*(N+2)*sizeof(float));
    diffuse(x, x0, diff, dt);
    set_bnd(0, x);
    
    memcpy(x0, x, (N+2)*(N+2)*sizeof(float));
    advect(x, x0, current_u, current_v, dt);
    set_bnd(0, x);
    
    return;
}


void set_bnd(int b, float* x){
    
    for(int i=0; i<N+2;i++){
        
        if(b==0){
            x[IX(0,i)] = x[IX(1,i)];
            x[IX(N+1,i)] = x[IX(N,i)];
            x[IX(i,0)] = x[IX(i,1)];
            x[IX(i,N+1)] = x[IX(i,N)];
            
        }
        else if(b==1){ // horizontal
            
             x[IX(0,i)]= x[IX(1,i)];
            x[IX(N+1,i)] = -x[IX(N,i)];
            x[IX(i,0)]=  x[IX(i,1)];
            x[IX(i,N+1)] = x[IX(i,N)];
            
        }
        else if(b==2){ // vertical 
            
            
            
             x[IX(0,i)]= x[IX(1,i)];
            x[IX(N+1,i)] = x[IX(N,i)];
            x[IX(i,0)]=  x[IX(i,1)];
            x[IX(i,N+1)] = -x[IX(i,N)];
            
            
        }
        
    }
    
    if(b==1 || b==2){
       x[IX(0,0)]       = 0.5f*(x[IX(1,0)]   + x[IX(0,1)]);
x[IX(N+1,0)]     = 0.5f*(x[IX(N,0)]   + x[IX(N+1,1)]);
x[IX(0,N+1)]     = 0.5f*(x[IX(1,N+1)] + x[IX(0,N)]);
x[IX(N+1,N+1)]   = 0.5f*(x[IX(N,N+1)] + x[IX(N+1,N)]);
    }
   
    
   
    
    return;
}


void project(float* u, float* v, float* p, float* div){
    
    // step 1: compute divergence
    for(int j = 1; j <= N; j++){
        for(int i = 1; i <= N; i++){
            div[IX(i,j)] = -0.5f*(u[IX(i+1,j)]-u[IX(i-1,j)]+
                                   v[IX(i,j+1)]-v[IX(i,j-1)])/N;
            p[IX(i,j)] = 0;
        }
    }
    set_bnd(0, div);
    set_bnd(0, p);
    
    // step 2: solve poisson equation for pressure (gauss-seidel)
    for(int k = 0; k < 20; k++){
        for(int j = 1; j <= N; j++){
            for(int i = 1; i <= N; i++){
                p[IX(i,j)] = (div[IX(i,j)]+p[IX(i-1,j)]+p[IX(i+1,j)]+
                               p[IX(i,j-1)]+p[IX(i,j+1)])/4;
            }
        }
        set_bnd(0, p);
    }
    
    // step 3: subtract pressure gradient
    for(int j = 1; j <= N; j++){
        for(int i = 1; i <= N; i++){
            u[IX(i,j)] -= 0.5f*(p[IX(i+1,j)]-p[IX(i-1,j)])*N;
            v[IX(i,j)] -= 0.5f*(p[IX(i,j+1)]-p[IX(i,j-1)])*N;
        }
    }
    set_bnd(1, u);
    set_bnd(2, v);
}
