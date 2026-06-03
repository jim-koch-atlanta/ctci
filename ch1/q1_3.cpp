#include <cstring>
#include <iostream>
#include <list>
#include <string>
#include <stdexcept>

namespace ctci {
    namespace ch1 {

        void urlify(char* &input) {
            // Edge case.
            if (strlen(input) == 0) {
                return;
            }

            // Find the last non-space.
            int source_index = 0;
            for (source_index = strlen(input) - 1; source_index >= 0; source_index--) {
                if (input[source_index] != ' ') {
                    break;
                }
            }
            if (source_index < 0) {
                throw std::runtime_error("String contains only spaces.");
            }

            // We found the last non-space. Start copying to the back of the string.
            int dest_index = strlen(input) - 1;
            while (source_index >= 0) {
                if (input[source_index] == ' ') {
                    // Hack, because we're going backwards.
                    input[dest_index--] = '0';
                    input[dest_index--] = '2';
                    input[dest_index--] = '%';
                } else {
                    input[dest_index--] = input[source_index];
                }
                source_index--;
            }
        }

        class Example {
            public:
                const char* input;
                const char* output;
        };

        std::list<Example> examples = {
            {"This is a test      ", "This%20is%20a%20test"},
            {"This_is_a_test", "This_is_a_test"},
            {"    ThisIsATest        ", "%20%20%20%20ThisIsATest"},
        };

        int main(int argc, char** argv) {
            for (auto example : examples) {
                std::cout << "Input: " << example.input << "\n";
                std::cout << "Expected Output: " << example.output << "\n";

                int input_len = strlen(example.input);
                char* copy = new char[input_len + 1];
                copy[input_len] = '\0';
                strncpy(copy, example.input, input_len);
                urlify(copy);
                std::cout << "Actual Output: " << copy << "\n";
                if (strcmp(copy, example.output) != 0) {
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