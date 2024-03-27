#include <iostream>
#include <ostream>
#include <vector>
#include <cstdarg>
#include <cmath>

#include "code/inc/vector.h"

Vector::Vector(size_t _dimension)
{
    for (size_t i = 0; i < _dimension; ++i)
        coordinates.push_back(0.0);
}

Vector::~Vector() {}

Vector::Vector(std::initializer_list<double> coords) : coordinates(coords) {}

Vector::Vector(std::vector<double> coords) : coordinates(coords) {}

Vector::Vector(const Vector &another)
{
    for (size_t i = 0; i < another.getDimension(); ++i)
        this->coordinates.push_back(another.getCoordinates()[i]);
}

Vector& Vector::operator=(const Vector& b) {
    if (this == &b)
		return *this;

	this->coordinates = b.getCoordinates();
	return *this;
}


const size_t Vector::getDimension() const
{
    return this->coordinates.size();
}

const std::vector<double> Vector::getCoordinates() const
{
    return this->coordinates;
}

const double Vector::getEuclideanNorm() const {
    double norm = 0.0;
    for (size_t i = 0; i < this->coordinates.size(); ++i) norm += this->coordinates[i]*this->coordinates[i];
    return sqrt(norm);
}

std::ostream & operator<<(std::ostream &os, const Vector &v)
{
    os << '(';
    for (size_t i = 0; i < v.getDimension(); ++i)
    {
        os << v.getCoordinates()[i];
        if (i != v.getDimension() - 1) os << ", ";
    }
    os << ")";
    return os;
}

bool operator==(const Vector& a, const Vector& b) {
    if (a.getDimension() != b.getDimension()) return false; 

    for (size_t i = 0; i < a.getDimension(); ++i) {
        if (a.coordinates[i] != b.coordinates[i]) return false;
    }
    return true;
}
bool operator!=(const Vector& a, const Vector& b) {
    return !(a == b);
}

const Vector operator+(const Vector& a, const Vector& b) {
    if (a.getDimension() != b.getDimension()) {
        throw std::invalid_argument("Vectors must have the same dimension for addition");
    }
    std::vector<double> sumVector;
    for (size_t i = 0; i < a.getDimension(); ++i) sumVector.push_back(a.coordinates[i] + b.coordinates[i]);
    return Vector(sumVector);
}

const Vector operator-(const Vector& a, const Vector& b) {
    if (a.getDimension() != b.getDimension()) {
        throw std::invalid_argument("Vectors must have the same dimension for subtraction");
    }
    std::vector<double> subVector;
    for (size_t i = 0; i < a.getDimension(); ++i) subVector.push_back(a.coordinates[i] - b.coordinates[i]);
    return Vector(subVector);
}

const double scalarProduct(const Vector& a, const Vector& b) {
    if (a.getDimension() != b.getDimension()) {
        throw std::invalid_argument("Vectors must have the same dimension for scalar product");
    }
    double result = 0.0;
    for (size_t i = 0; i < a.getDimension(); ++i) {
        result += a.coordinates[i] * b.coordinates[i];
    }
    return result;
}
const Vector vectorProduct(const Vector& a, const Vector& b) {
    if (a.getDimension() != 3 or b.getDimension() != 3) {
        throw std::invalid_argument("Vectors must have the dimension = 3 for vector product");
    }
    std::vector<double> result;
    result.push_back(a.coordinates[1]*b.coordinates[2] - b.coordinates[1]*a.coordinates[2]);
    result.push_back(-(a.coordinates[0]*b.coordinates[2] - b.coordinates[0]*a.coordinates[2]));
    result.push_back(a.coordinates[0]*b.coordinates[1] - b.coordinates[0]*a.coordinates[1]);
    return Vector(result);
}
