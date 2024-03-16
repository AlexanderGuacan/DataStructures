#include "Node.hpp"

template <typename T>
inline Node<T>::Node(const T& initialElement): element{ initialElement } {}

template <typename T>
inline Node<T>::~Node() {
    if (previousNode != nullptr)
        previousNode = nullptr;

    if (nextNode != nullptr)
        nextNode = nullptr;
}