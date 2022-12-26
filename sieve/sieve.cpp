/*******************************************************************************
 * Name        : sieve.cpp
 * Author      : Noah Ehrlich and Grace Miguel
 * Date        : 2/19/2021
 * Description : Sieve of Eratosthenes
 * Pledge      : I pledge my honor that I have abided by the stevens honor system. 
 ******************************************************************************/
#include <cmath>
#include <iomanip>
#include <iostream>
#include <sstream>

using namespace std;

class PrimesSieve {
public:
    PrimesSieve(int limit);

    ~PrimesSieve() {
        delete [] is_prime_;
    }

    int num_primes() const {
        return num_primes_;
    }

    void display_primes() const;

private:
    // Instance variables
    bool * const is_prime_;
    const int limit_;
    int num_primes_, max_prime_;

    // Method declarations
    int count_num_primes() const;
    void sieve();
    static int num_digits(int num);
};

PrimesSieve::PrimesSieve(int limit) :
        is_prime_{new bool[limit + 1]}, limit_{limit} {
    sieve();
}

void PrimesSieve::display_primes() const {
    // TODO: write code to display the primes in the format specified in the
    // requirements document.
    cout<< endl << "Number of primes found: "<< num_primes_ <<endl;
    cout<< "Primes up to "<< limit_<<":" <<endl;
    //max prime calculation
   
    const int max_prime_width = num_digits(max_prime_),
    primes_per_row = 80 / (max_prime_width + 1);
    //if numbers can fit on one line do this
    if(num_primes_ <= primes_per_row){
        for(int i=2; i<=limit_; i++){
            if(is_prime_[i]==true){
                if(i == max_prime_){
                    cout << i << endl;
                }
                else{
                    cout << i << " "; 
                }
            }
        }
    }
        //if numbers go onto next line
        else{
            int count = 1;
            //reset the count at the beginning of each new line
            int new_line = 1;
            for(int k=2; k<=limit_; k++){
                if(is_prime_[k]==true){
                    if(count >=primes_per_row){
                        cout <<setw(max_prime_width) << k << endl;
                        count = new_line; 
                    }
                else{
                    if(k == max_prime_){
                        cout <<setw(max_prime_width) << k;
                        count++;
                    }
                    else{
                        cout << setw(max_prime_width) << k << " "; 
                        count++;
                    }
                }
                }
            }
        }
    }
    



int PrimesSieve::count_num_primes() const {
    // TODO: write code to count the number of primes found
    int num=0;
    for(int i=2;i<=limit_; i++){
        if(is_prime_[i]==true){
            num++;
        }
    }
    return num;
}

void PrimesSieve::sieve() {
    // TODO: write sieve algorithm
    is_prime_[0] = false;
    is_prime_[1] = false; 
    for(int i=2; i<=limit_; i++){//sets everything to true
        is_prime_[i]=true;
    }

    for(int i=2; i<=floor(sqrt(limit_)); i++){ //floor rounds a decimal down to an int, essentially truncates
        if(is_prime_[i]==true){
            for(int j=i*i;j<=limit_;j+=i){
                is_prime_[j]=false;
            }
        }
    }
    num_primes_ = count_num_primes();
   
    for(int i = 2; i <= limit_; i++){
        if(is_prime_[i]==true){
            max_prime_ = i;
        }
    } 

}

int PrimesSieve::num_digits(int num) {
    // TODO: write code to determine how many digits are in an integer
    // Hint: No strings are needed. Keep dividing by 10.
    int count = 0;
    while(num!=0){
        num = num/10; 
        count++;
    }
    return count; 
    }

int main() {
    cout << "**************************** " <<  "Sieve of Eratosthenes" <<
            " ****************************" << endl;
    cout << "Search for primes up to: ";
    string limit_str;
    cin >> limit_str;
    int limit;

    // Use stringstream for conversion. Don't forget to #include <sstream>
    istringstream iss(limit_str);

    // Check for error.
    if ( !(iss >> limit) ) {
        cerr << "Error: Input is not an integer." << endl;
        return 1;
    }
    if (limit < 2) {
        cerr << "Error: Input must be an integer >= 2." << endl;
        return 1;
    }

    // TODO: write code that uses your class to produce the desired output.

    PrimesSieve prime(limit);
    prime.display_primes();

    /* using the heap rather than stack, pointer
    PrimesSieve * prime = new PrimesSieve(limit);
    prime->display_primes();
    delete prime;
    */

    return 0;
}
