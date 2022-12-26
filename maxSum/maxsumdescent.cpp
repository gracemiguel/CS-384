/*******************************************************************************
 * Name        : maxsumdescent.cpp
 * Author      : Noah Ehrlich and Grace Miguel
 * Version     : 1.0
 * Date        :4/30/2021
 * Description : Dynamic programming solution to max sum descent problem.
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System. 
 ******************************************************************************/
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <cstring>
#include <bits/stdc++.h>

using namespace std;

const char DELIMITER = ' ';

int **values, // This is your 2D array of values, read from the file.
    **sums;   // This is your 2D array of partial sums, used in DP.

int num_rows; // num_rows tells you how many rows the 2D array has.
              // The first row has 1 column, the second row has 2 columns, and
              // so on...



/**
 * Displays the 2D array of values read from the file in the format of a table.
 */
void display_table() {
    // TODO
   
    for (int i =0; i<num_rows;i++){
        cout<<values[i][0];
        for(int j=0;j<i;j++){
            
            cout<<" "<< values[i][j];
        }
        cout<<"\n";
    }
}

/**
 * Returns the maximum sum possible in the triangle of values.
 * By starting at the top of the triangle and moving to adjacent numbers on the
 * row below, this function uses dynamic programming to build up another table
 * of partial sums.
 */
int compute_max_sum() {
    // TODO/
    sums[0]=values[0];
    int max_sum = 0; 
    for(int i =1;i<num_rows;i++){
        //first
        sums[i][0]=values[i][0]+sums[i-1][0];
        //last
        sums[i][i]=values[i][i]+sums[i-1][i-1];
        for(int j=1; j<i; j++){
            sums[i][j]=values[i][j]+max(sums[i-1][j], sums[i-1][j-1]);
        }
        
    }
        
    // Populate the 2D array of partial sums. It should still work even if
    // num_rows is 0 (i.e. the file was blank).

    // Loop over the last row to find the max sum.
   
    max_sum = max_element(sums[num_rows][0], sums[num_rows][num_rows]); 

    // Return the max sum.
    return max_sum;
}

/**
 * Returns a vector of ints with the values from the top to the bottom of the
 * triangle that comprise the maximum sum.
 */
vector<int> backtrack_solution() {
    vector<int> solution;
    // TODO
    //int max_sum = max_element(sums[num_rows][0], sums[num_rows][num_rows]); 
    int n = sizeof(sums)/sizeof(int);
    int indexOfMax = distance(sums, max_element(sums, sums+n)); 
    // auto itr = find(sums[num_rows],sizeof(sums[num_rows]),max_sum)
    // int indexOfMax = distance(sums[num_rows], itr);
    // solution.insert(solution.begin(), values[num_rows][indexOfMax]);
    int j=indexOfMax;
    for(int i=num_rows;i>0; i-- ){
        if(j == 0){     //all the way to left so look up
            solution.insert(solution.begin(), values[i][j]);
        }
        else if(j==i-1){ // all the way right so look left
            solution.insert(solution.begin(), values[i][j-1]);
            j=j-1;
        }
        else{
            if(sums[i][j]>sums[i][j-1]){//directly above
                solution.insert(solution.begin(),values[i][j]);
            }
            else{//moved from the left
                solution.insert(solution.begin(),values[i][j-1]);
                j=j-1;
            }
            
        }
    }
    solution.insert(solution.begin(),values[0][0]);
    return solution;
}

/**
 * Reads the contents of the file into the global 2D array 'values'. If
 * successful, the function also allocates memory for the 2D array 'sums'.
 */
bool load_values_from_file(const string &filename) {
    ifstream input_file(filename.c_str());
    if (!input_file) {
        cerr << "Error: Cannot open file '" << filename << "'." << endl;
        return false;
    }
    input_file.exceptions(ifstream::badbit);
    string line;
    vector<string> data;
    try {
        while (getline(input_file, line)) {
            data.push_back(line);
        }
        input_file.close();
    } catch (const ifstream::failure &f) {
        cerr << "Error: An I/O error occurred reading '" << filename << "'.";
        return false;
    }
    

    // TODO
    num_rows=data.size();
    values = new int* [num_rows];
    sums= new int* [num_rows];
    for(int i = 0; i< num_rows; i++){
        vector<int> nums;
        stringstream ss(data[i]);
        string word;
        while(ss>>word){
            nums.push_back(stoi(word));     //stoi converts string to int
        }  
        values[i] = &nums[0];
        sums[i]= new int [i+1];      
    }


    // num_rows=data.size();
    // values = new int* [num_rows];
    // sums= new int* [num_rows];
    // for(int i = 0; i< num_rows; i++){
    //     string line = data[i];
    //     int n = line.length();
    //     char char_array[n+1];
    //     vector<int> nums;
        
    //     strcpy(char_array, line.c_str());
    //     char *token = strtok(char_array, " ");
    //     while(token != NULL){
    //         nums.push_back((int)token);
    //     }
    //      //parse the line
    //     values[i] = &nums[0];
    //     sums[i]= new int [i+1];

    // }
    return true;
}

/**
 * Frees up the memory allocated for the 2D array of values and the 2D array of
 * partial sums.
 */
void cleanup() {
    // TODO
    for(int i = 0; i<num_rows;i++){
        delete [] values[i];
        delete [] sums[i];
        
    }
    delete[] values;
    delete[] sums;

}

int main(int argc, char * const argv[]) {
    if (argc != 2) {
        cerr << "Usage: " << argv[0] << " <filename>" << endl;
        return 1;
    }
    string filename(argv[1]);
    if (!load_values_from_file(filename)) {
        return 1;
    }
    // TODO
    if(num_rows==0){
        cout<<"Max sum: 0"<<endl;
        cout<<"Values: []"<<endl;
        return 0;
    }
    
    display_table();
    cout<<"Max sum: "<< compute_max_sum() <<endl;
    vector<int> solution = backtrack_solution();
    cout<<"Values: ["<<solution[0];
    for(int i=1; i<(int)solution.size(); i++){
        cout<< ", " << solution[i] ;
    }
    cout<<"]"<<endl;
    cleanup();
    return 0;
}
