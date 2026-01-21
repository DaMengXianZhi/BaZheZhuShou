#include "MyRect.h"

MyRect::MyRect() {

}

MyRect::MyRect(int x, int y, int width, int height)
{
    start.x = x;
    start.y = y;
    this->width = width;
    this->height = height;
}

MyRect::MyRect(MyPoint start, int width, int height)
{
    this->start = start;
    this->width = width;
    this->height = height;
}


