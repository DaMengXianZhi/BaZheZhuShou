#ifndef DATINGWORKER_H
#define DATINGWORKER_H

#include "MyWorker.h"
#include "MyRect.h"

class DaTingWorker : public MyWorker
{
public:
    explicit DaTingWorker(QObject *parent = nullptr);
    ~DaTingWorker();

protected:
    virtual void init();

    //侦测打怪
    virtual void zhenCeDaGuai();

    //清理窗口以便于接下来切图
    virtual void cleanWindow();

    //开始战斗（等待进入危险区）
    virtual void startZhanDou();



private:
    bool isAvailable();

    //获得材料子窗口
    MyRect escHuoDeCaiLiao;

};

#endif // DATINGWORKER_H
