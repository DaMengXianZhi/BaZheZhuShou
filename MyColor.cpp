#include "MyColor.h"


MyColor::MyColor()
{
    red = 0xff;
    green = 0xff;
    blue = 0xff;
}

MyColor::MyColor(QString strBGR)
{
    if (strBGR.length() != 6) {
        red = 0xff;
        green = 0xff;
        blue = 0xff;
        return;
    }
    //0707AB    BGR
    red = strBGR.mid(4, 2).toInt(NULL, 16);
    green = strBGR.mid(2, 2).toInt(NULL, 16);
    blue = strBGR.mid(0, 2).toInt(NULL, 16);
}

void MyColor::setColor(QString strBGR)
{
    if (strBGR.length() != 6) {
        red = 0xff;
        green = 0xff;
        blue = 0xff;
        return;
    }
    //0707AB    BGR
    red = strBGR.mid(4, 2).toInt(NULL, 16);
    green = strBGR.mid(2, 2).toInt(NULL, 16);
    blue = strBGR.mid(0, 2).toInt(NULL, 16);
}

QString MyColor::toString()
{
    return "MyColor[red=" + QString::number(red) + ", green=" + QString::number(green) + ", blue=" + QString::number(blue) + "]";
}
