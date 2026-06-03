#include <algorithm>
#include <cctype>
#include <cstring>
#include <iostream>
#include <list>
#include <string>
#include <sstream>
#include <stdexcept>
#include <vector>

namespace ctci {
    namespace ch1 {
        // Rotate an NxN matrix. We'll just go clockwise 90 degrees, to make it easy.
        // For fun, we're going to rotate in-place.
        void rotateMatrix(std::vector<std::vector<int>>& matrix, int n) {
        }

        class Example {
            public:
                std::vector<std::vector<int>> input;
                std::vector<std::vector<int>> output;
                int n;
        };

        std::list<Example> examples = {
            // 1x1: single element, no change
            {
                {{42}},
                {{42}},
                1
            },
            // 2x2
            {
                {{1, 2},
                 {3, 4}},
                {{3, 1},
                 {4, 2}},
                2
            },
            // 3x3
            {
                {{1, 2, 3},
                 {4, 5, 6},
                 {7, 8, 9}},
                {{7, 4, 1},
                 {8, 5, 2},
                 {9, 6, 3}},
                3
            },
            // 4x4
            {
                {{ 1,  2,  3,  4},
                 { 5,  6,  7,  8},
                 { 9, 10, 11, 12},
                 {13, 14, 15, 16}},
                {{13,  9,  5,  1},
                 {14, 10,  6,  2},
                 {15, 11,  7,  3},
                 {16, 12,  8,  4}},
                4
            },
        };

        int main(int argc, char** argv) {
            for (auto example : examples) {
                rotateMatrix(example.input, example.n);
                for (int x = 0; x < example.n; x++) {
                    for (int y = 0; y < example.n; y++) {
                        if (example.input[x][y] != example.output[x][y]) {
                            throw std::runtime_error("Test failed.");
                        }
                    }
                }
            }

            std::cout << "All tests passed.\n";
            return 0;
        }
    }
}

int main(int argc, char** argv) {
    return ctci::ch1::main(argc, argv);
}
