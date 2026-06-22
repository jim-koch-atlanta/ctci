namespace ctci::jim {

template <typename T>
StackNode<T>::StackNode(T value) {
    this->next = nullptr;
    this->value = value;
}

template <typename T>
Stack<T>::Stack() {
}

template <typename T>
void Stack<T>::push(T value) {
    StackNode<T>* newFirst = new StackNode<T>(value);
    newFirst->next = first;
    first = newFirst;
}

template <typename T>
T Stack<T>::pop() {
    if (first == nullptr)
        throw std::runtime_error("Stack is empty.");

    T value = first->value;
    StackNode<T>* tmp = first;
    first = first->next;
    delete tmp;
    return value;
}

template <typename T>
T Stack<T>::peek() {
    if (first == nullptr)
        throw std::runtime_error("Stack is empty.");

    return first->value;
}

template <typename T>
bool Stack<T>::isEmpty() {
    return (first == nullptr);
}

template <typename T>
std::string Stack<T>::toString() {
    std::string output;
    StackNode<T>* current = first;
    while (current != nullptr) {
        output = output + std::to_string(current->value) + ",";
        current = current->next;
    }
    if (!output.empty())
        output.pop_back();
    return output;
}

}
