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


        void partitionList(LinkedList& list, int partitionValue) {
            Node *beginning = list.first;
            Node *end = list.first;
            Node *current = list.first->next;

            // We'll iterate over the list. Any nodes that are less than the partition
            // value will be placed on the front ("beginning"). Any nodes that are greater
            // than the partition value will be placed on the back ("end").
            while (current != nullptr) {
                Node *next = current->next;
                if (current->value >= partitionValue) {
                    end->next = current;
                    end = current;
                } else {
                    current->next = beginning;
                    beginning = current;
                }
                current = next;
            }

            end->next = nullptr;
            list.first = beginning;
            list.last = end;
        }

        class Example {
            public:
                std::vector<int> input;
                int partitionValue;
        };

        std::list<Example> examples = {
            {{3,5,8,5,10,2,1}, 5},
            {{3,5,8,5,4,4,6,8,4,9,3,10,2,1}, 5},
        };

        int main(int argc, char** argv) {
            for (auto example : examples) {
                LinkedList list(example.input);

                std::cout << "Input: " << list.toString() << "\n";
                partitionList(list, example.partitionValue);
                std::cout << "Output: " << list.toString() << "\n";
            }
 
            std::cout << "All tests passed.\n";
            return 0;
        }
    }
}

int main(int argc, char** argv) {
    return ctci::ch2::main(argc, argv);
}