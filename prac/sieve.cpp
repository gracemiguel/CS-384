/*******************************************************************************
 * Name    : sieve.cpp
 * Author  : Zenya Koprowski
 * Version : 1.0
 * Date    : February 11, 2020
 * Description : Computes the GCD of two command-line arguments.
 * Pledge : I pledge my honor that I have abided by the Stevens Honor System.
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

    inline int num_primes() const {
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
    cout << endl << "Number of primes found: " << num_primes_ << endl;
    cout << "Primes up to " << limit_ << ":" << endl;
    //Below is the calculation for the max prime number, whcih we later use in the max_prime_width functoin
    int max_prime_ = 0;
    for (int i = 2; i <= limit_; i++) {
        if (is_prime_[i] == true) {
            max_prime_ = i;
        }
    }
    //function to tell us the max_prime_width of a printing cell
    //This is needed if the code prints out more than one line of code, otherwise all the numbers fit on one
    //  line with just a space in between
    const int max_prime_width = num_digits(max_prime_), primes_per_row = 80 / (max_prime_width + 1);
    //case if the numbers can all fit on one line
    if (num_primes_ <= primes_per_row) {
        for (int i = 2; i <= limit_; i++) {
            if (is_prime_[i] == true) {
                if(i == max_prime_) {
                    cout << i << endl;
                } else {
                    cout << i << " ";
                }
            }
        }
    //case if the numbers spill onto the next line
    } else {
        int counter = 1;
        // need a reset so that the counter can restart at the beginning of each new line
        int reset = 1;
        for (int i = 2; i <= limit_; i++) {
            if (is_prime_[i] == true) {
                if (counter >= primes_per_row) {
                    cout << setw(max_prime_width) << i << endl;
                    counter = reset;
                } else {
                    if ( i == max_prime_) {
                        cout << setw(max_prime_width) << i;
                        counter++;
                    } else {
                        cout << setw(max_prime_width) << i << " ";
                        counter++;
                    }
                }
            }
        }
    }
}


int PrimesSieve::count_num_primes() const {
    // TODO: write code to count the number of primes found
    //simple for statement that will find all the true's and increase the counter
    int counter = 0;
    for(int i = 2; i <= limit_; i++) {
        if(is_prime_[i] == true){
            counter = counter + 1;
        }
    }
    return counter;
}

void PrimesSieve::sieve() {
    // TODO: write sieve algorithm
    // This function marks all the indexes in the list as true if they are a prime
    is_prime_[0] = false;
    is_prime_[1] = false;
    //sets all the indexes equal to true except 0 and 1 which are primes
    for( int i = 2; i <= limit_; i++) {
        is_prime_[i] = true;
    }
    //Used the formula given to determine if an index was prime or not
    for(int i = 2; i <= floor(sqrt(limit_)); i++){
        if (is_prime_[i] == true) {
            for (int j = i*i; j <= limit_; j+=i) {
                is_prime_[j] = false;
            }
        }
    }
    num_primes_ = count_num_primes();
}

int PrimesSieve::num_digits(int num) {
    // TODO: write code to determine how many digits are in an integer
    // Hint: No strings are needed. Keep dividing by 10.
    // Counts how many spaces are in the int num; ex: num_digits(500) = 3
    int count = 0;
    while(num!=0){
        num = num / 10;
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
    PrimesSieve mySieve(limit);
    mySieve.display_primes();
    return 0;
}

