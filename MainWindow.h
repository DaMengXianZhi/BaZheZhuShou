#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <windows.h>
#include <QPoint>
#include <QColor>
#include <QDate>
#include <QComboBox>
#include <QTimer>
#include <QTime>
#include <QThread>
#include <QList>
#include <QKeyEvent>
#include <QPixmap>
#include <QSettings>

#include "MapManager.h"
#include "MyWorker.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void initWindow(int platform, int type, int zone, QDate endDate);

signals:
    void onBackPressed();

private:
    Ui::MainWindow *ui;

    QSettings *pSettings;

    //新老区
    int mZone;
    //辅助类型（至尊，钻石，铂金）
    int mType;
    //游戏平台（QQ游戏大厅，QQ游戏中心）
    int mPlatform;
    //分辨率
    int width, height;
    //到期日期
    QDate mEndDate;

    //
    MapManager *pMapManager;

    QThread *pMaxThread;
    QThread *pMinThread;

    MyWorker *pMaxWorker;
    MyWorker *pMinWorker;
    //大小号线程是否初始化
    bool maxInited;
    bool minInited;
    bool maxStarted;
    bool minStarted;
    bool maxInHuoDong;
    bool minInHuoDong;

    //计时器
    QTimer *pTimer;

    //
    int maxHuoDongStatus;   //-1:停止 0:刷图    1:魔龙    2:黄金树   3:世界boss    4:行会试炼
    int minHuoDongStatus;
    bool maxToShuaTu;
    bool minToShuaTu;
    bool maxToHuoDong;
    bool minToHuoDong;

    //是否启动休眠
    bool xiuMianEnable[2];

    int xiuMianStartMax[2];
    int xiuMianEndMax[2];
    int xiuMianStartMin[2];
    int xiuMianEndMin[2];

    int startTimeMax;
    int endTimeMax;
    int startTimeMin;
    int endTimeMin;

    QList<HWND> hwndList;
    QList<QPixmap> hwndNameList;

    void initJiChuPage();
    void initDengJiPage();
    void initDouLiPage();
    void initHuDunPage();
    void initXingZuoPage();
    void initJinShenPage();
    void initBaGuaPage();
    void initYouMingPage();
    void initXunLongPage();
    void initShenMoPage();
    void initComboBox(QComboBox *pComboBox, int start, int end);
    void initBaGuaList(QComboBox *pComboBox);

    void resumeSettings();
    //初始化游戏窗口句柄
    void initHwnd();
    //抓捕游戏等级区域
    QPixmap captureHiddenWindow(HWND hwnd);
    //显示游戏窗口等级
    void showHwndInfo();

    //后台点击
    void backgroundClick(HWND hwnd, QPoint point);
    //找色
    bool checkPixelColor(HWND hwnd, QPoint point, QColor color);

    void setMaxThreadParameter();
    void setMinThreadParameter();

private slots:
    void onTimerOut();

    void onBackButtonClicked();
    void onStartButtonClicked();
    void onStopButtonClicked();
    void onSaveButtonClicked();
    void onCleanButtonClicked();

    void onMaxWindowHwndChanged();
    void onMinWindowHwndChanged();

    void onMaxDengJiTopChanged();
    void onMinDengJiTopChanged();

    void onMaxDouLiTopChanged();
    void onMinDouLiTopChanged();

    void onMaxHuDunTopChanged();
    void onMinHuDunTopChanged();

    void onMaxXingZuoTopChanged();
    void onMinXingZuoTopChanged();

    void onMaxJinShenTopChanged();
    void onMinJinShenTopChanged();

    void onMaxYouMingTopChanged();
    void onMinYouMingTopChanged();

    void onMaxXunLongTopChanged();
    void onMinXunLongTopChanged();

    void onMaxShenMoTopChanged();
    void onMinShenMoTopChanged();

};

#endif // MAINWINDOW_H
