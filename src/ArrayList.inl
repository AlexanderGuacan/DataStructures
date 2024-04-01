#include "ArrayList.hpp"

template <typename T>
void ArrayList<T>::copy(const List<T>& list) {
    const ArrayList<T>* arrayList{ dynamic_cast<const ArrayList<T>*>(&list) };
    for (const T& element : *arrayList)
        addAtEnd(element);
}

template<typename T>
inline bool ArrayList<T>::isFull() {
    return List<T>::length >= capacity;
}

template<typename T>
inline bool ArrayList<T>::hasUnusedIncrease() {
    const int extraIncrease = increase + increase;
    return capacity - List<T>::length == extraIncrease;
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

    for (int i{}; i < List<T>::length; ++i)
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
inline ArrayList<T>::ArrayList(const ArrayList<T>& list): ArrayList(list.capacity, list.increase) {
    copy(list);
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
inline void ArrayList<T>::clear() {
    capacity = defaultCapacity;
    List<T>::length = 0;

    delete[] array;
    array = new T[capacity]{};
}

template<typename T>
inline void ArrayList<T>::addAtBegin(const T& element) {
    for (int currentPosition = List<T>::length; currentPosition > 0; --currentPosition) {
        int leftSidePosition = currentPosition - 1;
        array[currentPosition] = array[leftSidePosition];
    }

    int begin{};
    array[begin] = element;
    ++List<T>::length;

    if (isFull())
        increaseArrayCapacity();
}

template<typename T>
inline void ArrayList<T>::addAtEnd(const T& element) {
    array[List<T>::length] = element;
    ++List<T>::length;

    if (isFull())
        increaseArrayCapacity();
}

template<typename T>
inline void ArrayList<T>::addToIndex(const T& element, int index) {
    if (List<T>::isOutOfBounded(index))
        throw "Index out of bounded exception";

    for (int currentPosition = List<T>::length; currentPosition > index; --currentPosition) {
        int leftSidePosition = currentPosition - 1;
        array[currentPosition] = array[leftSidePosition];
    }

    array[index] = element;
    ++List<T>::length;

    if (isFull())
        increaseArrayCapacity();
}

template<typename T>
inline T ArrayList<T>::removeFirst() {
    if (List<T>::isEmpty())
        throw "Empty list exception";

    T elementRemoved{ array[0] };

    for (int currentPosition{}; currentPosition < List<T>::length; ++currentPosition) {
        int rightSidePosition = currentPosition + 1;
        array[currentPosition] = array[rightSidePosition];
    }

    --List<T>::length;

    if (hasUnusedIncrease())
        decreaseArrayCapacity();

    return elementRemoved;
}

template<typename T>
inline T ArrayList<T>::removeLast() {
    if (List<T>::isEmpty())
        throw "Empty list exception";

    T elementRemoved{ array[List<T>::length - 1] };
    --List<T>::length;

    if (hasUnusedIncrease())
        decreaseArrayCapacity();

    return elementRemoved;
}

template<typename T>
inline T ArrayList<T>::removeAtIndex(int index) {
    T elementRemoved{ array[index] };

    for (int currentPosition{ index }; currentPosition < List<T>::length; ++currentPosition) {
        int rightSidePosition = currentPosition + 1;
        array[currentPosition] = array[rightSidePosition];
    }

    --List<T>::length;

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
inline ArrayList<T>* ArrayList<T>::map(std::function<T(const T& element)> process) const {
    ArrayList<T>* mappedList{ new ArrayList<T>(capacity, increase) };

    for (const T& element : *this)
        mappedList->addAtEnd(process(element));

    return mappedList;
}

template<typename T>
inline ArrayList<T>* ArrayList<T>::filter(std::function<bool(const T& element)> isFilteredMatch) const {
    ArrayList<T>* filteredList{ new ArrayList<T>(capacity, increase) };

    for (const T& element : *this) {
        if (isFilteredMatch(element))
            filteredList->addAtEnd(element);
    }

    return filteredList;
}

template<typename T>
inline T* ArrayList<T>::begin() const {
    return array;
}

template<typename T>
inline T* ArrayList<T>::end() const {
    return array + List<T>::length;
}

template<typename T>
inline T& ArrayList<T>::operator[](int index) {
    return array[index];
}

template<typename T>
inline const T& ArrayList<T>::operator[](int index) const {
    return array[index];
}

template<typename T>
inline ArrayList<T>& ArrayList<T>::operator=(const List<T>& rightHandSideOperator) {
    const ArrayList<T>* castedOperator{ dynamic_cast<const ArrayList<T>*>(&rightHandSideOperator) };

    if (castedOperator == this)
        return *this;

    defaultCapacity = castedOperator->defaultCapacity;
    increase = castedOperator->increase;
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