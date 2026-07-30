#include <iostream>
#include <stdexcept>
#include "../jim/bit-manipulation.h"

namespace ctci {
    namespace ch5 {
        /**
         * Insert M into N, such that M starts at bit j and ends at bit i.
         * 
         * For example:
         *   N = 10000000000
         *   M =       10011
         *   i = 2, j = 6
         * 
         * 10001001100
         */
        int performInsertion(int N, int M, int i, int j) {
            // Set bits i through j of N to 0.
            int maskMSB = (-1 << (j + 1));
            int maskLSB = (1 << i) - 1;
            int mask = maskMSB | maskLSB;

            int maskedN = N & mask;

            int result = maskedN | (M << i);
            return result;
        }
        
        int main(int argc, char** argv) {
            if (performInsertion(0b10000000000, 0b10011, 2, 6) != 0b10001001100) throw std::runtime_error("Test failed.");
            if (performInsertion(0b11111111111, 0b10011, 2, 6) != 0b11111001111) throw std::runtime_error("Test failed.");
            if (performInsertion(0b11111111111, 0b00000, 2, 6) != 0b11110000011) throw std::runtime_error("Test failed.");

            std::cout << "All tests passed.\n";
            return 0;
        }
    }
}

int main(int argc, char** argv) {
    return ctci::ch5::main(argc, argv);
}
