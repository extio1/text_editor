#ifndef TEXT_EDITOR_POINT_H_
#define TEXT_EDITOR_POINT_H_

struct Point {
    int x = 0;
    int y = 0;

    Point() = default;
    Point(int x, int y);

    bool operator==(const Point& p);
};

#endif  // TEXT_EDITOR_POINT_H_