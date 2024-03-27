#include "../include/vector.h"
#include <cstdint>

Vector::Vector(): length(3), 
                  data(std::make_unique<int[]>(length))
{}

Vector::Vector(std::size_t n_dimensions):
                length(n_dimensions), 
                data(std::make_unique<int[]>(length))
{}

Vector::Vector(std::initializer_list<int> l):
                length(l.size()) 
{
    data = std::make_unique<int[]>(length);
    auto o = l.begin();
    for(std::size_t i = 0; i < length; ++i){
        data[i] = *o;
        ++o;
    }
} 

Vector::Vector(const Vector& o): length(o.length)
{
    data = std::make_unique<int[]>(length);
    for(std::size_t i = 0; i < length; ++i){
        data[i] = o.data[i];
    }
} 

std::size_t Vector::get_dimension() const
{
    return length;
}

Vector& Vector::operator=(const Vector &o)
{
    length = o.length;
    data = std::make_unique<int[]>(length);
    
    for(std::size_t i = 0; i < length; ++i){
        data[i] = o.data[i];
    }

    return *this;
}

bool Vector::operator==(const Vector& o) const
{
    if(length != o.length){
        throw vector_dimension_exception("Vectors haven't same dimension");
    }

    bool eq = true;
    for(std::size_t i = 0; i < length; ++i){
        if(data[i] != o.data[i]){
            eq = false;
            break;
        }
    }

    return eq;
}

bool Vector::operator!=(const Vector& o) const
{
    if(length != o.length){
        throw vector_dimension_exception("Vectors haven't same dimension");
    }

    return !(*this == o);
}

Vector& Vector::operator+=(const Vector& o)
{
    if(length != o.length){
        throw vector_dimension_exception("Vectors haven't same dimension");
    }

    for(std::size_t i = 0; i < length; ++i){
        data[i] += o.data[i];
    }

    return *this;
}

Vector& Vector::operator-=(const Vector& o)
{
    if(length != o.length){
        throw vector_dimension_exception("Vectors haven't same dimension");
    }

    for(std::size_t i = 0; i < length; ++i){
        data[i] -= o.data[i];
    }

    return *this;
}

Vector& Vector::operator*=(const Vector& o)
{
    if(length != o.length){
        throw vector_dimension_exception("Vectors haven't same dimension");
    }

    for(std::size_t i = 0; i < length; ++i){
        data[i] *= o.data[i];
    }

    return *this;
}

Vector& Vector::operator/=(const Vector& o)
{
    if(length != o.length){
        throw vector_dimension_exception("Vectors haven't same dimension");
    }

    for(std::size_t i = 0; i < length; ++i){
        data[i] /= o.data[i];
    }

    return *this;
}

Vector operator+(const Vector& l, const Vector &r)
{
    if(l.length != r.length){
        throw vector_dimension_exception("Vectors haven't same dimension");
    }

    auto new_vector = Vector(l.length);

    for(std::size_t i = 0; i < l.length; ++i){
        new_vector.data[i] = l.data[i] + r.data[i];
    }

    return new_vector;
}

Vector operator-(const Vector& l, const Vector &r)
{
    if(l.length != r.length){
        throw vector_dimension_exception("Vectors haven't same dimension");
    }

    auto new_vector = Vector(l.length);

    for(std::size_t i = 0; i < l.length; ++i){
        new_vector.data[i] = l.data[i] - r.data[i];
    }

    return new_vector;
}

Vector operator*(const Vector& l, const Vector &r)
{
    if(l.length != r.length){
        throw vector_dimension_exception("Vectors haven't same dimension");
    }

    auto new_vector = Vector(l.length);

    for(std::size_t i = 0; i < l.length; ++i){
        new_vector.data[i] = l.data[i] * r.data[i];
    }

    return new_vector;
}

Vector operator/(const Vector& l, const Vector &r)
{
    if(l.length != r.length){
        throw vector_dimension_exception("Vectors haven't same dimension");
    }

    auto new_vector = Vector(l.length);

    for(std::size_t i = 0; i < l.length; ++i){
        new_vector.data[i] = l.data[i] / r.data[i];
    }

    return new_vector;
}

std::ostream& operator<<(std::ostream& os, const Vector& v)
{
    os << "(";
    for(std::size_t i = 0; i < v.length-1; ++i){
        os << v.data[i] << ", ";
    }
    os << v.data[v.length-1] << ")";
    return os;
}