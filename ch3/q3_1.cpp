#include <iostream>
#include <optional>
#include <stdexcept>
#include <string>
#include <vector>

namespace ctci {

namespace ch3 {

template <typename T>
class StackNode {
    public:
        int indexOfNext;
        std::optional<T> value;

        StackNode(T value) {
            this->value = value;
            indexOfNext = -1;
        }

        StackNode() {
            this->value = std::nullopt;
        }
};

template <typename T>
class StacksAsArray {
    protected:
        // The array that will store the elements of multiple stacks.
        std::vector<StackNode<T>> array;

        // The number of stacks represented by the array.
        int numberOfStacks;

        // List of free nodes (nodes that were previously used, and have since been pop'd).
        std::vector<int> freeList;

        // First available element in the array.
        int firstAvailable;

        // Number of available elements in array.
        int availableElements;

    public:
        StacksAsArray(int numberOfStacks) {
            array.resize(100);

            for (int i = 0; i < numberOfStacks; i++) {
                StackNode<T> node;
                node.indexOfNext = -1;
                array[i] = node;
            }

            this->numberOfStacks = numberOfStacks;
            this->firstAvailable = numberOfStacks;
            this->availableElements = 100 - numberOfStacks;
        }

        void push(int stackNumber, T value) {
            int indexOfFirst = array[stackNumber].indexOfNext;
            StackNode<T> node(value);
            node.indexOfNext = indexOfFirst;

            if (freeList.empty()) {
                if (availableElements == 0) {
                    int currentSize = array.size();
                    array.resize(array.size() * 2);
                    availableElements  = currentSize;
                }
                array[firstAvailable] = node;

                // Update "pointer" to first element.
                array[stackNumber].indexOfNext = firstAvailable;

                firstAvailable++;
            } else {
                int index = freeList.back();
                freeList.pop_back();
                array[index] = node;

                // Update "pointer" to first element.
                array[stackNumber].indexOfNext = index;
            }
        }

        T pop(int stackNumber) {
            if (this->isEmpty(stackNumber)) {
                throw std::runtime_error("Stack is empty.");
            }

            int indexOfFirst = array[stackNumber].indexOfNext;
            StackNode<T> node = array[indexOfFirst];

            freeList.push_back(indexOfFirst);
            array[stackNumber].indexOfNext = node.indexOfNext;

            return node.value.value();
        }

        T peek(int stackNumber) {
            if (this->isEmpty(stackNumber)) {
                throw std::runtime_error("Stack is empty.");
            }

            int indexOfFirst = array[stackNumber].indexOfNext;
            StackNode<T> node = array[indexOfFirst];
            return node.value.value();
        }

        bool isEmpty(int stackNumber) {
            return (array[stackNumber].indexOfNext == -1);
        }

        std::string toString(int stackNumber) {
            std::string output;
            int currentIndex = array[stackNumber].indexOfNext;
            while (currentIndex != -1) {
                StackNode<T> currentNode = array[currentIndex];
                output = output + std::to_string(currentNode.value.value()) + ",";
                currentIndex = currentNode.indexOfNext;
            }

            if (!output.empty())
                output.pop_back();

            return output;
        }
};

int main(int argc, char** argv) {
    // Push to three separate stacks and verify contents.
    {
        StacksAsArray<int> stacks(3);
        stacks.push(0, 1);
        stacks.push(0, 2);
        stacks.push(0, 3);
        stacks.push(1, 4);
        stacks.push(1, 5);
        stacks.push(2, 6);

        if (stacks.toString(0) != "3,2,1") throw std::runtime_error("Test failed.");
        if (stacks.toString(1) != "5,4")   throw std::runtime_error("Test failed.");
        if (stacks.toString(2) != "6")     throw std::runtime_error("Test failed.");
    }

    // Pop from a stack and verify the free list is reused.
    {
        StacksAsArray<int> stacks(3);
        stacks.push(0, 1);
        stacks.push(0, 2);
        stacks.push(0, 3);

        if (stacks.pop(0) != 3) throw std::runtime_error("Test failed.");
        if (stacks.toString(0) != "2,1") throw std::runtime_error("Test failed.");

        stacks.push(0, 99);
        if (stacks.toString(0) != "99,2,1") throw std::runtime_error("Test failed.");
    }

    // isEmpty
    {
        StacksAsArray<int> stacks(2);
        if (!stacks.isEmpty(0)) throw std::runtime_error("Test failed.");
        stacks.push(0, 42);
        if (stacks.isEmpty(0))  throw std::runtime_error("Test failed.");
        stacks.pop(0);
        if (!stacks.isEmpty(0)) throw std::runtime_error("Test failed.");
    }

    // Interleaved pushes across stacks, then pop all from one.
    {
        StacksAsArray<int> stacks(3);
        stacks.push(0, 10);
        stacks.push(1, 20);
        stacks.push(0, 11);
        stacks.push(2, 30);
        stacks.push(0, 12);

        if (stacks.pop(0) != 12) throw std::runtime_error("Test failed.");
        if (stacks.pop(0) != 11) throw std::runtime_error("Test failed.");
        if (stacks.pop(0) != 10) throw std::runtime_error("Test failed.");
        if (!stacks.isEmpty(0))  throw std::runtime_error("Test failed.");

        if (stacks.peek(1) != 20) throw std::runtime_error("Test failed.");
        if (stacks.peek(2) != 30) throw std::runtime_error("Test failed.");
    }

    std::cout << "All tests passed.\n";
    return 0;
}

}
}

int main(int argc, char** argv) {
    return ctci::ch3::main(argc, argv);
}