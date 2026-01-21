#ifndef ZHONGXINWORKER_H
#define ZHONGXINWORKER_H

#include "MyWorker.h"

class ZhongXinWorker : public MyWorker
{
public:
    explicit ZhongXinWorker(QObject *parent = nullptr);
    ~ZhongXinWorker();

protected:
    virtual void init();

    //侦测打怪
    virtual void zhenCeDaGuai();

    //检查某一坐标是否是指定颜色
    virtual bool checkPixelColor(MyPoint point, MyColor color, int step = 5);

    //清理窗口以便于接下来切图
    virtual void cleanWindow();

    //开始战斗（等待进入危险区）
    virtual void startZhanDou();

    //右上角活动子窗口
    virtual void openHuoDongRightWindow();
    //左上角活动子窗口（魔龙、黄金树、世界boss）
    virtual void openHuoDongLeftWindow();
    virtual void openHuoDongCenterWindow();
    virtual void doMoLong();
    virtual void doHuangJinShu();
    virtual void doShiJieBoss();
    virtual void doHangHuiShiLian();
};

#endif // ZHONGXINWORKER_H
