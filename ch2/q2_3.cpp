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
                std::string value;

            Node(std::string value) {
                this->next = nullptr;
                this->value = value;
            }
        };

        class LinkedList {
            public:
                Node* first = nullptr;
                Node* last = nullptr;
            
            LinkedList(std::vector<std::string> initialValues) {
                for (std::string initialValue : initialValues) {
                    this->insertBack(initialValue);
                }
            }

            void insertBack(std::string value) {
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
                    output = output + current->value + ",";
                    current = current->next;
                }
                return output.substr(0, output.length() - 1);
            }
        };


        void removeMiddle(Node* nodeToRemove) {
            if (nodeToRemove->next == nullptr) {
                throw std::runtime_error("Cannot delete the last node.");
            }

            Node* nextNode = nodeToRemove->next;
            nodeToRemove->value = nextNode->value;
            nodeToRemove->next = nextNode->next;
            delete nextNode;
        }

        Node* findNode(const LinkedList &list, std::string nodeValue) {
            Node *current = list.first;

            while ((current != nullptr) && (current->value != nodeValue)) {
                current = current->next;
            }

            return current;
        }

        class Example {
            public:
                std::vector<std::string> input;
                std::string stringToRemove;
                std::string output;
        };

        std::list<Example> examples = {
            {{"a","b","c","d","e"}, "c", "a,b,d,e"},
            {{"a","f","b","g","c","h","d","i","e"}, "c", "a,f,b,g,h,d,i,e"},
        };

        int main(int argc, char** argv) {
            for (auto example : examples) {
                LinkedList list(example.input);

                Node* node = findNode(list, example.stringToRemove);
                removeMiddle(node);
                if (list.toString() != example.output) {
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