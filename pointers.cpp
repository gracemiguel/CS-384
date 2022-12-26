
#include <iostream>
#include <sstream>
using namespace std;

void display_array(int array[], const int length){
    cout << "[";
    if(length>=1){
        cout << array[0]; 
    }
    for(int i=0; i< length; i++){
        cout << ", " << array[i];
    }
}

void display_array_ptr(int array[], const int length){
    cout << "["; 
    if(length>=1){
        cout << *array;
    }
}
void pass_by_pointer(int *x){
    *x=10;
}

void pass_by_value(int x){
    x =10;
}

void pass_by_reference(int &x){ // use this to read objects
    x=10; 
}
