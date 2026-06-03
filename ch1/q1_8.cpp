#include <iostream>
#include <list>
#include <math.h>
#include <stdexcept>
#include <utility>
#include <vector>

namespace ctci {
    namespace ch1 {
        void zeroRow(std::vector<std::vector<int>>& matrix, int n, int row) {
            for (int y = 0; y < n; y++) {
                matrix[row][y] = 0;
            }
        }

        void zeroColumn(std::vector<std::vector<int>>& matrix, int n, int column) {
            for (int x = 0; x < n; x++) {
                matrix[x][column] = 0;
            }
        }

        void zeroMatrix(std::vector<std::vector<int>>& matrix, int n) {

            std::vector<int> rowsToZeroOut;
            std::vector<int> columnsToZeroOut;

            for (int x = 0; x < n; x++) {
                for (int y = 0; y < n; y++) {
                    if (matrix[x][y] == 0) {
                        rowsToZeroOut.push_back(x);
                        columnsToZeroOut.push_back(y);
                    }
                }
            }

            for (int row : rowsToZeroOut) {
                zeroRow(matrix, n, row);
            }

            for (int column : columnsToZeroOut) {
                zeroColumn(matrix, n, column);
            }
        }

        class Example {
            public:
                std::vector<std::vector<int>> input;
                std::vector<std::vector<int>> output;
                int n;
        };

        std::list<Example> examples = {
            // 1x1: no zeros, no change
            {
                {{42}},
                {{42}},
                1
            },
            // 1x1: zero
            {
                {{0}},
                {{0}},
                1
            },
            // 3x3: zero in the middle — entire row 1 and column 1 zeroed
            {
                {{1, 2, 3},
                 {4, 0, 6},
                 {7, 8, 9}},
                {{1, 0, 3},
                 {0, 0, 0},
                 {7, 0, 9}},
                3
            },
            // 3x3: no zeros, no change
            {
                {{1, 2, 3},
                 {4, 5, 6},
                 {7, 8, 9}},
                {{1, 2, 3},
                 {4, 5, 6},
                 {7, 8, 9}},
                3
            },
            // 4x4: two zeros in different rows and columns
            {
                {{ 1,  2,  3,  4},
                 { 5,  0,  7,  8},
                 { 9, 10, 11,  0},
                 {13, 14, 15, 16}},
                {{ 1,  0,  3,  0},
                 { 0,  0,  0,  0},
                 { 0,  0,  0,  0},
                 {13,  0, 15,  0}},
                4
            },
            // 4x4: two zeros in the same row
            {
                {{ 1,  2,  3,  4},
                 { 5,  0,  7,  0},
                 { 9, 10, 11, 12},
                 {13, 14, 15, 16}},
                {{ 1,  0,  3,  0},
                 { 0,  0,  0,  0},
                 { 9,  0, 11,  0},
                 {13,  0, 15,  0}},
                4
            },
        };

        int main(int argc, char** argv) {
            for (auto example : examples) {
                zeroMatrix(example.input, example.n);
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
