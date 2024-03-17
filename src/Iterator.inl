#include "Iterator.hpp"

template<typename T>
inline void Iterator<T>::scrollCursorForward(int positions) {
    for (int i{}; i < positions; ++i)
        cursor = cursor->next;
}

template<typename T>
inline void Iterator<T>::scrollCursorBackward(int positions) {
    for (int i{}; i < positions; ++i)
        cursor = cursor->previous;
}

template<typename T>
inline Iterator<T>::Iterator(Node<T>* begin): cursor{ begin } {}

template<typename T>
inline T& Iterator<T>::currentElement() {
    return cursor->element;
}

template<typename T>
inline T& Iterator<T>::operator*() {
    return currentElement();
}

template<typename T>
inline Iterator<T>& Iterator<T>::operator++() {
    constexpr int nextNode{ 1 };
    scrollCursorForward(nextNode);
    return *this;
}

template<typename T>
inline Iterator<T>& Iterator<T>::operator--() {
    constexpr int previousNode{ 1 };
    scrollCursorBackward(previousNode);
    return *this;
}

template<typename T>
inline Iterator<T> Iterator<T>::operator++(int) {
    Iterator<T> iteratorBeforeScroll{ cursor };

    constexpr int nextNode{ 1 };
    scrollCursorForward(nextNode);

    return iteratorBeforeScroll;
}

template<typename T>
inline Iterator<T> Iterator<T>::operator--(int) {
    Iterator<T> iteratorBeforeScroll{ cursor };

    constexpr int previousNode{ 1 };
    scrollCursorBackward(previousNode);

    return iteratorBeforeScroll;
}

template<typename T>
inline Iterator<T>& Iterator<T>::operator+=(int positions) {
    scrollCursorForward(positions);
    return *this;
}

template<typename T>
inline Iterator<T>& Iterator<T>::operator-=(int positions) {
    scrollCursorBackward(positions);
    return *this;
}

template<typename T>
inline bool operator==(const Iterator<T>& lhs, const Iterator<T>& rhs) {
    return lhs.cursor == rhs.cursor;
}

template<typename T>
inline bool operator!=(const Iterator<T>& lhs, const Iterator<T>& rhs) {
    return !(lhs == rhs);
}

template<typename T>
inline Iterator<T> operator+(Iterator<T> iterator, int positions) {
    Iterator<T> iteratorScrolledForward{ iterator.cursor };
    iteratorScrolledForward.scrollCursorForward(positions);
    return iteratorScrolledForward;
}

template<typename T>
inline Iterator<T> operator-(Iterator<T> iterator, int positions) {
    Iterator<T> iteratorScrolledBackward{ iterator.cursor };
    iteratorScrolledBackward.scrollCursorBackward(positions);
    return iteratorScrolledBackward;
}

template<typename T>
inline Iterator<T>::~Iterator() {
    if (!cursor)
        return;

    cursor = nullptr;
}