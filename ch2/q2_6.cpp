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

            int length() {
                Node* current = first;
                int length = 0;
                while (current != nullptr) {
                    current = current->next;
                    length++;
                }
                return length;
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


        std::pair<Node*, bool> isPalindrome(Node* forwards, Node* backwards) {
            if (forwards->next != nullptr) {
                auto result = isPalindrome(forwards->next, backwards);
                if (result.second == false) {
                    return std::pair<Node*, bool>(nullptr, false);
                } else {
                    bool boolResult = (forwards->value == result.first->value);
                    return std::pair<Node*, bool>(result.first->next, boolResult);
                }
            } else {
                bool boolResult = (forwards->value == backwards->value);
                return std::pair<Node*, bool>(backwards->next, boolResult);
            }
        }

        bool isPalindrome(LinkedList& list) {
            return isPalindrome(list.first, list.first).second;
        }

        class Example {
            public:
                std::vector<int> elements;
                bool isPalindrome;
        };

        std::list<Example> examples = {
            {{1,2,1}, true},
            {{1,2,2,1}, true},
            {{1,2,3,4,5,4,3,2,1}, true},
            {{1,2,3,4,5}, false},
        };

        int main(int argc, char** argv) {
            for (auto example : examples) {
                LinkedList list(example.elements);
                if (isPalindrome(list) != example.isPalindrome) {
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