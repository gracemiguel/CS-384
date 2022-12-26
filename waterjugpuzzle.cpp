/*******************************************************************************
 * Name        : waterjugpuzzle.cpp
 * Author      : Noah Ehrlich and Grace Miguel
 * Date        : 3/19/2021
 * Description : Computes solution to water jug problem
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System. 
 ******************************************************************************/

#include <iostream>
#include <sstream>
#include <vector>
#include <queue>

using namespace std; 
// Struct to represent state of water in the jugs.
struct State {    
    int a, b, c;    
    string directions;    
    State *parent;
    State(int _a, int _b, int _c, string _directions) :         
    a{_a}, b{_b}, c{_c}, directions{_directions}, parent{nullptr} {} 

    // String representation of state in tuple form.
    string to_string() {        
        ostringstream oss;        
        oss << "(" << a << ", " << b << ", " << c << ")";        
        return oss.str();    
        }

    bool is_equal(State check){
        if(check.a==a && check.b == b && check.c == c){
            return true;
        }
        else{
            return false;
        }
    }

}


vector<struct State> pour(*State value, int a, int b, int c){
   vector<State> output;
     //go step by step in order for the pours
     for(int i=0; i< (int)output.size(); i++ ){
       if(value->a < a && value->c >0 ){
           string directions = "Pour " + string(&value.c) + " gallons from C to A"; 
           struct State obj= {&value.a + &value.c, &value.b, &value.c-&value.a, directions}; 
           obj.parent=value;
           output.push_back(*obj);
       }
       else if(&value.a+&value.b < a){
           string directions = "Pour " + string(&value.b) + " gallons from B to A"; 
           struct State obj = {&value.a+&value.b, &value.b-&value.a, &value.c, directions};  
           obj.parent = value; 
           output.push_back(*obj); 
           
       }
       else if(&value.c+&value.b < b){
           string directions = "Pour " + string(&value.c) + " gallons from C to B"; 
           struct State obj = {&value.a; &value.b+ &value.c; &value.c-&value.b, directions};
           obj.parent = value;
           output.push_back(*obj); 
            
       }
       else if(&value.a + &value.b < b){
            string directions+= "Pour " + string(&value.b) + " gallons from A to B"; 
            struct State obj = {&value.a-&value.b; &value.b+ &value.a; &value.c, directions};
            obj.parent = value;
            output.push_back(*obj); 
            
       }
       else if(&value.b+ &value.c < c){
           string directions = "Pour " + string(&value.c) + " gallons from B to C"; 
           struct State obj = {&value.a; &value.b - &value.c; &value.c+&value.b, directions};
           obj.parent = value;
           output.push_back(*obj); 
            
         
       }
       else if(&value.a+ &value.c < c){
           string directions = "Pour " + string(&value.c) + " gallons from A to C";
            struct State obj = {&value.a-&value.c; &value.b; &value.c+&value.b, directions};
           obj.parent = value;
           output.push_back(*obj); 
       }
     }
       return output; 
   }

 

string printSol( *State finish){
    queue<struct State> q;
    struct State temp = &finish;
    while(temp.parent!=nullptr){
        q.push(temp);
        temp=&temp.parent
    }
    for(auto i=0; i<q.size();i++){
        temp=q.front;
        cout<<temp.directions<<" "<<temp.to_string<<endl;
        q.pop;
    }
}

void bfs(int a, int b, int c, *State goal, *State initial){
    queue<struct *State> q;
    q.push(initial);

    // Declare a 2-dimensional array with 'some_size' rows.
    bool **array = new bool*[a];

    // For each row, make an array of 'some_other_size' booleans.
    for (int i = 0; i < a; ++i) {
    array[i] = new bool[sb];
    // Fill the array with zeros.
    fill(array[i], array[i] + b, false);
    }
    

    while(!(q.empty)){
        struct *State temp = q.front;
        q.pop;
       
        if(temp->is_equal(goal)){
            printSol(temp);
        }
        else if(array[temp->a][temp->b]){
            continue;
        }
        array[temp->a][temp->b]=true;
        vector<struct State> pours = pour(temp,a,b,c);
        for(auto i=0;i<(int)pours.size();i++ ){
            q.push(*pours[i]);
        }
        

    }
    cout<<"No Solution"<<endl;
    // Delete each array, that is, all the columns, first.
    for (int i = 0; i < a; ++i) {
    delete [] array[i];
}
    // Delete the array itself.
    delete [] array;
    
}

vector<int> inputs(int argc, char * const argv[]){
    istringstream iss;
    
    int capA, capB, capC, goalA, goalB, goalC;
    iss.str(argv[1]);
    if(!(iss>>capA)|| capA<1){
        cout << "Error: Invalid capacity '"<<iss.str()<<"' for jug A."<<endl;
        return {};
}
    iss.clear();
    iss.str(argv[2]);
    if(!(iss>>capB)||capB<1){
        cout << "Error: Invalid capacity '"<<iss.str()<<"' for jug B."<<endl;
        return {};
}
    iss.clear();
    iss.str(argv[3]); 
    if(!(iss>>capC)||capC<1){
        cout << "Error: Invalid capacity '" << iss.str()<< "' for jug C." << endl;
        return {};
    }
    iss.clear();
    iss.str(argv[4]);
    if(!(iss>>goalA)|| goalA<0){
        cout << "Error: Invalid goal '"<<iss.str()<<"' for jug A."<<endl;
        return {};
}
    iss.clear();
    iss.str(argv[5]);
    if(!(iss>>goalB)||goalB<0){
        cout << "Error: Invalid goal '"<<iss.str()<<"' for jug B."<<endl;
        return {};
}
    iss.clear();
    iss.str(argv[6]);
    if(!(iss>>goalC)||goalC<0){
        cout << "Error: Invalid goal '"<<iss.str()<<"' for jug C."<<endl;
        return {};
}
    if( goalA > capA){
        cout << "Error: Goal cannot exceed capacity of jug A." << endl;
        return {};
}
    if( goalB > capB){
        cout << "Error: Goal cannot exceed capacity of jug B." << endl;
        return {};
    }
    if( goalC > capC){
        cout << "Error: Goal cannot exceed capacity of jug C." << endl;
        return {};
    }

    if(capC!=(goalA+goalB+goalC)){
        cout<<"Error: Total gallons in goal state must be equal to the capacity of jug C."<<endl;
        return {};
    }
    vector<int> jugs{capA, capB, capC, goalA, goalB, goalC};
    return jugs;

}
int main(int argc, char * const argv[]) {
if (argc!=7){
    cout<<"Usage: ./waterjugpuzzle <cap A> <cap B> <cap C> <goal A> <goal B> <goal C>"<<endl;
    return 0;
}
//int capA, capB, capC, goalA, goalB, goalC;
vector<int> jugs = inputs(argc,argv);
if(jugs.empty()){
  return 0;
}
struct State initial = {0,0,jugs[2],"Initial state."};
struct State goal = {jugs[3],jugs[4],jugs[5],"goal"};
bfs(jugs[0],jugs[1],jugs[2],&goal,&initial);

  
}



