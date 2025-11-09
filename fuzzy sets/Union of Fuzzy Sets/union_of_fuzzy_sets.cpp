#include <iostream>
using namespace std;
int main(){
float A[4][2] = {{2,1},{4,0.3},{6,0.5},{8,0.2}};
float B[4][2] = {{2,0.5},{4,0.4},{6,0.1},{8,1}};

float Union[4][2];

for(int i =0;i<4;i++){
    for(int j=0;j<2;j++){
        Union[i][j] =max((A[i][j]),(B[i][j]));
    }
}

for(int i=0;i<4;i++){
    cout<<"{ ";
    for(int j=0;j<2;j++){
         cout<<Union[i][j]<<"  ";
    }
    
    cout<<"}  ";
   
}
return 0;
}