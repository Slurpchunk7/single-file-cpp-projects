#include <iostream>
#include <vector>
#include <random>
#include <chrono>
#include <thread>
#include <cmath>

struct Site {
    int x, y;
};

inline float dist(float x1, float y1, float x2, float y2) {
    float dx = x1 - x2;
    float dy = y1 - y2;
    return std::sqrt(dx * dx + dy * dy);
}

int main() {
    const int width = 100;
    const int height = 40;
    const int siteCount = 20;

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dx(0, width - 1);
    std::uniform_int_distribution<int> dy(0, height - 1);

    std::vector<Site> sites;
    for (int i = 0; i < siteCount; i++)
        sites.push_back({dx(gen), dy(gen)});

    const std::string shades = " .:-=+*#%@";

    std::cout << "\x1B[2J\x1B[H";

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {

            float f1 = 1e9f;
            float f2 = 1e9f;

            for (auto& s : sites) {
                float d = dist((float)x, (float)y, (float)s.x, (float)s.y);

                if (d < f1) {
                    f2 = f1;
                    f1 = d;
                } else if (d < f2) {
                    f2 = d;
                }
            }

            float value = f2 - f1;

            // contrast control (tweak this)
            float t = value / 6.0f;
            if (t > 1.0f) t = 1.0f;

            int idx = (int)(t * (shades.size() - 1));
            std::cout << shades[idx];
        }
        std::cout << '\n';
    }

    std::this_thread::sleep_for(std::chrono::milliseconds(40));
}
