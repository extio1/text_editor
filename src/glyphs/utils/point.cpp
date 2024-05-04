#include "glyphs/utils/point.h"


Point::Point(int _x, int _y): x(_x), y(_y) {}

bool Point::operator==(const Point& p) { 
    return (x == p.x && y == p.y); 
}
