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

        // Detects if a linked list contains a loop.
        // If so, it returns the node at the beginning of the loop.
        // If not, returns nullptr.
        Node* detectLoop(const LinkedList& list) {
            Node* slow = list.first;
            Node* fast = list.first;

            while (slow != nullptr && fast != nullptr) {
                slow = slow->next;
                fast = fast->next;
                if (fast == nullptr) {
                    return nullptr;
                }
                fast = fast->next;
                if (slow == fast) {
                    break;
                }
            }

            if (slow == nullptr || fast == nullptr) {
                return nullptr;
            }

            Node* tmp = list.first;
            while (tmp != slow) {
                slow = slow->next;
                tmp = tmp->next;
            }

            return tmp;
        }

        int main(int argc, char** argv) {
            // No loop
            {
                LinkedList list({1, 2, 3, 4, 5});
                if (detectLoop(list) != nullptr)
                    throw std::runtime_error("Test failed.");
            }

            // Empty list
            {
                LinkedList list({});
                if (detectLoop(list) != nullptr)
                    throw std::runtime_error("Test failed.");
            }

            // Single node pointing to itself
            {
                LinkedList list({1});
                list.first->next = list.first;
                if (detectLoop(list) != list.first)
                    throw std::runtime_error("Test failed.");
            }

            // Loop back to the first node
            {
                LinkedList list({1, 2, 3, 4, 5});
                list.last->next = list.first;
                if (detectLoop(list) != list.first)
                    throw std::runtime_error("Test failed.");
            }

            // Loop back to the second node
            {
                LinkedList list({1, 2, 3, 4, 5});
                Node* second = list.first->next;
                list.last->next = second;
                if (detectLoop(list) != second)
                    throw std::runtime_error("Test failed.");
            }

            // Loop back to a node in the middle
            {
                LinkedList list({1, 2, 3, 4, 5});
                Node* third = list.first->next->next;
                list.last->next = third;
                if (detectLoop(list) != third)
                    throw std::runtime_error("Test failed.");
            }

            std::cout << "All tests passed.\n";
            return 0;
        }
    }
}

int main(int argc, char** argv) {
    return ctci::ch2::main(argc, argv);
}