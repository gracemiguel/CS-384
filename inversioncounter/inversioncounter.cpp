/*******************************************************************************
 * Name        : inversioncounter.cpp
 * Author      :Noah Ehrlich and Grace Miguel
 * Version     : 1.0
 * Date        :
 * Description : Counts the number of inversions in an array.
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <iostream>
#include <algorithm>
#include <sstream>
#include <vector>
#include <cstdio>
#include <cctype>
#include <cstring>

using namespace std;

// Function prototype.
//static long mergesort(int array[], int scratch[], int low, int high);

/**
 * Counts the number of inversions in an array in theta(n^2) time.
 */
long count_inversions_slow(int array[], int length) {
    // TODO
    long count=0;
    for(int i=0;i<length; i++){
        for(int j=i+1;j<length;j++){
            if(array[i]>array[j]){
                count++;
            }
        }
    }
    return count;
}




static long mergesort(int array[], int scratch[], int low, int high) {      //low is first index and high is last index
    if(low==high){
        return 0;
    } 
     long count = 0;
    int middle = low+ (high-low)/2; 
    count = count + mergesort(array,scratch, low, middle); 
    count = count + mergesort(array, scratch, middle+1, high);
    int i =low;
    int k= low;
    int j = middle+1;
    for(k=low; k<=high; k++){
        if(i<= middle && (j> high || array[i] <= array[j])){
            scratch[k] = array[i];
            i+=1; 
        }
        else{
            scratch[k] = array[j];
            count = count+middle-i+1; 
            j+=1;
        }
    }
    for(k=low; k<=high; k++){
        array[k] = scratch[k];
    }
    
    return count; 
}

/**
 * Counts the number of inversions in an array in theta(n lg n) time.
 */
long count_inversions_fast(int array[], int length) {
    int *scratch = new int [length] ;
    long count =mergesort(array,scratch,0,length-1);
    delete []scratch;
    return count;
}

int main(int argc, char *argv[]) {
    

    if(argc>2){
        cerr<<"Usage: ./inversioncounter [slow]"<<endl;
        return 1;
    }
    else if(argc==2 && strcmp(argv[1],"slow")!=0 ){
        cerr << "Error: Unrecognized option '" << argv[1] << "'." << endl;
        return 1;
    }

    cout << "Enter sequence of integers, each followed by a space: " << flush;
    
    istringstream iss;
    int value, index = 0;
    vector<int> values;
    string str;
    str.reserve(11);
    char c;
    while (true) {
        c = getchar();
        const bool eoln = c == '\r' || c == '\n';
        if (isspace(c) || eoln) {
            if (str.length() > 0) {
                iss.str(str);
                if (iss >> value) {
                    values.push_back(value);
                } else {
                    cerr << "Error: Non-integer value '" << str
                         << "' received at index " << index << "." << endl;
                    return 1;
                }
                iss.clear();
                ++index;
            }
            if (eoln) {
                break;
            }
            str.clear();
        } else {
            str += c;
        }
    }

    if(values.empty()){
        cerr<<"Error: Sequence of integers not received."<<endl;
        return 1;
    }

    
    if(argc ==2){
        cout << "Number of inversions: " <<count_inversions_slow(&values[0],values.size()) <<endl;        
    }
    else{
        cout<< "Number of inversions: " << count_inversions_fast(&values[0],values.size())<<endl;
    }

    return 0;
}
