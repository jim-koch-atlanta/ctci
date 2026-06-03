#include <algorithm>
#include <cctype>
#include <cstring>
#include <iostream>
#include <list>
#include <string>
#include <stdexcept>

namespace ctci {
    namespace ch1 {
        std::string toLower(std::string s)
        {
            std::transform(
                s.begin(),
                s.end(),
                s.begin(),
                [](unsigned char c) {
                    return static_cast<char>(std::tolower(c));
                }
            );

            return s;
        }

        std::string onlyLetters(const std::string& input) {
            std::string output;

            for (char c : input) {
                if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')) {
                    output += c;
                }
            }

            return output;
        }

        bool isPalindromePermutation(const std::string& input) {
            // "You can ignore casing and non-letter characters".
            std::string letters = toLower(onlyLetters(input));

            int letter_count[26] = { 0 };
            for (char c : letters) {
                letter_count[c - 'a']++;
            }

            // It's not a palindrome permutation if there are two or more characters that occur an odd number of times.
            int odds = 0;
            for (int i = 0; i < 26; i++) {
                if (letter_count[i] % 2 == 1) {
                    odds++;
                }

                if (odds > 1) {
                    return false;
                }
            }

            return true;
        }

        class Example {
            public:
                std::string input;
                bool isPalindromePermutation;
        };

        std::list<Example> examples = {
            {"taco cat taco cat taco cat", true},
            {"race car", true},
            {"never odd or even", true},
            {"dooood", true},
            {"doooood", true},
            {"Was it a car or a cat I saw", true},
            {"No lemon no melon", true},
            {"abc", false},
            {"civil", false},
            {"ivicc", true},
        };

        int main(int argc, char** argv) {
            for (auto example : examples) {
                if (isPalindromePermutation(example.input) != example.isPalindromePermutation) {
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