#include <iostream>
#include <list>
#include <stdexcept>
#include <vector>

namespace ctci {
    namespace ch1 {
        using Matrix = std::vector<std::vector<int>>;

        Matrix matMul(const Matrix& A, const Matrix& B, int n) {
            Matrix result(n, std::vector<int>(n, 0));
            for (int i = 0; i < n; i++)
                for (int j = 0; j < n; j++)
                    for (int k = 0; k < n; k++)
                        result[i][j] += A[i][k] * B[k][j];
            return result;
        }

        Matrix transpose(const Matrix& M, int n) {
            Matrix result(n, std::vector<int>(n, 0));
            for (int i = 0; i < n; i++)
                for (int j = 0; j < n; j++)
                    result[i][j] = M[j][i];
            return result;
        }

        // Anti-diagonal permutation matrix: P[i][n-1-i] = 1.
        // Multiplying by P on the right reverses columns.
        Matrix makeP(int n) {
            Matrix P(n, std::vector<int>(n, 0));
            for (int i = 0; i < n; i++)
                P[i][n - 1 - i] = 1;
            return P;
        }

        // 90° clockwise rotation = transpose(input) * P.
        // Not in-place; O(n^3) time, O(n^2) space.
        Matrix rotateMatrix(const Matrix& input, int n) {
            return matMul(transpose(input, n), makeP(n), n);
        }

        class Example {
            public:
                Matrix input;
                Matrix output;
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
            // 5x5
            {
                {{ 1,  2,  3,  4,  5},
                 { 6,  7,  8,  9, 10},
                 {11, 12, 13, 14, 15},
                 {16, 17, 18, 19, 20},
                 {21, 22, 23, 24, 25}},
                {{21, 16, 11,  6,  1},
                 {22, 17, 12,  7,  2},
                 {23, 18, 13,  8,  3},
                 {24, 19, 14,  9,  4},
                 {25, 20, 15, 10,  5}},
                5
            },
        };

        int main(int argc, char** argv) {
            for (auto example : examples) {
                Matrix result = rotateMatrix(example.input, example.n);
                for (int x = 0; x < example.n; x++) {
                    for (int y = 0; y < example.n; y++) {
                        if (result[x][y] != example.output[x][y]) {
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
