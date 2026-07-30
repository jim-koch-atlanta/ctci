#include <cstdint>
#include <iostream>
#include <stdexcept>
#include <string>
#include <sstream>

#include "../jim/bit-manipulation.h"

namespace ctci {
    namespace ch5 {
        /**
         * Perform pairwise swaps of neighboring bits.
         * Bit 0 and Bit 1 swap.
         * Bit 2 and Bit 3 swap.
         * Bit 4 and Bit 5 swap.
         * ...
         * 
         * @param num The number.
         * 
         * @return The result.
         */
        uint32_t pairwiseSwap(uint32_t num) {
            // All of the **even** bits shift to the left.
            uint32_t result1 = (num << 1) & 0xAAAAAAAAu;

            // All of the **odd** bits shift to the right.
            uint32_t result2 = (num >> 1) & (0x55555555u);

            return result1 | result2;
        }

        int main(int argc, char** argv) {
            if (pairwiseSwap(0b10101010) != 0b01010101) throw std::runtime_error("Test failed");

            std::cout << "All tests passed.\n";
            return 0;
        }
    }
}

int main(int argc, char** argv) {
    return ctci::ch5::main(argc, argv);
}