#include <iostream>
#include <random>
#include <chrono>

using namespace std;

int main() {
    unsigned seed = chrono::system_clock::now().time_since_epoch().count();
    mt19937 gen(seed);

    cout << "Range of numbers: ";
    int range;
    cin >> range;

    uniform_int_distribution<int> dist(0, range);
    int num = dist(gen);

    bool found = false;

    while (!found) {
        cout << endl << "Guess number: ";
        
        int guess;
        cin >> guess;

        if (guess == num) {
            cout << guess << " was the number!\n";
            found = true;
        } else {
            cout << guess << " wasnt the number. ";
            if (guess > num) {
                cout << "Lower.\n";
            } else {
                cout << "Higher.\n";
            }
        }
    }

    return 0;
}