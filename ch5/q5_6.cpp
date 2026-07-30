#include <iostream>
#include <stdexcept>
#include <string>
#include <sstream>

#include "../jim/bit-manipulation.h"

namespace ctci {
    namespace ch5 {
        /**
         * Calculates the number of bits to flip to convert integer A to integer B.
         * Brute force.
         * 
         * @param A The number A.
         * @param B The number B.
         * 
         * @return The number of bits to flip.
         */
        int calculateFlips(int A, int B) {
            int flips = 0;

            while ((A != 0) || (B != 0)) {
                if ((B % 2) != (A % 2)) {
                    flips++;
                }
                B = B / 2;
                A = A / 2;
            }

            return flips;
        }

        int calculateFlipsFaster(int A, int B) {
            // Use XOR to get a 1 in each position where they differ.
            int diff = A ^ B;

            // Use what we just learned to calculate the number of 1s faster.
            int flips = 0;
            while (diff != 0) {
                diff = diff & (diff - 1);
                flips++;
            }

            return flips;
        }

        int main(int argc, char** argv) {
            if (calculateFlips(0b11101, 0b01111) != 2) throw std::runtime_error("Test failed");
            if (calculateFlipsFaster(0b11101, 0b01111) != 2) throw std::runtime_error("Test failed");

            std::cout << "All tests passed.\n";
            return 0;
        }
    }
}

int main(int argc, char** argv) {
    return ctci::ch5::main(argc, argv);
}