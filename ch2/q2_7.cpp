#include <cstring>
#include <iostream>
#include <list>
#include <string>
#include <stdexcept>
#include <unordered_map>
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


        bool doListsIntersect(const LinkedList& list1, const LinkedList& list2) {
            // Let's assume we don't have the `list` member variable of LinkedList,
            // just to make it interesting.
            Node* last1 = list1.first;
            while (last1 != nullptr && last1->next != nullptr) {
                last1 = last1->next;
            }

            Node* last2 = list2.first;
            while (last2 != nullptr && last2->next != nullptr) {
                last2 = last2->next;
            }

            return (last1 == last2);
        }

        bool doListsIntersectAlternative(const LinkedList& list1, const LinkedList& list2) {
            std::unordered_map<Node*, bool> mapOfList;

            // Let's assume we don't have the `list` member variable of LinkedList,
            // just to make it interesting.
            Node* node = list1.first;
            while (node != nullptr) {
                mapOfList[node] = true;
                node = node->next;
            }

            node = list2.first;
            while (node != nullptr) {
                if (mapOfList.find(node) != mapOfList.end())
                {
                    return true;
                }
                node = node->next;
            }

            return false;
        }

        int main(int argc, char** argv) {
            // No intersection
            {
                LinkedList list1({1, 2, 3});
                LinkedList list2({4, 5, 6});
                if (doListsIntersect(list1, list2) != false)
                    throw std::runtime_error("Test failed.");
                if (doListsIntersectAlternative(list1, list2) != false)
                    throw std::runtime_error("Test failed.");
            }

            // Intersection at the last node
            {
                Node* shared = new Node(99);
                LinkedList list1({1, 2, 3});
                list1.last->next = shared;
                LinkedList list2({4, 5});
                list2.last->next = shared;
                if (doListsIntersect(list1, list2) != true)
                    throw std::runtime_error("Test failed.");
                if (doListsIntersectAlternative(list1, list2) != true)
                    throw std::runtime_error("Test failed.");
            }

            // Intersection partway through (shared tail of two nodes)
            {
                Node* shared1 = new Node(7);
                Node* shared2 = new Node(8);
                shared1->next = shared2;
                LinkedList list1({1, 2, 3});
                list1.last->next = shared1;
                LinkedList list2({4, 5});
                list2.last->next = shared1;
                if (doListsIntersect(list1, list2) != true)
                    throw std::runtime_error("Test failed.");
                if (doListsIntersectAlternative(list1, list2) != true)
                    throw std::runtime_error("Test failed.");
            }

            // Different lengths, no intersection
            {
                LinkedList list1({1, 2, 3, 4, 5});
                LinkedList list2({6});
                if (doListsIntersect(list1, list2) != false)
                    throw std::runtime_error("Test failed.");
                if (doListsIntersectAlternative(list1, list2) != false)
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