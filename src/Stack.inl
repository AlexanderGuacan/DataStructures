#include "Stack.hpp"

template <typename T>
inline void Stack<T>::copy(const Stack& elements) {
    mHead = new OneWayNode{ elements.mHead->getElement() };
    const OneWayNode<T>* iterator{ elements.mHead->getNextNode() };

    OneWayNode<T>* lastNode{ mHead };

    while (iterator != nullptr) {
        lastNode->setNextNode(new OneWayNode{ iterator->getElement() });
        lastNode = lastNode->getNextNode();
        iterator = iterator->getNextNode();
    }

    lastNode = nullptr;
    mLength = elements.mLength;
}

template <typename T>
inline Stack<T>::Stack(std::initializer_list<T> elements) {
    for (const auto& element : elements)
        push(element);
}

template <typename T>
inline Stack<T>::Stack(const Stack& elements) {
    copy(elements);
}

template <typename T>
inline void Stack<T>::clear() {
    while (!isEmpty())
        pop();
}

template <typename T>
inline bool Stack<T>::isEmpty() const {
    return mLength <= 0;
}

template <typename T>
inline ssize_t Stack<T>::length() const {
    return mLength;
}

template <typename T>
inline Stack<T>& Stack<T>::operator=(const Stack& rhs) {
    if (&rhs == this)
        return *this;

    clear();
    copy(rhs);

    return *this;
}

template <typename T>
inline bool operator==(const Stack<T>& lhs, const Stack<T>& rhs) {
    if (lhs.mLength != rhs.mLength)
        return false;

    OneWayNode<T>* iteratorLeft{ lhs.mHead };
    OneWayNode<T>* iteratorRight{ rhs.mHead };

    while (iteratorLeft != nullptr) {
        if (iteratorLeft->getElement() != iteratorRight->getElement())
            return false;

        iteratorLeft = iteratorLeft->getNextNode();
        iteratorRight = iteratorRight->getNextNode();
    }

    return true;
}

template <typename T>
inline bool operator!=(const Stack<T>& lhs, const Stack<T>& rhs) {
    return !(lhs == rhs);
}

template <typename T>
inline const T& Stack<T>::peek() const {
    return mHead->getElement();
}

template <typename T>
inline T Stack<T>::pop() {
    if (isEmpty())
        throw "Empty stack exception";

    T lastElementInserted{ mHead->getElement() };

    const OneWayNode<T>* lastNodeInserted{ mHead };
    mHead = mHead->getNextNode();

    delete lastNodeInserted;
    lastNodeInserted = nullptr;

    --mLength;

    return lastElementInserted;
}

template <typename T>
inline void Stack<T>::push(const T& element) {
    OneWayNode<T>* next{ new OneWayNode{ element } };

    if (!isEmpty())
        next->setNextNode(mHead);

    mHead = next;

    ++mLength;
}

template <typename T>
inline Stack<T>::~Stack() {
    clear();
}