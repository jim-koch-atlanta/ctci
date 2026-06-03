#include <cstring>
#include <iostream>
#include <list>
#include <string>
#include <stdexcept>

namespace ctci {
    namespace ch1 {

        bool isStringRotation(std::string str1, std::string str2) {
            if (str1.length() != str2.length()) {
                return false;
            }

            std::string repeatedString = str1 + str1;
            if (repeatedString.find(str2) != std::string::npos) {
                return true;
            }

            return false;
        }

        class Example {
            public:
                std::string str1;
                std::string str2;
                bool isStringRotation;
        };

        std::list<Example> examples = {
            {"waterbottle", "erbottlewat", true},
            {"This is a test", "s is a testThi", true},
            {"Jim already knows the answer.", "answer.Jim already knows the ", true},
            {"waterbottle", "rbottlewat", false},
            {"waterbottle", "erboddlewat", false},
            {"Jim needs to verify.", "to verify. Jim does not need ", false},
        };

        int main(int argc, char** argv) {
            for (auto example : examples) {
                if (isStringRotation(example.str1, example.str2) != example.isStringRotation) {
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