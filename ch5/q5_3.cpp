#include <iostream>
#include <stdexcept>
#include <string>
#include <sstream>

#include "../jim/bit-manipulation.h"

namespace ctci {
    namespace ch5 {
        /**
         * Report the maximum number of 1's in a row, if we can flip a single 0 to a 1
         * 
         * @param num The number.
         * 
         * @return The maximum 1's in a row.
         */
        int flipBitToWin(unsigned int num) {
            int previousCounter = 0;
            int currentCounter = 0;
            int max = 1;

            while (num != 0) {
                if ((num & 0b1) != 0) {
                    currentCounter++;
                    if ((currentCounter + previousCounter + 1) > max) {
                        max = currentCounter + previousCounter + 1;
                    }
                } else {
                    previousCounter = currentCounter;
                    currentCounter = 0;
                }

                num = num >> 1;
            }

            return std::min(max, 32);
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