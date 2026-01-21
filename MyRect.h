#ifndef MYRECT_H
#define MYRECT_H

#include <QString>

#include "MyPoint.h"

class MyRect
{
public:
    MyRect();
    MyRect(int x, int y, int width, int height);
    MyRect(MyPoint start, int width, int height);

    MyPoint start;
    int width;
    int height;

    QString strLeftUp;
    QString strRightUp;
    QString strLeftDown;
    QString strRightDown;
};

#endif // MYRECT_H
