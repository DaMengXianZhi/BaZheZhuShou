#ifndef MYCOLOR_H
#define MYCOLOR_H

#include <QString>

class MyColor
{
public:
    MyColor();
    MyColor(QString str);
    void setColor(QString strBGR);
    QString toString();

    int red;
    int green;
    int blue;
};

#endif // MYCOLOR_H
