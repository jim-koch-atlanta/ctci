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

        // An implementation of queue using two stacks. First in, first out.
        template <typename T>
        class QueueViaStacks {
            protected:
                ctci::jim::Stack<T> stack1;
                ctci::jim::Stack<T> stack2;

            public:
                QueueViaStacks() {
                }

                void add(T value) {
                    stack1.push(value);
                }

                T remove() {
                    if (isEmpty()) {
                        throw std::runtime_error("Stack is empty.");
                    }

                    if (!stack2.isEmpty()) {
                        return stack2.pop();
                    }

                    while (!stack1.isEmpty()) {
                        stack2.push(stack1.pop());                        
                    }

                    return stack2.pop();
                }

                T peek() {
                    if (isEmpty()) {
                        throw std::runtime_error("Stack is empty.");
                    }

                    if (!stack2.isEmpty()) {
                        return stack2.peek();
                    }

                    while (!stack1.isEmpty()) {
                        stack2.push(stack1.pop());                        
                    }

                    return stack2.peek();
                }

                bool isEmpty() {
                    return (stack1.isEmpty() && stack2.isEmpty());
                }

                std::string toString() {
                    std::string result;
                    
                    if (!stack2.isEmpty()) {
                        result = stack2.toString() + ",";
                    };

                    int count = 0;
                    while (!stack1.isEmpty()) {
                        stack2.push(stack1.pop());
                        count++;
                    }

                    while (count > 0) {
                        T value = stack2.pop();
                        result += std::to_string(value) + ",";
                        stack1.push(value);
                        count--;
                    }

                    if (result.length() == 0) {
                        return result;
                    }
                    
                    return result.substr(0, result.length() - 1);
                }
        };

        int main(int argc, char** argv) {
            // Basic FIFO order.
            {
                QueueViaStacks<int> q;
                q.add(1); q.add(2); q.add(3);
                if (q.remove() != 1) throw std::runtime_error("Test failed.");
                if (q.remove() != 2) throw std::runtime_error("Test failed.");
                if (q.remove() != 3) throw std::runtime_error("Test failed.");
            }

            // Interleaved add and remove.
            {
                QueueViaStacks<int> q;
                q.add(1); q.add(2);
                if (q.remove() != 1) throw std::runtime_error("Test failed.");
                q.add(3);
                if (q.remove() != 2) throw std::runtime_error("Test failed.");
                if (q.remove() != 3) throw std::runtime_error("Test failed.");
            }

            // peek doesn't remove.
            {
                QueueViaStacks<int> q;
                q.add(1); q.add(2);
                if (q.peek() != 1)   throw std::runtime_error("Test failed.");
                if (q.remove() != 1) throw std::runtime_error("Test failed.");
            }

            // isEmpty.
            {
                QueueViaStacks<int> q;
                if (!q.isEmpty()) throw std::runtime_error("Test failed.");
                q.add(1);
                if (q.isEmpty())  throw std::runtime_error("Test failed.");
                q.remove();
                if (!q.isEmpty()) throw std::runtime_error("Test failed.");
            }

            // toString — basic display.
            {
                QueueViaStacks<int> q;
                q.add(1); q.add(2); q.add(3);
                if (q.toString() != "1,2,3") throw std::runtime_error("Test failed.");
            }

            // toString — doesn't corrupt state.
            {
                QueueViaStacks<int> q;
                q.add(1); q.add(2); q.add(3);
                q.toString();
                if (q.remove() != 1) throw std::runtime_error("Test failed.");
                if (q.remove() != 2) throw std::runtime_error("Test failed.");
                if (q.remove() != 3) throw std::runtime_error("Test failed.");
            }

            std::cout << "All tests passed.\n";
            return 0;
        }
    }
}

int main(int argc, char** argv) {
    return ctci::ch3::main(argc, argv);
}