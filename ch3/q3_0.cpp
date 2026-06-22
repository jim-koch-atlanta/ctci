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

       int main(int argc, char** argv) {
            // Stack test.
            ctci::jim::Stack<int> stack;
            std::cout << "(Empty) stack contents: " << stack.toString() << std::endl;
            stack.push(1);
            stack.push(2);
            stack.push(3);
            stack.push(4);
            stack.push(5);
            stack.push(6);

            std::cout << "Stack contents: " << stack.toString() << std::endl;

            // Queue test.
            ctci::jim::Queue<int> queue;
            std::cout << "(Empty) queue contents: " << queue.toString() << std::endl;
            queue.add(1);
            queue.add(2);
            queue.add(3);
            queue.add(4);
            queue.add(5);
            queue.add(6);

            std::cout << "Queue contents: " << queue.toString() << std::endl;

            return 0;
        }
    }
}

int main(int argc, char** argv) {
    return ctci::ch3::main(argc, argv);
}