#include <cstring>
#include <iostream>
#include <list>
#include <string>
#include <stdexcept>
#include <vector>

namespace ctci {
    namespace ch2 {

        class Node {
            public:
                Node* next;
                int value;

            Node(int value) {
                this->next = nullptr;
                this->value = value;
            }
        };

        class LinkedList {
            public:
                Node* first = nullptr;
                Node* last = nullptr;
            
            LinkedList(std::vector<int> initialValues) {
                for (int initialValue : initialValues) {
                    this->insertBack(initialValue);
                }
            }

            void insertBack(int value) {
                if (first == nullptr) {
                    first = new Node(value);
                    last = first;
                } else {
                    last->next = new Node(value);
                    last = last->next;
                }
            }

            std::string toString() {
                std::string output;
                Node* current = first;
                while (current != nullptr) {
                    output = output + std::to_string(current->value) + ",";
                    current = current->next;
                }
                return output.substr(0, output.length() - 1);
            }
        };


        // <distance, value>
        std::pair<int, int> returnKthToLast(const Node* node, int k) {
            if (node->next == nullptr) {
                return std::pair<int, int>(1, node->value);
            }
            std::pair<int, int> downstream = returnKthToLast(node->next, k);
            if (downstream.first == k) {
                return downstream;
            }

            return std::pair<int, int>(downstream.first + 1, node->value);
        }

        int returnKthToLast(const LinkedList& list, int k) {
            return returnKthToLast(list.first, k).second;
        }

        class Example {
            public:
                std::vector<int> input;
                int k;
                int output;
        };

        std::list<Example> examples = {
            {{1,2,3,4,5}, 3, 3},
            {{1,2,3,4,5}, 2, 4},
            {{1,2,3,4,5}, 1, 5},
            {{1}, 1, 1},
            {{1,2,3,4,5,6,7,8,9,10}, 3, 8},
        };

        int main(int argc, char** argv) {
            for (auto example : examples) {
                LinkedList list(example.input);

                if (returnKthToLast(list, example.k) != example.output) {
                    throw std::runtime_error("Test failed.");
                }
            }

            std::cout << "All tests passed.\n";
            return 0;
        }
    }
}

int main(int argc, char** argv) {
    return ctci::ch2::main(argc, argv);
}