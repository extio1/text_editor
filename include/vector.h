#include <iostream>
#include <vector>

class Vector {
    public:
        size_t getDimension() const;
        const std::vector<double> getCoordinates() const;

        Vector(size_t dimension);
        Vector(std::initializer_list<double> coords);
        Vector(std::vector<double> coords);

        ~Vector();
        
        Vector(const Vector& another);
        Vector& operator=(const Vector& b);

        double getEuclideanNorm() const;

        friend std::ostream & operator<<(std::ostream &os, const Vector &v);

        friend bool operator==(const Vector& a, const Vector& b);
        friend bool operator!=(const Vector& a, const Vector& b);

        friend const Vector operator+(const Vector& a, const Vector& b);
        friend const Vector operator-(const Vector& a, const Vector& b);

        friend double scalarProduct(const Vector& a, const Vector& b);
        friend const Vector vectorProduct(const Vector& a, const Vector& b);

    private:
        std::vector<double> coordinates;
};


