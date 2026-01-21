#include "DaTingWorker.h"
#include <QDateTime>

DaTingWorker::DaTingWorker(QObject *parent)
    : MyWorker{parent}
{
    //初始化坐标系统
    init();
}

DaTingWorker::~DaTingWorker()
{

}

void DaTingWorker::init()
{
    if (width == 1920 && height == 1080) {
        //坐标声明
        //win11比win10相差4像素
        DeltaY = 4;

        //首领挑战
        shouLingTiaoZhanPoint.x = 1696;
        shouLingTiaoZhanPoint.y = 43;

        //首领挑战子窗口 右上角Esc
        escShouLingTiaoZhanRect.start.setPoint(1411, 232);
        escShouLingTiaoZhanRect.width = 23;
        escShouLingTiaoZhanRect.height = 42;
        escShouLingTiaoZhanRect.strLeftUp = "00007F";
        escShouLingTiaoZhanRect.strRightUp = "000054";
        escShouLingTiaoZhanRect.strLeftDown = "000022";
        escShouLingTiaoZhanRect.strRightDown = "000022";

        //首领挑战子窗口 右边类型
        typeRect.start.x = 1410;
        typeRect.start.y = 310;
        typeRect.width = 33;
        typeRect.height = 104;
        typeRect.strLeftUp = "B8D9E0";
        typeRect.strRightUp = "5793A0";
        typeRect.strLeftDown = "AFB2B3";

        TypeStepY = 82;

        //首领挑战子窗口 上面标题 B字母左边上中下
        titleRect.start.x = 607;
        titleRect.start.y = 291;
        titleRect.height = 14;
        titleRect.strLeftUp = "758993";
        titleRect.strRightUp = "A3C2CF";
        titleRect.strLeftDown = "66757E";
        TitleStepX = 126;

        //首领挑战子窗口 左侧列表
        listRect.start.x = 542;
        listRect.start.y = 331;
        listRect.width = 164;
        listRect.height = 77;
        listRect.strLeftUp = "1DD5FF";
        listRect.strLeftDown = "1DD5FF";
        listRect.strRightDown = "1DD5FF";
        ListStepY = 92;

        //首领挑战子窗口 左侧八卦列表
        baGuaListRect.start.x = 539;
        baGuaListRect.start.y = 328;
        baGuaListRect.width = 169;
        baGuaListRect.height = 64;
        baGuaListRect.strLeftUp = "1DD5FF";
        baGuaListRect.strRightUp = "1DD5FF";
        baGuaListRect.strLeftDown = "1DD4FE";
        baGuaListRect.strRightDown = "1DD5FF";
        BaGuaListStepY = 77;
        baGuaQianWangTiaoZhanPoint.x = 1046;
        baGuaQianWangTiaoZhanPoint.y = 752;

        //首领挑战子窗口 下面表格
        tablePoint.x = 839;
        tablePoint.y = 654;
        TableStepX = 220;
        TableStepY = 70;

        //左上角目标地图
        targetMapPoint.x = 125;
        targetMapPoint.y = 292;
        TargetMapStepX = 222;
        TargetMapStepY = 86;

        //左上角目标地图子窗口Esc
        escTargetMapRect.start.setPoint(640, 2);
        escTargetMapRect.width = 23;
        escTargetMapRect.height = 41;
        escTargetMapRect.strLeftUp = "000077";
        escTargetMapRect.strRightUp = "00008D";
        escTargetMapRect.strLeftDown = "030336";
        escTargetMapRect.strRightDown = "000041";

        //随机石
        suiJiPoint.setPoint(820, 803);
        suiJiPlusPoint.setPoint(1070, 465);
        suiJiGouMaiPoint.setPoint(1031, 576);
        suiJiColor = "F4F4F4";

        //随机石子窗口Esc
        escSuiJiRect.start.setPoint(1137, 309);
        escSuiJiRect.width = 23;
        escSuiJiRect.height = 41;
        escSuiJiRect.strLeftUp = "0101F5";
        escSuiJiRect.strRightUp = "000084";
        escSuiJiRect.strLeftDown = "000042";
        escSuiJiRect.strRightDown = "000038";

        //退出地图
        exitRect1.start.setPoint(300, 178);
        exitRect1.width = 14;
        exitRect1.height = 17;
        exitRect1.strLeftUp = "7BCFDD";
        exitRect1.strRightUp = "74C4D1";
        exitRect1.strLeftDown = "2D5762";
        exitRect1.strRightDown = "2C464A";

        exitRect2.start.setPoint(304, 181);
        exitRect2.width = 14;
        exitRect2.height = 17;
        exitRect2.strLeftUp = "7ED3E2";
        exitRect2.strRightUp = "74C3D0";
        exitRect2.strLeftDown = "2C545F";
        exitRect2.strRightDown = "2B4448";

        exitRect3.start.setPoint(305, 252);
        exitRect3.width = 16;
        exitRect3.height = 19;
        exitRect3.strLeftUp = "7ED4E3";
        exitRect3.strRightUp = "78C9D7";
        exitRect3.strLeftDown = "376D7C";
        exitRect3.strRightDown = "33565D";

        //exitRect4;

        exitQueDingPoint.setPoint(1047, 573);

        //快捷装备子窗口
        escZhuangBeiRect.start.setPoint(1725, 500);
        escZhuangBeiRect.width = 23;
        escZhuangBeiRect.height = 41;
        escZhuangBeiRect.strLeftUp = "00008C";
        escZhuangBeiRect.strRightUp = "000098";
        escZhuangBeiRect.strLeftDown = "020337";
        escZhuangBeiRect.strRightDown = "000041";
        zhuangBeiPoint.setPoint(1640, 678);

        //回城复活 回字四个角像素
        huiZiRect.start.setPoint(833, 572);
        huiZiRect.width = 14;
        huiZiRect.height = 14;
        huiZiRect.strLeftUp = "A5C8D6";
        huiZiRect.strRightUp = "A5C7D5";
        huiZiRect.strLeftDown = "A2C2D0";
        huiZiRect.strRightDown = "A4C4D2";

        //危险区 区字中心点
        weiXianQuPoint.setPoint(1836, 184);
        weiXianQuColor = "1ECF2C";

        //行会模式
        hangHuiModePoint.setPoint(420, 995);
        hangHuiModeColor = "A8C6D0";

        // //重连 确认按钮四个角
        // int QueRenL;
        // int QueRenR;
        // int QueRenU;
        // int QueRenD;
        // QString ColorQueRenLU;
        // QString ColorQueRenRU;
        // QString ColorQueRenLD;
        // QString ColorQueRenRD;

        // //人物血条
        // int RenWuXueTiaoX;
        // int RenWuXueTiaoY;
        // int HuiChengFuHuoX;
        // int HuiChengFuHuoY;
        // QString ColorRenWuXueTiao;

        //人物血条-
        renWuXueTiaoPoint.setPoint(467, 972);
        huiChengFuHuoPoint.setPoint(870, 579);
        renWuXueTiaoColor = "080B15";

        //活动图标坐标
        huoDongPoint.setPoint(1696, 126);
        HuoDongStepX = 95;

        //魔龙捡东西
        jianDongXiPoint.setPoint(960, 718);

        //右上角 活动图标
        escHuoDongRRect.start.setPoint(1724, 188);
        escHuoDongRRect.width = 23;
        escHuoDongRRect.height = 41;
        escHuoDongRRect.strLeftUp = "1414F9";
        escHuoDongRRect.strRightUp = "000081";
        escHuoDongRRect.strLeftDown = "000030";
        escHuoDongRRect.strRightDown = "000028";
        dianJiQianWangPoint.setPoint(1632, 386);

        //左上角 活动图标
        escHuoDongLRect.start.setPoint(640, 2);
        escHuoDongLRect.width = 23;
        escHuoDongLRect.height = 41;
        escHuoDongLRect.strLeftUp = "000077";
        escHuoDongLRect.strRightUp = "00008D";
        escHuoDongLRect.strLeftDown = "030336";
        escHuoDongLRect.strRightDown = "000041";
        jinRuPoint.setPoint(90, 177);

        //中间 活动图标
        escHuoDongCRect.start.setPoint(1411, 232);
        escHuoDongCRect.width = 23;
        escHuoDongCRect.height = 42;
        escHuoDongCRect.strLeftUp = "00007F";
        escHuoDongCRect.strRightUp = "000054";
        escHuoDongCRect.strLeftDown = "000022";
        escHuoDongCRect.strRightDown = "000022";
        liJiQianWangPoint.setPoint(960, 760);

        //获得材料子窗口
        escHuoDeCaiLiao.start.setPoint(1178, 328);
        escHuoDeCaiLiao.width = 17;
        escHuoDeCaiLiao.height = 27;
        escHuoDeCaiLiao.strLeftUp = "0D0EA9";
        escHuoDeCaiLiao.strRightUp = "0F0FB0";
        escHuoDeCaiLiao.strLeftDown = "010267";
        escHuoDeCaiLiao.strRightDown = "02035A";

    } else if (width == 1366 && height == 768) {
        //坐标声明
        //win11比win10相差4像素
        DeltaY = 4;

        //首领挑战-
        shouLingTiaoZhanPoint.x = 1183;
        shouLingTiaoZhanPoint.y = 34;

        //首领挑战子窗口 右上角Esc-
        escShouLingTiaoZhanRect.start.x = 1053;
        escShouLingTiaoZhanRect.start.y = 126;
        escShouLingTiaoZhanRect.width = 18;
        escShouLingTiaoZhanRect.height = 34;
        escShouLingTiaoZhanRect.strLeftUp = "0101CF";
        escShouLingTiaoZhanRect.strRightUp = "0000B1";
        escShouLingTiaoZhanRect.strRightUp = "00002A";
        escShouLingTiaoZhanRect.strRightDown = "00002E";

        //首领挑战子窗口 右边类型-
        typeRect.start.x = 1052;
        typeRect.start.y = 189;
        typeRect.width = 27;
        typeRect.height = 86;
        typeRect.strLeftUp = "BFE0E8";
        typeRect.strRightUp = "518B9B";
        typeRect.strLeftDown = "BEC3C4";
        TypeStepY = 67;

        //首领挑战子窗口 上面标题 B字母左边上中下-
        titleRect.start.x = 397;
        titleRect.start.y = 179;
        titleRect.height = 10;
        titleRect.strLeftUp = "ACCFDC";
        titleRect.strRightUp = "ABCDDB";
        titleRect.strLeftDown = "AFD2E0";
        TitleStepX = 103;

        //首领挑战子窗口 左侧列表-
        listRect.start.x = 341;
        listRect.start.y = 207;
        listRect.width = 34;
        listRect.height = 63;
        listRect.strLeftUp = "1ECEF6";
        listRect.strLeftDown = "1DD5FF";
        listRect.strRightDown = "1DD5FF";
        ListStepY = 75;

        //首领挑战子窗口 左侧八卦列表-
        baGuaListRect.start.x = 338;
        baGuaListRect.start.y = 205;
        baGuaListRect.width = 138;
        baGuaListRect.height = 52;
        baGuaListRect.strLeftUp = "1FD1FB";
        baGuaListRect.strRightUp = "1FD1FB";
        baGuaListRect.strLeftDown = "1ED4FE";
        baGuaListRect.strRightDown = "1ED4FE";
        BaGuaListStepY = 63;
        baGuaQianWangTiaoZhanPoint.x = 754;
        baGuaQianWangTiaoZhanPoint.y = 552;

        //首领挑战子窗口 下面表格-
        tablePoint.x = 584;
        tablePoint.y = 472;
        TableStepX = 180;
        TableStepY = 57;

        //左上角目标地图-
        targetMapPoint.x = 102;
        targetMapPoint.y = 240;
        TargetMapStepX = 182;
        TargetMapStepY = 70;

        //左上角目标地图子窗口Esc-
        escTargetMapRect.start.setPoint(525, 2);
        escTargetMapRect.width = 19;
        escTargetMapRect.height = 23;
        escTargetMapRect.strLeftUp = "1717F8";
        escTargetMapRect.strRightUp = "00006B";
        escTargetMapRect.strLeftDown = "060755";
        escTargetMapRect.strRightDown = "000029";

        //随机石-
        suiJiPoint.setPoint(566, 530);
        suiJiPlusPoint.setPoint(774, 316);
        suiJiGouMaiPoint.setPoint(740, 407);
        suiJiColor = "F5F5F5";

        //随机石子窗口Esc-
        escSuiJiRect.start.setPoint(828, 189);
        escSuiJiRect.width = 19;
        escSuiJiRect.height = 34;
        escSuiJiRect.strLeftUp = "0C0CFC";
        escSuiJiRect.strRightUp = "00006D";
        escSuiJiRect.strLeftDown = "00001A";
        escSuiJiRect.strRightDown = "000012";

        //退出地图-
        exitRect1.start.setPoint(249, 148);
        exitRect1.width = 12;
        exitRect1.height = 14;
        exitRect1.strLeftUp = "58959F";
        exitRect1.strRightUp = "50868F";
        exitRect1.strLeftDown = "2B535E";
        exitRect1.strRightDown = "284045";

        exitRect2.start.setPoint(250, 142);
        exitRect2.width = 13;
        exitRect2.height = 16;
        exitRect2.strLeftUp = "7ED4E3";
        exitRect2.strRightUp = "79CCDA";
        exitRect2.strLeftDown = "356774";
        exitRect2.strRightDown = "304F55";

        exitRect3.start.setPoint(252, 149);
        exitRect3.width = 11;
        exitRect3.height = 14;
        exitRect3.strLeftUp = "5D9CA7";
        exitRect3.strRightUp = "5D9CA7";
        exitRect3.strLeftDown = "346673";
        exitRect3.strRightDown = "33545A";

        //exitRect4;
        exitQueDingPoint.setPoint(755, 406);

        //快捷装备子窗口-
        escZhuangBeiRect.start.setPoint(1206, 281);
        escZhuangBeiRect.width = 19;
        escZhuangBeiRect.height = 34;
        escZhuangBeiRect.strLeftUp = "00006E";
        escZhuangBeiRect.strRightUp = "00007D";
        escZhuangBeiRect.strLeftDown = "000025";
        escZhuangBeiRect.strRightDown = "000039";
        zhuangBeiPoint.setPoint(1136, 425);

        //回城复活 回字四个角像素-
        huiZiRect.start.setPoint(833, 572);
        huiZiRect.width = 14;
        huiZiRect.height = 14;
        huiZiRect.strLeftUp = "A5C8D6";
        huiZiRect.strRightUp = "A5C7D5";
        huiZiRect.strLeftDown = "A2C2D0";
        huiZiRect.strRightDown = "A4C4D2";

        //危险区 区字中心点-
        weiXianQuPoint.setPoint(1297, 132);
        weiXianQuColor = "16D725";

        //行会模式-
        hangHuiModePoint.setPoint(239, 687);
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
        renWuXueTiaoPoint.setPoint(279, 668);
        huiChengFuHuoPoint.setPoint(609, 410);
        renWuXueTiaoColor = "080B15";

        //活动图标坐标-
        huoDongPoint.setPoint(1182, 103);
        HuoDongStepX = 77;

        //魔龙捡东西-
        jianDongXiPoint.setPoint(683, 460);

        //右上角 活动图标-
        escHuoDongRRect.start.setPoint(1205, 154);
        escHuoDongRRect.width = 19;
        escHuoDongRRect.height = 33;
        escHuoDongRRect.strLeftUp = "1515EB";
        escHuoDongRRect.strRightUp = "000093";
        escHuoDongRRect.strLeftDown = "08095A";
        escHuoDongRRect.strRightDown = "000038";
        dianJiQianWangPoint.setPoint(1130, 318);

        //左上角 活动图标-
        escHuoDongLRect.start.setPoint(525, 2);
        escHuoDongLRect.width = 19;
        escHuoDongLRect.height = 33;
        escHuoDongLRect.strLeftUp = "1717F8";
        escHuoDongLRect.strRightUp = "00006B";
        escHuoDongLRect.strLeftDown = "060755";
        escHuoDongLRect.strRightDown = "000029";
        jinRuPoint.setPoint(74, 145);

        //中间 活动图标
        escHuoDongCRect.start.setPoint(1053, 126);
        escHuoDongCRect.width = 18;
        escHuoDongCRect.height = 34;
        escHuoDongCRect.strLeftUp = "0101CF";
        escHuoDongCRect.strRightUp = "0000B1";
        escHuoDongCRect.strLeftDown = "00002A";
        escHuoDongCRect.strRightDown = "00002E";
        liJiQianWangPoint.setPoint(683, 559);
    }
}

void DaTingWorker::zhenCeDaGuai()
{
    //检查游戏窗口是否存在
    if (exit || !IsWindow(hwnd)) {
        //窗口不存在
        qWarning() << "zhenCeDaGuai: 窗口不存在";
        return;
    }

    //怪物血条
    if (systemVersion < 11) {
        //win 10
        if (width == 1920 && height == 1080) {
            //1920x1080
            point[0].x = 933;
            point[0].y = 39;

            color[0].setColor("0202F6");
        } else {
            //1366x768
            point[0].x = 661;
            point[0].y = 32;

            color[0].setColor("0000FA");
        }
    } else {
        //win 11
        point[0].x = 933;
        point[0].y = 39;

        color[0].setColor("0202F6");
    }

    qint64 millisecs = QDateTime::currentMSecsSinceEpoch(); // 获取自1970年1月1日以来的毫秒数
    int suiJiCount = 0;

    for (int i = 0; !exit && !huoDong && IsWindow(hwnd) && i < 2400; i++) {
        Sleep(50);

        //检查怪物血条
        if (checkPixelColor(point[0], color[0])) {
            //在打怪
            //刷新计时
            millisecs = QDateTime::currentMSecsSinceEpoch();
            //刷新随机计数
            suiJiCount = 0;

        } else {
            //没有打怪
            if (QDateTime::currentMSecsSinceEpoch() - millisecs > 1500) {
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

void DaTingWorker::cleanWindow()
{
    //重连
    if (chongLian) {
        //
    }

    //复活
    if (fuHuo) {
        if (!isAvailable()) {
            //取消获得材料子窗口
            if (systemVersion < 11) {
                //win 10及以下
                //左上
                point[1].x = escHuoDeCaiLiao.start.x;
                point[1].y = escHuoDeCaiLiao.start.y;

                //右上
                point[2].x = escHuoDeCaiLiao.start.x + escHuoDeCaiLiao.width;
                point[2].y = escHuoDeCaiLiao.start.y;

                //左下
                point[3].x = escHuoDeCaiLiao.start.x;
                point[3].y = escHuoDeCaiLiao.start.y + escHuoDeCaiLiao.height;

                //右下
                point[4].x = escHuoDeCaiLiao.start.x + escHuoDeCaiLiao.width;
                point[4].y = escHuoDeCaiLiao.start.y + escHuoDeCaiLiao.height;

                //中心点
                point[0].x = escHuoDeCaiLiao.start.x + escHuoDeCaiLiao.width / 2;
                point[0].y = escHuoDeCaiLiao.start.y + escHuoDeCaiLiao.height / 2;

            } else {
                //win 11
                //左上
                point[1].x = escHuoDeCaiLiao.start.x;
                point[1].y = escHuoDeCaiLiao.start.y - DeltaY;

                //右上
                point[2].x = escHuoDeCaiLiao.start.x + escHuoDeCaiLiao.width;
                point[2].y = escHuoDeCaiLiao.start.y - DeltaY;

                //左下
                point[3].x = escHuoDeCaiLiao.start.x;
                point[3].y = escHuoDeCaiLiao.start.y + escHuoDeCaiLiao.height - DeltaY;

                //右下
                point[4].x = escHuoDeCaiLiao.start.x + escHuoDeCaiLiao.width;
                point[4].y = escHuoDeCaiLiao.start.y + escHuoDeCaiLiao.height - DeltaY;

                //中心点
                point[0].x = escHuoDeCaiLiao.start.x + escHuoDeCaiLiao.width / 2;
                point[0].y = escHuoDeCaiLiao.start.y + escHuoDeCaiLiao.height / 2 - DeltaY;
            }
            //左上
            color[1].setColor(escHuoDeCaiLiao.strLeftUp);
            //右上
            color[2].setColor(escHuoDeCaiLiao.strRightUp);
            //左下
            color[3].setColor(escHuoDeCaiLiao.strLeftDown);
            //右下
            color[4].setColor(escHuoDeCaiLiao.strRightDown);

            for (int i = 0; i < 15; i++) {
                if (checkPixelColor(point[1], color[1]) && checkPixelColor(point[2], color[2])
                    && checkPixelColor(point[3], color[3]) && checkPixelColor(point[4], color[4])) {
                    backgroundClick(point[0]);
                    Sleep(300);
                    qDebug() << "cleanWindow: 取消获得材料=" + point[0].toString();
                } else {
                    break;
                }
            }

            if (systemVersion < 11) {
                //win 10及以下
                point[0].x = huiChengFuHuoPoint.x;
                point[0].y = huiChengFuHuoPoint.y;
            } else {
                //win 11
                point[0].x = huiChengFuHuoPoint.x;
                point[0].y = huiChengFuHuoPoint.y - DeltaY;
            }
            backgroundClick(point[0]);
            Sleep(500);
            qDebug() << "cleanWindow: 复活=" + point[0].toString();
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
                qDebug() << "cleanWindow: 穿装备=" + point[0].toString();
            } else {
                break;
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
            backgroundKeyPress(81);

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
            qDebug() << "cleanWindow: 买随机=" + point[0].toString();
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
            qDebug() << "cleanWindow: 行会模式=" + point[0].toString();
        }
    }
}

void DaTingWorker::startZhanDou()
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

bool DaTingWorker::isAvailable()
{
    if (!IsWindow(hwnd)) {
        qWarning() << "isAvailable: 窗口不存在";
        return false;
    }

    if (systemVersion < 11) {
        //win 10及以下
        point[0].x = renWuXueTiaoPoint.x;
        point[0].y = renWuXueTiaoPoint.y;
    } else {
        //win 11
        point[0].x = renWuXueTiaoPoint.x;
        point[0].y = renWuXueTiaoPoint.y - DeltaY * 2;
    }

    //获取窗口上下文
    HDC hdc = GetDC(hwnd);
    if (hdc == NULL) {
        qWarning() << "isAvailable: hdc获取失败";
        return false;
    }
    COLORREF colorREF = GetPixel(hdc, point[0].x, point[0].y);

    //释放窗口上下文
    ReleaseDC(hwnd, hdc);

    unsigned char red = GetRValue(colorREF);
    unsigned char geen = GetGValue(colorREF);
    unsigned char blue = GetBValue(colorREF);
    //qDebug() << "R:" << red << ", G:" << geen << ", B:" << blue;

    if ((red > 48 && red < 69) && (geen < 5) && (blue < 5)) {
        return true;
    }
    return false;
}


























