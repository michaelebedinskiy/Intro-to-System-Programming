
#include "Utilities.h"
#include "MataMvidia.h"

using std::string;
using std::endl;

MataMvidia::MataMvidia(const string& movieName, const string& creatorName,
                       Matrix* frameCollection, int length) :
    movieName(movieName),
    creatorName(creatorName),
    length(length)
{
    this->frameCollection = new Matrix[length];
    for (int i = 0; i < length; i++) {
        this->frameCollection[i] = frameCollection[i];
    }
}

MataMvidia::MataMvidia(const MataMvidia& oldFilm) :
    movieName(oldFilm.movieName),
    creatorName(oldFilm.creatorName),
    length(oldFilm.length)
{
    frameCollection = new Matrix[oldFilm.length];
    for (int i = 0; i < length; ++i) {
            frameCollection[i] = oldFilm.frameCollection[i];
    }
}

MataMvidia::~MataMvidia() {
    delete[] frameCollection;
}

int MataMvidia::size() const {
    return length;
}

MataMvidia& MataMvidia::operator=(const MataMvidia& oldFilm) {
    if (&oldFilm == this) {
        return *this;
    }
    creatorName = oldFilm.creatorName;
    movieName = oldFilm.movieName;
    length = oldFilm.length;
    if (this->frameCollection != oldFilm.frameCollection){
        delete[] frameCollection;
        frameCollection = new Matrix[oldFilm.length];
        for (int i = 0; i < length; ++i) {
            frameCollection[i] = oldFilm.frameCollection[i];
        }
    }
    return *this;
}


const Matrix& MataMvidia::operator[](int index) const { //read only
    if (index >= size() || index < 0) {
        exitWithError(MatamErrorType::OutOfBounds);
    }
    return frameCollection[index];
}

Matrix& MataMvidia::operator[](int index) {
    if (index >= size() || index < 0) {
        exitWithError(MatamErrorType::OutOfBounds);
    }
    return frameCollection[index];
}

MataMvidia& MataMvidia::operator+=(const MataMvidia& toAdd) {
    int newLength = length + toAdd.length;
    Matrix* newCollection = new Matrix[newLength];

    for (int i = 0; i < length; ++i) {
        newCollection[i] = frameCollection[i];
    }

    for (int i = 0; i < toAdd.length; ++i) {
        newCollection[length + i] = toAdd.frameCollection[i];
    }

    delete[] frameCollection;
    frameCollection = newCollection;
    length = newLength;

    return *this;
}

MataMvidia& MataMvidia::operator+=(const Matrix& toAdd) {
    int newLength = length + 1;
    Matrix* newCollection = new Matrix[newLength];

    for (int i = 0; i < length; i++) {
        newCollection[i] = frameCollection[i];
    }

    newCollection[newLength - 1] = toAdd;

    delete[] frameCollection;
    frameCollection = newCollection;
    length = newLength;

    return *this;
}

MataMvidia operator+(const MataMvidia& film1, const MataMvidia& film2) {
    MataMvidia result(film1);
    result += film2;
    return result;
}

std::ostream& operator<<(std::ostream& output, const MataMvidia& film) {
    output << "Movie Name: " << film.movieName << endl;
    output << "Author: " << film.creatorName << endl << endl;

    for (int i = 0; i < film.length; ++i) {
        output << "Frame " << i << ":" << endl;
        output << film.frameCollection[i] << endl;
    }

    output << "-----End of Movie-----" << endl;
    return output;
}
