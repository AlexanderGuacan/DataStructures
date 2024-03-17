#include "Stack.hpp"

template<typename T>
inline void Stack<T>::copy(const Stack& stack) {
    Node<T>* iterator{ stack.top };
    Stack<T> reverseList{};

    while (iterator != nullptr) {
        reverseList.push(iterator->element);
        iterator = iterator->previous;
    }

    while (!reverseList.isEmpty())
        push(reverseList.pop());
}

template<typename T>
inline Stack<T>::Stack(std::initializer_list<T> list) {
    for (const auto& element : list)
        push(element);
}

template<typename T>
inline Stack<T>::Stack(const Stack& stack) {
    copy(stack);
}

template<typename T>
inline int Stack<T>::getLength() const {
    return length;
}

template<typename T>
inline const T& Stack<T>::getTop() const {
    return top->element;
}

template<typename T>
inline void Stack<T>::push(const T& element) {
    Node<T>* newNode{ new Node{ element } };

    if (!isEmpty())
        newNode->connectPrevious(top);

    top = newNode;
    ++length;
}

template<typename T>
inline T Stack<T>::pop() {
    if (isEmpty())
        throw "Empty collection exception";

    T elementPopped = top->element;
    Node<T>* nodePopped = top;

    top = top->previous;
    --length;

    delete nodePopped;
    nodePopped = nullptr;

    return elementPopped;
}

template<typename T>
inline bool Stack<T>::isEmpty() const {
    return !length;
}

template<typename T>
inline void Stack<T>::clear() {
    while (!isEmpty())
        pop();
}

template<typename T>
inline Stack<T>& Stack<T>::operator=(const Stack& rightHandSideOperator) {
    if (this == &rightHandSideOperator)
        return *this;

    clear();
    copy(rightHandSideOperator);

    return *this;
}

template<typename T>
inline bool operator==(const Stack<T>& leftHandSideOperator, const Stack<T>& rightHandSideOperator) {
    if (&leftHandSideOperator == &rightHandSideOperator)
        return true;

    if (leftHandSideOperator.length != rightHandSideOperator.length)
        return false;

    Node<T>* iteratorLeftOperator{ leftHandSideOperator.top };
    Node<T>* iteratorRightOperator{ rightHandSideOperator.top };

    while (iteratorLeftOperator != nullptr) {
        if (iteratorLeftOperator->element != iteratorRightOperator->element)
            return false;

        iteratorLeftOperator = iteratorLeftOperator->previous;
        iteratorRightOperator = iteratorRightOperator->previous;
    }

    return true;
}

template<typename T>
inline bool operator!=(const Stack<T>& leftHandSideOperator, const Stack<T>& rightHandSideOperator) {
    return !(leftHandSideOperator == rightHandSideOperator);
}

template<typename T>
inline Stack<T>::~Stack() {
    clear();
}
