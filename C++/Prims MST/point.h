#ifndef POINT_H
#define POINT_H

class Point {
private:
    int x;
    int y;

public:
    Point();
    Point(int x, int y);
    void setX(int x);
    void setY(int y);
    int getX();
    int getY();

};
#endif