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


        LinkedList sumListsReverse(LinkedList& first, LinkedList& second) {

            LinkedList result({});

            Node* left = first.first;
            Node* right = second.first;

            int carry = 0;
            while ((left != nullptr) && (right != nullptr)) {
                int resultValue = left->value + right->value + carry;
                if (resultValue >= 10) {
                    carry = 1;
                    resultValue -= 10;
                } else {
                    carry = 0;
                }

                result.insertBack(resultValue);
                left = left->next;
                right = right->next;
            }

            // "Left" might be longer than "right".
            while (left != nullptr) {
                int resultValue = left->value + carry;
                if (resultValue >= 10) {
                    carry = 1;
                    resultValue -= 10;
                } else {
                    carry = 0;
                }
                result.insertBack(resultValue);
                left = left->next;
            }

            // "Right" might be longer than "left".
            while (right != nullptr) {
                int resultValue = right->value + carry;
                if (resultValue >= 10) {
                    carry = 1;
                    resultValue -= 10;
                } else {
                    carry = 0;
                }
                result.insertBack(resultValue);
                right = right->next;
            }

            if (carry != 0) {
                result.insertBack(carry);
                carry = 0;
            }

            return result;
        }

        std::pair<Node*, int> sumListsForward(Node* first, Node* second) {
            if ((first != nullptr) && (second != nullptr)) {
                auto result = sumListsForward(first->next, second->next);
                int carry = 0;
                int value = first->value + second->value + result.second;
                if (value >= 10) {
                    value = value - 10;
                    carry = 1;
                }
                Node* front = new Node(value);
                front->next = result.first;
                return std::pair<Node*, int>(front, carry);
            } else {
                return std::pair<Node*, int>({}, 0);
            }
        }

        void zeroPadList(LinkedList& list, int count) {
            for (int i = 0; i < count; i++) {
                Node *zero = new Node(0);
                zero->next = list.first;
                list.first = zero;
            }
        }

        LinkedList sumListsForward(LinkedList& first, LinkedList& second) {
            // Make them the same length.
            int lengthFirst = first.length();
            int lengthSecond = second.length();

            if (lengthFirst > lengthSecond) {
                zeroPadList(second, lengthFirst - lengthSecond);
            } else {
                zeroPadList(first, lengthSecond - lengthFirst);
            }

            std::pair<Node*, int> result = sumListsForward(first.first, second.first);
            LinkedList list({});
            list.first = result.first;
            if (result.second != 0) {
                Node* front = new Node(result.second);
                front->next = list.first;
                list.first = front;
            }
            return list;
        }

        bool compareLists(const LinkedList& first, const LinkedList& second) {
            Node* firstNode = first.first;
            Node* secondNode = second.first;

            while ((firstNode != nullptr) && (secondNode != nullptr)) {
                if (firstNode->value != secondNode->value) {
                    return false;
                }
                firstNode = firstNode->next;
                secondNode = secondNode->next;
            }

            if (firstNode != nullptr) {
                return false;
            }

            if (secondNode != nullptr) {
                return false;
            }

            return true;
        }

        class Example {
            public:
                std::vector<int> first;
                std::vector<int> second;
                std::vector<int> result;
        };

        std::list<Example> examplesReverse = {
            {{7,1,6}, {5,9,2}, {2,1,9}},
            {{7,1,6}, {5,9,5}, {2,1,2,1}},
            {{7,1,6}, {5,9,5,9}, {2,1,2,0,1}},
        };

        std::list<Example> examplesForward = {
            //{{6,1,7}, {2,9,5}, {9,1,2}},
            //{{6,1,7}, {5,9,5}, {1,2,1,2}},
            {{6,1,7}, {9,5,9,5}, {1,0,2,1,2}},
        };

        int main(int argc, char** argv) {
            for (auto example : examplesReverse) {
                LinkedList first(example.first);
                LinkedList second(example.second);
                LinkedList expectedResult(example.result);

                LinkedList actualResult = sumListsReverse(first, second);
                if (compareLists(actualResult, expectedResult) != true) {
                    throw std::runtime_error("Test failed.");
                }
            }
 
            for (auto example : examplesForward) {
                LinkedList first(example.first);
                LinkedList second(example.second);
                LinkedList expectedResult(example.result);

                LinkedList actualResult = sumListsForward(first, second);
                if (compareLists(actualResult, expectedResult) != true) {
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