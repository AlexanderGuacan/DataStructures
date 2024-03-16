#include "Queue.hpp"
#include <iostream>

template<typename T>
inline void Queue<T>::copy(const Queue& queue) {
    const Node<T>* iterator{ queue.head };

    while (iterator != nullptr) {
        enqueue(iterator->element);
        iterator = iterator->nextNode;
    }
}

template <typename T>
inline Queue<T>::Queue(std::initializer_list<T> list) {
    for (const T& element : list)
        enqueue(element);
}

template<typename T>
inline Queue<T>::Queue(const Queue& queue) {
    copy(queue);
}

template<typename T>
inline int Queue<T>::getLength() {
    return length;
}

template<typename T>
inline const T& Queue<T>::getHead() const {
    return head->element;
}

template<typename T>
inline void Queue<T>::enqueue(const T& element) {
    Node<T>* node{ new Node{ element } };

    if (isEmpty())
        head = node;
    else
        tail->nextNode = node;

    tail = node;
    ++length;
}

template<typename T>
inline T Queue<T>::dequeue() {
    if (isEmpty())
        throw "Empty collection exception";

    T elementDequeued = head->element;
    Node<T>* nodeDequeued = head;

    head = head->nextNode;
    --length;

    delete nodeDequeued;
    nodeDequeued = nullptr;

    if (isEmpty())
        tail = nullptr;

    return elementDequeued;
}

template<typename T>
inline bool Queue<T>::isEmpty() const {
    return !length;
}

template<typename T>
inline void Queue<T>::clear() {
    while (!isEmpty())
        dequeue();
}

template<typename T>
inline Queue<T>& Queue<T>::operator=(const Queue& rightHandSideOperator) {
    if (this == &rightHandSideOperator)
        return *this;

    clear();
    copy(rightHandSideOperator);

    return *this;
}

template<typename T>
inline bool operator==(const Queue<T>& leftHandSideOperator, const Queue<T>& rightHandSideOperator) {
    if (&leftHandSideOperator == &rightHandSideOperator)
        return true;

    if (leftHandSideOperator.length != rightHandSideOperator.length)
        return false;

    Node<T>* iteratorLeftOperator{ leftHandSideOperator.top };
    Node<T>* iteratorRightOperator{ rightHandSideOperator.top };

    while (iteratorLeftOperator != nullptr) {
        if (iteratorLeftOperator->element != iteratorRightOperator->element)
            return false;

        iteratorLeftOperator = iteratorLeftOperator->previousNode;
        iteratorRightOperator = iteratorRightOperator->previousNode;
    }

    return true;
}

template<typename T>
inline bool operator!=(const Queue<T>& leftHandSideOperator, const Queue<T>& rightHandSideOperator) {
    return !(leftHandSideOperator == rightHandSideOperator);
}

template<typename T>
inline Queue<T>::~Queue() {
    clear();
}