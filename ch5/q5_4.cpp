#include <iostream>
#include <stdexcept>
#include <string>
#include <sstream>

#include "../jim/bit-manipulation.h"

namespace ctci {
    namespace ch5 {
        /**
         * Calculate the next-smallest value with the same number of 1's.
         * 
         * @param num The number.
         * 
         * @return The next-smallest value.
         */
        int nextSmallest(unsigned int num) {
            // We want to flip the smallest 1 to a 0. We want to flip the smallest 0 **higher than that** to a 1.
            // That increments, but by the lowest amount.
            return 1;
        }

        /**
         * Calculate the next-largest value with the same number of 1's.
         * 
         * @param num The number.
         * 
         * @return The next-largest value.
         */
        int nextLargest(unsigned int num) {
            // Set the highest 1 to a 0. Set the bit above it to a 1. Then
            // "push" all of the 1's as far right as possible.
            return 1;
        }

        int main(int argc, char** argv) {
            if (flipBitToWin(0b11011101111) != 8) throw std::runtime_error("Test failed");
            if (flipBitToWin(0b11001001111) != 5) throw std::runtime_error("Test failed");
            if (flipBitToWin(0b00000000000) != 1) throw std::runtime_error("Test failed");
            if (flipBitToWin(0xFFFFFFFF) != 32) throw std::runtime_error("Test failed");
            std::cout << "All tests passed.\n";
            return 0;
        }
    }
}

int main(int argc, char** argv) {
    return ctci::ch5::main(argc, argv);
}