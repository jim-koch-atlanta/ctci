#include <array>
#include <iostream>
#include <list>
#include <string>
#include <stdexcept>

namespace ctci {
    namespace ch1 {

        std::array<int, 128> getCharset(std::string str) {
            std::array<int, 128> charset = { 0 };
            for (char c : str) {
                charset[static_cast<int>(c)]++;
            }

            return charset;
        }

        bool isPermutation(std::string str1, std::string str2) {
            if (str1.length() != str2.length()) {
                return false;
            }

            std::array<int, 128> charset1 = getCharset(str1);
            std::array<int, 128> charset2 = getCharset(str2);

            for (int i = 0; i < 128; i++) {
                if (charset1[i] != charset2[i]) {
                    return false;
                }
            }

            return true;
        }

        class Example {
            public:
                std::string str1;
                std::string str2;
                bool isPermutation;
        };

        std::list<Example> examples = {
            {"snuffleufagus", "sugafuelffuns", true},
            {"abcdefghijklmnop", "abcdefghihgfedcba", false},
            {"abcdefghijklmnop", "abcdefghijklmnop", true},
            {"jim koch", "kim joch", true}
        };

        int main(int argc, char** argv) {
            for (auto example : examples) {
                if (isPermutation(example.str1, example.str2) != example.isPermutation) {
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