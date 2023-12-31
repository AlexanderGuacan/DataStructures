#include "Matrix.hpp"

template <typename T>
inline Matrix<T>::Matrix(ssize_t rows, ssize_t columns): mRows{ rows }, mColumns{ columns }, mComponents{ new Vector<T>[rows]{} } {
    for (ssize_t i{}; i < rows; ++i)
        mComponents[i] = Vector<T>(columns);
}

template <typename T>
inline Matrix<T>::Matrix(const Matrix<T>& matrix) : Matrix(matrix.mRows, matrix.mColumns) {
    for (ssize_t row{}; row < matrix.mRows; ++row) {
        for (ssize_t column{}; column < matrix.mColumns; ++column)
            mComponents[row][column] = matrix.mComponents[row][column];
    }
}

template <typename T>
inline Matrix<T>::Matrix(std::initializer_list<Vector<T>> matrix): Matrix(matrix.size(), matrix.begin()->dimension()) {
    ssize_t row{};

    for (const auto& vector : matrix) {
        if (vector.dimension() != matrix.begin()->dimension()) {
            delete[] mComponents;
            mComponents = nullptr;
            throw "Vectors of different dimentions";
        }

        ssize_t column{};
        for (const auto& component : vector) {
            mComponents[row][column] = component;
            ++column;
        }

        ++row;
    }
}

template <typename T>
inline Vector<T>* Matrix<T>::begin() const {
    return mComponents;
}

template <typename T>
inline ssize_t Matrix<T>::columns() const {
    return mColumns;
}

template <typename T>
inline bool Matrix<T>::contain(const T& element) const {
    for (ssize_t row{}; row < mRows; ++row) {
        for (ssize_t column{}; column < mColumns; ++column) {
            if (element == mComponents[row][column])
                return true;
        }
    }

    return false;
}

template <typename T>
inline Vector<T>* Matrix<T>::end() const {
    return mComponents + mRows;
}

template <typename T>
inline const T& Matrix<T>::get(ssize_t row, ssize_t column) const {
    return mComponents[row][column];
}

template <typename T>
inline Vector<ssize_t> Matrix<T>::indexOf(const T& element) const {
    for (ssize_t row{}; row < mRows; ++row) {
        for (ssize_t column{}; column < mColumns; ++column) {
            if (element == mComponents[row][column])
                return Vector{ row, column };
        }
    }

    return Vector{ -1ll, -1ll };
}

template <typename T>
inline Vector<ssize_t> Matrix<T>::lastIndexOf(const T& element) const {
    for (ssize_t row{ mRows - 1 }; row >= 0; --row) {
        for (ssize_t column{ mColumns - 1 }; column >= 0; --column) {
            if (element == mComponents[row][column])
                return Vector{ row, column };
        }
    }

    return Vector{ -1ll, -1ll };
}

template <typename T>
inline Vector<ssize_t> Matrix<T>::dimension() const {
    return Vector{ mRows, mColumns };
}

template <typename T>
inline Vector<T>& Matrix<T>::operator[](ssize_t index) {
    return mComponents[index];
}

template <typename T>
inline const Vector<T>& Matrix<T>::operator[](ssize_t index) const {
    return mComponents[index];
}

template <typename T>
inline Matrix<T>& Matrix<T>::operator=(const Matrix<T>& rhs) {
    if (this == &rhs)
        return *this;

    mRows = rhs.mRows;
    mColumns = rhs.mColumns;

    delete[] mComponents;
    mComponents = new Vector<T>[mRows](mColumns);

    for (ssize_t row{}; row < mRows; ++row) {
        for (ssize_t column{}; column < mColumns; ++column)
            mComponents[row][column] = rhs.mComponents[row][column];
    }
}

template <typename T>
inline Matrix<T> operator+(const Matrix<T>& lhs, const Matrix<T>& rhs) {
    if (lhs.mRows != rhs.mRows || lhs.mColumns != rhs.mColumns)
        throw "Addition: Matrix with different dimensions";

    Matrix<T> combination(lhs.mRows, lhs.mColumns);

    for (ssize_t row{}; row < combination.mRows; ++row) {
        for (ssize_t column{}; column < combination.mColumns; ++column)
            combination.mComponents[row][column] = lhs.mComponents[row][column] + rhs.mComponents[row][column];
    }

    return combination;
}

template <typename T>
inline Matrix<T> operator-(const Matrix<T>& lhs, const Matrix<T>& rhs) {
    if (lhs.mRows != rhs.mRows || lhs.mColumns != rhs.mColumns)
        throw "Substraction: Matrix with different dimensions";

    Matrix<T> combination(lhs.mRows, lhs.mColumns);

    for (ssize_t row{}; row < combination.mRows; ++row) {
        for (ssize_t column{}; column < combination.mColumns; ++column)
            combination.mComponents[row][column] = lhs.mComponents[row][column] - rhs.mComponents[row][column];
    }

    return combination;
}

template <typename T>
inline Matrix<T> operator*(const Matrix<T>& lhs, const T& rhs) {
    Matrix<T> product(lhs.mRows, lhs.mColumns);

    for (ssize_t row{}; row < product.mRows; ++row) {
        for (ssize_t column{}; column < product.mColumns; ++column)
            product.mComponents[row][column] = lhs.mComponents[row][column] * rhs;
    }

    return product;
}

template <typename T>
inline Matrix<T> operator*(const T& lhs, const Matrix<T>& rhs) {
    return rhs * lhs;
}

template <typename T>
inline Matrix<T> operator*(const Matrix<T>& lhs, const Matrix<T>& rhs) {
    if (lhs.mColumns != rhs.mRows)
        throw "Multiplication: Matrix columns and rows differents";

    Matrix<T> product(lhs.mRows, rhs.mColumns);

    for (ssize_t row{}; row < product.mRows; ++row) {
        for (ssize_t column{}; column < product.mColumns; ++column) {
            for (ssize_t k{}; k < lhs.mColumns; ++k)
                product.mComponents[row][column] += lhs.mComponents[row][k] * rhs.mComponents[k][column];
        }
    }

    return product;
}

template <typename T>
inline Matrix<T>& Matrix<T>::operator+=(const Matrix<T>& rhs) {
    if (mRows != rhs.mRows || mColumns != rhs.mColumns)
        throw "Substraction: Matrix with different dimensions";

    for (ssize_t row{}; row < mRows; ++row) {
        for (ssize_t column{}; column < mColumns; ++column)
            mComponents[row][column] += rhs.mComponents[row][column];
    }

    return *this;
}

template <typename T>
inline Matrix<T>& Matrix<T>::operator-=(const Matrix<T>& rhs) {
    if (mRows != rhs.mRows || mColumns != rhs.mColumns)
        throw "Substraction: Matrix with different dimensions";

    for (ssize_t row{}; row < mRows; ++row) {
        for (ssize_t column{}; column < mColumns; ++column)
            mComponents[row][column] -= rhs.mComponents[row][column];
    }

    return *this;
}

template <typename T>
inline Matrix<T>& Matrix<T>::operator*=(const T& rhs) {
    for (ssize_t row{}; row < mRows; ++row) {
        for (ssize_t column{}; column < mColumns; ++column)
            mComponents[row][column] *= rhs;
    }

    return *this;
}

template <typename T>
inline Matrix<T>& Matrix<T>::operator*=(const Matrix<T>& rhs) {
    *this = *this * rhs;
}

template <typename T>
inline bool operator==(const Matrix<T>& lhs, const Matrix<T>& rhs) {
    if (lhs.mRows != rhs.mRows || lhs.mColumns != rhs.mColumns)
        return false;

    for (ssize_t row{}; row < lhs.mRows; ++row) {
        for (ssize_t column{}; column < lhs.mColumns; ++column) {
            if (lhs.mComponents[row][column] != rhs.mComponents[row][column])
                return false;
        }
    }

    return true;
}

template <typename T>
inline bool operator!=(const Matrix<T>& lhs, const Matrix<T>& rhs) {
    return !(lhs == rhs);
}

template <typename T>
inline ssize_t Matrix<T>::rows() const {
    return mRows;
}

template <typename T>
inline void Matrix<T>::set(ssize_t row, ssize_t column, const T& element) {
    mComponents[row][column] = element;
}

template <typename T>
inline Matrix<T>::~Matrix() {
    if (mComponents != nullptr)
        delete[] mComponents;
}