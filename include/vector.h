#include <memory>
#include <cstddef>
#include <ostream>
#include <initializer_list>

#include "exception.h"

class Vector
{
public:
    Vector();
    Vector(const Vector& o);
    Vector(std::size_t n_dimensions);
    Vector(std::initializer_list<int> l);

    std::size_t get_dimension() const;

    Vector& operator=(const Vector &);

    bool operator==(const Vector& o) const;
    bool operator!=(const Vector& o) const;

    Vector& operator+=(const Vector& o);
    Vector& operator-=(const Vector& o);
    Vector& operator*=(const Vector& o);
    Vector& operator/=(const Vector& o);

    friend Vector operator+(const Vector& l, const Vector &r);
    friend Vector operator-(const Vector& l, const Vector &r);
    friend Vector operator*(const Vector& l, const Vector &r);
    friend Vector operator/(const Vector& l, const Vector &r);

    friend std::ostream& operator<<(std::ostream& os, const Vector& v);
private:
    std::size_t length; // почему ругается, если поменять местами??
    std::unique_ptr<int[]> data;
};
