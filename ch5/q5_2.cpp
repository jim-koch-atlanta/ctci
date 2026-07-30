#include <iostream>
#include <stdexcept>
#include <string>
#include <sstream>

#include "../jim/bit-manipulation.h"

namespace ctci {
    namespace ch5 {
        /**
         * Convert num to a string of binary characters.
         * 
         * @param num A number between 0 and 1.
         * 
         * @return num as a binary string of at most 32 characters.
         */
        std::string binaryToString(double num) {
            if ((num > 1) || (num < 0))
                return "ERROR";

            std::string result{"0."};
            int digits = 1;
            while ((num != 0) && (digits < 32)) {
                num = num * 2;
                if (num >= 1) {
                    result += "1";
                    num = num - 1;
                } else {
                    result += "0";
                }

                digits++;
            }

            if (num != 0) {
                return "ERROR";
            }

            return result;
        }

        int main(int argc, char** argv) {
            if (binaryToString(0.5) != "0.1") throw std::runtime_error("Test failed");
            if (binaryToString(0.25) != "0.01") throw std::runtime_error("Test failed");
            if (binaryToString(0.75) != "0.11") throw std::runtime_error("Test failed");
            if (binaryToString(0.875) != "0.111") throw std::runtime_error("Test failed");
            if (binaryToString(0.625) != "0.101") throw std::runtime_error("Test failed");
            if (binaryToString(0.3333333333333333) != "ERROR") throw std::runtime_error("Test failed");
            std::cout << "All tests passed.\n";
            return 0;
        }
    }
}

int main(int argc, char** argv) {
    return ctci::ch5::main(argc, argv);
}