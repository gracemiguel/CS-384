/*******************************************************************************
 * Name        : stairclimber.cpp
 * Author      : Noah Ehrlich and Grace Miguel
 * Date        : 3/8/2021
 * Description : Lists the number of ways to climb n stairs.
 * Pledge      : I pledge my honor that I have abided by the stevens honor system. 
 ******************************************************************************/
#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>
#include <iomanip>

using namespace std;

vector< vector<int> > get_ways(int num_stairs) {
    // TODO: Return a vector of vectors of ints representing
    // the different combinations of ways to climb num_stairs
    // stairs, moving up either 1, 2, or 3 stairs at a time.
    vector<vector<int>> ways;
    if(num_stairs<=0){
        return{{}};
    }
    for(int i=1;i<4;i++){
        if(num_stairs>=i){
            vector<vector<int>> result;
            result = get_ways(num_stairs-i);
            for(int j=0;j<(int)result.size();j++){
                result[j].insert(result[j].begin(), i );
            }
            ways.insert(ways.end(), result.begin(), result.end());

        }
    }
    return ways;
}
int num_digits(int num) {
    // TODO: write code to determine how many digits are in an integer
    // Hint: No strings are needed. Keep dividing by 10.
    int digits=1;
    // if(num<=9){
    //     return 1;
    // }
    while(num >= 9){
        digits++;
        num = num / 10;
    }
    return digits;
}

void display_ways(const vector< vector<int> > &ways) {    
    // TODO: Display the ways to climb stairs by iterating over
    // the vector of vectors and printing each combination.
    for(int i=0; i<(int)ways.size(); i++){
        cout<<right<<setw(num_digits((int)ways.size()));
        cout << i+1 << ". "; 
        cout << "[";
        for(int j=0; j<(int)ways[i].size(); j++){
            if(j == (int)ways[i].size()-1){
                cout << ways[i][j]; 
            }
            else{
            cout << ways[i][j] << ", " ;
            } 
        }
        cout << "]" << endl;
    }
    
}

int main(int argc, char * const argv[]) {
    istringstream iss;

    if((argc!=2)){
        cout<<"Usage: ./stairclimber <number of stairs>"<<endl;
        return 0;
    }
    iss.str(argv[1]);
    int num_stairs;
    if(!(iss>>num_stairs)){
        cout<<"Error: Number of stairs must be a positive integer."<<endl;
        return 0;
    }
    if(num_stairs<=0){
        cout<<"Error: Number of stairs must be a positive integer."<<endl;
        return 0;
    }
    if(num_stairs==1){
        cout<<"1 way to climb 1 stair."<<endl;
        cout<<"1. [1]"<<endl;
        return 1;
    }
    else{
        vector< vector<int> > ways=get_ways(num_stairs);
        cout<<ways.size()<<" ways to climb "<<num_stairs<<" stairs."<<endl;
        display_ways(ways);
        return 1;
    }
}
