#ifndef MYPOINT_H
#define MYPOINT_H

#include <QString>

class MyPoint
{
public:
    MyPoint();
    MyPoint(int x, int y);

    void setPoint(int x, int y);
    QString toString();

    int x;
    int y;
};

#endif // MYPOINT_H
