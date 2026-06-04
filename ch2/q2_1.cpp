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


        void removeDups(LinkedList& list) {
            Node* currentElement = list.first;

            // Iterate over each of the elements of the list.
            while (currentElement != nullptr) {
                Node* runner = currentElement;

                // Compare it to all other elements of the list.
                while (runner != nullptr && runner->next != nullptr) {
                    if (currentElement->value == runner->next->value) {
                        Node* temp = runner->next;
                        runner->next = runner->next->next;
                        delete temp;
                    } else {
                        runner = runner->next;
                    }
                }

                currentElement = currentElement->next;
            }
        }

        class Example {
            public:
                std::vector<int> input;
                std::string output;
        };

        std::list<Example> examples = {
            {{1,2,3,4,5}, "1,2,3,4,5"},
            {{1,2,3,4,1,1,5}, "1,2,3,4,5"},
            {{1,2,3,4,5,1,1}, "1,2,3,4,5"},
            {{1,1,1,2,3,4,5}, "1,2,3,4,5"},
            {{1}, "1"},
            {{1,1,1}, "1"},
        };

        int main(int argc, char** argv) {
            for (auto example : examples) {
                LinkedList list(example.input);

                removeDups(list);
                std::string result = list.toString();
                if (result != example.output) {
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