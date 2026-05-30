#include <algorithm>
#include <cctype>
#include <cstring>
#include <iostream>
#include <list>
#include <string>
#include <sstream>
#include <stdexcept>

namespace ctci {
    namespace ch1 {
        // aabcccccaaa

        std::string compressString(const std::string& input) {
            if (input == "") {
                return input;
            }

            std::ostringstream output;
            char lastChar = input.at(0);
            int lastCharCount = 0;
            
            int index = 0;
            while (index < input.length()) {
                if (input.at(index) == lastChar) {
                    lastCharCount++;
                } else {
                    output << lastChar << lastCharCount;
                    lastChar = input.at(index);
                    lastCharCount = 1;
                }

                index++;
            }

            output << lastChar << lastCharCount;
            std::string result = output.str();

            if (result.length() >= input.length()) {
                return input;
            }
            return result;
        }

        class Example {
            public:
                std::string input;
                std::string output;
        };

        std::list<Example> examples = {
            {"aabcccccaaa", "a2b1c5a3"},
            {"aabcccccaaab", "a2b1c5a3b1"},
            {"aabcdefg", "aabcdefg"},   // Compressed string would not be shorter. 
            {"aabb", "aabb"},           // Compressed string would not be shorter.
        };

        int main(int argc, char** argv) {
            for (auto example : examples) {
                std::string output = compressString(example.input);
                if (output != example.output) {
                    throw std::runtime_error("Test failed.");
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