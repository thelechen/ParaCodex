// Golden serial Jacobi stencil. Do not edit during the tutorial.
#include <chrono>
#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

int main(int argc, char** argv) {
    if (argc != 5) {
        std::cerr << "Usage: program WIDTH HEIGHT STEPS dump|summary\n";
        return 2;
    }
    const int w = std::atoi(argv[1]);
    const int h = std::atoi(argv[2]);
    const int steps = std::atoi(argv[3]);
    const std::string mode = argv[4];
    if (w < 3 || h < 3 || w > 2000 || h > 2000 || steps < 0 || steps > 1000 ||
        (mode != "dump" && mode != "summary")) {
        std::cerr << "Invalid arguments\n";
        return 2;
    }
    std::vector<double> a(w * h), b(w * h);
    for (int y = 0; y < h; ++y) {
        for (int x = 0; x < w; ++x) {
            a[y * w + x] = ((y * 17 + x * 31) % 97) / 97.0 + 0.001 * y;
        }
    }
    const auto start = std::chrono::steady_clock::now();
    for (int t = 0; t < steps; ++t) {
        b = a; // boundary cells remain unchanged
        for (int y = 1; y < h - 1; ++y) {
            for (int x = 1; x < w - 1; ++x) {
                const int i = y * w + x;
                b[i] = 0.25 * (a[i - w] + a[i + w] + a[i - 1] + a[i + 1]);
            }
        }
        a.swap(b); // time steps depend on the previous step
    }
    const auto stop = std::chrono::steady_clock::now();
    std::cout << std::fixed << std::setprecision(12);
    if (mode == "dump") {
        std::cout << "GRID " << w << " " << h << " " << steps << "\n";
        for (int y = 0; y < h; ++y) {
            for (int x = 0; x < w; ++x) {
                if (x) std::cout << " ";
                std::cout << a[y * w + x];
            }
            std::cout << "\n";
        }
    } else {
        double sum = 0.0;
        for (double v : a) sum += v;
        std::chrono::duration<double, std::milli> ms = stop - start;
        std::cout << "TIME_MS " << ms.count() << "\n";
        std::cout << "CHECKSUM " << sum << "\n";
    }
}
