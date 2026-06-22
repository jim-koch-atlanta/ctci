#include <stdexcept>
#include <string>

namespace ctci {
    namespace jim {
        template <typename T>
        class QueueNode {

        public:
            QueueNode* next;
            T value;

            QueueNode(T value);
        };

        template <typename T>
        class Queue {

        protected:
            QueueNode<T>* first = nullptr;
            QueueNode<T>* last = nullptr;

        public:
            Queue();

            void add(T value);

            T remove();

            T peek();

            bool isEmpty();

            std::string toString();
        };
   }
}

#include "queue.tpp"