#include <cstring>
#include <iostream>
#include <list>
#include <string>
#include <stdexcept>

#include "../jim/stack.h"

namespace ctci {
    namespace ch3 {
        void SortStack(ctci::jim::Stack<int>& stack) {
            // Sort a stack in-place. The only other structure we can use is a
            // temporary second stack.
            ctci::jim::Stack<int> tmpStack;

            while (!stack.isEmpty()) {
                int currentElement = stack.pop();
                while (!tmpStack.isEmpty() && tmpStack.peek() > currentElement) {
                    stack.push(tmpStack.pop());
                }
                tmpStack.push(currentElement);
            }

            while (!tmpStack.isEmpty())
            {
                stack.push(tmpStack.pop());
            }
        }

        int main(int argc, char** argv) {
            // Basic case where elements are already in-order.
            {
                ctci::jim::Stack<int> s;
                s.push(5);
                s.push(4);
                s.push(3);
                s.push(2);
                s.push(1);
                SortStack(s);
                if (s.toString() != "1,2,3,4,5") throw std::runtime_error("Test failed.");
            }

            // Elements are in reverse-order.
            {
                ctci::jim::Stack<int> s;
                s.push(1);
                s.push(2);
                s.push(3);
                s.push(4);
                s.push(5);
                SortStack(s);
                if (s.toString() != "1,2,3,4,5") throw std::runtime_error("Test failed.");
            }

            // Up down up down up down.
            {
                ctci::jim::Stack<int> s;
                s.push(1);
                s.push(4);
                s.push(2);
                s.push(5);
                s.push(3);
                s.push(6);
                SortStack(s);
                if (s.toString() != "1,2,3,4,5,6") throw std::runtime_error("Test failed.");
            }

            // Repeating values.
            {
                ctci::jim::Stack<int> s;
                s.push(1);
                s.push(1);
                s.push(1);
                s.push(1);
                s.push(1);
                SortStack(s);
                if (s.toString() != "1,1,1,1,1") throw std::runtime_error("Test failed.");
            }

            std::cout << "All tests passed.\n";
            return 0;
        }
    }
}

int main(int argc, char** argv) {
    return ctci::ch3::main(argc, argv);
}