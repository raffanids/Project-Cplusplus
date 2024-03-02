#include <iostream>
#include <ctime>
#include <algorithm>
#include <vector>
#include <random>

using namespace std;

int main() {
    random_device rd;
    mt19937 g(rd());

    vector<int> numbers = {2, 3, 3, 4, 4, 5, 5, 6, 6, 8, 8, 9, 9, 10, 10, 11, 11, 12};

    shuffle(numbers.begin(), numbers.end(), g);

    cout << "Randomized Hex Numbers for Catan: ";
    for (int number : numbers) {
        cout << number << " ";
    }
    cout << endl;

    return 0;
}
