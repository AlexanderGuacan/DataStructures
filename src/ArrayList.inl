#include "ArrayList.hpp"

template <typename T>
void ArrayList<T>::copy(const ArrayList& list) {
    for (const T& element : list)
        addAtEnd(element);
}

template <typename T>
bool ArrayList<T>::isOutOfBounded(int index) {
    return index < 0 || index >= length;
}

template<typename T>
inline bool ArrayList<T>::isFull() {
    return length >= capacity;
}

template<typename T>
inline bool ArrayList<T>::hasUnusedIncrease() {
    constexpr int extraIncrease = increase + increase;
    return capacity - length == extraIncrease;
}

template<typename T>
inline void ArrayList<T>::increaseArrayCapacity() {
    capacity += increase;
    resizeArray();
}

template<typename T>
inline void ArrayList<T>::decreaseArrayCapacity() {
    capacity -= increase;
    resizeArray();
}

template<typename T>
inline void ArrayList<T>::resizeArray() {
    T* resizedArray{ new T[capacity]{} };

    for (int i{}; i < length; ++i)
        resizedArray[i] = array[i];

    delete[] array;
    array = resizedArray;
    resizedArray = nullptr;
}

template<typename T>
inline ArrayList<T>::ArrayList(int capacity, int increase): defaultCapacity{ capacity }, capacity{ capacity }, increase{ increase }, array{ new T[capacity]{} } {}

template<typename T>
inline ArrayList<T>::ArrayList(std::initializer_list<T> list) : ArrayList(list.size()) {
    if (!list.size())
        throw "Empty initializer list exception";

    for (const T& element : list)
        addAtEnd(element);
}

template<typename T>
inline ArrayList<T>::ArrayList(const ArrayList& list): ArrayList(list.capacity, list.increase) {
    copy(list);
}

template<typename T>
inline int ArrayList<T>::getLength() const {
    return length;
}

template<typename T>
inline int ArrayList<T>::getCapacity() const {
    return capacity;
}

template<typename T>
inline void ArrayList<T>::setIncrease(int newIncrease) {
    increase = newIncrease;
}

template<typename T>
inline bool ArrayList<T>::isEmpty() const {
    return !length;
}

template<typename T>
inline void ArrayList<T>::clear() {
    capacity = defaultCapacity;
    length = 0;

    delete[] array;
    array = new T[capacity]{};
}

template<typename T>
inline void ArrayList<T>::addAtBegin(const T& element) {
    for (int currentPosition = length; currentPosition > 0; --currentPosition) {
        int leftSidePosition = currentPosition - 1;
        array[currentPosition] = array[leftSidePosition];
    }

    int begin{};
    array[begin] = element;
    ++length;

    if (isFull())
        increaseArrayCapacity();
}

template<typename T>
inline void ArrayList<T>::addAtEnd(const T& element) {
    array[length] = element;
    ++length;

    if (isFull())
        increaseArrayCapacity();
}

template<typename T>
inline void ArrayList<T>::addToIndex(const T& element, int index) {
    if (isOutOfBounded(index))
        throw "Index out of bounded exception";

    for (int currentPosition = length - 1; currentPosition >= index; --currentPosition) {
        int rightSidePosition = currentPosition + 1;
        array[rightSidePosition] = array[currentPosition];
    }

    array[index] = element;
    ++length;

    if (isFull())
        increaseArrayCapacity();
}

template<typename T>
inline T ArrayList<T>::removeFirst() {
    if (isEmpty())
        throw "Empty list exception";

    T elementRemoved{ array[0] };

    for (int currentPosition{}; currentPosition < length; ++currentPosition) {
        int rightSidePosition = currentPosition + 1;
        array[currentPosition] = array[rightSidePosition];
    }

    --length;

    if (hasUnusedIncrease())
        decreaseArrayCapacity();

    return elementRemoved;
}

template<typename T>
inline T ArrayList<T>::removeLast() {
    if (isEmpty())
        throw "Empty list exception";

    T elementRemoved{ array[length - 1] };
    --length;

    if (hasUnusedIncrease())
        decreaseArrayCapacity();

    return elementRemoved;
}

template<typename T>
inline T ArrayList<T>::removeAtIndex(int index) {
    T elementRemoved{ array[index] };

    for (int currentPosition{ index }; currentPosition < length; ++currentPosition) {
        int rightSidePosition = currentPosition + 1;
        array[currentPosition] = array[rightSidePosition];
    }

    --length;

    if (hasUnusedIncrease())
        decreaseArrayCapacity();

    return elementRemoved;
}

template<typename T>
inline void ArrayList<T>::forEach(std::function<void(const T& element)> callback) const {
    for (const T& element : *this)
        callback(element);
}

template<typename T>
inline ArrayList<T> ArrayList<T>::map(std::function<T(const T& element)> process) const {
    ArrayList<T> mappedList{};

    for (const T& element : *this)
        mappedList.addAtEnd(process(element));

    return mappedList;
}

template<typename T>
inline ArrayList<T> ArrayList<T>::filter(std::function<bool(const T& element)> isFilteredMatch) const {
    ArrayList<T> filteredList{};

    for (const T& element : *this) {
        if (isFilteredMatch(element))
            filteredList.addAtEnd(element);
    }

    return filteredList;
}

template<typename T>
inline T* ArrayList<T>::begin() const {
    return array;
}

template<typename T>
inline T* ArrayList<T>::end() const {
    return array + length;
}

template<typename T>
inline T& ArrayList<T>::operator[](int index) {
    return array[index];
}

template<typename T>
inline ArrayList<T>& ArrayList<T>::operator=(const ArrayList& rightHandSideOperator) {
    if (&rightHandSideOperator == this)
        return *this;

    defaultCapacity = rightHandSideOperator.defaultCapacity;
    increase = rightHandSideOperator.increase;
    clear();
    copy(rightHandSideOperator);

    return *this;
}

template<typename T>
inline bool operator==(const ArrayList<T>& leftHandSideOperator, const ArrayList<T>& rightHandSideOperator) {
    if (&leftHandSideOperator == &rightHandSideOperator)
        return true;

    if (leftHandSideOperator.length != rightHandSideOperator.length)
        return false;

    for (int i{}; i < leftHandSideOperator.length; ++i) {
        if (leftHandSideOperator[i] != rightHandSideOperator[i])
            return false;
    }

    return true;
}

template<typename T>
inline bool operator!=(const ArrayList<T>& leftHandSideOperator, const ArrayList<T>& rightHandSideOperator) {
    return !(leftHandSideOperator == rightHandSideOperator);
}

template<typename T>
inline ArrayList<T> operator+(const ArrayList<T>& leftHandSideOperator, const ArrayList<T>& rightHandSideOperator) {
    ArrayList<T> result{ leftHandSideOperator };
    result.copy(rightHandSideOperator);
    return result;
}

template<typename T>
inline ArrayList<T>::~ArrayList() {
    delete[] array;
    array = nullptr;
}