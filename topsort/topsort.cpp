#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

vector<int> toposort(vector<int> graph[], const size_t size){
    int *indegree = new int[size]; //making it on the heap
    //Fill all the elements with 0 except for index 0, which is not used.
    fill(indegree+1, indegree + size, 0);

    //Determine the indegree of each vertex
    for(size_t row = 1; row < size; row++){
        for(size_t col = 0; col<graph[row].size(); col++){
            indegree[graph[row][col]]++; 
        }
    }
    //Declare a min heap priority queue.
    priority_queue<int, vector<int>, greater<int>> q;
    for(size_t i =1; i<size; i++){
        if(indegree[i]==0){
            q.push(i);
        }
    }
    //Perform the core algorithm
    vector<int> order;
    while(!q.empty()){
        int vertex = q.top();
        q.pop();
        order.push_back(vertex) ;    //this is the output
        for(int adjacent: graph[vertex]){       //decrement all vertices that are connected to the one that was popped
            indegree[adjacent]--;
            if(indegree[adjacent]==0){
                q.push(adjacent);           //check to see if indegree is 0, if yes, push to queue
            }
        }


    }
    //Look for a cycle
    if(order.size() !=size -1){
        order.clear();

    }
    delete [] indegree; //clear the heap
    return order;
}

int main(){
    ios::sync_with_stdio(false); 
    cin.tie(NULL);
    int n, m;
    cin>> n >> m;

    //make an adjacency list in a simple, straightforward manner
    vector<int> *graph = new vector<int>[n+1];
    while(m--){
        int x, y;
        cin >>x >> y;
        graph[x].push_back(y);
    }
    vector<int> order = toposort(graph, n+1);
    if(order.size() >0){
        for(int vertex: order){
            cout << vertex << " "; //trailing space is ok for this problem.
        }

    }
    else{
        cout << "Sandro fails.";
    }
    cout <<endl;
    delete [] graph; 

    return 0;
}