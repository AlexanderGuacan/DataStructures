#include "Matrix.hpp"
#include <iostream>
#include <time.h>

template <typename T>
std::ostream& operator<<(std::ostream& output, const Matrix<T>& rhs) {
    output << "[\t";

    for (const auto& row : rhs) {
        for (const auto& column : row)
            output << column << ' ';

        output << '\n';
    }

    output << "\t]";

    return output;
}

int main() {
    std::srand(time(nullptr));

    using T = float;
    Matrix<T> matrix(3, 3);

    constexpr int max{ 150 };
    constexpr int min{ 1 };
    constexpr auto computeRandomNumber{
        [](const int min, const int max) -> T {
            return min + rand() % ((max + 1) - min);
        }
    };

    for (auto& row : matrix) {
        for (auto& column : row)
            column = computeRandomNumber(min, max);
    }

    std::cout << matrix;

    return 0;
}