#include <algorithm>
#include <cctype>
#include <cstring>
#include <iostream>
#include <list>
#include <string>
#include <stdexcept>

namespace ctci {
    namespace ch1 {
        bool isOneAway(const std::string& str1, const std::string& str2) {
            int length_difference = str1.length() - str2.length();

            if (abs(length_difference) > 1) {
                // Their lengths must be within one of each other.
                return false;
            }
            
            int differencesFound = 0;
            int index_str1 = 0;
            int index_str2 = 0;

            while (index_str1 < str1.length() && index_str2 < str2.length()) {
                if (str1.at(index_str1) != str2.at(index_str2)) {
                    differencesFound++;
                    if (differencesFound > 1) {
                        return false;
                    }

                    if (length_difference == 1) {
                        // str1 is longer than str2. So possibly an addition to str1.
                        index_str1++;
                    } else if (length_difference == -1) {
                        // str2 is longer than str1. So possibly an addition to str2.
                        index_str2++;
                    } else {
                        //Possibly a modification.
                        index_str1++;
                        index_str2++;
                    }
                } else {
                    index_str1++;
                    index_str2++;
                }
            }
            return true;
        }

        class Example {
            public:
                std::string str1;
                std::string str2;
                bool isOneAway;
        };

        std::list<Example> examples = {
            {"pale", "ple", true},      // Deletion
            {"pales", "pale", true},    // Deletion
            {"pale", "bale", true},     // Replace
            {"pale", "bake", false},
            {"ple", "pale", true},      // Addition
            {"pale", "pale", true},     // Zero edits is also true
            {"aisle", "weasel", false},
        };

        int main(int argc, char** argv) {
            for (auto example : examples) {
                if (isOneAway(example.str1, example.str2) != example.isOneAway) {
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