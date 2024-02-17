#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

int rollDice() {
    return (rand() % 6) + 1;
}

int main() {
    srand(time(0));

    int result1 = rollDice();
    int result2 = rollDice();

    int sum = result1 + result2;

    cout << "Dice 1: " << result1 << endl;
    cout << "Dice 2: " << result2 << endl;
    cout << "Sum: " << sum << endl;

    return 0;
}
