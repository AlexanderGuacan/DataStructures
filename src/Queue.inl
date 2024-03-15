#include "Queue.hpp"
#include <iostream>

template <typename T>
inline Queue<T>::Queue(std::initializer_list<T> list) {
    for (const T& element : list)
        enqueue(element);
}

template<typename T>
inline Queue<T>::Queue(const Queue& queue) {
    const Node<T>* iterator{ queue.front };

    while (iterator != nullptr) {
        enqueue(iterator->data);
        iterator = iterator->nextAdjacentNode;
    }
}

template<typename T>
inline int Queue<T>::getLength() {
    return length;
}

template<typename T>
inline const T& Queue<T>::getFront() const {
    return front;
}

template<typename T>
inline void Queue<T>::enqueue(const T& element) {
    Node<T>* node{ new Node{ element } };

    if (isEmpty()) {
        front = node;
    } else {
        back->nextAdjacentNode = node;
    }

    back = node;
    ++length;
}

template<typename T>
inline T Queue<T>::dequeue() {
    if (isEmpty())
        throw "Empty collection exception";

    T dequeueElement = front->data;
    Node<T>* dequeueNode = front;

    front = front->nextAdjacentNode;

    delete dequeueNode;
    dequeueNode = nullptr;

    --length;

    if (isEmpty())
        back = nullptr;

    return dequeueElement;
}

template<typename T>
inline bool Queue<T>::isEmpty() const {
    return !length;
}

template<typename T>
inline Queue<T>::~Queue() {
    while (!isEmpty())
        dequeue();
}