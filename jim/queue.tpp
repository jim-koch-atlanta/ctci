namespace ctci::jim {

template <typename T>
QueueNode<T>::QueueNode(T value) {
    this->next = nullptr;
    this->value = value;
}

template <typename T>
Queue<T>::Queue() {
}

template <typename T>
void Queue<T>::add(T value) {
    QueueNode<T>* newLast = new QueueNode<T>(value);
    if (last != nullptr) {
        last->next = newLast;
    }

    last = newLast;

    if (first == nullptr) {
        first = last;
    }
}

template <typename T>
T Queue<T>::remove() {
    if (first == nullptr)
        throw std::runtime_error("Queue is empty.");

    T value = first->value;
    QueueNode<T>* tmp = first;
    first = first->next;

    if (first == nullptr) {
        last = nullptr;
    }

    delete tmp;
    return value;
}

template <typename T>
T Queue<T>::peek() {
    if (first == nullptr)
        throw std::runtime_error("Queue is empty.");

    return first->value;
}

template <typename T>
bool Queue<T>::isEmpty() {
    return (first == nullptr);
}

template <typename T>
std::string Queue<T>::toString() {
    std::string output;
    QueueNode<T>* current = first;
    while (current != nullptr) {
        output = output + std::to_string(current->value) + ",";
        current = current->next;
    }
    if (!output.empty())
        output.pop_back();
    return output;
}

}
