#include "Node.hpp"

template <typename T>
inline Node<T>::Node(const T& element): element{ element } {}

template<typename T>
inline void Node<T>::connectPrevious(Node<T>* node) {
    previous = node;
}

template<typename T>
inline void Node<T>::connectNext(Node<T>* node) {
    next = node;
}

template<typename T>
inline void Node<T>::interconnectPrevious(Node<T>* node) {
    previous = node;
    node->next = this;
}

template<typename T>
inline void Node<T>::interconnectNext(Node<T>* node) {
    next = node;
    node->previous = this;
}

template <typename T>
inline Node<T>::~Node() {
    if (previous != nullptr)
        previous = nullptr;

    if (next != nullptr)
        next = nullptr;
}