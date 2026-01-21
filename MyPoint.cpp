#include "MyPoint.h"

MyPoint::MyPoint() {}

MyPoint::MyPoint(int x, int y)
{
    this->x = x;
    this->y = y;
}

void MyPoint::setPoint(int x, int y)
{
    this->x = x;
    this->y = y;
}

QString MyPoint::toString()
{
    return "MyPoint[" + QString::number(x) + "," + QString::number(y) + "]";
}
