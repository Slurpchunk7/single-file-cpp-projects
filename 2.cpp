#include <iostream>
#include <vector>
#include <thread>
#include <chrono>
#include <cmath>

using namespace std;

int main() {
    const int size = 30;
    const int cx = size / 2;
    const int cy = size / 2;
    const double radius = 2.0;

    double angle = 0.0;

    int frame = 0;

    while (frame != 100) {
        int xPos = cx + static_cast<int>(round(cos(angle) * radius));
        int yPos = cy + static_cast<int>(round(sin(angle) * radius));

        cout << "\033[2J\033[1;1H";

        for (int y = 0; y < size; y++) {
            for (int x = 0; x < size; x++) {
                if (x == xPos && y == yPos)
                    cout << "#";
                else
                    cout << ".";
            }
            cout << endl;
        }

        angle += 0.15; // speed of rotation
        this_thread::sleep_for(chrono::milliseconds(60));
        frame++;
    }

    return 0;
}
