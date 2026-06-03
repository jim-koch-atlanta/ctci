#include <map>
#include <stdexcept>
#include <string>

namespace ctci {
    namespace ch1 {
        bool isUnique(std::string str) {
            bool charSet[128] = { false };

            for (char c : str) {
                if (charSet[static_cast<int>(c)] == true)
                {
                    return false;
                }
                charSet[static_cast<int>(c)] = true;
            }

            return true;
        }

        std::map<std::string, bool> examples = {
            {"snuffleufagus", false},
            {"abcdefghijklmnop", true},
            {"abcdefghijklmnopa", false},
            {"jim koch", true},
        };

        int main(int argc, char** argv) {
            for (auto example : examples) {
                if (isUnique(example.first) != example.second) {
                    throw std::runtime_error("Test failed.");
                }
            }

            printf("All tests passed.\n");
            return 0;
        }
    }
}

int main(int argc, char** argv) {
    return ctci::ch1::main(argc, argv);
}