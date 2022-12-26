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
#include <stack>
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

    bool is_equal(State* check){
        if(check->a==a && check->b == b && check->c == c){
            return true;
        }
        else{
            return false;
        }
    }

};


//print the solution
void printSol( State* finish){
   
    stack<State*> q;
    State* temp = finish;
    
    while(temp!=nullptr){
        //cout<<temp->a<<endl;
        q.push(temp);
        temp=temp->parent;
    }
    
    while(!(q.empty())){
        temp=q.top();
        cout<<temp->directions<<" "<<temp->to_string()<<endl;
        q.pop();
    }
}

void bfs(int a, int b, int c, State* goal, State* initial){
    queue<State*> q;
    q.push(initial);

    // Declare a 2-dimensional array with 'some_size' rows.
    bool **array = new bool*[a+1];

    // For each row, make an array of 'some_other_size' booleans.
    for (int i = 0; i < a+1; ++i) {
        array[i] = new bool[b+1];
        // Fill the array with zeros.
        fill(array[i], array[i] + b+1, false);
    }
    

    while(!(q.empty())){
        State* temp = q.front();
        q.pop();
        //cout<<"here"<<endl;
       
        if(temp->is_equal(goal)){
            //cout<<"here 2"<<endl;
            printSol(temp); 
            return;
        }
        else if(array[temp->a][temp->b]){
            continue;
        }
        array[temp->a][temp->b]=true;
        //vector< State> pours = pour(&temp,a,b,c);
        State* value = temp;
        vector<State> output;
        //go step by step in order for the pours
        
            if(value->a <a && value->c>0){
                int curra=value->a;
                int currc=value->c;
                if((a-curra)<=currc){
                    curra=a;
                    currc=(currc-(a-value->a));

                }
                else{
                    curra=curra+currc;
                    currc=0;

                }
                if(curra-value->a == 1){
                    string directions = "Pour " + to_string(curra-value->a) + " gallon from C to A.";
                    State* obj = new State(curra, value->b, currc, directions); 
                    obj->parent=value;
                    q.push(obj);
                }
                else{
                    string directions = "Pour " + to_string(curra-value->a) + " gallons from C to A."; 
                    State* obj = new State(curra, value->b, currc, directions); 
                    obj->parent=value;
                    q.push(obj);
                    }
            }
            if(value->a <a && value->b>0){
                int curra=value->a;
                int currb=value->b;
                if((a-curra)<=currb){
                    curra=a;
                    currb=(currb-(a-value->a));

                }
                else{
                    curra=curra+currb;
                    currb=0;

                }
                if(curra-value->a ==1){
                    string directions = "Pour " + to_string(curra-value->a) + " gallon from B to A.";
                     State* obj = new State (curra, currb, value->c, directions);  
                    obj->parent = value; 
                    q.push(obj); 
                    
                }
                else{
                    string directions = "Pour " + to_string(curra-value->a) + " gallons from B to A."; 
                    State* obj = new State (curra, currb, value->c, directions);  
                    obj->parent = value; 
                    q.push(obj); 
                    
                }
                
               
           
            }
            if(value->b <b && value->c>0){
                int currc=value->c;
                int currb=value->b;
                if((b-currb)<=currc){
                    currb=b;
                    currc=(currc-(b-value->b));

                }
                else{
                    currb=currb+currc;
                    currc=0;

                }
                if(currb-value->b == 1){
                    string directions = "Pour " + to_string(currb-value->b) + " gallon from C to B."; 
                    State* obj = new State(value->a, currb, currc, directions);
                    obj->parent = value;
                    q.push(obj); 
                }
                else{
                    string directions = "Pour " + to_string(currb-value->b) + " gallons from C to B."; 
                    State* obj = new State(value->a, currb, currc, directions);
                    obj->parent = value;
                    q.push(obj); 
                }
                    
            }
            if(value->b <b && value->a>0){
                int curra=value->a;
                int currb=value->b;
                if((b-currb)<=curra){
                    currb=b;
                    curra=(curra-(b-value->b));

                }
                else{
                    currb=currb+curra;
                    curra=0;

                }
                if(currb-value->b ==1 ){
                    string directions= "Pour " + to_string(currb-value->b) + " gallon from A to B."; 
                    State* obj = new State(curra, currb, value->c, directions);
                    obj->parent = value;
                    q.push(obj); 
                }
                else{
                    string directions= "Pour " + to_string(currb-value->b) + " gallons from A to B."; 
                    State* obj = new State(curra, currb, value->c, directions);
                    obj->parent = value;
                    q.push(obj); 
                }
                    
            }
            if(value->c <c && value->b>0){
                int currc=value->c;
                int currb=value->b;
                if((c-currc)<=currb){
                    currc=c;
                    currb=(currb-(c-value->c));

                }
                else{
                    currc=currc+currb;
                    currb=0;

                }
                if(currc-value->c ==1 ){
                    string directions = "Pour " + to_string(currc-value->c) + " gallon from B to C."; 
                    State* obj = new State (value->a, currb, currc, directions);
                    obj->parent = value;
                    q.push(obj);                     
                }
                else{
                    string directions = "Pour " + to_string(currc-value->c) + " gallons from B to C."; 
                    State* obj = new State (value->a, currb, currc, directions);
                    obj->parent = value;
                    q.push(obj);
                } 
                    
                
            }
            if(value->c <c && value->a>0){
                int currc=value->c;
                int curra=value->a;
                if((c-currc)<=curra){
                    currc=c;
                    curra=(curra-(c-value->c));

                }
                else{
                    currc=currc+curra;
                    curra=0;

                }
                if(currc-value->c ==1 ){
                    string directions = "Pour " + to_string(currc-value->c) + " gallon from A to C.";
                    State* obj = new State(curra, value->b, currc, directions);
                    obj->parent = value;
                    q.push(obj);                   
                }
                else{
                    string directions = "Pour " + to_string(currc-value->c) + " gallons from A to C.";
                    State* obj = new State(curra, value->b, currc, directions);
                    obj->parent = value;
                    q.push(obj); 
                }
            }

       
        

    }
    cout<<"No solution."<<endl;
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
State initial = {0,0,jugs[2],"Initial state."};
State goal = {jugs[3],jugs[4],jugs[5],"goal"};
bfs(jugs[0],jugs[1],jugs[2], &goal, &initial);
return 1;
}



