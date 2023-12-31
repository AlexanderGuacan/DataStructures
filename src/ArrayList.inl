#include "ArrayList.hpp"

template <typename T>
inline void ArrayList<T>::resize(ssize_t capacity) {
    if (capacity <= mLength)
        throw "Invalid resize. Capacity lower than length";

    mCapacity = capacity;
    T* arrayResized{ new T[mCapacity]{} };

    for (ssize_t i{}; i < mLength; ++i)
        arrayResized[i] = mArray[i];

    delete[] mArray;
    mArray = arrayResized;
}

template <typename T>
inline ArrayList<T>::ArrayList(ssize_t capacity): mCapacity{ capacity }, mArray{ new T[capacity]{} } {
}

template <typename T>
inline ArrayList<T>::ArrayList(std::initializer_list<T> elements) : ArrayList( elements.size() + (elements.size() * .25) ) {
    for (const auto& element : elements)
        add(element);
}

template <typename T>
inline ArrayList<T>::ArrayList(const ArrayList& elements): ArrayList( elements.mCapacity ) {
    add(elements);
}

template <typename T>
inline void ArrayList<T>::add(const T& element) {
    mArray[mLength] = element;
    ++mLength;

    if (mLength == mCapacity) {
        if (static_cast<int>(mCapacity * .25) <= 0)
            resize(10);
        else
            resize(mCapacity + (mCapacity * .25));
    }
}

template <typename T>
inline void ArrayList<T>::add(const ArrayList& elements) {
    for (ssize_t i{}; i < elements.mLength; ++i)
        add(elements.mArray[i]);
}

template <typename T>
inline T* ArrayList<T>::begin() const {
    return mArray;
}

template <typename T>
inline ssize_t ArrayList<T>::capacity() const {
    return mCapacity;
}

template <typename T>
inline void ArrayList<T>::clear() {
    if (isEmpty())
        return;

    constexpr ssize_t defaultCapacity{ 10 };
    mCapacity = defaultCapacity;
    mLength = 0;

    delete[] mArray;
    mArray = new T[mCapacity]{};
}

template <typename T>
inline bool ArrayList<T>::contain(const T& element) const {
    for (ssize_t i{}; i < mLength; ++i) {
        if (mArray[i] == element)
            return true;
    }

    return false;
}

template <typename T>
inline T* ArrayList<T>::end() const {
    return mArray + mLength;
}

template <typename T>
inline const T& ArrayList<T>::get(ssize_t index) const {
    if (index >= mLength)
        throw "Index out of bounds exception";

    return mArray[index];
}

template <typename T>
inline ssize_t ArrayList<T>::indexOf(const T& element) const {
    for (ssize_t i{}; i < mLength; ++i) {
        if (element == mArray[i])
            return i;
    }

    return -1;
}

template <typename T>
inline bool ArrayList<T>::isEmpty() const {
    return mLength == 0;
}

template <typename T>
inline ssize_t ArrayList<T>::lastIndexOf(const T& element) const {
    for (ssize_t i{ mLength - 1 }; i >= 0; --i) {
        if (element == mArray[i])
            return i;
    }

    return -1;
}

template <typename T>
inline ssize_t ArrayList<T>::length() const {
    return mLength;
}

template <typename T>
inline T& ArrayList<T>::operator[](ssize_t index) {
    return mArray[index];
}

template <typename T>
inline const T& ArrayList<T>::operator[](ssize_t index) const {
    return mArray[index];
}

template <typename T>
inline ArrayList<T>& ArrayList<T>::operator=(const ArrayList& rhs) {
    if (this == &rhs)
        return *this;

    delete[] mArray;
    mArray = new T[rhs.mCapacity];

    for (ssize_t i{}; i < rhs.mLength; ++i)
        mArray[i] = rhs.mArray[i];

    mCapacity = rhs.mCapacity;
    mLength = rhs.mLength;

    return *this;
}

template <typename T>
inline ArrayList<T> operator+(const ArrayList<T>& lhs, const ArrayList<T>& rhs) {
    ArrayList<T> combination( lhs.mCapacity + rhs.mCapacity );

    combination.add(lhs);
    combination.add(rhs);

    return combination;
}

template <typename T>
inline ArrayList<T>& ArrayList<T>::operator+=(const ArrayList& rhs) {
    add(rhs);
    return *this;
}

template <typename T>
inline bool operator==(const ArrayList<T>& lhs, const ArrayList<T>& rhs) {
    if (lhs.mLength != rhs.mLength)
        return false;

    if (&lhs == &rhs)
        return true;

    for (ssize_t i{}; i < lhs.mLength; ++i) {
        if (lhs.mArray[i] != rhs.mArray[i])
            return false;
    }

    return true;
}

template <typename T>
inline bool operator!=(const ArrayList<T>& lhs, const ArrayList<T>& rhs) {
    return !(lhs == rhs);
}

template <typename T>
inline const T& ArrayList<T>::peek() const {
    return mArray[mLength - 1];
}

template <typename T>
inline T ArrayList<T>::pop() {
    if (isEmpty())
        throw "Empty list exception";

    T lastElement{ mArray[mLength - 1] };
    --mLength;

    if (mLength < mCapacity * .5)
        resize(mCapacity * .75);

    return lastElement;
}

template <typename T>
inline T ArrayList<T>::pull() {
    if (isEmpty())
        throw "Empty list exception";

    T* arrayResized{};
    T firstElement{ mArray[0] };

    if (mLength < mCapacity * .5) {
        mCapacity = mCapacity * .75;
        arrayResized = new T[mCapacity];

        for (ssize_t i{}; i < mLength; ++i)
            arrayResized[i] = mArray[i + 1];

        delete[] mArray;
        mArray = arrayResized;
    } else {
        for (ssize_t i{}; i < mLength; ++i)
            mArray[i] = mArray[i + 1];
    }

    --mLength;

    return firstElement;
}

template <typename T>
inline void ArrayList<T>::push(const T& element) {
    for (ssize_t i{ mLength }; i >= 0; --i)
        mArray[i] = mArray[i - 1];

    ++mLength;

    if (mLength == mCapacity) {
        if (static_cast<int>(mCapacity * .25) <= 0)
            resize(10);
        else
            resize(mCapacity + (mCapacity * .25));
    }
}

template <typename T>
inline T ArrayList<T>::remove(ssize_t index) {
    if (index >= mLength)
        throw "Index out of bounds exception";

    if (index == 0)
        return pull();

    if (index == mLength - 1)
        return pop();


    T* arrayResized{};
    T element{ mArray[index] };

    if (mLength < mCapacity * .5) {
        mCapacity = mCapacity * .75;
        arrayResized = new T[mCapacity];

        ssize_t j{};
        for (ssize_t i{}; i < mLength; ++i) {
            if (i == index)
                continue;

            arrayResized[j] = mArray[i];
            ++j;
        }

        delete[] mArray;
        mArray = arrayResized;
    } else {
        for (ssize_t i{ index }; i < mLength; ++i)
            mArray[i] = mArray[i + 1];
    }

    --mLength;
    return element;
}

template <typename T>
inline void ArrayList<T>::set(ssize_t index, const T& element) {
    if (index >= mLength)
        throw "Index out of bounds exception";

    mArray[index] = element;
}

template <typename T>
inline const T& ArrayList<T>::top() const {
    return mArray[0];
}

template <typename T>
inline ArrayList<T>::~ArrayList() {
    delete[] mArray;
    mArray = nullptr;
}