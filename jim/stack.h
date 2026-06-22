#include <stdexcept>
#include <string>

namespace ctci {
    namespace jim {
        template <typename T>
        class StackNode {

        public:
            StackNode* next;
            T value;

            StackNode(T value);
        };

        template <typename T>
        class Stack {

        protected:
            StackNode<T>* first = nullptr;

        public:
            Stack();

            void push(T value);

            T pop();

            T peek();

            bool isEmpty();

            std::string toString();
        };
   }
}

#include "stack.tpp"