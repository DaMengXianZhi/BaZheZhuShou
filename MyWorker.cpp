#include "MyWorker.h"

#include <QDebug>
#include <QScreen>
#include <QRect>
#include <QTime>
#include <windows.h>

#include "Define.h"

MyWorker::MyWorker(QObject *parent)
    : QObject{parent}
{
    systemVersion = QSysInfo::productVersion().toInt();

    // 获取屏幕分辨率
    QScreen *screen = QGuiApplication::primaryScreen();
    if (screen == NULL) {
        width = 1920;
        height = 1080;
    } else {
        const QRect geometry = screen->geometry();
        width = geometry.width();
        height = geometry.height();
    }
}

void MyWorker::exitWorking()
{
    exit = true;
}

void MyWorker::huoDongStart(int type)
{
    huoDong = true;
    huoDongType = type;
}

void MyWorker::huoDongEnd()
{
    huoDong = false;
}

void MyWorker::initThread(HWND hwnd, MapManager *mapManager)
{
    this->hwnd = hwnd;
    pMapManager = mapManager;
}

void MyWorker::setJiChu(bool zhenCe, bool fuHuo, bool chongLian, bool suiJi, bool zhuangBei, bool hangHuiMode)
{
    qDebug() << "setJiChu: zhenCe=" + QString::number(zhenCe ? 1 : 0) + ", fuHuo=" + QString::number(fuHuo ? 1 : 0) + ", chongLian=" + QString::number(chongLian ? 1 : 0)
                    + ", suiJi=" + QString::number(suiJi ? 1 : 0) + ", zhuangBei=" + QString::number(zhuangBei ? 1 : 0) + ", hangHuiMode=" + QString::number(hangHuiMode ? 1 : 0);
    this->zhenCe = zhenCe;
    this->fuHuo = fuHuo;
    this->chongLian = chongLian;
    this->suiJi = suiJi;
    this->zhuangBei = zhuangBei;
    this->hangHuiMode = hangHuiMode;
}

void MyWorker::setFenJie(bool *fenJie, int size)
{
    for (int i = 0; i < size; i++) {
        this->fenJie[i] = fenJie[i];
    }
}

void MyWorker::setDengJiParameter(int *top, int size, QStringList list)
{
    dengJiList.clear();
    for (int i = 0; i < size; i++) {
        dengJiTop[i] = top[i];
    }
    dengJiList = list;
}

void MyWorker::setDouLiParameter(int *top, int size, QStringList list)
{
    douLiList.clear();
    for (int i = 0; i < size; i++) {
        douLiTop[i] = top[i];
    }
    douLiList = list;
}

void MyWorker::setHuDunParameter(int *top, int size, QStringList list)
{
    huDunList.clear();
    for (int i = 0; i < size; i++) {
        huDunTop[i] = top[i];
    }
    huDunList = list;
}

void MyWorker::setXingZuoParameter(int *top, int size, QStringList list)
{
    xingZuoList.clear();
    for (int i = 0; i < size; i++) {
        xingZuoTop[i] = top[i];
    }
    xingZuoList = list;
}

void MyWorker::setBaGuaParameter(QStringList list)
{
    baGuaList.clear();
    baGuaList = list;
}

void MyWorker::setJinShenParameter(int *top, int size, QStringList list)
{
    jinShenList.clear();
    for (int i = 0; i < size; i++) {
        jinShenTop[i] = top[i];
    }
    jinShenList = list;
}

void MyWorker::setYouMingParameter(int *top, int size, QStringList list)
{
    youMingList.clear();
    for (int i = 0; i < size; i++) {
        youMingTop[i] = top[i];
    }
    youMingList = list;
}

void MyWorker::setXunLongParameter(int *top, int size, QStringList list)
{
    xunLongList.clear();
    for (int i = 0; i < size; i++) {
        xunLongTop[i] = top[i];
    }
    xunLongList = list;
}

void MyWorker::setShenMoParameter(int *top, int size, QStringList list)
{
    shenMoList.clear();
    for (int i = 0; i < size; i++) {
        shenMoTop[i] = top[i];
    }
    shenMoList = list;
}

void MyWorker::doShuaTu()
{
    exit = false;
    huoDong = false;

    while (!exit && IsWindow(hwnd)) {
        //活动
        if (huoDong) {
            if (huoDongType == 1) {
                //魔龙
                doMoLong();
            } else if (huoDongType == 2) {
                //黄金树
                doHuangJinShu();
            } else if (huoDongType == 3) {
                //世界Boss
                doShiJieBoss();
            } else if (huoDongType == 4) {
                //行会试炼
                doHangHuiShiLian();
            }
        } else {
            //等级
            for (int i = 0; !exit && !huoDong && i < dengJiList.size(); i++) {
                enterDengJiBossMap(dengJiList.at(i));
                Sleep(1000);
            }
            //斗笠
            for (int i = 0; !exit && !huoDong && i < douLiList.size(); i++) {
                enterDouLiBossMap(douLiList.at(i));
                Sleep(1000);
                if (i == douLiList.size() - 1 && fenJie[0]) {
                    fenJieSuiPian(FEN_JIE_TYPE_DOU_LI);
                }
            }
            //护盾
            for (int i = 0; !exit && !huoDong && i < huDunList.size(); i++) {
                enterHuDunBossMap(huDunList.at(i));
                Sleep(1000);
                if (i == huDunList.size() - 1 && fenJie[1]) {
                    fenJieSuiPian(FEN_JIE_TYPE_HU_DUN);
                }
            }
            //星座
            for (int i = 0; !exit && !huoDong && i < xingZuoList.size(); i++) {
                enterXingZuoBossMap(xingZuoList.at(i));
                Sleep(1000);
            }
            //八卦
            for (int i = 0; !exit && !huoDong && i < baGuaList.size(); i++) {
                enterBaGuaBossMap(baGuaList.at(i));
                Sleep(1000);
                if (i == baGuaList.size() - 1 && fenJie[2]) {
                    fenJieSuiPian(FEN_JIE_TYPE_BA_GUA);
                }
            }
            //金身
            for (int i = 0; !exit && !huoDong && i < jinShenList.size(); i ++) {
                enterJinShenBossMap(jinShenList.at(i));
                Sleep(1000);
            }
            //幽冥
            for (int i = 0; !exit && !huoDong && i < youMingList.size(); i++) {
                enterYouMingBossMap(youMingList.at(i));
                Sleep(1000);
                if (i == youMingList.size() - 1 && fenJie[3]) {
                    fenJieSuiPian(FEN_JIE_TYPE_YOU_MING);
                }
            }
            //驯龙
            for (int i = 0; !exit && !huoDong && i < xunLongList.size(); i++) {
                enterXunLongBossMap(xunLongList.at(i));
                Sleep(1000);
            }
            //神魔
            for (int i = 0; !exit && !huoDong && i < shenMoList.size(); i++) {
                enterShenMoBossMap(shenMoList.at(i));
                Sleep(1000);
            }
        }
    }
}

void MyWorker::backgroundClick(MyPoint point)
{
    if (!IsWindow(hwnd)) {
        qWarning() << "backgroundClick: 窗口不存在";
        return;
    }
    LPARAM lParam = MAKELPARAM(point.x, point.y);
    PostMessage(hwnd, WM_MOUSEMOVE, 0, lParam);
    PostMessage(hwnd, WM_LBUTTONDOWN, MK_LBUTTON, lParam);
    PostMessage(hwnd, WM_LBUTTONUP, 0, lParam);
}

void MyWorker::backgroundKeyPress(int keyCode)
{
    if (!IsWindow(hwnd)) {
        qWarning() << "backgroundKeyPress: 窗口不存在";
        return;
    }
    DWORD dwVKFkeydata; //lParam 参数值
    WORD dwScanCode = MapVirtualKey(keyCode, MAPVK_VK_TO_VSC);
    dwVKFkeydata = 1;
    dwVKFkeydata |= dwScanCode << 16;
    dwVKFkeydata |= 0 << 24;
    dwVKFkeydata |= 1 << 29;
    PostMessage(hwnd, WM_KEYDOWN, keyCode, dwVKFkeydata);

    dwVKFkeydata = 1;
    dwVKFkeydata |= dwScanCode << 16;
    dwVKFkeydata |= 0 << 24;
    dwVKFkeydata |= 1 << 29;
    dwVKFkeydata |= 3 << 30;
    PostMessage(hwnd, WM_KEYUP, keyCode, dwVKFkeydata);
}

bool MyWorker::checkPixelColor(MyPoint point, MyColor color)
{
    if (!IsWindow(hwnd)) {
        qWarning() << "checkPixelColor: 窗口不存在";
        return false;
    }

    //获取窗口上下文
    HDC hdc = GetDC(hwnd);
    if (hdc == NULL) {
        qWarning() << "checkPixelColor: hdc获取失败";
        return false;
    }
    COLORREF colorREF = GetPixel(hdc, point.x, point.y);

    //释放窗口上下文
    ReleaseDC(hwnd, hdc);

    unsigned char red = GetRValue(colorREF);
    unsigned char geen = GetGValue(colorREF);
    unsigned char blue = GetBValue(colorREF);
    //qDebug() << "R:" << red << ", G:" << geen << ", B:" << blue;

    if ((red > color.red - 5 && red < color.red + 5) && (geen > color.green - 5 && geen < color.green + 5) && (blue > color.blue - 5 && blue < color.blue + 5)) {
        return true;
    }
    return false;
}

void MyWorker::openShouLingTiaoZhanWindow(int typeIndex, int titleIndex)
{
    //清理窗口
    cleanWindow();

    //等待子窗口打开
    if (systemVersion < 11) {
        //win 10及以下
        //首领挑战 中心
        point[0].x = shouLingTiaoZhanPoint.x;
        point[0].y = shouLingTiaoZhanPoint.y;

        //左上
        point[1].x = escShouLingTiaoZhanRect.start.x;
        point[1].y = escShouLingTiaoZhanRect.start.y;

        //右上
        point[2].x = escShouLingTiaoZhanRect.start.x + escShouLingTiaoZhanRect.width;
        point[2].y = escShouLingTiaoZhanRect.start.y;

        //左下
        point[3].x = escShouLingTiaoZhanRect.start.x;
        point[3].y = escShouLingTiaoZhanRect.start.y + escShouLingTiaoZhanRect.height;

        //右下
        point[4].x = escShouLingTiaoZhanRect.start.x + escShouLingTiaoZhanRect.width;
        point[4].y = escShouLingTiaoZhanRect.start.y + escShouLingTiaoZhanRect.height;

    } else {
        //win 11
        //首领挑战 中心
        point[0].x = shouLingTiaoZhanPoint.x;
        point[0].y = shouLingTiaoZhanPoint.y;

        //左上
        point[1].x = escShouLingTiaoZhanRect.start.x;
        point[1].y = escShouLingTiaoZhanRect.start.y - DeltaY;

        //右上
        point[2].x = escShouLingTiaoZhanRect.start.x + escShouLingTiaoZhanRect.width;
        point[2].y = escShouLingTiaoZhanRect.start.y - DeltaY;

        //左下
        point[3].x = escShouLingTiaoZhanRect.start.x;
        point[3].y = escShouLingTiaoZhanRect.start.y + escShouLingTiaoZhanRect.height - DeltaY;

        //右下
        point[4].x = escShouLingTiaoZhanRect.start.x + escShouLingTiaoZhanRect.width;
        point[4].y = escShouLingTiaoZhanRect.start.y + escShouLingTiaoZhanRect.height - DeltaY;

    }
    //左上
    color[1].setColor(escShouLingTiaoZhanRect.strLeftUp);
    //右上
    color[2].setColor(escShouLingTiaoZhanRect.strRightUp);
    //左下
    color[3].setColor(escShouLingTiaoZhanRect.strLeftDown);
    //右下
    color[4].setColor(escShouLingTiaoZhanRect.strRightDown);

    //点击 首领挑战
    qDebug() << "openShouLingTiaoZhanWindow: 点击首领挑战:" + point[0].toString();
    backgroundClick(point[0]);

    //等等打开子窗口
    for (int i = 0; i < 15; i++) {
        Sleep(200);
        if (checkPixelColor(point[1], color[1]) && checkPixelColor(point[2], color[2])
            && checkPixelColor(point[3], color[3]) && checkPixelColor(point[4], color[4])) {
            Sleep(200);
            break;
        }
    }

    //右边类型
    if (systemVersion < 11) {
        //win 10及以下 y:->82
        point[0].x = typeRect.start.x + typeRect.width / 2;
        point[0].y = typeRect.start.y + typeRect.height / 2 + TypeStepY * typeIndex;

        //左上
        point[1].x = typeRect.start.x;
        point[1].y = typeRect.start.y + TypeStepY * typeIndex;

        //右上
        point[2].x = typeRect.start.x + typeRect.width;
        point[2].y = typeRect.start.y + TypeStepY * typeIndex;

        //左下
        point[3].x = typeRect.start.x;
        point[3].y = typeRect.start.y + typeRect.height + TypeStepY * typeIndex;
    } else {
        //win 11
        point[0].x = typeRect.start.x + typeRect.width / 2;
        point[0].y = typeRect.start.y + typeRect.height / 2 + TypeStepY * typeIndex - DeltaY;

        //左上
        point[1].x = typeRect.start.x;
        point[1].y = typeRect.start.y + TypeStepY * typeIndex - DeltaY;

        //右上
        point[2].x = typeRect.start.x + typeRect.width;
        point[2].y = typeRect.start.y + TypeStepY * typeIndex - DeltaY;

        //左下
        point[3].x = typeRect.start.x;
        point[3].y = typeRect.start.y + typeRect.height + TypeStepY * typeIndex - DeltaY;
    }
    //左上
    color[1].setColor(typeRect.strLeftUp);
    //右上
    color[2].setColor(typeRect.strRightUp);
    //左下
    color[3].setColor(typeRect.strLeftDown);

    //点击类型
    qDebug() << "openShouLingTiaoZhanWindow: 点击类型:" + point[0].toString();
    backgroundClick(point[0]);

    //等待子窗口
    for (int i = 0; i < 15; i++) {
        Sleep(200);
        if (checkPixelColor(point[1], color[1]) && checkPixelColor(point[2], color[2])
            && checkPixelColor(point[3], color[3])) {
            Sleep(200);
            break;
        }
    }

    //上面标题
    if (systemVersion < 11) {
        //win 10及以下
        //标题中心点
        point[0].x = titleRect.start.x + TitleStepX * titleIndex;
        point[0].y = titleRect.start.y + titleRect.height / 2;

        //左上
        point[1].x = titleRect.start.x + TitleStepX * titleIndex;
        point[1].y = titleRect.start.y;

        //左下
        point[3].x = titleRect.start.x + TitleStepX * titleIndex;
        point[3].y = titleRect.start.y + titleRect.height;
    } else {
        //win 11
        //标题中心点
        point[0].x = titleRect.start.x + TitleStepX * titleIndex;
        point[0].y = titleRect.start.y + titleRect.height / 2 - DeltaY;

        //左上
        point[1].x = titleRect.start.x + TitleStepX * titleIndex;
        point[1].y = titleRect.start.y - DeltaY;

        //左下
        point[3].x = titleRect.start.x + TitleStepX * titleIndex;
        point[3].y = titleRect.start.y + titleRect.height - DeltaY;
    }
    //xxBOSS中“B”左边上中下三点坐标
    //左上
    color[1].setColor(titleRect.strLeftUp);
    //左下
    color[3].setColor(titleRect.strLeftDown);

    //点击标题
    qDebug() << "openShouLingTiaoZhanWindow: 点击标题:" + point[0].toString();
    backgroundClick(point[0]);

    //等待子窗口
    for (int i = 0; i < 15; i++) {
        Sleep(200);
        if (checkPixelColor(point[1], color[1]) && checkPixelColor(point[3], color[3])) {
            Sleep(200);
            break;
        }
    }
}

void MyWorker::openListAndTableWindow(int listIndex, int tableIndex)
{
    //列表	368 460 552->92
    if (systemVersion < 11) {
        //win 10及以下
        //列表中心点
        point[0].x = listRect.start.x + listRect.width / 2;
        point[0].y = listRect.start.y + listRect.height / 2 + ListStepY * listIndex;

        //左上
        point[1].x = listRect.start.x;
        point[1].y = listRect.start.y;

        //左下
        point[3].x = listRect.start.x;
        point[3].y = listRect.start.y + listRect.height;

        //右下
        point[4].x = listRect.start.x + listRect.width;
        point[4].y = listRect.start.y + listRect.height;
    } else {
        //win 11
        //列表中心点
        point[0].x = listRect.start.x + listRect.width / 2;
        point[0].y = listRect.start.y + listRect.height / 2 + ListStepY * listIndex - DeltaY;

        //左上
        point[1].x = listRect.start.x;
        point[1].y = listRect.start.y - DeltaY;

        //左下
        point[3].x = listRect.start.x;
        point[3].y = listRect.start.y + listRect.height - DeltaY;

        //右下
        point[4].x = listRect.start.x + listRect.width;
        point[4].y = listRect.start.y + listRect.height - DeltaY;
    }
    //左上
    color[1].setColor(listRect.strLeftUp);
    //左下
    color[3].setColor(listRect.strLeftDown);
    //右下
    color[4].setColor(listRect.strRightDown);

    //点击列表中心点
    qDebug() << "openListAndTableWindow: 点击列表中心:" + point[0].toString();
    backgroundClick(point[0]);

    //等待子窗口
    for (int i = 0; i < 15; i++) {
        Sleep(200);
        if (checkPixelColor(point[1], color[1]) &&  checkPixelColor(point[3], color[3]) && checkPixelColor(point[4], color[4])) {
            Sleep(200);
            break;
        }
    }

    //点击表格
    int index = tableIndex;
    if (systemVersion < 11) {
        //win 10及以下 x:->220  y:->70
        if (tableIndex > 5) {
            //mouseDrag(TableX, TableY + TableStepY, TableX, TableY);
            mouseDrag(tablePoint.x, tablePoint.y + TableStepY, tablePoint.x, tablePoint.y);
            index = tableIndex - 3;
        }
        if (index < 3) {
            //pointCenter.setPoint(TableX + TableStepX * index, TableY);
            point[0].x = tablePoint.x + TableStepX * index;
            point[0].y = tablePoint.y;
        } else {
            //pointCenter.setPoint(TableX + TableStepX * (index - 3), TableY + TableStepY);
            point[0].x = tablePoint.x + TableStepX * (index - 3);
            point[0].y = tablePoint.y + TableStepY;
        }
    } else {
        //win 11
        //win 10及以下 x:->220  y:->70
        if (tableIndex > 5) {
            //mouseDrag(TableX, TableY + TableStepY - DeltaY, TableX, TableY - DeltaY);
            mouseDrag(tablePoint.x, tablePoint.y + TableStepY, tablePoint.x, tablePoint.y - DeltaY);
            index = tableIndex - 3;
        }
        if (index < 3) {
            //pointCenter.setPoint(TableX + TableStepX * index, TableY - DeltaY);
            point[0].x = tablePoint.x + TableStepX * index;
            point[0].y = tablePoint.y - DeltaY;
        } else {
            //pointCenter.setPoint(TableX + TableStepX * (index - 3), TableY + TableStepY - DeltaY);
            point[0].x = tablePoint.x + TableStepX * (index - 3);
            point[0].y = tablePoint.y + TableStepY - DeltaY;
        }
    }

    //点击表格（下方）
    qDebug() << "openListAndTableWindow: 点击表格中心:" + point[0].toString();
    backgroundClick(point[0]);
    Sleep(1000);
}

void MyWorker::openBaGuaListWindow(int listIndex)
{
    //点击八卦list
    int index = listIndex;
    int pointY;
    if (systemVersion < 11) {
        //win 10及以下 y:->77
        point[0].x = baGuaListRect.start.x + baGuaListRect.width / 2;
        if (listIndex > 5) {
            pointY = baGuaListRect.start.y + baGuaListRect.height / 2 + BaGuaListStepY * 5;
            mouseDrag(point[0].x, pointY, point[0].x, pointY - 70);
            index = 5;
        }
        point[0].y = baGuaListRect.start.y + baGuaListRect.height / 2 + BaGuaListStepY * index;
    } else {
        //win 11
        point[0].x = baGuaListRect.start.x + baGuaListRect.width / 2;
        if (listIndex > 5) {
            pointY = baGuaListRect.start.y + baGuaListRect.height / 2 + BaGuaListStepY * 5 - DeltaY;
            mouseDrag(point[0].x, pointY, point[0].x, pointY - 70);
            index = 5;
        }
        point[0].y = baGuaListRect.start.y + baGuaListRect.height / 2 + BaGuaListStepY * index - DeltaY;
    }
    backgroundClick(point[0]);

    //等待子窗口
    if (systemVersion < 11) {
        //win 10及以下
        //左上
        point[1].x = baGuaListRect.start.x;
        point[1].y = baGuaListRect.start.y + BaGuaListStepY * listIndex;

        //右上
        point[2].x = baGuaListRect.start.x + baGuaListRect.width;
        point[2].y = baGuaListRect.start.y + BaGuaListStepY * listIndex;

        //左下
        point[3].x = baGuaListRect.start.x;
        point[3].y = baGuaListRect.start.y + baGuaListRect.height + BaGuaListStepY * listIndex;

        //右下
        point[4].x = baGuaListRect.start.x + baGuaListRect.width;
        point[4].y = baGuaListRect.start.y + baGuaListRect.height + BaGuaListStepY * listIndex;

    } else {
        //win 11
        //左上
        point[1].x = baGuaListRect.start.x;
        point[1].y = baGuaListRect.start.y + BaGuaListStepY * listIndex - DeltaY;

        //右上
        point[2].x = baGuaListRect.start.x + baGuaListRect.width;
        point[2].y = baGuaListRect.start.y + BaGuaListStepY * listIndex - DeltaY;

        //左下
        point[3].x = baGuaListRect.start.x;
        point[3].y = baGuaListRect.start.y + baGuaListRect.height + BaGuaListStepY * listIndex - DeltaY;

        //右下
        point[4].x = baGuaListRect.start.x + baGuaListRect.width;
        point[4].y = baGuaListRect.start.y + baGuaListRect.height + BaGuaListStepY * listIndex - DeltaY;

    }
    //左上
    color[1].setColor(baGuaListRect.strLeftUp);
    //右上
    color[2].setColor(baGuaListRect.strRightUp);
    //左下
    color[3].setColor(baGuaListRect.strLeftDown);
    //右下
    color[4].setColor(baGuaListRect.strRightDown);

    for (int i = 0; i < 15; i++) {
        Sleep(200);
        if (checkPixelColor(point[1], color[1]) && checkPixelColor(point[2], color[2])
            && checkPixelColor(point[3], color[3]) && checkPixelColor(point[4], color[4])) {
            Sleep(200);
            break;
        }
    }

    //点击前往挑战
    if (systemVersion < 11) {
        //win 10及以下
        point[0].x = baGuaQianWangTiaoZhanPoint.x;
        point[0].y = baGuaQianWangTiaoZhanPoint.y;
    } else {
        //win 11
        point[0].x = baGuaQianWangTiaoZhanPoint.x;
        point[0].y = baGuaQianWangTiaoZhanPoint.y - DeltaY;
    }
    backgroundClick(point[0]);
    Sleep(1000);
}

void MyWorker::openTargetWindow(int targetIndex)
{
    //等待目标地图显示
    //左上
    point[1].x = escTargetMapRect.start.x;
    point[1].y = escTargetMapRect.start.y;

    //右上
    point[2].x = escTargetMapRect.start.x + escTargetMapRect.width;
    point[2].y = escTargetMapRect.start.y;

    //左下
    point[3].x = escTargetMapRect.start.x;
    point[3].y = escTargetMapRect.start.y + escTargetMapRect.height;

    //右下
    point[4].x = escTargetMapRect.start.x + escTargetMapRect.width;
    point[4].y = escTargetMapRect.start.y + escTargetMapRect.height;

    //左上
    color[1].setColor(escTargetMapRect.strLeftUp);
    //右上
    color[2].setColor(escTargetMapRect.strRightUp);
    //左下
    color[3].setColor(escTargetMapRect.strLeftDown);
    //右下
    color[4].setColor(escTargetMapRect.strRightDown);

    for (int i = 0; i < 35; i++) {
        Sleep(200);
        if (checkPixelColor(point[1], color[1]) && checkPixelColor(point[2], color[2])
            && checkPixelColor(point[3], color[3]) && checkPixelColor(point[4], color[4])) {
            Sleep(200);
            break;
        }
    }

    //点击目标地图
    if (systemVersion < 11) {
        //win 10及以下 x:->222 y:->86
        if (targetIndex < 2) {
            point[0].x = targetMapPoint.x + TargetMapStepX * targetIndex;
            point[0].y = targetMapPoint.y;
        } else if (targetIndex < 4) {
            point[0].x = targetMapPoint.x + TargetMapStepX * (targetIndex - 2);
            point[0].y = targetMapPoint.y + TargetMapStepY;
        } else if (targetIndex < 6) {
            point[0].x = targetMapPoint.x + TargetMapStepX * (targetIndex - 4);
            point[0].y = targetMapPoint.y + TargetMapStepY * 2;
        } else if (targetIndex < 8) {
            point[0].x = targetMapPoint.x + TargetMapStepX * (targetIndex - 6);
            point[0].y = targetMapPoint.y + TargetMapStepY * 3;
        } else if (targetIndex < 10) {
            point[0].x = targetMapPoint.x + TargetMapStepX * (targetIndex - 8);
            point[0].y = targetMapPoint.y + TargetMapStepY * 4;
        }
    } else {
        //win 11    x:->222 y:->86
        if (targetIndex < 2) {
            point[0].x = targetMapPoint.x + TargetMapStepX * targetIndex;
            point[0].y = targetMapPoint.y - DeltaY;
        } else if (targetIndex < 4) {
            point[0].x = targetMapPoint.x + TargetMapStepX * (targetIndex - 2);
            point[0].y = targetMapPoint.y + TargetMapStepY - DeltaY;
        } else if (targetIndex < 6) {
            point[0].x = targetMapPoint.x + TargetMapStepX * (targetIndex - 4);
            point[0].y = targetMapPoint.y + TargetMapStepY * 2 - DeltaY;
        } else if (targetIndex < 8) {
            point[0].x = targetMapPoint.x + TargetMapStepX * (targetIndex - 6);
            point[0].y = targetMapPoint.y + TargetMapStepY * 3 - DeltaY;
        } else if (targetIndex < 10) {
            point[0].x = targetMapPoint.x + TargetMapStepX * (targetIndex - 8);
            point[0].y = targetMapPoint.y + TargetMapStepY * 4 - DeltaY;
        }
    }
    //点击目标
    qDebug() << "openTargetWindow: 点击目标=" + point[0].toString();
    backgroundClick(point[0]);
    Sleep(2000);
}

void MyWorker::fenJieSuiPian(int fenJieType)
{
    if (fenJieType == FEN_JIE_TYPE_DOU_LI) {

    } else if (fenJieType == FEN_JIE_TYPE_HU_DUN) {

    } else if (fenJieType == FEN_JIE_TYPE_BA_GUA) {

    } else if (fenJieType == FEN_JIE_TYPE_YOU_MING) {

    }
}

void MyWorker::enterDengJiBossMap(QString name)
{
    qDebug() << "enterDengJiBossMap: name=" + name;
    if (exit || !IsWindow(hwnd)) {
        qWarning() << "enterDengJiBossMap: 窗口不存在";
        return;
    }

    if (name.endsWith("跨服")) {
        QTime now = QTime::currentTime();
        int hour = now.hour();
        int minute = now.minute();
        if (hour < 11) {
            return;
        }
        if (hour == 23 && minute > 40) {
            return;
        }
    }

    QList<int> list = pMapManager->getDengJiBossMapParameter(name, dengJiTop[0], dengJiTop[1], dengJiTop[2]);
    if (list.empty() || list.size() < 3) {
        qWarning() << "enterDengJiBossMap: 列表为空";
        return;
    }
    openShouLingTiaoZhanWindow(1, 0);
    openListAndTableWindow(list.at(0), list.at(1));
    openTargetWindow(list.at(2));
    //按Z触发战斗
    startZhanDou();
    //侦测打怪
    zhenCeDaGuai();
}

void MyWorker::enterDouLiBossMap(QString name)
{
    qDebug() << "enterDouLiBossMap: name=" + name;
    if (exit || !IsWindow(hwnd)) {
        qWarning() << "enterDouLiBossMap: 窗口不存在";
        return;
    }
    if (name.endsWith("跨服")) {
        QTime now = QTime::currentTime();
        int hour = now.hour();
        int minute = now.minute();
        if (hour < 11) {
            return;
        }
        if (hour == 23 && minute > 40) {
            return;
        }
    }
    QList<int> list = pMapManager->getDouLiBossMapParameter(name, douLiTop[0], douLiTop[1], douLiTop[2]);
    if (list.empty() || list.size() < 3) {
        qWarning() << "enterDouLiBossMap: 列表为空";
        return;
    }
    openShouLingTiaoZhanWindow(1, 1);
    openListAndTableWindow(list.at(0), list.at(1));
    openTargetWindow(list.at(2));
    //按Z触发战斗
    startZhanDou();
    //侦测打怪
    zhenCeDaGuai();
}

void MyWorker::enterHuDunBossMap(QString name)
{
    qDebug() << "enterHuDunBossMap: name=" + name;
    if (exit || !IsWindow(hwnd)) {
        qWarning() << "enterHuDunBossMap: 窗口不存在";
        return;
    }
    if (name.endsWith("跨服")) {
        QTime now = QTime::currentTime();
        int hour = now.hour();
        int minute = now.minute();
        if (hour < 11) {
            return;
        }
        if (hour == 23 && minute > 40) {
            return;
        }
    }
    QList<int> list = pMapManager->getHuDunBossMapParameter(name, huDunTop[0], huDunTop[1], huDunTop[2]);
    if (list.empty() || list.size() < 3) {
        qWarning() << "enterHuDunBossMap: 列表为空";
        return;
    }
    openShouLingTiaoZhanWindow(1, 2);
    openListAndTableWindow(list.at(0), list.at(1));
    openTargetWindow(list.at(2));
    //按Z触发战斗
    startZhanDou();
    //侦测打怪
    zhenCeDaGuai();
}

void MyWorker::enterXingZuoBossMap(QString name)
{
    qDebug() << "enterXingZuoBossMap: name=" + name;
    if (exit || !IsWindow(hwnd)) {
        qWarning() << "enterXingZuoBossMap: 窗口不存在";
        return;
    }
    if (name.endsWith("跨服")) {
        QTime now = QTime::currentTime();
        int hour = now.hour();
        int minute = now.minute();
        if (hour < 11) {
            return;
        }
        if (hour == 23 && minute > 40) {
            return;
        }
    }
    QList<int> list = pMapManager->getXingZuoBossMapParameter(name, xingZuoTop[0], xingZuoTop[1], xingZuoTop[2]);
    if (list.empty() || list.size() < 3) {
        qWarning() << "enterXingZuoBossMap: 列表为空";
        return;
    }
    openShouLingTiaoZhanWindow(1, 3);
    openListAndTableWindow(list.at(0), list.at(1));
    openTargetWindow(list.at(2));
    //按Z触发战斗
    startZhanDou();
    //侦测打怪
    zhenCeDaGuai();
}

void MyWorker::enterBaGuaBossMap(QString name)
{
    qDebug() << "enterBaGuaBossMap: name=" + name;
    if (exit || !IsWindow(hwnd)) {
        qWarning() << "enterBaGuaBossMap: 窗口不存在";
        return;
    }

    int listIndex = name.mid(2, 1).toInt();
    openShouLingTiaoZhanWindow(3, 0);
    openBaGuaListWindow(listIndex - 1);
    //按Z触发战斗
    startZhanDou();
    //侦测打怪
    zhenCeDaGuai();
}

void MyWorker::enterJinShenBossMap(QString name)
{
    qDebug() << "enterJinShenBossMap: name=" + name;
    if (exit || !IsWindow(hwnd)) {
        qWarning() << "enterJinShenBossMap: 窗口不存在";
        return;
    }
    if (name.endsWith("跨服")) {
        QTime now = QTime::currentTime();
        int hour = now.hour();
        int minute = now.minute();
        if (hour < 11) {
            return;
        }
        if (hour == 23 && minute > 40) {
            return;
        }
    }
    QList<int> list = pMapManager->getJinShenBossMapParameter(name, jinShenTop[0], jinShenTop[1], jinShenTop[2]);
    if (list.empty() || list.size() < 3) {
        qWarning() << "enterJinShenBossMap: 列表为空";
        return;
    }
    openShouLingTiaoZhanWindow(1, 6);
    openListAndTableWindow(list.at(0), list.at(1));
    openTargetWindow(list.at(2));
    //按Z触发战斗
    startZhanDou();
    //侦测打怪
    zhenCeDaGuai();
}

void MyWorker::enterYouMingBossMap(QString name)
{
    qDebug() << "enterYouMingBossMap: name=" + name;
    if (exit || !IsWindow(hwnd)) {
        qWarning() << "enterYouMingBossMap: 窗口不存在";
        return;
    }
    if (name.endsWith("跨服")) {
        QTime now = QTime::currentTime();
        int hour = now.hour();
        int minute = now.minute();
        if (hour < 11) {
            return;
        }
        if (hour == 23 && minute > 40) {
            return;
        }
    }
    QList<int> list = pMapManager->getYouMingBossMapParameter(name, youMingTop[0], youMingTop[1], youMingTop[2]);
    if (list.empty() || list.size() < 2) {
        qWarning() << "enterYouMingBossMap: 列表为空";
        return;
    }
    openShouLingTiaoZhanWindow(4, 0);
    openListAndTableWindow(list.at(0), list.at(1));
    if (name.endsWith("跨服")) {
        openTargetWindow(list.at(2));
        //按Z触发战斗
        startZhanDou();
    }
    //侦测打怪
    zhenCeDaGuai();
}

void MyWorker::enterXunLongBossMap(QString name)
{
    qDebug() << "enterXunLongBossMap: name=" + name;
    if (exit || !IsWindow(hwnd)) {
        qWarning() << "enterXunLongBossMap: 窗口不存在";
        return;
    }
    if (name.endsWith("跨服")) {
        QTime now = QTime::currentTime();
        int hour = now.hour();
        int minute = now.minute();
        if (hour < 11) {
            return;
        }
        if (hour == 23 && minute > 40) {
            return;
        }
    }
    QList<int> list = pMapManager->getXunLongBossMapParameter(name, xunLongTop[0], xunLongTop[1], xunLongTop[2]);
    if (list.empty() || list.size() < 2) {
        qWarning() << "enterXunLongBossMap: 列表为空";
        return;
    }
    openShouLingTiaoZhanWindow(4, 3);
    openListAndTableWindow(list.at(0), list.at(1));
    if (name.endsWith("跨服")) {
        openTargetWindow(list.at(2));
        //按Z触发战斗
        startZhanDou();
    }
    //侦测打怪
    zhenCeDaGuai();
}

void MyWorker::enterShenMoBossMap(QString name)
{
    qDebug() << "enterShenMoBossMap: name=" + name;
    if (exit || !IsWindow(hwnd)) {
        qWarning() << "enterShenMoBossMap: 窗口不存在";
        return;
    }
    if (name.endsWith("跨服")) {
        QTime now = QTime::currentTime();
        int hour = now.hour();
        int minute = now.minute();
        if (hour < 11) {
            return;
        }
        if (hour == 23 && minute > 40) {
            return;
        }
    }
    QList<int> list = pMapManager->getShenMoBossMapPerameter(name, shenMoTop[0], shenMoTop[1], shenMoTop[2]);
    if (list.empty() || list.size() < 3) {
        qWarning() << "enterShenMoBossMap: 列表为空";
        return;
    }
    openShouLingTiaoZhanWindow(4, 5);
    openListAndTableWindow(list.at(0), list.at(1));
    openTargetWindow(list.at(2));
    //按Z触发战斗
    startZhanDou();
    //侦测打怪
    zhenCeDaGuai();
}

void MyWorker::openHuoDongRightWindow()
{
    //检测右上角活动子窗口
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
        point[3].x = escHuoDongRRect.start.x + escHuoDongRRect.width;
        point[3].y = escHuoDongRRect.start.y + escHuoDongRRect.height;

        //点击前往
        point[0].x = dianJiQianWangPoint.x;
        point[0].y = dianJiQianWangPoint.y;
    } else {
        //win 11
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
        point[3].x = escHuoDongRRect.start.x + escHuoDongRRect.width;
        point[3].y = escHuoDongRRect.start.y + escHuoDongRRect.height;

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

void MyWorker::openHuoDongLeftWindow()
{
    //检测左上角活动子窗口
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
        point[3].x = escHuoDongLRect.start.x + escHuoDongLRect.width;
        point[3].y = escHuoDongLRect.start.y + escHuoDongLRect.height;

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
        point[3].x = escHuoDongLRect.start.x + escHuoDongLRect.width;
        point[3].y = escHuoDongLRect.start.y + escHuoDongLRect.height;

        //点击前往
        point[0].x = jinRuPoint.x;
        point[0].y = jinRuPoint.y;
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

void MyWorker::openHuoDongCenterWindow()
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

void MyWorker::doMoLong()
{
    if (exit || !IsWindow(hwnd)) {
        qWarning() << "doMoLong: 结束或者窗口不存在";
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

void MyWorker::doHuangJinShu()
{
    if (exit || !IsWindow(hwnd)) {
        qWarning() << "doHuangJinShu: 结束或者窗口不存在";
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

void MyWorker::doShiJieBoss()
{
    if (exit || !IsWindow(hwnd)) {
        qWarning() << "doShiJieBoss: 结束或者窗口不存在";
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

void MyWorker::doHangHuiShiLian()
{
    if (exit || !IsWindow(hwnd)) {
        qWarning() << "doHangHuiShiLian: 结束或者窗口不存在";
        return;
    }

    //清理窗口
    cleanWindow();

    //点击魔龙图标
    if (systemVersion < 11) {
        //win 10及以下
        point[0].x = huoDongPoint.x;
        point[0].y = huoDongPoint.y;
    } else {
        //win 11
        point[0].x = huoDongPoint.x;
        point[0].y = huoDongPoint.y;
    }
    backgroundClick(point[0]);

    //打开右上角活动子窗口
    openHuoDongRightWindow();

    //打开中间子窗口
    openHuoDongCenterWindow();

    while (!exit && huoDong && IsWindow(hwnd)) {
        Sleep(1000);
    }
}

void MyWorker::mouseDrag(int startX, int startY, int endX, int endY)
{
    // 将鼠标移动到起始位置并按下左键
    LPARAM lParamStart = MAKELPARAM(startX, startY);
    SendMessage(hwnd, WM_MOUSEMOVE, MK_LBUTTON, lParamStart);
    SendMessage(hwnd, WM_LBUTTONDOWN, MK_LBUTTON, lParamStart);
    /*
    // 计算每步的移动增量
    double deltaX = (endX - startX) / (double)steps;
    double deltaY = (endY - startY) / (double)steps;

    for(int i = 1; i <= steps; ++i) {
        int currentX = startX + static_cast<int>(deltaX * i);
        int currentY = startY + static_cast<int>(deltaY * i);
        LPARAM lParamMove = MAKELPARAM(currentX, currentY);
        SendMessage(hwnd, WM_MOUSEMOVE, MK_LBUTTON, lParamMove);
        Sleep(10); // 添加延迟，使拖动过程更自然
    }
    */
    Sleep(400);
    // 在结束位置松开左键
    LPARAM lParamEnd = MAKELPARAM(endX, endY);
    SendMessage(hwnd, WM_MOUSEMOVE, MK_LBUTTON, lParamEnd);
    Sleep(100);
    SendMessage(hwnd, WM_LBUTTONUP, 0, lParamEnd);
}

