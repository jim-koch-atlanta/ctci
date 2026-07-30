#include <iostream>
#include <stdexcept>
#include <string>
#include <sstream>

#include "../jim/bit-manipulation.h"

namespace ctci {
    namespace ch5 {
        /**
         * Calculate the next-smallest value with the same number of 1's.
         * (Largest number smaller than num)
         * 
         * @param num The number.
         * 
         * @return The next-smallest value.
         */
        int nextSmallest(unsigned int num) {
            if (num == 0) {
                return 0;
            }

            // Count the number of 1s at the very bottom (trailing 1s).
            int c1 = 0;
            int origNum = num;
            while (num % 2 == 1) {
                num = num / 2;
                c1++;
            }

            // Edge-case: If the number was all 1's, there is no "next-smallest".
            //   Return the original number.
            if (num == 0) {
                return origNum;
            }

            // Count the number of 0s that sit right above the trailing 1s.
            int c0 = 0;
            while (num % 2 == 0) {
                num = num / 2;
                c0++;
            }

            // We found the rightmost 1 that has 0s to its right.
            // Turn it into a 0, and put a 1 to its right.
            num = num - 1;
            num = num * 2;
            num = num + 1;
            c0--;

            // Slide all 1st as far left as possible.
            while (c1 > 0) {
                num = num * 2 + 1;
                c1--;
            }

            while (c0 > 0) {
                num = num * 2;
                c0--;
            }

            return num;
        }

        /**
         * Calculate the next-largest value with the same number of 1's.
         * (Smallest number larger than num)
         * 
         * @param num The number.
         * 
         * @return The next-largest value.
         */
        int nextLargest(unsigned int num) {
            // Edge-case: If the number was all 0's, there is no "next-smallest".
            //   Return the original number.
            if (num == 0) {
                return 0;
            }

            // Count the number of 0s at the very bottom (trailing 0s).
            int c0 = 0;
            while (num % 2 == 0) {
                num = num / 2;
                c0++;
            }

            // Count the number of 1s that sit right above the trailing 0s.
            int c1 = 0;
            while (num % 2 == 1) {
                num = num / 2;
                c1++;
            }

            // We found the rightmost 0 that has 1s to its right.
            // Turn it into a 1, and put a 0 to its right.
            num = num + 1;
            num = num * 2;
            c1--;

            // Slide all 1st as far right as possible.
            while (c0 > 0) {
                num = num * 2;
                c0--;
            }

            while (c1 > 0) {
                num = num * 2 + 1;
                c1--;
            }

            return num;
        }

        int main(int argc, char** argv) {
            if (nextLargest( 0b10011100) != 0b10100011) throw std::runtime_error("Test failed");
            if (nextSmallest(0b10011100) != 0b10011010) throw std::runtime_error("Test failed");
            if (nextSmallest(0b11111111) != 0b11111111) throw std::runtime_error("Test failed");

            std::cout << "All tests passed.\n";
            return 0;
        }
    }
}

int main(int argc, char** argv) {
    return ctci::ch5::main(argc, argv);
}