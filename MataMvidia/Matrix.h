
#pragma once
#include <iostream>
#include "Utilities.h"

class Matrix {
    int rows;
    int columns;
    int* contents;

    friend std::ostream &operator<<(std::ostream &os, const Matrix &matrix);
public:
    Matrix();
    Matrix(int rows, int columns);
    Matrix(const Matrix& matrix);
    ~Matrix();

    int& operator()(int i, int j);
    const int& operator()(int i, int j) const;
    Matrix& operator=(const Matrix& other);
    bool operator==(const Matrix& other) const;
    bool operator!=(const Matrix& other) const;

    Matrix& operator+=(const Matrix& toAdd);
    Matrix& operator-=(const Matrix& toSubtract);
    Matrix operator-() const;
    Matrix& operator*=(const Matrix& toMultiply);
    Matrix& operator*=(int scalar);

    Matrix rotateClockwise() const;
    Matrix rotateCounterClockwise() const;
    Matrix transpose() const;
};

Matrix operator+(const Matrix& matrix, const Matrix& toAdd);
Matrix operator-(const Matrix& matrix, const Matrix& toSubtract);
Matrix operator*(const Matrix& matrix, const Matrix& toMultiply);
Matrix operator*(const Matrix& matrix, int scalar);
Matrix operator*(int scalar, const Matrix& matrix);
