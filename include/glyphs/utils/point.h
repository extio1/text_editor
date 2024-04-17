#ifndef TEXT_EDITOR_POINT
#define TEXT_EDITOR_POINT

struct Point
{
    int x = 0;
    int y = 0;

    Point() = default;
    Point(int _x, int _y);

    bool operator==(const Point& p);
};

#endif  // TEXT_EDITOR_POINT