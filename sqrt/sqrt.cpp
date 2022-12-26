/**
 * * Name: sqrt.cpp
 * * Author: Grace Miguel
 * * Version: 1.0
 * * Date: February 8, 2021
 * * Description: Takes the square root of a number.
 * * Pledge: I pledge my honor that I have abided by the Stevens Honor System.
 */

#include <iostream>
#include <sstream>
#include <iomanip>
#include <limits>

using namespace std;

double sqrt(double num, double epsilon = 1e-7){
    if(num == 0 || num == 1){
        return num;
    }
    if(num<0){
        return numeric_limits<double>::quiet_NaN();
    }
    
    double nextGuess = 0;
    double lastGuess = abs(num);
    double diff = lastGuess - nextGuess;
    while(diff > epsilon){
        double n = num;
        nextGuess = 0.5 * (lastGuess + (n/lastGuess));
        diff = abs(lastGuess - nextGuess);
        lastGuess = nextGuess;
        
        
    }
    return lastGuess;

}

int main (int argc, char* const argv[]){
    
    double a, b;
    istringstream iss;
    
    if(argc<2|| argc> 3){
        cerr << "Usage: " << argv[0] << " <value> [epsilon]" << endl;
        return 1;
    }
    
    iss.str(argv[1]);
    if(!(iss >> a)){
        cerr << "Error: Value argument must be a double." << endl;
        return 1;
    }
    iss.clear();
    if(argc == 3){
        iss.str(argv[2]);
        if(!(iss >> b )|| b<=0 ){
            cerr << "Error: Epsilon argument must be a positive double." << endl;
            return 1;
        }
    
    }

    cout << fixed;
    cout << setprecision(8);
    cout << sqrt(a,b) << endl;
    return 0;



}