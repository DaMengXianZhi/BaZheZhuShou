#ifndef MYWORKER_H
#define MYWORKER_H

#include <QObject>
#include <QString>

#include "MyPoint.h"
#include "MyColor.h"
#include "MyRect.h"
#include "MapManager.h"

class MyWorker : public QObject
{
    Q_OBJECT
public:
    explicit MyWorker(QObject *parent = nullptr);

    /**
     * @brief exitWorking 退出刷图
     */
    void exitWorking();
    /**
     * @brief huoDongStart  开始活动
     * @param type 1:魔龙宝藏   2:黄金树   3:世界Boss    4:行会试炼
     */
    void huoDongStart(int type);
    void huoDongEnd();

    void initThread(HWND hwnd, MapManager *mapManager);
    void setJiChu(bool zhenCe, bool fuHuo, bool chongLian, bool suiJi, bool zhuangBei, bool hangHuiMode);
    void setFenJie(bool *fenJie, int size);

    void setDengJiParameter(int *top, int size, QStringList list);
    void setDouLiParameter(int *top, int size, QStringList list);
    void setHuDunParameter(int *top, int size, QStringList list);
    void setXingZuoParameter(int *top, int size, QStringList list);
    void setBaGuaParameter(QStringList list);
    void setJinShenParameter(int *top, int size, QStringList list);
    void setYouMingParameter(int *top, int size, QStringList list);
    void setXunLongParameter(int *top, int size, QStringList list);
    void setShenMoParameter(int *top, int size, QStringList list);

public slots:
    void doShuaTu();

protected:
    //后台点击某一坐标
    void backgroundClick(MyPoint point);

    //后台按某一键
    void backgroundKeyPress(int keyCode);

    //初始化坐标
    virtual void init() = 0;

    //检查某一坐标是否是指定颜色
    virtual bool checkPixelColor(MyPoint point, MyColor color);

    //侦测打怪
    virtual void zhenCeDaGuai() = 0;

    //清理窗口以便于接下来切图
    virtual void cleanWindow() = 0;

    //开始战斗（等待进入危险区）
    virtual void startZhanDou() = 0;

    //打开首领挑战子窗口
    virtual void openShouLingTiaoZhanWindow(int typeIndex, int titleIndex);

    //打开列表和表格
    virtual void openListAndTableWindow(int listIndex, int tableIndex);

    //打开八卦地图列表
    virtual void openBaGuaListWindow(int listIndex);

    //打开左上角目标地图窗口
    virtual void openTargetWindow(int targetIndex);

    //分解碎片
    virtual void fenJieSuiPian(int fenJieType);

    void enterDengJiBossMap(QString name);
    void enterDouLiBossMap(QString name);
    void enterHuDunBossMap(QString name);
    void enterXingZuoBossMap(QString name);
    void enterBaGuaBossMap(QString name);
    void enterJinShenBossMap(QString name);
    void enterYouMingBossMap(QString name);
    void enterXunLongBossMap(QString name);
    void enterShenMoBossMap(QString name);

    //右上角活动子窗口
    virtual void openHuoDongRightWindow();
    //左上角活动子窗口（魔龙、黄金树、世界boss）
    virtual void openHuoDongLeftWindow();
    virtual void openHuoDongCenterWindow();
    virtual void doMoLong();
    virtual void doHuangJinShu();
    virtual void doShiJieBoss();
    virtual void doHangHuiShiLian();
    virtual void mouseDrag(int startX, int startY, int endX, int endY);

protected:

    // 获取屏幕分辨率
    int width;
    int height;

    //坐标/颜色
    MyPoint point[5];
    MyColor color[5];

    //活动状态
    volatile bool exit;
    volatile bool huoDong;
    volatile int huoDongType;

    //基础
    HWND hwnd;
    MapManager *pMapManager;
    int systemVersion;

    bool zhenCe;
    bool fuHuo;
    bool chongLian;
    bool suiJi;
    bool zhuangBei;
    bool hangHuiMode;
    bool jianRenSuiJi = false;

    //分解
    bool fenJie[4];

    //等级
    int dengJiTop[3];
    QStringList dengJiList;

    //斗笠
    int douLiTop[3];
    QStringList douLiList;

    //护盾
    int huDunTop[3];
    QStringList huDunList;

    //星座
    int xingZuoTop[3];
    QStringList xingZuoList;

    //八卦
    QStringList baGuaList;

    //金身
    int jinShenTop[3];
    QStringList jinShenList;

    //幽冥
    int youMingTop[3];
    QStringList youMingList;

    //驯龙
    int xunLongTop[3];
    QStringList xunLongList;

    //神魔
    int shenMoTop[3];
    QStringList shenMoList;

    //===========================================================

    //坐标声明
    //win11比win10相差4像素
    int DeltaY;

    //首领挑战
    MyPoint shouLingTiaoZhanPoint;

    //首领挑战子窗口 右上角Esc
    MyRect escShouLingTiaoZhanRect;

    //首领挑战子窗口 右边类型
    MyRect typeRect;
    int TypeStepY;

    //首领挑战子窗口 上面标题 B字母左边上中下
    MyRect titleRect;
    int TitleStepX;

    //首领挑战子窗口 左侧列表
    MyRect listRect;
    int ListStepY = 95;

    //首领挑战子窗口 左侧八卦列表
    MyRect baGuaListRect;
    int BaGuaListStepY;
    MyPoint baGuaQianWangTiaoZhanPoint;

    //首领挑战子窗口 下面表格
    MyPoint tablePoint;
    int TableStepX;
    int TableStepY;

    //左上角目标地图
    MyPoint targetMapPoint;
    int TargetMapStepX;
    int TargetMapStepY;

    //左上角目标地图子窗口Esc
    MyRect escTargetMapRect;

    //随机石
    MyPoint suiJiPoint;
    MyPoint suiJiPlusPoint;
    MyPoint suiJiGouMaiPoint;
    QString suiJiColor;

    //随机石子窗口Esc
    MyRect escSuiJiRect;

    //退出地图
    MyRect exitRect1;
    MyRect exitRect2;
    MyRect exitRect3;
    MyRect exitRect4;

    MyPoint exitQueDingPoint;

    //快捷装备子窗口
    MyRect escZhuangBeiRect;
    MyPoint zhuangBeiPoint;

    //回城复活 回字四个角像素
    MyRect huiZiRect;

    //危险区 区字中心点
    MyPoint weiXianQuPoint;
    QString weiXianQuColor;

    //行会模式
    MyPoint hangHuiModePoint;
    QString hangHuiModeColor;

    //重连 确认按钮四个角
    int QueRenL;
    int QueRenR;
    int QueRenU;
    int QueRenD;
    QString ColorQueRenLU;
    QString ColorQueRenRU;
    QString ColorQueRenLD;
    QString ColorQueRenRD;

    //人物血条
    MyPoint renWuXueTiaoPoint;
    MyPoint huiChengFuHuoPoint;
    QString renWuXueTiaoColor;

    //活动图标坐标
    MyPoint huoDongPoint;
    int HuoDongStepX;

    //魔龙捡东西
    MyPoint jianDongXiPoint;

    //右上角 活动图标
    MyRect escHuoDongRRect;
    MyPoint dianJiQianWangPoint;

    //左上角 活动图标
    MyRect escHuoDongLRect;
    MyPoint jinRuPoint;

    //中间 活动图标
    MyRect escHuoDongCRect;
    MyPoint liJiQianWangPoint;

signals:
};


#endif // MYWORKER_H
