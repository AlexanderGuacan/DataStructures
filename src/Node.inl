#include "Node.hpp"

template <typename T>
inline Node<T>::Node(const T& element): element{ element } {}

template<typename T>
inline void Node<T>::interconnectWith(Node<T>* next) {
    nextNode = next;
    next->previousNode = this;
}

template <typename T>
inline Node<T>::~Node() {
    if (previousNode != nullptr)
        previousNode = nullptr;

    if (nextNode != nullptr)
        nextNode = nullptr;
}