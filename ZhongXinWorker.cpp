#include "ZhongXinWorker.h"

#include <QGuiApplication>
#include <QImage>
#include <QScreen>
#include <QPixmap>
#include <QDateTime>

ZhongXinWorker::ZhongXinWorker(QObject *parent)
    : MyWorker{parent}
{
    //初始化坐标系统
    init();
}

ZhongXinWorker::~ZhongXinWorker()
{

}

void ZhongXinWorker::init()
{
    //坐标声明
    //win11比win10相差4像素
    DeltaY = 4;

    //首领挑战-
    shouLingTiaoZhanPoint.x = 1696;
    shouLingTiaoZhanPoint.y = 82;

    //首领挑战子窗口 右上角Esc-
    escShouLingTiaoZhanRect.start.x = 1412;
    escShouLingTiaoZhanRect.start.y = 262;
    escShouLingTiaoZhanRect.width = 23;
    escShouLingTiaoZhanRect.height = 41;
    escShouLingTiaoZhanRect.strLeftUp = "0303FE";
    escShouLingTiaoZhanRect.strRightUp = "00007B";
    escShouLingTiaoZhanRect.strRightUp = "00003D";
    escShouLingTiaoZhanRect.strRightDown = "000031";

    //首领挑战子窗口 右边类型-
    typeRect.start.x = 1409;
    typeRect.start.y = 341;
    typeRect.width = 33;
    typeRect.height = 105;
    typeRect.strLeftUp = "C1ECF2";
    typeRect.strRightUp = "35636B";
    typeRect.strLeftDown = "9FA2A4";

    TypeStepY = 82;

    //首领挑战子窗口 上面标题 B字母左边上中下-
    titleRect.start.x = 607;
    titleRect.start.y = 315;
    titleRect.height = 12;
    TitleStepX = 125;
    titleRect.strLeftUp = "9BFFFE";
    titleRect.strRightUp = "9BFFFE";
    titleRect.strLeftDown = "8EEAE9";

    //首领挑战子窗口 左侧列表-
    listRect.start.x = 541;
    listRect.start.y = 354;
    listRect.width = 165;
    listRect.height = 79;
    listRect.strLeftUp = "1DD4FE";
    listRect.strLeftDown = "28B3D4";
    listRect.strRightDown = "33BDE0";
    ListStepY = 95;

    //首领挑战子窗口 左侧八卦列表-
    baGuaListRect.start.x = 540;
    baGuaListRect.start.y = 356;
    baGuaListRect.width = 164;
    baGuaListRect.height = 63;
    baGuaListRect.strLeftUp = "27B2D3";
    baGuaListRect.strRightUp = "328FA8";
    baGuaListRect.strLeftDown = "1DD5FF";
    baGuaListRect.strRightDown = "3592AC";
    BaGuaListStepY = 80;
    baGuaQianWangTiaoZhanPoint.x = 1046;
    baGuaQianWangTiaoZhanPoint.y = 788;

    //首领挑战子窗口 下面表格-
    tablePoint.x = 835;
    tablePoint.y = 686;
    TableStepX = 220;
    TableStepY = 76;

    //左上角目标地图-
    targetMapPoint.x = 125;
    targetMapPoint.y = 332;
    TargetMapStepX = 222;
    TargetMapStepY = 86;

    //左上角目标地图子窗口Esc-
    escTargetMapRect.start.setPoint(644, 42);
    escTargetMapRect.width = 23;
    escTargetMapRect.height = 41;
    escTargetMapRect.strLeftUp = "010192";
    escTargetMapRect.strRightUp = "000098";
    escTargetMapRect.strLeftDown = "020238";
    escTargetMapRect.strRightDown = "000041";

    //随机石-
    suiJiPoint.setPoint(817, 828);
    suiJiPlusPoint.setPoint(1019, 503);
    suiJiGouMaiPoint.setPoint(965, 556);
    suiJiColor = "F7F7F7";

    //随机石子窗口Esc-
    escSuiJiRect.start.setPoint(1174, 350);
    escSuiJiRect.width = 24;
    escSuiJiRect.height = 41;
    escSuiJiRect.strLeftUp = "07077D";
    escSuiJiRect.strRightUp = "000054";
    escSuiJiRect.strLeftDown = "00001E";
    escSuiJiRect.strRightDown = "00001E";

    //退出地图-
    exitRect1.start.setPoint(295, 221);
    exitRect1.width = 13;
    exitRect1.height = 16;
    exitRect1.strLeftUp = "7ED4E3";
    exitRect1.strRightUp = "79CBD9";
    exitRect1.strLeftDown = "3A7282";
    exitRect1.strRightDown = "34575E";

    exitRect2.start.setPoint(303, 218);
    exitRect2.width = 14;
    exitRect2.height = 17;
    exitRect2.strLeftUp = "7CD0DF";
    exitRect2.strRightUp = "6DB8C5";
    exitRect2.strLeftDown = "31606C";
    exitRect2.strRightDown = "2B4449";

    exitRect3.start.setPoint(305, 252);
    exitRect3.width = 16;
    exitRect3.height = 19;
    exitRect3.strLeftUp = "7ED4E3";
    exitRect3.strRightUp = "78C9D7";
    exitRect3.strLeftDown = "376D7C";
    exitRect3.strRightDown = "33565D";

    //exitRect4;

    exitQueDingPoint.setPoint(1089, 586);

    //快捷装备子窗口-
    escZhuangBeiRect.start.setPoint(1724, 589);
    escZhuangBeiRect.width = 23;
    escZhuangBeiRect.height = 42;
    escZhuangBeiRect.strLeftUp = "000082";
    escZhuangBeiRect.strRightUp = "00004D";
    escZhuangBeiRect.strLeftDown = "000020";
    escZhuangBeiRect.strRightDown = "00001E";
    zhuangBeiPoint.setPoint(1617, 794);

    //回城复活 回字四个角像素-
    huiZiRect.start.setPoint(843, 599);
    huiZiRect.width = 15;
    huiZiRect.height = 17;
    huiZiRect.strLeftUp = "768F98";
    huiZiRect.strRightUp = "7B959E";
    huiZiRect.strLeftDown = "4B5A60";
    huiZiRect.strRightDown = "4E5E64";

    //危险区 区字中心点-
    weiXianQuPoint.setPoint(1832, 194);
    weiXianQuColor = "00CF00";

    //行会模式
    hangHuiModePoint.setPoint(416, 1020);
    hangHuiModeColor = "ABC9D3";

    // //重连 确认按钮四个角
    // int QueRenL;
    // int QueRenR;
    // int QueRenU;
    // int QueRenD;
    // QString ColorQueRenLU;
    // QString ColorQueRenRU;
    // QString ColorQueRenLD;
    // QString ColorQueRenRD;

    //人物血条-
    renWuXueTiaoPoint.setPoint(466, 972);
    huiChengFuHuoPoint.setPoint(870, 578);
    renWuXueTiaoColor = "060716";

    //活动图标坐标-
    huoDongPoint.setPoint(1696, 161);
    HuoDongStepX = 83;

    //魔龙捡东西
    jianDongXiPoint.setPoint(960, 718);

    //右上角 活动图标-
    escHuoDongRRect.start.setPoint(1724, 188);
    escHuoDongRRect.width = 23;
    escHuoDongRRect.height = 41;
    escHuoDongRRect.strLeftUp = "1414F9";
    escHuoDongRRect.strRightUp = "000081";
    escHuoDongRRect.strLeftDown = "000030";
    escHuoDongRRect.strRightDown = "000028";
    dianJiQianWangPoint.setPoint(1632, 386);

    //左上角 活动图标-
    escHuoDongLRect.start.setPoint(640, 2);
    escHuoDongLRect.width = 23;
    escHuoDongLRect.height = 41;
    escHuoDongLRect.strLeftUp = "000077";
    escHuoDongLRect.strRightUp = "00008D";
    escHuoDongLRect.strLeftDown = "030336";
    escHuoDongLRect.strRightDown = "000041";
    jinRuPoint.setPoint(90, 177);

    //中间 活动图标-
    escHuoDongCRect.start.setPoint(1411, 232);
    escHuoDongCRect.width = 23;
    escHuoDongCRect.height = 42;
    escHuoDongCRect.strLeftUp = "00007F";
    escHuoDongCRect.strRightUp = "000054";
    escHuoDongCRect.strLeftDown = "000022";
    escHuoDongCRect.strRightDown = "000022";
    liJiQianWangPoint.setPoint(960, 760);
}

void ZhongXinWorker::zhenCeDaGuai()
{
    if (exit || !IsWindow(hwnd)) {
        //窗口不存在
        qWarning() << "zhenCeDaGuai: 窗口不存在";
        return;
    }

    int count = 0;
    MyPoint pointXueTiao;
    MyColor colorXueTiao;

    //怪物血条
    pointXueTiao.setPoint(885, 80);
    colorXueTiao.setColor("0000FE");

    //qint64 timestamp = QDateTime::currentSecsSinceEpoch(); // 获取自1970年1月1日以来的秒数
    //qDebug() << "Current timestamp in seconds:" << timestamp;
    qint64 millisecs = QDateTime::currentMSecsSinceEpoch(); // 获取自1970年1月1日以来的毫秒数
    int suiJiCount = 0;
    //qDebug() << "Current timestamp in milliseconds:" << millisecs;
    for (int i = 0; !exit && !huoDong && IsWindow(hwnd) && i < 2400; i++) {
        Sleep(100);

        //检查怪物血条
        if (checkPixelColor(pointXueTiao, colorXueTiao)) {
            //在打怪
            //刷新计时
            millisecs = QDateTime::currentMSecsSinceEpoch();
            //刷新随机计数
            suiJiCount = 0;
        } else {
            //没有打怪
            if (QDateTime::currentMSecsSinceEpoch() - millisecs > 2000) {
                //随机一次
                backgroundKeyPress(81);
                //刷新计时
                millisecs = QDateTime::currentMSecsSinceEpoch();
                //刷新随机计数
                suiJiCount++;
            }
            if (suiJiCount > 2) {
                break;
            }
        }
    }
}

bool ZhongXinWorker::checkPixelColor(MyPoint point, MyColor color, int step)
{
    QScreen *screen = QGuiApplication::primaryScreen();
    QImage image = screen->grabWindow(0, point.x, point.y, 1, 1).toImage();

    QRgb qRgb = image.pixel(0, 0);
    QColor qColor(qRgb);

    if ((qColor.red() > color.red - step && qColor.red() < color.red + step)
        && (qColor.green() > color.green - step && qColor.green() < color.green + step)
        && (qColor.blue() > color.blue - step && qColor.blue() < color.blue + step)) {
        return true;
    }
    return false;
}

void ZhongXinWorker::cleanWindow()
{
    //重连
    if (chongLian) {
        //
    }

    //复活
    if (fuHuo) {
        if (systemVersion < 11) {
            //win 10及以下
            //左上
            point[1].x = huiZiRect.start.x;
            point[1].y = huiZiRect.start.y;

            //右上
            point[2].x = huiZiRect.start.x + huiZiRect.width;
            point[2].y = huiZiRect.start.y;

            //左下
            point[3].x = huiZiRect.start.x;
            point[3].y = huiZiRect.start.y + huiZiRect.height;

            //右下
            point[4].x = huiZiRect.start.x + huiZiRect.width;
            point[4].y = huiZiRect.start.y + huiZiRect.height;

            point[0].setPoint(huiChengFuHuoPoint.x, huiChengFuHuoPoint.y);
        } else {
            //win 11
            //左上
            point[1].x = huiZiRect.start.x;
            point[1].y = huiZiRect.start.y - DeltaY * 2;

            //右上
            point[2].x = huiZiRect.start.x + huiZiRect.width;
            point[2].y = huiZiRect.start.y - DeltaY * 2;

            //左下
            point[3].x = huiZiRect.start.x;
            point[3].y = huiZiRect.start.y + huiZiRect.height - DeltaY * 2;

            //右下
            point[4].x = huiZiRect.start.x + huiZiRect.width;
            point[4].y = huiZiRect.start.y + huiZiRect.height - DeltaY * 2;

            point[0].setPoint(huiChengFuHuoPoint.x, huiChengFuHuoPoint.y - DeltaY * 2);
        }
        //左上
        color[1].setColor(huiZiRect.strLeftUp);
        //右上
        color[2].setColor(huiZiRect.strRightUp);
        //左下
        color[3].setColor(huiZiRect.strLeftDown);
        //右下
        color[4].setColor(huiZiRect.strRightDown);

        if (checkPixelColor(point[1], color[1]) && checkPixelColor(point[2], color[2])
            && checkPixelColor(point[3], color[3]) && checkPixelColor(point[4], color[4])) {
            backgroundClick(point[0]);
            Sleep(1000);
            //连续按2此Esc键
            backgroundKeyPress(27);
            Sleep(200);
            backgroundKeyPress(27);
            Sleep(200);
        }
    }

    //穿装备
    if (zhuangBei) {
        if (systemVersion < 11) {
            //win 10及以下
            //左上
            point[1].x = escZhuangBeiRect.start.x;
            point[1].y = escZhuangBeiRect.start.y;

            //右上
            point[2].x = escZhuangBeiRect.start.x + escZhuangBeiRect.width;
            point[2].y = escZhuangBeiRect.start.y;

            //左下
            point[3].x = escZhuangBeiRect.start.x;
            point[3].y = escZhuangBeiRect.start.y + escZhuangBeiRect.height;

            //右下
            point[4].x = escZhuangBeiRect.start.x + escZhuangBeiRect.width;
            point[4].y = escZhuangBeiRect.start.y + escZhuangBeiRect.height;

            //装备
            point[0].x = zhuangBeiPoint.x;
            point[0].y = zhuangBeiPoint.y;

        } else {
            //win 11
            //左上
            point[1].x = escZhuangBeiRect.start.x;
            point[1].y = escZhuangBeiRect.start.y - DeltaY * 2;

            //右上
            point[2].x = escZhuangBeiRect.start.x + escZhuangBeiRect.width;
            point[2].y = escZhuangBeiRect.start.y - DeltaY * 2;

            //左下
            point[3].x = escZhuangBeiRect.start.x;
            point[3].y = escZhuangBeiRect.start.y + escZhuangBeiRect.height - DeltaY * 2;

            //右下
            point[4].x = escZhuangBeiRect.start.x + escZhuangBeiRect.width;
            point[4].y = escZhuangBeiRect.start.y + escZhuangBeiRect.height - DeltaY * 2;

            //装备
            point[0].x = zhuangBeiPoint.x;
            point[0].y = zhuangBeiPoint.y - DeltaY * 2;
        }
        //左上
        color[1].setColor(escZhuangBeiRect.strLeftUp);
        //右上
        color[2].setColor(escZhuangBeiRect.strRightUp);
        //左下
        color[3].setColor(escZhuangBeiRect.strLeftDown);
        //右下
        color[4].setColor(escZhuangBeiRect.strRightDown);

        //穿装备
        for (int i = 0; i < 15; i++) {
            if (checkPixelColor(point[1], color[1]) && checkPixelColor(point[2], color[2])
                && checkPixelColor(point[3], color[3]) && checkPixelColor(point[4], color[4])) {
                backgroundClick(point[0]);
                Sleep(1100);
            }
        }
    }

    //连续按2此Esc键
    backgroundKeyPress(27);
    Sleep(200);
    backgroundKeyPress(27);
    Sleep(200);
    backgroundKeyPress(27);
    Sleep(200);

    //退出地图1
    if (systemVersion < 11) {
        //win 10及以下
        //左上
        point[1].x = exitRect1.start.x;
        point[1].y = exitRect1.start.y;

        //右上
        point[2].x = exitRect1.start.x + exitRect1.width;
        point[2].y = exitRect1.start.y;

        //左下
        point[3].x = exitRect1.start.x;
        point[3].y = exitRect1.start.y + exitRect1.height;

        //右下
        point[4].x = exitRect1.start.x + exitRect1.width;
        point[4].y = exitRect1.start.y + exitRect1.height;

        //确定退出
        point[0].x = exitRect1.start.x + exitRect1.width / 2;
        point[0].y = exitRect1.start.y + exitRect1.height / 2;
    } else {
        //win 11
        //左上
        point[1].x = exitRect1.start.x;
        point[1].y = exitRect1.start.y;

        //右上
        point[2].x = exitRect1.start.x + exitRect1.width;
        point[2].y = exitRect1.start.y;

        //左下
        point[3].x = exitRect1.start.x;
        point[3].y = exitRect1.start.y + exitRect1.height;

        //右下
        point[4].x = exitRect1.start.x + exitRect1.width;
        point[4].y = exitRect1.start.y + exitRect1.height;

        //确定退出
        point[0].x = exitRect1.start.x + exitRect1.width / 2;
        point[0].y = exitRect1.start.y + exitRect1.height / 2;
    }
    //左上
    color[1].setColor(exitRect1.strLeftUp);
    //右上
    color[2].setColor(exitRect1.strRightUp);
    //左下
    color[3].setColor(exitRect1.strLeftDown);
    //右下
    color[4].setColor(exitRect1.strRightDown);

    if (checkPixelColor(point[1], color[1]) && checkPixelColor(point[2], color[2])
        && checkPixelColor(point[3], color[3]) && checkPixelColor(point[4], color[4])) {
        backgroundClick(point[0]);
        Sleep(1000);
        //点击确定
        if (systemVersion < 11) {
            //win 10及以下
            point[0].x = exitQueDingPoint.x;
            point[0].y = exitQueDingPoint.y;
        } else {
            //win 11
            point[0].x = exitQueDingPoint.x;
            point[0].y = exitQueDingPoint.y - DeltaY;
        }
        backgroundClick(point[0]);
        Sleep(1000);
    }

    //退出地图2
    if (systemVersion < 11) {
        //win 10及以下
        //左上
        point[1].x = exitRect2.start.x;
        point[1].y = exitRect2.start.y;

        //右上
        point[2].x = exitRect2.start.x + exitRect2.width;
        point[2].y = exitRect2.start.y;

        //左下
        point[3].x = exitRect2.start.x;
        point[3].y = exitRect2.start.y + exitRect2.height;

        //右下
        point[4].x = exitRect2.start.x + exitRect2.width;
        point[4].y = exitRect2.start.y + exitRect2.height;

        //确定退出
        point[0].x = exitRect2.start.x + exitRect2.width / 2;
        point[0].y = exitRect2.start.y + exitRect2.height / 2;
    } else {
        //win 11
        //左上
        point[1].x = exitRect2.start.x;
        point[1].y = exitRect2.start.y;

        //右上
        point[2].x = exitRect2.start.x + exitRect2.width;
        point[2].y = exitRect2.start.y;

        //左下
        point[3].x = exitRect2.start.x;
        point[3].y = exitRect2.start.y + exitRect2.height;

        //右下
        point[4].x = exitRect2.start.x + exitRect2.width;
        point[4].y = exitRect2.start.y + exitRect2.height;

        //确定退出
        point[0].x = exitRect2.start.x + exitRect2.width / 2;
        point[0].y = exitRect2.start.y + exitRect2.height / 2;
    }
    //左上
    color[1].setColor(exitRect2.strLeftUp);
    //右上
    color[2].setColor(exitRect2.strRightUp);
    //左下
    color[3].setColor(exitRect2.strLeftDown);
    //右下
    color[4].setColor(exitRect2.strRightDown);

    if (checkPixelColor(point[1], color[1]) && checkPixelColor(point[2], color[2])
        && checkPixelColor(point[3], color[3]) && checkPixelColor(point[4], color[4])) {
        backgroundClick(point[0]);
        Sleep(1000);
        //点击确定
        if (systemVersion < 11) {
            //win 10及以下
            point[0].x = exitQueDingPoint.x;
            point[0].y = exitQueDingPoint.y;
        } else {
            //win 11
            point[0].x = exitQueDingPoint.x;
            point[0].y = exitQueDingPoint.y - DeltaY;
        }
        backgroundClick(point[0]);
        Sleep(1000);
    }

    //退出地图3
    if (systemVersion < 11) {
        //win 10及以下
        //左上
        point[1].x = exitRect3.start.x;
        point[1].y = exitRect3.start.y;

        //右上
        point[2].x = exitRect3.start.x + exitRect3.width;
        point[2].y = exitRect3.start.y;

        //左下
        point[3].x = exitRect3.start.x;
        point[3].y = exitRect3.start.y + exitRect3.height;

        //右下
        point[4].x = exitRect3.start.x + exitRect3.width;
        point[4].y = exitRect3.start.y + exitRect3.height;

        //确定退出
        point[0].x = exitRect3.start.x + exitRect3.width / 2;
        point[0].y = exitRect3.start.y + exitRect3.height / 2;
    } else {
        //win 11
        //左上
        point[1].x = exitRect3.start.x;
        point[1].y = exitRect3.start.y;

        //右上
        point[2].x = exitRect3.start.x + exitRect3.width;
        point[2].y = exitRect3.start.y;

        //左下
        point[3].x = exitRect3.start.x;
        point[3].y = exitRect3.start.y + exitRect3.height;

        //右下
        point[4].x = exitRect3.start.x + exitRect3.width;
        point[4].y = exitRect3.start.y + exitRect3.height;

        //确定退出
        point[0].x = exitRect3.start.x + exitRect3.width / 2;
        point[0].y = exitRect3.start.y + exitRect3.height / 2;
    }
    //左上
    color[1].setColor(exitRect3.strLeftUp);
    //右上
    color[2].setColor(exitRect3.strRightUp);
    //左下
    color[3].setColor(exitRect3.strLeftDown);
    //右下
    color[4].setColor(exitRect3.strRightDown);

    if (checkPixelColor(point[1], color[1]) && checkPixelColor(point[2], color[2])
        && checkPixelColor(point[3], color[3]) && checkPixelColor(point[4], color[4])) {
        backgroundClick(point[0]);
        Sleep(1000);
        //点击确定
        if (systemVersion < 11) {
            //win 10及以下
            point[0].x = exitQueDingPoint.x;
            point[0].y = exitQueDingPoint.y;
        } else {
            //win 11
            point[0].x = exitQueDingPoint.x;
            point[0].y = exitQueDingPoint.y - DeltaY;
        }
        backgroundClick(point[0]);
        Sleep(1000);
    }

    //买随机
    if (suiJi) {
        if (systemVersion < 11) {
            //win 10及以下
            point[0].x = suiJiPoint.x;
            point[0].y = suiJiPoint.y;
        } else {
            //win 11
            point[0].x = suiJiPoint.x;
            point[0].y = suiJiPoint.y - DeltaY * 2;
        }
        color[0].setColor(suiJiColor);

        if (checkPixelColor(point[0], color[0])) {
            //没有随机石
            //backgroundKeyPress(81);
            backgroundClick(point[0]);

            //等待买随机子窗口
            if (systemVersion < 11) {
                //win 10及以下
                //左上
                point[1].x = escSuiJiRect.start.x;
                point[1].y = escSuiJiRect.start.y;

                //右上
                point[2].x = escSuiJiRect.start.x + escSuiJiRect.width;
                point[2].y = escSuiJiRect.start.y;

                //左下
                point[3].x = escSuiJiRect.start.x;
                point[3].y = escSuiJiRect.start.y + escSuiJiRect.height;

                //右下
                point[4].x = escSuiJiRect.start.x + escSuiJiRect.width;
                point[4].y = escSuiJiRect.start.y + escSuiJiRect.height;

            } else {
                //win 11
                //左上
                point[1].x = escSuiJiRect.start.x;
                point[1].y = escSuiJiRect.start.y - DeltaY;

                //右上
                point[2].x = escSuiJiRect.start.x + escSuiJiRect.width;
                point[2].y = escSuiJiRect.start.y - DeltaY;

                //左下
                point[3].x = escSuiJiRect.start.x;
                point[3].y = escSuiJiRect.start.y + escSuiJiRect.height - DeltaY;

                //右下
                point[4].x = escSuiJiRect.start.x + escSuiJiRect.width;
                point[4].y = escSuiJiRect.start.y + escSuiJiRect.height - DeltaY;

            }
            //左上
            color[1].setColor(escSuiJiRect.strLeftUp);
            //右上
            color[2].setColor(escSuiJiRect.strRightUp);
            //左下
            color[3].setColor(escSuiJiRect.strLeftDown);
            //右下
            color[4].setColor(escSuiJiRect.strRightDown);

            for (int i = 0; i < 15; i++) {
                Sleep(200);
                if (checkPixelColor(point[1], color[1]) && checkPixelColor(point[2], color[2])
                    && checkPixelColor(point[3], color[3]) && checkPixelColor(point[4], color[4])) {
                    break;
                }
            }

            //点击max
            if (systemVersion < 11) {
                //win 10及以下
                point[0].x = suiJiPlusPoint.x;
                point[0].y = suiJiPlusPoint.y;
            } else {
                //win 11
                point[0].x = suiJiPlusPoint.x;
                point[0].y = suiJiPlusPoint.y - DeltaY;
            }
            backgroundClick(point[0]);
            Sleep(500);

            //点击购买
            if (systemVersion < 11) {
                //win 10及以下
                point[0].x = suiJiGouMaiPoint.x;
                point[0].y = suiJiGouMaiPoint.y;
            } else {
                //win 11
                point[0].x = suiJiGouMaiPoint.x;
                point[0].y = suiJiGouMaiPoint.y - DeltaY;
            }
            backgroundClick(point[0]);
            Sleep(500);
        }
    }

    //行会模式
    if (hangHuiMode) {
        if (systemVersion < 11) {
            //win 10及以下
            point[0].x = hangHuiModePoint.x;
            point[0].y = hangHuiModePoint.y;
        } else {
            //win 11
            point[0].x = hangHuiModePoint.x;
            point[0].y = hangHuiModePoint.y - DeltaY * 2;
        }
        color[0].setColor(hangHuiModeColor);

        for (int i = 0; i < 6; i++) {
            if (checkPixelColor(point[0], color[0])) {
                break;
            }
            //按H切换模式
            backgroundKeyPress(72);
            Sleep(300);
        }
    }
}

void ZhongXinWorker::startZhanDou()
{
    if (systemVersion < 11) {
        //win 10及以下
        point[0].x = weiXianQuPoint.x;
        point[0].y = weiXianQuPoint.y;
    } else {
        //win 11
        point[0].x = weiXianQuPoint.x;
        point[0].y = weiXianQuPoint.y;
    }
    color[0].setColor(weiXianQuColor);

    for (int i = 0; i < 15; i++) {
        if (checkPixelColor(point[0], color[0])) {
            //安全区
            Sleep(200);
        } else {
            break;
        }
    }
    //按Z战斗
    backgroundKeyPress(90);
}

void ZhongXinWorker::openHuoDongRightWindow()
{
    if (systemVersion < 11) {
        //win 10及以下
        //左上
        point[1].x = escHuoDongRRect.start.x;
        point[1].y = escHuoDongRRect.start.y;

        //右上
        point[2].x = escHuoDongRRect.start.x + escHuoDongRRect.width;
        point[2].y = escHuoDongRRect.start.y;

        //左下
        point[3].x = escHuoDongRRect.start.x;
        point[3].y = escHuoDongRRect.start.y + escHuoDongRRect.height;

        //右下
        point[4].x = escHuoDongRRect.start.x + escHuoDongRRect.width;
        point[4].y = escHuoDongRRect.start.y + escHuoDongRRect.height;

        //点击前往
        point[0].x = dianJiQianWangPoint.x;
        point[0].y = dianJiQianWangPoint.y;
    } else {
        //win 11
        //左上
        point[1].x = escHuoDongRRect.start.x;
        point[1].y = escHuoDongRRect.start.y - DeltaY;

        //右上
        point[2].x = escHuoDongRRect.start.x + escHuoDongRRect.width;
        point[2].y = escHuoDongRRect.start.y - DeltaY;

        //左下
        point[3].x = escHuoDongRRect.start.x;
        point[3].y = escHuoDongRRect.start.y + escHuoDongRRect.height - DeltaY;

        //右下
        point[4].x = escHuoDongRRect.start.x + escHuoDongRRect.width;
        point[4].y = escHuoDongRRect.start.y + escHuoDongRRect.height - DeltaY;

        //点击前往
        point[0].x = dianJiQianWangPoint.x;
        point[0].y = dianJiQianWangPoint.y;
    }
    //左上
    color[1].setColor(escHuoDongRRect.strLeftUp);
    //右上
    color[2].setColor(escHuoDongRRect.strRightUp);
    //左下
    color[3].setColor(escHuoDongRRect.strLeftDown);
    //右下
    color[4].setColor(escHuoDongRRect.strRightDown);

    for (int i = 0; i < 15; i++) {
        Sleep(200);
        if (checkPixelColor(point[1], color[1]) && checkPixelColor(point[2], color[2])
            && checkPixelColor(point[3], color[3]) && checkPixelColor(point[4], color[4])) {
            break;
        }
    }

    backgroundClick(point[0]);
}

void ZhongXinWorker::openHuoDongLeftWindow()
{
    if (systemVersion < 11) {
        //win 10及以下
        //左上
        point[1].x = escHuoDongLRect.start.x;
        point[1].y = escHuoDongLRect.start.y;

        //右上
        point[2].x = escHuoDongLRect.start.x + escHuoDongLRect.width;
        point[2].y = escHuoDongLRect.start.y;

        //左下
        point[3].x = escHuoDongLRect.start.x;
        point[3].y = escHuoDongLRect.start.y + escHuoDongLRect.height;

        //右下
        point[4].x = escHuoDongLRect.start.x + escHuoDongLRect.width;
        point[4].y = escHuoDongLRect.start.y + escHuoDongLRect.height;

        //点击前往
        point[0].x = jinRuPoint.x;
        point[0].y = jinRuPoint.y;
    } else {
        //win 11
        //左上
        point[1].x = escHuoDongLRect.start.x;
        point[1].y = escHuoDongLRect.start.y;

        //右上
        point[2].x = escHuoDongLRect.start.x + escHuoDongLRect.width;
        point[2].y = escHuoDongLRect.start.y;

        //左下
        point[3].x = escHuoDongLRect.start.x;
        point[3].y = escHuoDongLRect.start.y + escHuoDongLRect.height;

        //右下
        point[4].x = escHuoDongLRect.start.x + escHuoDongLRect.width;
        point[4].y = escHuoDongLRect.start.y + escHuoDongLRect.height;

        //点击前往
        point[0].x = jinRuPoint.x;
        point[0].y = jinRuPoint.y;
    }
    //左上
    color[1].setColor(escHuoDongLRect.strLeftUp);
    //右上
    color[2].setColor(escHuoDongLRect.strRightUp);
    //左下
    color[3].setColor(escHuoDongLRect.strLeftDown);
    //右下
    color[4].setColor(escHuoDongLRect.strRightDown);

    for (int i = 0; i < 15; i++) {
        Sleep(200);
        if (checkPixelColor(point[1], color[1]) && checkPixelColor(point[2], color[2])
            && checkPixelColor(point[3], color[3]) && checkPixelColor(point[4], color[4])) {
            break;
        }
    }

    backgroundClick(point[0]);
}

void ZhongXinWorker::openHuoDongCenterWindow()
{
    //检测中间活动子窗口
    if (systemVersion < 11) {
        //win 10及以下
        //左上
        point[1].x = escHuoDongCRect.start.x;
        point[1].y = escHuoDongCRect.start.y;

        //右上
        point[2].x = escHuoDongCRect.start.x + escHuoDongCRect.width;
        point[2].y = escHuoDongCRect.start.y;

        //左下
        point[3].x = escHuoDongCRect.start.x;
        point[3].y = escHuoDongCRect.start.y + escHuoDongCRect.height;

        //右下
        point[3].x = escHuoDongCRect.start.x + escHuoDongCRect.width;
        point[3].y = escHuoDongCRect.start.y + escHuoDongCRect.height;

        //点击前往
        point[0].x = liJiQianWangPoint.x;
        point[0].y = liJiQianWangPoint.y;
    } else {
        //win 11
        //左上
        point[1].x = escHuoDongCRect.start.x;
        point[1].y = escHuoDongCRect.start.y - DeltaY;

        //右上
        point[2].x = escHuoDongCRect.start.x + escHuoDongCRect.width;
        point[2].y = escHuoDongCRect.start.y - DeltaY;

        //左下
        point[3].x = escHuoDongCRect.start.x;
        point[3].y = escHuoDongCRect.start.y + escHuoDongCRect.height - DeltaY;

        //右下
        point[3].x = escHuoDongCRect.start.x + escHuoDongCRect.width;
        point[3].y = escHuoDongCRect.start.y + escHuoDongCRect.height - DeltaY;

        //点击前往
        point[0].x = liJiQianWangPoint.x;
        point[0].y = liJiQianWangPoint.y - DeltaY;
    }
    //左上
    color[1].setColor(escHuoDongRRect.strLeftUp);
    //右上
    color[2].setColor(escHuoDongRRect.strRightUp);
    //左下
    color[3].setColor(escHuoDongRRect.strLeftDown);
    //右下
    color[3].setColor(escHuoDongRRect.strRightDown);

    for (int i = 0; i < 15; i++) {
        Sleep(200);
        if (checkPixelColor(point[1], color[1]) && checkPixelColor(point[2], color[2])
            && checkPixelColor(point[3], color[3]) && checkPixelColor(point[4], color[4])) {
            break;
        }
    }
    //点击前往
    backgroundClick(point[0]);
}

void ZhongXinWorker::doMoLong()
{
    if (exit || !IsWindow(hwnd)) {
        qWarning() << "doMoLong: 窗口不存在";
        return;
    }

    //清理窗口
    cleanWindow();

    //点击魔龙图标
    if (systemVersion < 11) {
        //win 10及以下
        point[0].x = huoDongPoint.x - HuoDongStepX * 2;
        point[0].y = huoDongPoint.y;
    } else {
        //win 11
        point[0].x = huoDongPoint.x - HuoDongStepX * 2;
        point[0].y = huoDongPoint.y;
    }
    backgroundClick(point[0]);

    //打开右上角活动子窗口
    openHuoDongRightWindow();

    //打开左上角活动子窗口并进入活动地图
    openHuoDongLeftWindow();

    //点击随机按键开始捡东西
    if (systemVersion < 11) {
        //捡东西
        point[0].x = jianDongXiPoint.x;
        point[0].y = jianDongXiPoint.y;
    } else {
        //win 11
        //捡东西
        point[0].x = jianDongXiPoint.x;
        point[0].y = jianDongXiPoint.y - DeltaY * 2;
    }

    while (!exit && huoDong && IsWindow(hwnd)) {
        Sleep(500);
        //点击捡东西
        backgroundClick(point[0]);
        Sleep(500);
        //随机一次防止被蹲点
        backgroundKeyPress(81);
    }
}

void ZhongXinWorker::doHuangJinShu()
{
    if (exit || !IsWindow(hwnd)) {
        qWarning() << "doHuangJinShu: 窗口不存在";
        return;
    }

    //清理窗口
    cleanWindow();

    //点击魔龙图标
    if (systemVersion < 11) {
        //win 10及以下
        point[0].x = huoDongPoint.x - HuoDongStepX * 2;
        point[0].y = huoDongPoint.y;
    } else {
        //win 11
        point[0].x = huoDongPoint.x - HuoDongStepX * 2;
        point[0].y = huoDongPoint.y;
    }
    backgroundClick(point[0]);

    //打开右上角活动子窗口
    openHuoDongRightWindow();

    //打开左上角活动子窗口并进入活动地图
    openHuoDongLeftWindow();

    //按Z触发战斗
    startZhanDou();

    while (!exit && huoDong && IsWindow(hwnd)) {
        Sleep(1000);
    }
}

void ZhongXinWorker::doShiJieBoss()
{
    if (exit || !IsWindow(hwnd)) {
        qWarning() << "doShiJieBoss: 窗口不存在";
        return;
    }

    //清理窗口
    cleanWindow();

    //点击魔龙图标
    if (systemVersion < 11) {
        //win 10及以下
        point[0].x = huoDongPoint.x - HuoDongStepX * 2;
        point[0].y = huoDongPoint.y;
    } else {
        //win 11
        point[0].x = huoDongPoint.x - HuoDongStepX * 2;
        point[0].y = huoDongPoint.y;
    }
    backgroundClick(point[0]);

    //打开右上角活动子窗口
    openHuoDongRightWindow();

    //打开左上角活动子窗口并进入活动地图
    openHuoDongLeftWindow();

    //按Z触发战斗
    startZhanDou();

    while (!exit && huoDong && IsWindow(hwnd)) {
        Sleep(1000);
    }

    //随机一次防止被蹲点
    backgroundKeyPress(81);
    huoDong = false;
}

void ZhongXinWorker::doHangHuiShiLian()
{

}
