/**
 * * Name: mypoint
 * * Author: Grace Miguel
 * * Version: 1.0
 * * Description:
 * * Pledge: I pledge my honor that I have abided by the Stevens Honor System.
 */

// /n is a new line
#include <iostream>
#include <iomanip>
#include <vector>

using namespace std; 

class MyPoint{
public: 
    //Constructor that uses an intializer list.
    MyPoint(int x, int y, float z): x_{x}, y_{y}, z_{z} {}   //the var_{var} initializes the variable before you open the constructor
    //Methods that do not modify member variables should be declared const.
    void print_coords() const {
        cout << "(x,y,z) = (" << x_ << ", " << fixed    
             << setprecision(2) << z_ << ")" << endl; 
    }

    //Mutator
    void set_x(int x){
        x_=x;
    }
    //Accessor
    int get_x() const{
        return x_;

    }
private: 
    //Member variables(fields). Use the trailing _ for these variables.
    //better at encapsulation
    int x_, y_; 
    float z_;
}; //must close class with a semicolon

void display_points(const vector<MyPoint> &points){ //refer to the pointers by reference, don't want to make copies
 for(auto it = points.cbegin(); it !=points.cend(); ++it){
     it-> print_coords(); 
 }   // it is the name of the iterator   
}
int main(){
    MyPoint point1(5,7,1.9823412); //this is instantiated on the stack
    MyPoint point2(1,2,3); 
    MyPoint point3(4,5,6); 

    vector<MyPoint> points; 
    points.push_back(point1); 
    points.push_back(point2); 
    points.push_back(point3); 

    vector<MyPoint> points_above_two; //this is making a copy of each point
    for( const auto &point : points){
        if(point.get_x() >2){
            points_above_two.push_back(point);
        }
    }
    display_points(points_above_two);

    int x,y; 
    cout << "Input x: ";
    cin >> x; 
    cout << "Input y: ";
    MyPoint *some_point = new MyPoint(x,y,7.00); //this is on the heap
    some_point->print_coords(); 
    delete some_point;
    return 0;
}