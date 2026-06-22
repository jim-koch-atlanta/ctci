#include <iostream>
#include <stdexcept>
#include <string>

namespace ctci {

namespace ch3 {

class StackNodeWithMin {
    public:
        StackNodeWithMin* next;
        int value;

        // Null if this instance was never a minimum. Otherwise points to the
        // element with the next-smallest value.
        StackNodeWithMin* nextSmallest;

        StackNodeWithMin(int value) {
            this->next = nullptr;
            this->nextSmallest = nullptr;
            this->value = value;
        }
};

class StackWithMin {
    protected:
        StackNodeWithMin* first = nullptr;
        StackNodeWithMin* smallest = nullptr;

    public:
        StackWithMin() {
        }

        void push(int value) {
            StackNodeWithMin* newFirst = new StackNodeWithMin(value);

            // Standard push.
            newFirst->next = first;
            first = newFirst;

            if (smallest == nullptr) {
                smallest = newFirst;
            } else if (value < this->min()) {
                newFirst->nextSmallest = smallest;
                smallest = newFirst;
            }
        }

        int pop() {
            if (first == nullptr)
                throw std::runtime_error("Stack is empty.");

            int value = first->value;
            StackNodeWithMin* tmp = first;
            first = first->next;

            if (smallest == tmp) {
                smallest = smallest->nextSmallest;
            }

            delete tmp;
            return value;
        }

        int peek() {
        if (first == nullptr)
            throw std::runtime_error("Stack is empty.");

        return first->value;
        }

        int min() {
            if (first == nullptr) {
                throw std::runtime_error("Stack is empty.");
            }

            return smallest->value;
        }

        bool isEmpty() {
            return (first == nullptr);
        }

        std::string toString() {
            std::string output;
            StackNodeWithMin* current = first;
            while (current != nullptr) {
                output = output + std::to_string(current->value) + ",";
                current = current->next;
            }
            if (!output.empty())
                output.pop_back();
            return output;
        }
};

int main(int argc, char** argv) {
    // Push in descending order — min updates every push.
    {
        ctci::ch3::StackWithMin s;
        s.push(5);
        if (s.min() != 5) throw std::runtime_error("Test failed.");
        s.push(3);
        if (s.min() != 3) throw std::runtime_error("Test failed.");
        s.push(1);
        if (s.min() != 1) throw std::runtime_error("Test failed.");
    }

    // Push in ascending order — min stays at the bottom.
    {
        ctci::ch3::StackWithMin s;
        s.push(1);
        s.push(3);
        s.push(5);
        if (s.min() != 1) throw std::runtime_error("Test failed.");
    }

    // Pop the minimum and verify min() updates correctly.
    {
        ctci::ch3::StackWithMin s;
        s.push(3);
        s.push(1);
        if (s.min() != 1) throw std::runtime_error("Test failed.");
        s.pop();
        if (s.min() != 3) throw std::runtime_error("Test failed.");
    }

    // Duplicate minimum values — min() stays correct after popping one.
    {
        ctci::ch3::StackWithMin s;
        s.push(5);
        s.push(3);
        s.push(3);
        if (s.min() != 3) throw std::runtime_error("Test failed.");
        s.pop();
        if (s.min() != 3) throw std::runtime_error("Test failed.");
        s.pop();
        if (s.min() != 5) throw std::runtime_error("Test failed.");
    }

    // Mixed pushes and pops.
    {
        ctci::ch3::StackWithMin s;
        s.push(4);
        s.push(2);
        s.push(6);
        if (s.min() != 2) throw std::runtime_error("Test failed.");
        s.pop(); // removes 6
        if (s.min() != 2) throw std::runtime_error("Test failed.");
        s.pop(); // removes 2
        if (s.min() != 4) throw std::runtime_error("Test failed.");
    }

    std::cout << "All tests passed.\n";
    return 0;
}

}
}

int main(int argc, char** argv) {
    return ctci::ch3::main(argc, argv);
}