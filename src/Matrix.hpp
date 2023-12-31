#pragma once

#ifndef MATRIX_HPP
#define MATRIX_HPP

#include "Vector.hpp"

template <typename T>
class Matrix {
    private:
        ssize_t mRows{};
        ssize_t mColumns{};
        Vector<T>* mComponents{};

    public:
        Matrix(ssize_t rows, ssize_t columns);
        Matrix(const Matrix& matrix);
        Matrix(std::initializer_list<Vector<T>> matrix);
        Vector<T>* begin() const;
        ssize_t columns() const;
        bool contain(const T& element) const;
        Vector<T>* end() const;
        const T& get(ssize_t row, ssize_t column) const;
        Vector<ssize_t> indexOf(const T& element) const;
        Vector<ssize_t> lastIndexOf(const T& element) const;
        Vector<ssize_t> dimension() const;
        Vector<T>& operator[](ssize_t row);
        const Vector<T>& operator[](ssize_t row) const;
        Matrix& operator=(const Matrix& rhs);
        template <typename _T>
        friend Matrix<_T> operator+(const Matrix<_T>& lhs, const Matrix<_T>& rhs);
        template <typename _T>
        friend Matrix<_T> operator-(const Matrix<_T>& lhs, const Matrix<_T>& rhs);
        template <typename _T>
        friend Matrix<_T> operator*(const Matrix<_T>& lhs, const _T& rhs);
        template <typename _T>
        friend Matrix<_T> operator*(const _T& lhs, const Matrix<_T>& rhs);
        template <typename _T>
        friend Matrix<_T> operator*(const Matrix<_T>& lhs, const Matrix<_T>& rhs);
        Matrix& operator+=(const Matrix& rhs);
        Matrix& operator-=(const Matrix& rhs);
        Matrix& operator*=(const T& rhs);
        Matrix& operator*=(const Matrix& rhs);
        template <typename _T>
        friend bool operator==(const Matrix<_T>& lhs, const Matrix<_T>& rhs);
        template <typename _T>
        friend bool operator!=(const Matrix<_T>& lhs, const Matrix<_T>& rhs);
        ssize_t rows() const;
        void set(ssize_t row, ssize_t column, const T& element);
        ~Matrix();
};

#include "Matrix.inl"

#endif