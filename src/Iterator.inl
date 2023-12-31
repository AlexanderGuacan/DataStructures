#include "Iterator.hpp"

template <typename T>
inline Iterator<T>::Iterator(TwoWayNode<T>* begin): mCursor{ begin } {
}

template <typename T>
inline Iterator<T>::Iterator(const Iterator& iterator): mCursor{ iterator.mCursor } {
}

template <typename T>
inline const T& Iterator<T>::get() {
    if (mCursor == nullptr)
        throw "Null pointer exception";

    return mCursor->getElement();
}

template <typename T>
inline void Iterator<T>::operator++() {
    mCursor = mCursor->getNextNode();
}

template <typename T>
inline void Iterator<T>::operator--() {
    mCursor = mCursor->getPreviousNode();
}

template <typename T>
inline const T& Iterator<T>::operator*() {
    return get();
}

template <typename T>
inline Iterator<T>& Iterator<T>::operator=(const Iterator& rhs) {
    if (this == &rhs)
        return *this;

    mCursor = rhs.mCursor;

    return *this;
}

template <typename T>
inline bool operator==(const Iterator<T>& lhs, const Iterator<T>& rhs) {
    return lhs.mCursor == rhs.mCursor;
}

template <typename T>
inline bool operator!=(const Iterator<T>& lhs, const Iterator<T>& rhs) {
    return !(lhs.mCursor == rhs.mCursor);
}

template <typename T>
inline Iterator<T> operator-(const Iterator<T>& lhs, ssize_t rhs) {
    TwoWayNode<T>* cursor{ lhs.mCursor };

    for (ssize_t i{}; i < rhs; ++i)
        cursor = cursor->getPreviousNode();

    return Iterator<T>{ cursor };
}

template <typename T>
inline Iterator<T> operator+(const Iterator<T>& lhs, ssize_t rhs) {
    TwoWayNode<T>* cursor{ lhs.mCursor };

    for (ssize_t i{}; i < rhs; ++i)
        cursor = cursor->getNextNode();

    return Iterator<T>{ cursor };
}

template <typename T>
inline void Iterator<T>::set(const T& element) const {
    if (mCursor == nullptr)
        return;

    mCursor->setElement(element);
}

template <typename T>
inline Iterator<T>::~Iterator() {
    mCursor = nullptr;
}