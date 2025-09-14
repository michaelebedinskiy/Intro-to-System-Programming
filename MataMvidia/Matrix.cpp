
#include "Matrix.h"

Matrix::Matrix() :
    rows(0),
    columns(0),
    contents(nullptr)
{}

Matrix::Matrix(int rows, int columns) :
    rows(rows),
    columns(columns)
{
    if (rows == 0 || columns == 0) {
        contents = nullptr;
    } else {
        contents = new int[rows * columns]();
    }
}

Matrix::Matrix(const Matrix& matrix) :
    rows(matrix.rows),
    columns(matrix.columns),
    contents(new int[rows * columns])
{
    for (int i = 0; i < rows * columns; i++) {
        contents[i] = matrix.contents[i];
    }
}

Matrix::~Matrix() {
    delete[] contents;
}

int& Matrix::operator()(int i, int j) {
    if (i < 0 || i >= rows || j < 0 || j >= columns) {
        exitWithError(MatamErrorType::OutOfBounds);
    }
    return contents[i * columns + j];
}

const int& Matrix::operator()(int i, int j) const {
    if (i < 0 || i >= rows || j < 0 || j >= columns) {
        exitWithError(MatamErrorType::OutOfBounds);
    }
    return contents[i * columns + j];
}

std::ostream &operator<<(std::ostream &os, const Matrix &matrix){
    if (matrix.contents == nullptr) {
        return os;
    }
    for(int i = 0; i < matrix.rows; i++) {
        for(int j = 0; j < matrix.columns; j++) {
            os << "|" << matrix(i, j);
        }
        os << "|" << std::endl;
    }
    return os;
}

Matrix& Matrix::operator=(const Matrix& other) {
    if (this == &other) {
        return *this;
    }
    rows = other.rows;
    columns = other.columns;
    int* newContents = new int[rows * columns];
    for (int i = 0; i < rows * columns; i++) {
        newContents[i] = other.contents[i];
    }
    delete[] contents;
    contents = newContents;
    return *this;
}

Matrix& Matrix::operator+=(const Matrix& toAdd) {
    if (rows != toAdd.rows || columns != toAdd.columns) {
        exitWithError(MatamErrorType::UnmatchedSizes);
    }
    for(int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
             (*this)(i, j) += toAdd(i, j);
        }
    }
    return *this;
}

Matrix operator+(const Matrix& matrix, const Matrix& toAdd) {
    Matrix result(matrix);
    return (result += toAdd);
}

Matrix& Matrix::operator-=(const Matrix& toSubtract) {
    if (rows != toSubtract.rows || columns != toSubtract.columns) {
        exitWithError(MatamErrorType::UnmatchedSizes);
    }
    for(int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            (*this)(i, j) -= toSubtract(i, j);
        }
    }
    return *this;
}

Matrix operator-(const Matrix& matrix, const Matrix& toSubtract) {
    Matrix result(matrix);
    return (result -= toSubtract);
}

Matrix Matrix::operator-() const {
    Matrix result(*this);
    return (result *= -1);
}

Matrix& Matrix::operator*=(const Matrix& toMultiply) {
    if (columns != toMultiply.rows) {
        exitWithError(MatamErrorType::UnmatchedSizes);
    }
    Matrix temp(rows, toMultiply.columns);
    for(int i = 0; i < rows; i++) {
        for (int j = 0; j < toMultiply.columns; j++) {
            for (int k = 0; k < columns; k++) {
                temp(i, j) += (*this)(i, k) * toMultiply(k, j);
            }
        }
    }
    delete[] contents;
    columns = temp.columns;
    rows = temp.rows;
    contents = new int[rows * columns]();
    for (int i = 0; i < rows * columns; i++) {
        contents[i] = temp.contents[i];
    }
    return *this;
}

Matrix operator*(const Matrix& matrix, const Matrix& toMultiply) {
    Matrix result(matrix);
    return (result *= toMultiply);
}

Matrix& Matrix::operator*=(int scalar) {
    for(int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            (*this)(i, j) *= scalar;
        }
    }
    return *this;
}

Matrix operator*(const Matrix& matrix, int scalar) {
    Matrix result(matrix);
    return (result *= scalar);
}

Matrix operator*(int scalar, const Matrix& matrix) {
    return matrix * scalar;
}

bool Matrix::operator==(const Matrix& other) const {
    if (rows != other.rows || columns != other.columns) {
        return false;
    }
    for(int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            if ((*this)(i, j) != other(i, j)) {
                return false;
            }
        }
    }
    return true;
}

bool Matrix::operator!=(const Matrix& other) const {
    return !(*this == other);
}

Matrix Matrix::rotateClockwise() const {
    Matrix result(columns, rows);
    for(int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            result(j, rows - 1 - i) = (*this)(i, j);
        }
    }
    return result;
}

Matrix Matrix::rotateCounterClockwise() const {
    Matrix result(columns, rows);
    for(int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            result(columns - 1 - j, i) = (*this)(i, j);
        }
    }
    return result;
}

Matrix Matrix::transpose() const {
    Matrix result(columns, rows);
    for(int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            result(j, i) = (*this)(i, j);
        }
    }
    return result;
}
