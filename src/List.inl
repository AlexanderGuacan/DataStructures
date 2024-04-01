#include "List.hpp"

template<typename T>
inline bool List<T>::isOutOfBounded(int index) {
    return index < 0 || index >= length;
}

template<typename T>
inline int List<T>::getLength() const {
    return length;
}

template<typename T>
inline bool List<T>::isEmpty() const {
    return !length;
}
