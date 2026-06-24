#include <cstring>
#include <iostream>
#include <list>
#include <string>
#include <stdexcept>
#include <vector>

#include "../jim/stack.h"
#include "../jim/queue.h"

namespace ctci {
    namespace ch3 {

        template <typename T>
        class StackWithLength : public ctci::jim::Stack<T> {
            protected:
                int count;

            public:
                StackWithLength()
                : ctci::jim::Stack<T>() {
                    this->count = 0;
                }

                void push(T value) {
                    ctci::jim::Stack<T>::push(value);
                    this->count++;
                }

                T pop() {
                    auto result = ctci::jim::Stack<T>::pop();
                    this->count--;
                    return result;
                }

                int length() {
                    return count;
                }
        };

        template <typename T>
        class SetOfStacks {
            protected:
                // The stack, and its current size.
                std::vector<ctci::ch3::StackWithLength<T>> stacks;
                int maxHeight;

        public:
            SetOfStacks(int maxHeight) {
                this->maxHeight = maxHeight;
            }

            void push(T value) {
                if ((stacks.size() == 0) || (stacks.at(stacks.size() - 1).length() == maxHeight)) {
                    stacks.push_back(ctci::ch3::StackWithLength<T>());
                }

                stacks.at(stacks.size() - 1).push(value);
            }

            T pop() {
                if (stacks.size() == 0) {
                    throw std::runtime_error("Stack is empty.");
                }
                
                T result = stacks.at(stacks.size() - 1).pop();
                if (stacks.at(stacks.size() - 1).isEmpty()) {
                    stacks.pop_back();
                }

                return result;
            }

            T popAt(int stackNum) {
                if (stacks.size() == 0 || stacks.size() <= stackNum) {
                    throw std::runtime_error("Stack is empty.");
                }
                
                T result = stacks.at(stackNum).pop();
                if (stacks.at(stackNum).isEmpty()) {
                    stacks.erase(stacks.begin() + stackNum);
                }

                return result;
            }

            T peek() {
                if (stacks.size() == 0) {
                    throw std::runtime_error("Stack is empty.");
                }

                return stacks.at(stacks.size() - 1).peek();
            }

            bool isEmpty() {
                return stacks.empty();
            }

            std::string toString() {
                std::string result;
                for (int i = 0; i < stacks.size(); i++) {
                    auto &stack = stacks[stacks.size() - 1 - i];
                    result += stack.toString() + ",";
                }

                if (result.length() == 0) {
                    return result;
                }
                return result.substr(0, result.length() - 1);
            }
        };

        int main(int argc, char** argv) {
            // Push exactly fills two stacks of height 3.
            {
                SetOfStacks<int> set(3);
                set.push(1); set.push(2); set.push(3);
                set.push(4); set.push(5); set.push(6);
                if (set.peek() != 6) throw std::runtime_error("Test failed.");
            }

            // Pop drains the top sub-stack and falls back to the previous one.
            {
                SetOfStacks<int> set(3);
                set.push(1); set.push(2); set.push(3);
                set.push(4);
                if (set.pop() != 4) throw std::runtime_error("Test failed.");
                if (set.peek() != 3) throw std::runtime_error("Test failed.");
            }

            // Pop removes the last element and isEmpty returns true.
            {
                SetOfStacks<int> set(3);
                set.push(1);
                set.pop();
                if (!set.isEmpty()) throw std::runtime_error("Test failed.");
            }

            // Push after pop reuses the top sub-stack.
            {
                SetOfStacks<int> set(3);
                set.push(1); set.push(2); set.push(3);
                set.push(4);
                set.pop(); // removes 4, back to one full sub-stack
                set.push(99);
                if (set.peek() != 99) throw std::runtime_error("Test failed.");
            }

            // isEmpty on fresh set.
            {
                SetOfStacks<int> set(3);
                if (!set.isEmpty()) throw std::runtime_error("Test failed.");
            }

            // Pop a single element out of the middle stack.
            {
                SetOfStacks<int> set(3);
                set.push(1); set.push(2); set.push(3);
                set.push(4); set.push(5); set.push(6);
                set.push(7); set.push(8); set.push(9);
                if (set.popAt(1) != 6) throw std::runtime_error("Test failed.");
                if (set.popAt(1) != 5) throw std::runtime_error("Test failed.");
                if (set.popAt(1) != 4) throw std::runtime_error("Test failed.");

                if (set.toString() != "9,8,7,3,2,1") throw std::runtime_error("Test failed.");
            }

            std::cout << "All tests passed.\n";
            return 0;
        }
    }
}

int main(int argc, char** argv) {
    return ctci::ch3::main(argc, argv);
}