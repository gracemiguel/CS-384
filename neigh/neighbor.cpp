#include <iostream>
#include <string>
#include <limits>
#include <cmath>

using namespace std;

struct Neighbor{
    float x,y;
    string name; 
};

float distance(float x1, float x2, float y1, float y2){
    float x_diff = x2-x1;
    float y_diff = y2-y1; 
    return sqrt(x_diff*x_diff + y_diff* y_diff);
}

Neighbor* nearest_neighbors(Neighbor neighbors[], const int length){
    //runtime O(n^2)
    float min_distance = __FLT_MAX__; 
    int n_ind[2];
    for(int i=0; i<length-1; i++){
        for(int j=i+1; j<length; j++){
            float cur_dist = distance(neighbors[i].x, neighbors[i].y, neighbors[j].x, neighbors[j].y);
            if(cur_dist < min_distance){
                min_distance = cur_dist;
                n_ind[0]= i;
                n_ind[1] = j; 

            }
        }
    }
    //the star is a pointer to what is being returned
    Neighbor *result = new Neighbor[2];
    result[0] = neighbors[n_ind[0]];
    result[1] = neighbors[n_ind[1]];
    return result;
}

int main(){
    Neighbor neighbors[3];
    neighbors[0].x = 1;
    neighbors[0].y = 2; 
    neighbors[0].name = "John";
    
    neighbors[1].x = 10;
    neighbors[2].y = 20; 
    neighbors[1].name = "Jane";
    
    neighbors[2].x =2; 
    neighbors[2].y = 4; 
    neighbors[2].name = "Mary";

    Neighbor *nearest = nearest_neighbors(neighbors, 3); 
    cout <<nearest[0].name << ", " << nearest[1].name <<endl;

    delete [] nearest; 
}