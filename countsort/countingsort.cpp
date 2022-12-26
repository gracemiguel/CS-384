#include <algorithm>
#include<bits/stdc++.h>

using namespace std; 

vector<int>countingSort(vector<int> & arr){
    int max =0;
    for(auto val: arr){
        if(val>max){
            max = val;
        }
    }
    int *counts = new int[max+1];
    fill(counts, counts+max+1,0);
    for(auto val: arr){
        counts[val]++;
    }
    for(int i=0, j=0; i<=max; ){
        if(counts[i]!=0){
            arr[j++] =i;
        }
        else{
            i++;
        }
    }
    delete [] counts;
    return arr;
}