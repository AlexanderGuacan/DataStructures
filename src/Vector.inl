#include "Vector.hpp"
#include <cmath>

template <typename T>
inline Vector<T>::Vector(ssize_t dimension): mDimension{ dimension }, mComponents{ new T[dimension]{} } {
}

template <typename T>
inline Vector<T>::Vector(std::initializer_list<T> elements) : Vector(elements.size()) {
    ssize_t i{};

    for (const auto& element : elements) {
        mComponents[i] = element;
        ++i;
    }
}

template <typename T>
inline Vector<T>::Vector(const Vector& elements): Vector(elements.mDimension) {
    for (ssize_t i{}; i < mDimension; ++i)
        mComponents[i] = elements.mComponents[i];
}

template <typename T>
inline T* Vector<T>::begin() const {
    return mComponents;
}

template <typename T>
inline ssize_t Vector<T>::dimension() const {
    return mDimension;
}

template <typename T>
inline bool Vector<T>::contain(const T& element) const {
    for (ssize_t i{}; i < mDimension; ++i) {
        if (mComponents[i] == element)
            return true;
    }

    return false;
}

template <typename T>
inline T* Vector<T>::end() const {
    return mComponents + mDimension;
}

template <typename T>
inline const T& Vector<T>::get(ssize_t index) const {
    if (index >= mDimension)
        throw "Index out of bounds exception";

    return mComponents[index];
}

template <typename T>
inline ssize_t Vector<T>::indexOf(const T& element) const {
    for (ssize_t i{}; i < mDimension; ++i) {
        if (element == mComponents[i])
            return i;
    }

    return -1;
}

template <typename T>
inline ssize_t Vector<T>::lastIndexOf(const T& element) const {
    for (ssize_t i{ mDimension - 1 }; i >= 0; --i) {
        if (element == mComponents[i])
            return i;
    }

    return -1;
}

template <typename T>
inline double Vector<T>::norm() const {
    T sum{};

    for (ssize_t i{}; i < mDimension; ++i)
        sum += std::pow(mComponents[i], 2);

    return std::sqrt(sum);
}

template <typename T>
inline T& Vector<T>::operator[](ssize_t index) {
    return mComponents[index];
}

template <typename T>
inline const T& Vector<T>::operator[](ssize_t index) const {
    return mComponents[index];
}

template <typename T>
inline Vector<T>& Vector<T>::operator=(const Vector& rhs) {
    if (this == &rhs)
        return *this;

    delete[] mComponents;
    mComponents = new T[rhs.mDimension];

    for (ssize_t i{}; i < rhs.mDimension; ++i)
        mComponents[i] = rhs.mComponents[i];

    mDimension = rhs.mDimension;

    return *this;
}

template <typename T>
inline Vector<T> operator+(const Vector<T>& lhs, const Vector<T>& rhs) {
    if (lhs.mDimension != rhs.mDimension)
        throw "Not same dimension exception";

    Vector<T> combination(lhs.mDimension);

    for (ssize_t i{}; i < lhs.mDimension; ++i)
        combination.mComponents[i] = lhs.mComponents[i] + rhs.mComponents[i];

    return combination;
}

template <typename T>
inline Vector<T> operator-(const Vector<T>& lhs, const Vector<T>& rhs) {
    if (lhs.mDimension != rhs.mDimension)
        throw "Not same dimension exception";

    Vector<T> combination(lhs.mDimension);

    for (ssize_t i{}; i < lhs.mDimension; ++i)
        combination.mComponents[i] = lhs.mComponents[i] - rhs.mComponents[i];

    return combination;
}

template <typename T>
inline Vector<T> operator*(const Vector<T>& lhs, const T& rhs) {
    Vector<T> dotProduct(lhs.mDimension);

    for (ssize_t i{}; i < lhs.mDimension; ++i)
        dotProduct.mComponents[i] = lhs.mComponents[i] * rhs;

    return dotProduct;
}

template <typename T>
inline Vector<T> operator*(const T& lhs, const Vector<T>& rhs) {
    return rhs * lhs;
}

template <typename T>
inline Vector<T> operator*(const Vector<T>& lhs, const Vector<T>& rhs) {
    if (lhs.mDimension != 3 || rhs.mDimension != 3)
        throw "Vectors not are tridimensional";

    Vector<T> vectorialProduct(3);

    vectorialProduct[0] = (lhs[1] * rhs[2]) - (rhs[1] * lhs[2]);
    vectorialProduct[1] = -((lhs[0] * rhs[2]) - (rhs[0] * lhs[2]));
    vectorialProduct[2] = (lhs[0] * rhs[1]) - (rhs[0] * lhs[1]);

    return vectorialProduct;
}

template <typename T>
inline Vector<T>& Vector<T>::operator+=(const Vector& rhs) {
    if (mDimension != rhs.mDimension)
        throw "Not same dimension exception";

    for (ssize_t i{}; i < mDimension; ++i)
        mComponents[i] += rhs.mComponents[i];

    return *this;
}

template <typename T>
inline Vector<T>& Vector<T>::operator-=(const Vector& rhs) {
    if (mDimension != rhs.mDimension)
        throw "Not same dimension exception";

    for (ssize_t i{}; i < mDimension; ++i)
        mComponents[i] -= rhs.mComponents[i];

    return *this;
}

template <typename T>
inline Vector<T>& Vector<T>::operator*=(const T& rhs) {
    for (ssize_t i{}; i < mDimension; ++i)
        mComponents[i] *= rhs;

    return *this;
}

template <typename T>
inline Vector<T>& Vector<T>::operator*=(const Vector<T>& rhs) {
    constexpr ssize_t tridimensional{ 3ll };
    if (mDimension != tridimensional || rhs.mDimension != tridimensional)
        throw "Vectors not are tridimensional";

    mComponents[0] = (mComponents[1] * rhs[2]) - (rhs[1] * mComponents[2]);
    mComponents[1] = -((mComponents[0] * rhs[2]) - (rhs[0] * mComponents[2]));
    mComponents[2] = (mComponents[0] * rhs[1]) - (rhs[0] * mComponents[1]);

    return *this;
}

template <typename T>
inline bool operator==(const Vector<T>& lhs, const Vector<T>& rhs) {
    if (lhs.mDimension != rhs.mDimension)
        return false;

    if (&lhs == &rhs)
        return true;

    for (ssize_t i{}; i < lhs.mDimension; ++i) {
        if (lhs.mComponents[i] != rhs.mComponents[i])
            return false;
    }

    return true;
}

template <typename T>
inline bool operator!=(const Vector<T>& lhs, const Vector<T>& rhs) {
    return !(lhs == rhs);
}

template <typename T>
inline void Vector<T>::set(ssize_t index, const T& element) {
    if (index >= mDimension)
        throw "Index out of bounds exception";

    mComponents[index] = element;
}

template <typename T>
inline Vector<double> Vector<T>::unitary() const {
    Vector<double> unitary(mDimension);

    double unitaryVectorMeasure{ norm() };

    for (ssize_t i{}; i < mDimension; ++i)
        unitary[i] = mComponents[i] / unitaryVectorMeasure;

    return unitary;
}

template <typename T>
inline Vector<T>::~Vector() {
    if (mComponents != nullptr)
        delete[] mComponents;
}