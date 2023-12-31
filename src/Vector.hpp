#pragma once

#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <sys/types.h>
#include <initializer_list>

template <typename T>
class Vector {
    private:
        ssize_t mDimension{};
        T* mComponents{};

    public:
        Vector(ssize_t dimension);
        Vector(std::initializer_list<T> elements);
        Vector(const Vector& elements);
        T* begin() const;
        bool contain(const T& element) const;
        T* end() const;
        const T& get(ssize_t index) const;
        ssize_t indexOf(const T& element) const;
        ssize_t lastIndexOf(const T& element) const;
        ssize_t dimension() const;
        double norm() const;
        T& operator[](ssize_t index);
        const T& operator[](ssize_t index) const;
        Vector& operator=(const Vector& rhs);
        template <typename _T>
        friend Vector<_T> operator+(const Vector<_T>& lhs, const Vector<_T>& rhs);
        template <typename _T>
        friend Vector<_T> operator-(const Vector<_T>& lhs, const Vector<_T>& rhs);
        template <typename _T>
        friend Vector<_T> operator*(const Vector<_T>& lhs, const _T& rhs);
        template <typename _T>
        friend Vector<_T> operator*(const _T& lhs, const Vector<_T>& rhs);
        template <typename _T>
        friend Vector<_T> operator*(const Vector<_T>& lhs, const Vector<_T>& rhs);
        Vector& operator+=(const Vector& rhs);
        Vector& operator-=(const Vector& rhs);
        Vector& operator*=(const T& rhs);
        Vector& operator*=(const Vector& rhs);
        template <typename _T>
        friend bool operator==(const Vector<_T>& lhs, const Vector<_T>& rhs);
        template <typename _T>
        friend bool operator!=(const Vector<_T>& lhs, const Vector<_T>& rhs);
        void set(ssize_t index, const T& element);
        Vector<double> unitary() const;
        ~Vector();
};

#include "Vector.inl"

#endif