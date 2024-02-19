#include <iostream>
#include <random>
#include <ctime>

using namespace std;

int main() {
    mt19937 rng(time(nullptr)); 
    uniform_int_distribution<mt19937::result_type> dist6(1,6); 

    int dice1 = dist6(rng);
    int dice2 = dist6(rng);
    int sum = dice1 + dice2;

    cout << "Rolled a " << dice1 << " and a " << dice2 << " for a total of " << sum << endl;

    return 0;
}
