
#pragma once
#include "Matrix.h"
#include <string>
#include <iostream>

using std::string;

class MataMvidia {
    string movieName;
    string creatorName;
    Matrix* frameCollection;
    int length;

public:
    MataMvidia(const string& movieName, const string& creatorName,
               Matrix* frameCollection, int length);
    int size() const;
    MataMvidia(const MataMvidia& oldFilm);
    ~MataMvidia();

    MataMvidia& operator=(const MataMvidia& oldFilm);
    const Matrix& operator[](int index) const;
    Matrix& operator[](int index);
    MataMvidia& operator+=(const MataMvidia& toAdd);
    MataMvidia& operator+=(const Matrix& toAdd);

    friend std::ostream& operator<<(std::ostream&, const MataMvidia&);
};

MataMvidia operator+(const MataMvidia& film1, const MataMvidia& film2);