#include "glyphs/utils/point.h"


Point::Point(int x, int y): x(x), y(y) {}

bool Point::operator==(const Point& p) { 
    return (this->x == p.x && this->y == p.y); 
}
