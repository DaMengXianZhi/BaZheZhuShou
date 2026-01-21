#include "MainWindow.h"
#include "ui_MainWindow.h"

#include "Define.h"
#include "DaTingWorker.h"
#include "ZhongXinWorker.h"

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    mType = TYPE_BO_JIN;
    mZone = ZONE_NEW;
    mPlatform = PLATFORM_DA_TING;

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

    //设置
    pSettings = new QSettings("config.ini", QSettings::IniFormat);

    pMapManager = new MapManager();

    //大小号线程
    pMaxThread = new QThread(this);
    pMinThread = new QThread(this);
    //大小号状态
    maxInited = false;
    minInited = false;
    maxStarted = false;
    minStarted = false;
    maxInHuoDong = false;
    minInHuoDong = false;

    pTimer = new QTimer(this);
    pTimer->setInterval(5000);
    connect(pTimer, &QTimer::timeout, this, &MainWindow::onTimerOut);

    //开始、停止 处理
    connect(ui->pushButtonBack, &QPushButton::clicked, this, &MainWindow::onBackButtonClicked);
    connect(ui->pushButtonStart, &QPushButton::clicked, this, &MainWindow::onStartButtonClicked);
    connect(ui->pushButtonStop, &QPushButton::clicked, this, &MainWindow::onStopButtonClicked);
    connect(ui->pushButtonSave, &QPushButton::clicked, this, &MainWindow::onSaveButtonClicked);
    connect(ui->pushButtonClean, &QPushButton::clicked, this, &MainWindow::onCleanButtonClicked);

    //大小号窗口句柄
    connect(ui->comboBoxMaxId, &QComboBox::currentIndexChanged, this, &MainWindow::onMaxWindowHwndChanged);
    connect(ui->comboBoxMinId, &QComboBox::currentIndexChanged, this, &MainWindow::onMinWindowHwndChanged);

    //等级boss置顶变更事件
    connect(ui->comboBoxMaxDengJiTop1, &QComboBox::currentIndexChanged, this, &MainWindow::onMaxDengJiTopChanged);
    connect(ui->comboBoxMaxDengJiTop2, &QComboBox::currentIndexChanged, this, &MainWindow::onMaxDengJiTopChanged);
    connect(ui->comboBoxMaxDengJiTop3, &QComboBox::currentIndexChanged, this, &MainWindow::onMaxDengJiTopChanged);

    connect(ui->comboBoxMinDengJiTop1, &QComboBox::currentIndexChanged, this, &MainWindow::onMinDengJiTopChanged);
    connect(ui->comboBoxMinDengJiTop2, &QComboBox::currentIndexChanged, this, &MainWindow::onMinDengJiTopChanged);
    connect(ui->comboBoxMinDengJiTop3, &QComboBox::currentIndexChanged, this, &MainWindow::onMinDengJiTopChanged);

    //斗笠boss置顶变更事件
    connect(ui->comboBoxMaxDouLiTop1, &QComboBox::currentIndexChanged, this, &MainWindow::onMaxDouLiTopChanged);
    connect(ui->comboBoxMaxDouLiTop2, &QComboBox::currentIndexChanged, this, &MainWindow::onMaxDouLiTopChanged);
    connect(ui->comboBoxMaxDouLiTop3, &QComboBox::currentIndexChanged, this, &MainWindow::onMaxDouLiTopChanged);

    connect(ui->comboBoxMinDouLiTop1, &QComboBox::currentIndexChanged, this, &MainWindow::onMinDouLiTopChanged);
    connect(ui->comboBoxMinDouLiTop2, &QComboBox::currentIndexChanged, this, &MainWindow::onMinDouLiTopChanged);
    connect(ui->comboBoxMinDouLiTop3, &QComboBox::currentIndexChanged, this, &MainWindow::onMinDouLiTopChanged);
    //护盾boss置顶变更事件
    connect(ui->comboBoxMaxHuDunTop1, &QComboBox::currentIndexChanged, this, &MainWindow::onMaxHuDunTopChanged);
    connect(ui->comboBoxMaxHuDunTop2, &QComboBox::currentIndexChanged, this, &MainWindow::onMaxHuDunTopChanged);
    connect(ui->comboBoxMaxHuDunTop3, &QComboBox::currentIndexChanged, this, &MainWindow::onMaxHuDunTopChanged);

    connect(ui->comboBoxMinHuDunTop1, &QComboBox::currentIndexChanged, this, &MainWindow::onMinHuDunTopChanged);
    connect(ui->comboBoxMinHuDunTop2, &QComboBox::currentIndexChanged, this, &MainWindow::onMinHuDunTopChanged);
    connect(ui->comboBoxMinHuDunTop3, &QComboBox::currentIndexChanged, this, &MainWindow::onMinHuDunTopChanged);
    //星座boss置顶变更事件
    connect(ui->comboBoxMaxXingZuoTop1, &QComboBox::currentIndexChanged, this, &MainWindow::onMaxXingZuoTopChanged);
    connect(ui->comboBoxMaxXingZuoTop2, &QComboBox::currentIndexChanged, this, &MainWindow::onMaxXingZuoTopChanged);
    connect(ui->comboBoxMaxXingZuoTop3, &QComboBox::currentIndexChanged, this, &MainWindow::onMaxXingZuoTopChanged);

    connect(ui->comboBoxMinXingZuoTop1, &QComboBox::currentIndexChanged, this, &MainWindow::onMinXingZuoTopChanged);
    connect(ui->comboBoxMinXingZuoTop2, &QComboBox::currentIndexChanged, this, &MainWindow::onMinXingZuoTopChanged);
    connect(ui->comboBoxMinXingZuoTop3, &QComboBox::currentIndexChanged, this, &MainWindow::onMinXingZuoTopChanged);
    //金身boss置顶变更事件
    connect(ui->comboBoxMaxJinShenTop1, &QComboBox::currentIndexChanged, this, &MainWindow::onMaxJinShenTopChanged);
    connect(ui->comboBoxMaxJinShenTop2, &QComboBox::currentIndexChanged, this, &MainWindow::onMaxJinShenTopChanged);
    connect(ui->comboBoxMaxJinShenTop3, &QComboBox::currentIndexChanged, this, &MainWindow::onMaxJinShenTopChanged);

    connect(ui->comboBoxMinJinShenTop1, &QComboBox::currentIndexChanged, this, &MainWindow::onMinJinShenTopChanged);
    connect(ui->comboBoxMinJinShenTop2, &QComboBox::currentIndexChanged, this, &MainWindow::onMinJinShenTopChanged);
    connect(ui->comboBoxMinJinShenTop3, &QComboBox::currentIndexChanged, this, &MainWindow::onMinJinShenTopChanged);
    //幽冥boss置顶变更事件
    connect(ui->comboBoxMaxYouMingTop1, &QComboBox::currentIndexChanged, this, &MainWindow::onMaxYouMingTopChanged);
    connect(ui->comboBoxMaxYouMingTop2, &QComboBox::currentIndexChanged, this, &MainWindow::onMaxYouMingTopChanged);
    connect(ui->comboBoxMaxYouMingTop3, &QComboBox::currentIndexChanged, this, &MainWindow::onMaxYouMingTopChanged);

    connect(ui->comboBoxMinYouMingTop1, &QComboBox::currentIndexChanged, this, &MainWindow::onMinYouMingTopChanged);
    connect(ui->comboBoxMinYouMingTop2, &QComboBox::currentIndexChanged, this, &MainWindow::onMinYouMingTopChanged);
    connect(ui->comboBoxMinYouMingTop3, &QComboBox::currentIndexChanged, this, &MainWindow::onMinYouMingTopChanged);
    //驯龙boss置顶变更事件
    connect(ui->comboBoxMaxXunLongTop1, &QComboBox::currentIndexChanged, this, &MainWindow::onMaxXunLongTopChanged);
    connect(ui->comboBoxMaxXunLongTop2, &QComboBox::currentIndexChanged, this, &MainWindow::onMaxXunLongTopChanged);
    connect(ui->comboBoxMaxXunLongTop3, &QComboBox::currentIndexChanged, this, &MainWindow::onMaxXunLongTopChanged);

    connect(ui->comboBoxMinXunLongTop1, &QComboBox::currentIndexChanged, this, &MainWindow::onMinXunLongTopChanged);
    connect(ui->comboBoxMinXunLongTop2, &QComboBox::currentIndexChanged, this, &MainWindow::onMinXunLongTopChanged);
    connect(ui->comboBoxMinXunLongTop3, &QComboBox::currentIndexChanged, this, &MainWindow::onMinXunLongTopChanged);
    //神魔boss置顶变更事件
    connect(ui->comboBoxMaxShenMoTop1, &QComboBox::currentIndexChanged, this, &MainWindow::onMaxShenMoTopChanged);
    connect(ui->comboBoxMaxShenMoTop2, &QComboBox::currentIndexChanged, this, &MainWindow::onMaxShenMoTopChanged);
    connect(ui->comboBoxMaxShenMoTop3, &QComboBox::currentIndexChanged, this, &MainWindow::onMaxShenMoTopChanged);

    connect(ui->comboBoxMinShenMoTop1, &QComboBox::currentIndexChanged, this, &MainWindow::onMinShenMoTopChanged);
    connect(ui->comboBoxMinShenMoTop2, &QComboBox::currentIndexChanged, this, &MainWindow::onMinShenMoTopChanged);
    connect(ui->comboBoxMinShenMoTop3, &QComboBox::currentIndexChanged, this, &MainWindow::onMinShenMoTopChanged);
}

MainWindow::~MainWindow()
{
    delete ui;
    if (pMaxThread->isRunning()) {
        pMaxWorker->exitWorking();
        pMaxThread->quit();
        pMaxThread->wait();
    }
    delete pMaxWorker;
    delete pMaxThread;

    if (pMinThread->isRunning()) {
        pMinWorker->exitWorking();
        pMinThread->quit();
        pMinThread->wait();
    }
    delete pMinWorker;
    delete pMinThread;
}

void MainWindow::initWindow(int platform, int type, int zone, QDate endDate)
{
    mPlatform = platform;
    mZone = zone;
    mType = type;
    mEndDate = endDate;

    if (mZone == ZONE_NEW) {
        pMapManager->setNewZone(true);
    } else if (mZone == ZONE_OLD) {
        pMapManager->setNewZone(false);
    }

    initJiChuPage();
    initDengJiPage();
    initDouLiPage();
    initHuDunPage();
    initXingZuoPage();
    initJinShenPage();
    initBaGuaPage();
    initYouMingPage();
    initXunLongPage();
    initShenMoPage();
    //恢复设置
    resumeSettings();
    //初始化游戏窗口句柄
    initHwnd();

    ui->tabWidget->setCurrentIndex(0);
    ui->labelTimeMessage->setText(endDate.toString());
}

void MainWindow::initJiChuPage()
{
    //大号
    ui->checkBoxMaxEnable->setEnabled(true);
    ui->comboBoxMaxId->setEnabled(true);
    if (mType == TYPE_BO_JIN) {
        ui->checkBoxMaxZhenCe->setEnabled(false);
    } else {
        ui->checkBoxMaxZhenCe->setEnabled(true);
    }
    ui->checkBoxMaxFuHuo->setEnabled(true);
    ui->checkBoxMaxChongLian->setEnabled(true);
    ui->checkBoxMaxSuiJi->setEnabled(true);
    ui->checkBoxMaxZhuangBei->setEnabled(true);
    ui->checkBoxMaxHangHuiMode->setEnabled(true);
    ui->checkBoxMaxXiuMian->setEnabled(true);
    ui->timeEditMaxStart->setEnabled(true);
    ui->timeEditMaxEnd->setEnabled(true);
    //活动
    ui->checkBoxMaxMoLongBaoZang->setEnabled(true);
    ui->checkBoxMaxShiJieBoss->setEnabled(true);
    ui->checkBoxMaxHuangJinShu->setEnabled(true);
    ui->checkBoxMaxHangHuiShiLian->setEnabled(true);
    //分解
    ui->checkBoxMaxFenJieDouLi->setEnabled(true);
    ui->checkBoxMaxFenJieHuDun->setEnabled(true);
    ui->checkBoxMaxFenJieBaGua->setEnabled(true);
    ui->checkBoxMaxFenJieYouMing->setEnabled(true);

    if (mType == TYPE_ZHI_ZUN) {
        //小号
        ui->checkBoxMinEnable->setEnabled(true);
        ui->comboBoxMinId->setEnabled(true);
        ui->checkBoxMinZhenCe->setEnabled(true);
        ui->checkBoxMinFuHuo->setEnabled(true);
        ui->checkBoxMinChongLian->setEnabled(true);
        ui->checkBoxMinSuiJi->setEnabled(true);
        ui->checkBoxMinZhuangBei->setEnabled(true);
        ui->checkBoxMinHangHuiMode->setEnabled(true);
        ui->checkBoxMinXiuMian->setEnabled(true);
        ui->timeEditMinStart->setEnabled(true);
        ui->timeEditMinEnd->setEnabled(true);
        //活动
        ui->checkBoxMinMoLongBaoZang->setEnabled(true);
        ui->checkBoxMinShiJieBoss->setEnabled(true);
        ui->checkBoxMinHuangJinShu->setEnabled(true);
        ui->checkBoxMinHangHuiShiLian->setEnabled(true);
        //分解
        ui->checkBoxMinFenJieDouLi->setEnabled(true);
        ui->checkBoxMinFenJieHuDun->setEnabled(true);
        ui->checkBoxMinFenJieBaGua->setEnabled(true);
        ui->checkBoxMinFenJieYouMing->setEnabled(true);
    } else {
        //小号
        ui->checkBoxMinEnable->setEnabled(false);
        ui->comboBoxMinId->setEnabled(false);
        ui->checkBoxMinZhenCe->setEnabled(false);
        ui->checkBoxMinFuHuo->setEnabled(false);
        ui->checkBoxMinChongLian->setEnabled(false);
        ui->checkBoxMinSuiJi->setEnabled(false);
        ui->checkBoxMinZhuangBei->setEnabled(false);
        ui->checkBoxMinHangHuiMode->setEnabled(false);
        ui->checkBoxMinXiuMian->setEnabled(false);
        ui->timeEditMinStart->setEnabled(false);
        ui->timeEditMinEnd->setEnabled(false);
        //活动
        ui->checkBoxMinMoLongBaoZang->setEnabled(false);
        ui->checkBoxMinShiJieBoss->setEnabled(false);
        ui->checkBoxMinHuangJinShu->setEnabled(false);
        ui->checkBoxMinHangHuiShiLian->setEnabled(false);
        //分解
        ui->checkBoxMinFenJieDouLi->setEnabled(false);
        ui->checkBoxMinFenJieHuDun->setEnabled(false);
        ui->checkBoxMinFenJieBaGua->setEnabled(false);
        ui->checkBoxMinFenJieYouMing->setEnabled(false);
    }
}

void MainWindow::initDengJiPage()
{
    //大号
    //置顶等级
    ui->comboBoxMaxDengJiTop1->setEnabled(true);
    ui->comboBoxMaxDengJiTop2->setEnabled(true);
    ui->comboBoxMaxDengJiTop3->setEnabled(true);
    //地图
    ui->checkBoxMaxDengJiMap1->setEnabled(true);
    ui->checkBoxMaxDengJiMap2->setEnabled(true);
    ui->checkBoxMaxDengJiMap3->setEnabled(true);
    ui->checkBoxMaxDengJiMap4->setEnabled(true);
    ui->checkBoxMaxDengJiMap5->setEnabled(true);
    ui->checkBoxMaxDengJiMap6->setEnabled(true);
    ui->checkBoxMaxDengJiMap7->setEnabled(true);
    ui->checkBoxMaxDengJiMap8->setEnabled(true);
    //列表
    ui->comboBoxMaxDengJiList1->setEnabled(true);
    ui->comboBoxMaxDengJiList2->setEnabled(true);
    ui->comboBoxMaxDengJiList3->setEnabled(true);
    ui->comboBoxMaxDengJiList4->setEnabled(true);
    ui->comboBoxMaxDengJiList5->setEnabled(true);
    ui->comboBoxMaxDengJiList6->setEnabled(true);
    ui->comboBoxMaxDengJiList7->setEnabled(true);
    ui->comboBoxMaxDengJiList8->setEnabled(true);

    if (mType == TYPE_ZHI_ZUN) {
        //大号
        if (mZone == ZONE_NEW) {
            //新区
            initComboBox(ui->comboBoxMaxDengJiTop1, 450, 1200);
            initComboBox(ui->comboBoxMaxDengJiTop2, 450, 1200);
            initComboBox(ui->comboBoxMaxDengJiTop3, 450, 1200);
        } else if (mZone == ZONE_OLD) {
            //老区
            initComboBox(ui->comboBoxMaxDengJiTop1, 600, 1200);
            initComboBox(ui->comboBoxMaxDengJiTop2, 600, 1200);
            initComboBox(ui->comboBoxMaxDengJiTop3, 600, 1200);
        }

        //小号
        //置顶等级
        ui->comboBoxMinDengJiTop1->setEnabled(true);
        ui->comboBoxMinDengJiTop2->setEnabled(true);
        ui->comboBoxMinDengJiTop3->setEnabled(true);

        if (mZone == ZONE_NEW) {
            //新区
            initComboBox(ui->comboBoxMinDengJiTop1, 450, 1200);
            initComboBox(ui->comboBoxMinDengJiTop2, 450, 1200);
            initComboBox(ui->comboBoxMinDengJiTop3, 450, 1200);
        } else if (mZone == ZONE_OLD) {
            //老区
            initComboBox(ui->comboBoxMinDengJiTop1, 600, 1200);
            initComboBox(ui->comboBoxMinDengJiTop2, 600, 1200);
            initComboBox(ui->comboBoxMinDengJiTop3, 600, 1200);
        }

        //地图
        ui->checkBoxMinDengJiMap1->setEnabled(true);
        ui->checkBoxMinDengJiMap2->setEnabled(true);
        ui->checkBoxMinDengJiMap3->setEnabled(true);
        ui->checkBoxMinDengJiMap4->setEnabled(true);
        ui->checkBoxMinDengJiMap5->setEnabled(true);
        ui->checkBoxMinDengJiMap6->setEnabled(true);
        ui->checkBoxMinDengJiMap7->setEnabled(true);
        ui->checkBoxMinDengJiMap8->setEnabled(true);
        //列表
        ui->comboBoxMinDengJiList1->setEnabled(true);
        ui->comboBoxMinDengJiList2->setEnabled(true);
        ui->comboBoxMinDengJiList3->setEnabled(true);
        ui->comboBoxMinDengJiList4->setEnabled(true);
        ui->comboBoxMinDengJiList5->setEnabled(true);
        ui->comboBoxMinDengJiList6->setEnabled(true);
        ui->comboBoxMinDengJiList7->setEnabled(true);
        ui->comboBoxMinDengJiList8->setEnabled(true);
    } else {
        //大号
        if (mZone == ZONE_NEW) {
            //新区
            initComboBox(ui->comboBoxMaxDengJiTop1, 450, 1050);
            initComboBox(ui->comboBoxMaxDengJiTop2, 450, 1050);
            initComboBox(ui->comboBoxMaxDengJiTop3, 450, 1050);
        } else if (mZone == ZONE_OLD) {
            //老区
            initComboBox(ui->comboBoxMaxDengJiTop1, 600, 1050);
            initComboBox(ui->comboBoxMaxDengJiTop2, 600, 1050);
            initComboBox(ui->comboBoxMaxDengJiTop3, 600, 1050);
        }

        //小号
        //置顶等级
        ui->comboBoxMinDengJiTop1->setEnabled(false);
        ui->comboBoxMinDengJiTop2->setEnabled(false);
        ui->comboBoxMinDengJiTop3->setEnabled(false);

        //地图
        ui->checkBoxMinDengJiMap1->setEnabled(false);
        ui->checkBoxMinDengJiMap2->setEnabled(false);
        ui->checkBoxMinDengJiMap3->setEnabled(false);
        ui->checkBoxMinDengJiMap4->setEnabled(false);
        ui->checkBoxMinDengJiMap5->setEnabled(false);
        ui->checkBoxMinDengJiMap6->setEnabled(false);
        ui->checkBoxMinDengJiMap7->setEnabled(false);
        ui->checkBoxMinDengJiMap8->setEnabled(false);
        //列表
        ui->comboBoxMinDengJiList1->setEnabled(false);
        ui->comboBoxMinDengJiList2->setEnabled(false);
        ui->comboBoxMinDengJiList3->setEnabled(false);
        ui->comboBoxMinDengJiList4->setEnabled(false);
        ui->comboBoxMinDengJiList5->setEnabled(false);
        ui->comboBoxMinDengJiList6->setEnabled(false);
        ui->comboBoxMinDengJiList7->setEnabled(false);
        ui->comboBoxMinDengJiList8->setEnabled(false);
    }
}

void MainWindow::initDouLiPage()
{
    //大号
    //置顶
    ui->comboBoxMaxDouLiTop1->setEnabled(true);
    ui->comboBoxMaxDouLiTop2->setEnabled(true);
    ui->comboBoxMaxDouLiTop3->setEnabled(true);
    //地图
    ui->checkBoxMaxDouLiMap1->setEnabled(true);
    ui->checkBoxMaxDouLiMap2->setEnabled(true);
    ui->checkBoxMaxDouLiMap3->setEnabled(true);
    ui->checkBoxMaxDouLiMap4->setEnabled(true);
    ui->checkBoxMaxDouLiMap5->setEnabled(true);
    ui->checkBoxMaxDouLiMap6->setEnabled(true);
    ui->checkBoxMaxDouLiMap7->setEnabled(true);
    ui->checkBoxMaxDouLiMap8->setEnabled(true);
    //列表
    ui->comboBoxMaxDouLiList1->setEnabled(true);
    ui->comboBoxMaxDouLiList2->setEnabled(true);
    ui->comboBoxMaxDouLiList3->setEnabled(true);
    ui->comboBoxMaxDouLiList4->setEnabled(true);
    ui->comboBoxMaxDouLiList5->setEnabled(true);
    ui->comboBoxMaxDouLiList6->setEnabled(true);
    ui->comboBoxMaxDouLiList7->setEnabled(true);
    ui->comboBoxMaxDouLiList8->setEnabled(true);

    if (mType == TYPE_ZHI_ZUN) {
        //大号
        if (mZone == ZONE_NEW) {
            //新区
            initComboBox(ui->comboBoxMaxDouLiTop1, 100, 1200);
            initComboBox(ui->comboBoxMaxDouLiTop2, 100, 1200);
            initComboBox(ui->comboBoxMaxDouLiTop3, 100, 1200);
        } else if (mZone == ZONE_OLD) {
            //老区
            initComboBox(ui->comboBoxMaxDouLiTop1, 600, 1200);
            initComboBox(ui->comboBoxMaxDouLiTop2, 600, 1200);
            initComboBox(ui->comboBoxMaxDouLiTop3, 600, 1200);
        }

        //小号
        //置顶
        ui->comboBoxMinDouLiTop1->setEnabled(true);
        ui->comboBoxMinDouLiTop2->setEnabled(true);
        ui->comboBoxMinDouLiTop3->setEnabled(true);

        if (mZone == ZONE_NEW) {
            //新区
            initComboBox(ui->comboBoxMinDouLiTop1, 100, 1200);
            initComboBox(ui->comboBoxMinDouLiTop2, 100, 1200);
            initComboBox(ui->comboBoxMinDouLiTop3, 100, 1200);
        } else if (mZone == ZONE_OLD) {
            //老区
            initComboBox(ui->comboBoxMinDouLiTop1, 600, 1200);
            initComboBox(ui->comboBoxMinDouLiTop2, 600, 1200);
            initComboBox(ui->comboBoxMinDouLiTop3, 600, 1200);
        }

        //地图
        ui->checkBoxMinDouLiMap1->setEnabled(true);
        ui->checkBoxMinDouLiMap2->setEnabled(true);
        ui->checkBoxMinDouLiMap3->setEnabled(true);
        ui->checkBoxMinDouLiMap4->setEnabled(true);
        ui->checkBoxMinDouLiMap5->setEnabled(true);
        ui->checkBoxMinDouLiMap6->setEnabled(true);
        ui->checkBoxMinDouLiMap7->setEnabled(true);
        ui->checkBoxMinDouLiMap8->setEnabled(true);
        //列表
        ui->comboBoxMinDouLiList1->setEnabled(true);
        ui->comboBoxMinDouLiList2->setEnabled(true);
        ui->comboBoxMinDouLiList3->setEnabled(true);
        ui->comboBoxMinDouLiList4->setEnabled(true);
        ui->comboBoxMinDouLiList5->setEnabled(true);
        ui->comboBoxMinDouLiList6->setEnabled(true);
        ui->comboBoxMinDouLiList7->setEnabled(true);
        ui->comboBoxMinDouLiList8->setEnabled(true);
    } else {
        //大号
        if (mZone == ZONE_NEW) {
            //新区
            initComboBox(ui->comboBoxMaxDouLiTop1, 100, 1050);
            initComboBox(ui->comboBoxMaxDouLiTop2, 100, 1050);
            initComboBox(ui->comboBoxMaxDouLiTop3, 100, 1050);
        } else if (mZone == ZONE_OLD) {
            //老区
            initComboBox(ui->comboBoxMaxDouLiTop1, 600, 1050);
            initComboBox(ui->comboBoxMaxDouLiTop2, 600, 1050);
            initComboBox(ui->comboBoxMaxDouLiTop3, 600, 1050);
        }

        //小号
        //置顶
        ui->comboBoxMinDouLiTop1->setEnabled(false);
        ui->comboBoxMinDouLiTop2->setEnabled(false);
        ui->comboBoxMinDouLiTop3->setEnabled(false);
        //地图
        ui->checkBoxMinDouLiMap1->setEnabled(false);
        ui->checkBoxMinDouLiMap2->setEnabled(false);
        ui->checkBoxMinDouLiMap3->setEnabled(false);
        ui->checkBoxMinDouLiMap4->setEnabled(false);
        ui->checkBoxMinDouLiMap5->setEnabled(false);
        ui->checkBoxMinDouLiMap6->setEnabled(false);
        ui->checkBoxMinDouLiMap7->setEnabled(false);
        ui->checkBoxMinDouLiMap8->setEnabled(false);
        //列表
        ui->comboBoxMinDouLiList1->setEnabled(false);
        ui->comboBoxMinDouLiList2->setEnabled(false);
        ui->comboBoxMinDouLiList3->setEnabled(false);
        ui->comboBoxMinDouLiList4->setEnabled(false);
        ui->comboBoxMinDouLiList5->setEnabled(false);
        ui->comboBoxMinDouLiList6->setEnabled(false);
        ui->comboBoxMinDouLiList7->setEnabled(false);
        ui->comboBoxMinDouLiList8->setEnabled(false);
    }
}

void MainWindow::initHuDunPage()
{
    //大号
    //置顶
    ui->comboBoxMaxHuDunTop1->setEnabled(true);
    ui->comboBoxMaxHuDunTop2->setEnabled(true);
    ui->comboBoxMaxHuDunTop3->setEnabled(true);
    //地图
    ui->checkBoxMaxHuDunMap1->setEnabled(true);
    ui->checkBoxMaxHuDunMap2->setEnabled(true);
    ui->checkBoxMaxHuDunMap3->setEnabled(true);
    ui->checkBoxMaxHuDunMap4->setEnabled(true);
    ui->checkBoxMaxHuDunMap5->setEnabled(true);
    ui->checkBoxMaxHuDunMap6->setEnabled(true);
    ui->checkBoxMaxHuDunMap7->setEnabled(true);
    ui->checkBoxMaxHuDunMap8->setEnabled(true);
    //列表
    ui->comboBoxMaxHuDunList1->setEnabled(true);
    ui->comboBoxMaxHuDunList2->setEnabled(true);
    ui->comboBoxMaxHuDunList3->setEnabled(true);
    ui->comboBoxMaxHuDunList4->setEnabled(true);
    ui->comboBoxMaxHuDunList5->setEnabled(true);
    ui->comboBoxMaxHuDunList6->setEnabled(true);
    ui->comboBoxMaxHuDunList7->setEnabled(true);
    ui->comboBoxMaxHuDunList8->setEnabled(true);

    if (mType == TYPE_ZHI_ZUN) {
        //大号置顶
        if (mZone == ZONE_NEW) {
            //新区
            initComboBox(ui->comboBoxMaxHuDunTop1, 100, 1200);
            initComboBox(ui->comboBoxMaxHuDunTop2, 100, 1200);
            initComboBox(ui->comboBoxMaxHuDunTop3, 100, 1200);
        } else if (mZone == ZONE_OLD) {
            //老区
            initComboBox(ui->comboBoxMaxHuDunTop1, 600, 1200);
            initComboBox(ui->comboBoxMaxHuDunTop2, 600, 1200);
            initComboBox(ui->comboBoxMaxHuDunTop3, 600, 1200);
        }

        //小号
        //置顶
        ui->comboBoxMinHuDunTop1->setEnabled(true);
        ui->comboBoxMinHuDunTop2->setEnabled(true);
        ui->comboBoxMinHuDunTop3->setEnabled(true);
        //小号置顶
        if (mZone == ZONE_NEW) {
            //新区
            initComboBox(ui->comboBoxMinHuDunTop1, 100, 1200);
            initComboBox(ui->comboBoxMinHuDunTop2, 100, 1200);
            initComboBox(ui->comboBoxMinHuDunTop3, 100, 1200);
        } else if (mZone == ZONE_OLD) {
            //老区
            initComboBox(ui->comboBoxMinHuDunTop1, 600, 1200);
            initComboBox(ui->comboBoxMinHuDunTop2, 600, 1200);
            initComboBox(ui->comboBoxMinHuDunTop3, 600, 1200);
        }

        //地图
        ui->checkBoxMinHuDunMap1->setEnabled(true);
        ui->checkBoxMinHuDunMap2->setEnabled(true);
        ui->checkBoxMinHuDunMap3->setEnabled(true);
        ui->checkBoxMinHuDunMap4->setEnabled(true);
        ui->checkBoxMinHuDunMap5->setEnabled(true);
        ui->checkBoxMinHuDunMap6->setEnabled(true);
        ui->checkBoxMinHuDunMap7->setEnabled(true);
        ui->checkBoxMinHuDunMap8->setEnabled(true);
        //列表
        ui->comboBoxMinHuDunList1->setEnabled(true);
        ui->comboBoxMinHuDunList2->setEnabled(true);
        ui->comboBoxMinHuDunList3->setEnabled(true);
        ui->comboBoxMinHuDunList4->setEnabled(true);
        ui->comboBoxMinHuDunList5->setEnabled(true);
        ui->comboBoxMinHuDunList6->setEnabled(true);
        ui->comboBoxMinHuDunList7->setEnabled(true);
        ui->comboBoxMinHuDunList8->setEnabled(true);
    } else {
        //大号置顶
        if (mZone == ZONE_NEW) {
            //新区
            initComboBox(ui->comboBoxMaxHuDunTop1, 100, 1050);
            initComboBox(ui->comboBoxMaxHuDunTop2, 100, 1050);
            initComboBox(ui->comboBoxMaxHuDunTop3, 100, 1050);
        } else if (mZone == ZONE_OLD) {
            //老区
            initComboBox(ui->comboBoxMaxHuDunTop1, 600, 1050);
            initComboBox(ui->comboBoxMaxHuDunTop2, 600, 1050);
            initComboBox(ui->comboBoxMaxHuDunTop3, 600, 1050);
        }

        //小号
        //置顶
        ui->comboBoxMinHuDunTop1->setEnabled(false);
        ui->comboBoxMinHuDunTop2->setEnabled(false);
        ui->comboBoxMinHuDunTop3->setEnabled(false);
        //地图
        ui->checkBoxMinHuDunMap1->setEnabled(false);
        ui->checkBoxMinHuDunMap2->setEnabled(false);
        ui->checkBoxMinHuDunMap3->setEnabled(false);
        ui->checkBoxMinHuDunMap4->setEnabled(false);
        ui->checkBoxMinHuDunMap5->setEnabled(false);
        ui->checkBoxMinHuDunMap6->setEnabled(false);
        ui->checkBoxMinHuDunMap7->setEnabled(false);
        ui->checkBoxMinHuDunMap8->setEnabled(false);
        //列表
        ui->comboBoxMinHuDunList1->setEnabled(false);
        ui->comboBoxMinHuDunList2->setEnabled(false);
        ui->comboBoxMinHuDunList3->setEnabled(false);
        ui->comboBoxMinHuDunList4->setEnabled(false);
        ui->comboBoxMinHuDunList5->setEnabled(false);
        ui->comboBoxMinHuDunList6->setEnabled(false);
        ui->comboBoxMinHuDunList7->setEnabled(false);
        ui->comboBoxMinHuDunList8->setEnabled(false);
    }
}

void MainWindow::initXingZuoPage()
{
    //大号
    //置顶
    ui->comboBoxMaxXingZuoTop1->setEnabled(true);
    ui->comboBoxMaxXingZuoTop2->setEnabled(true);
    ui->comboBoxMaxXingZuoTop3->setEnabled(true);
    //地图
    ui->checkBoxMaxXingZuoMap1->setEnabled(true);
    ui->checkBoxMaxXingZuoMap2->setEnabled(true);
    ui->checkBoxMaxXingZuoMap3->setEnabled(true);
    ui->checkBoxMaxXingZuoMap4->setEnabled(true);
    ui->checkBoxMaxXingZuoMap5->setEnabled(true);
    ui->checkBoxMaxXingZuoMap6->setEnabled(true);
    ui->checkBoxMaxXingZuoMap7->setEnabled(true);
    ui->checkBoxMaxXingZuoMap8->setEnabled(true);
    //列表
    ui->comboBoxMaxXingZuoList1->setEnabled(true);
    ui->comboBoxMaxXingZuoList2->setEnabled(true);
    ui->comboBoxMaxXingZuoList3->setEnabled(true);
    ui->comboBoxMaxXingZuoList4->setEnabled(true);
    ui->comboBoxMaxXingZuoList5->setEnabled(true);
    ui->comboBoxMaxXingZuoList6->setEnabled(true);
    ui->comboBoxMaxXingZuoList7->setEnabled(true);
    ui->comboBoxMaxXingZuoList8->setEnabled(true);

    if (mType == TYPE_ZHI_ZUN) {
        //大号置顶
        if (mZone == ZONE_NEW) {
            //新区
            initComboBox(ui->comboBoxMaxXingZuoTop1, 100, 1200);
            initComboBox(ui->comboBoxMaxXingZuoTop2, 100, 1200);
            initComboBox(ui->comboBoxMaxXingZuoTop3, 100, 1200);
        } else if (mZone == ZONE_OLD) {
            //老区
            initComboBox(ui->comboBoxMaxXingZuoTop1, 750, 1200);
            initComboBox(ui->comboBoxMaxXingZuoTop2, 750, 1200);
            initComboBox(ui->comboBoxMaxXingZuoTop3, 750, 1200);
        }

        //小号
        //置顶
        ui->comboBoxMaxXingZuoTop1->setEnabled(true);
        ui->comboBoxMaxXingZuoTop2->setEnabled(true);
        ui->comboBoxMaxXingZuoTop3->setEnabled(true);
        //置顶
        if (mZone == ZONE_NEW) {
            //新区
            initComboBox(ui->comboBoxMinXingZuoTop1, 100, 1200);
            initComboBox(ui->comboBoxMinXingZuoTop2, 100, 1200);
            initComboBox(ui->comboBoxMinXingZuoTop3, 100, 1200);
        } else if (mZone == ZONE_OLD) {
            //老区
            initComboBox(ui->comboBoxMinXingZuoTop1, 750, 1200);
            initComboBox(ui->comboBoxMinXingZuoTop2, 750, 1200);
            initComboBox(ui->comboBoxMinXingZuoTop3, 750, 1200);
        }

        //地图
        ui->checkBoxMaxXingZuoMap1->setEnabled(true);
        ui->checkBoxMaxXingZuoMap2->setEnabled(true);
        ui->checkBoxMaxXingZuoMap3->setEnabled(true);
        ui->checkBoxMaxXingZuoMap4->setEnabled(true);
        ui->checkBoxMaxXingZuoMap5->setEnabled(true);
        ui->checkBoxMaxXingZuoMap6->setEnabled(true);
        ui->checkBoxMaxXingZuoMap7->setEnabled(true);
        ui->checkBoxMaxXingZuoMap8->setEnabled(true);
        //列表
        ui->comboBoxMaxXingZuoList1->setEnabled(true);
        ui->comboBoxMaxXingZuoList2->setEnabled(true);
        ui->comboBoxMaxXingZuoList3->setEnabled(true);
        ui->comboBoxMaxXingZuoList4->setEnabled(true);
        ui->comboBoxMaxXingZuoList5->setEnabled(true);
        ui->comboBoxMaxXingZuoList6->setEnabled(true);
        ui->comboBoxMaxXingZuoList7->setEnabled(true);
        ui->comboBoxMaxXingZuoList8->setEnabled(true);
    } else {
        //大号置顶
        if (mZone == ZONE_NEW) {
            //新区
            initComboBox(ui->comboBoxMaxXingZuoTop1, 100, 1050);
            initComboBox(ui->comboBoxMaxXingZuoTop2, 100, 1050);
            initComboBox(ui->comboBoxMaxXingZuoTop3, 100, 1050);
        } else if (mZone == ZONE_OLD) {
            //老区
            initComboBox(ui->comboBoxMaxXingZuoTop1, 750, 1050);
            initComboBox(ui->comboBoxMaxXingZuoTop2, 750, 1050);
            initComboBox(ui->comboBoxMaxXingZuoTop3, 750, 1050);
        }

        //小号
        //置顶
        ui->comboBoxMaxXingZuoTop1->setEnabled(false);
        ui->comboBoxMaxXingZuoTop2->setEnabled(false);
        ui->comboBoxMaxXingZuoTop3->setEnabled(false);
        //地图
        ui->checkBoxMaxXingZuoMap1->setEnabled(false);
        ui->checkBoxMaxXingZuoMap2->setEnabled(false);
        ui->checkBoxMaxXingZuoMap3->setEnabled(false);
        ui->checkBoxMaxXingZuoMap4->setEnabled(false);
        ui->checkBoxMaxXingZuoMap5->setEnabled(false);
        ui->checkBoxMaxXingZuoMap6->setEnabled(false);
        ui->checkBoxMaxXingZuoMap7->setEnabled(false);
        ui->checkBoxMaxXingZuoMap8->setEnabled(false);
        //列表
        ui->comboBoxMaxXingZuoList1->setEnabled(false);
        ui->comboBoxMaxXingZuoList2->setEnabled(false);
        ui->comboBoxMaxXingZuoList3->setEnabled(false);
        ui->comboBoxMaxXingZuoList4->setEnabled(false);
        ui->comboBoxMaxXingZuoList5->setEnabled(false);
        ui->comboBoxMaxXingZuoList6->setEnabled(false);
        ui->comboBoxMaxXingZuoList7->setEnabled(false);
        ui->comboBoxMaxXingZuoList8->setEnabled(false);
    }
}

void MainWindow::initJinShenPage()
{
    if (mType == TYPE_ZHI_ZUN) {
        //大号
        //置顶
        ui->comboBoxMaxJinShenTop1->setEnabled(true);
        ui->comboBoxMaxJinShenTop2->setEnabled(true);
        ui->comboBoxMaxJinShenTop3->setEnabled(true);
        //置顶等级
        initComboBox(ui->comboBoxMaxJinShenTop1, 2000, 2750);
        initComboBox(ui->comboBoxMaxJinShenTop2, 2000, 2750);
        initComboBox(ui->comboBoxMaxJinShenTop3, 2000, 2750);

        //地图
        ui->checkBoxMaxJinShenMap1->setEnabled(true);
        ui->checkBoxMaxJinShenMap2->setEnabled(true);
        ui->checkBoxMaxJinShenMap3->setEnabled(true);
        ui->checkBoxMaxJinShenMap4->setEnabled(true);
        ui->checkBoxMaxJinShenMap5->setEnabled(true);
        ui->checkBoxMaxJinShenMap6->setEnabled(true);
        ui->checkBoxMaxJinShenMap7->setEnabled(true);
        ui->checkBoxMaxJinShenMap8->setEnabled(true);
        //列表
        ui->comboBoxMaxJinShenList1->setEnabled(true);
        ui->comboBoxMaxJinShenList2->setEnabled(true);
        ui->comboBoxMaxJinShenList3->setEnabled(true);
        ui->comboBoxMaxJinShenList4->setEnabled(true);
        ui->comboBoxMaxJinShenList5->setEnabled(true);
        ui->comboBoxMaxJinShenList6->setEnabled(true);
        ui->comboBoxMaxJinShenList7->setEnabled(true);
        ui->comboBoxMaxJinShenList8->setEnabled(true);

        //小号
        //置顶
        ui->comboBoxMinJinShenTop1->setEnabled(true);
        ui->comboBoxMinJinShenTop2->setEnabled(true);
        ui->comboBoxMinJinShenTop3->setEnabled(true);
        //置顶等级
        initComboBox(ui->comboBoxMinJinShenTop1, 2000, 2750);
        initComboBox(ui->comboBoxMinJinShenTop2, 2000, 2750);
        initComboBox(ui->comboBoxMinJinShenTop3, 2000, 2750);

        //地图
        ui->checkBoxMinJinShenMap1->setEnabled(true);
        ui->checkBoxMinJinShenMap2->setEnabled(true);
        ui->checkBoxMinJinShenMap3->setEnabled(true);
        ui->checkBoxMinJinShenMap4->setEnabled(true);
        ui->checkBoxMinJinShenMap5->setEnabled(true);
        ui->checkBoxMinJinShenMap6->setEnabled(true);
        ui->checkBoxMinJinShenMap7->setEnabled(true);
        ui->checkBoxMinJinShenMap8->setEnabled(true);
        //列表
        ui->comboBoxMinJinShenList1->setEnabled(true);
        ui->comboBoxMinJinShenList2->setEnabled(true);
        ui->comboBoxMinJinShenList3->setEnabled(true);
        ui->comboBoxMinJinShenList4->setEnabled(true);
        ui->comboBoxMinJinShenList5->setEnabled(true);
        ui->comboBoxMinJinShenList6->setEnabled(true);
        ui->comboBoxMinJinShenList7->setEnabled(true);
        ui->comboBoxMinJinShenList8->setEnabled(true);
    } else {
        //大号
        //置顶
        ui->comboBoxMaxJinShenTop1->setEnabled(false);
        ui->comboBoxMaxJinShenTop2->setEnabled(false);
        ui->comboBoxMaxJinShenTop3->setEnabled(false);
        //地图
        ui->checkBoxMaxJinShenMap1->setEnabled(false);
        ui->checkBoxMaxJinShenMap2->setEnabled(false);
        ui->checkBoxMaxJinShenMap3->setEnabled(false);
        ui->checkBoxMaxJinShenMap4->setEnabled(false);
        ui->checkBoxMaxJinShenMap5->setEnabled(false);
        ui->checkBoxMaxJinShenMap6->setEnabled(false);
        ui->checkBoxMaxJinShenMap7->setEnabled(false);
        ui->checkBoxMaxJinShenMap8->setEnabled(false);
        //列表
        ui->comboBoxMaxJinShenList1->setEnabled(false);
        ui->comboBoxMaxJinShenList2->setEnabled(false);
        ui->comboBoxMaxJinShenList3->setEnabled(false);
        ui->comboBoxMaxJinShenList4->setEnabled(false);
        ui->comboBoxMaxJinShenList5->setEnabled(false);
        ui->comboBoxMaxJinShenList6->setEnabled(false);
        ui->comboBoxMaxJinShenList7->setEnabled(false);
        ui->comboBoxMaxJinShenList8->setEnabled(false);

        //小号
        //置顶
        ui->comboBoxMinJinShenTop1->setEnabled(false);
        ui->comboBoxMinJinShenTop2->setEnabled(false);
        ui->comboBoxMinJinShenTop3->setEnabled(false);
        //地图
        ui->checkBoxMinJinShenMap1->setEnabled(false);
        ui->checkBoxMinJinShenMap2->setEnabled(false);
        ui->checkBoxMinJinShenMap3->setEnabled(false);
        ui->checkBoxMinJinShenMap4->setEnabled(false);
        ui->checkBoxMinJinShenMap5->setEnabled(false);
        ui->checkBoxMinJinShenMap6->setEnabled(false);
        ui->checkBoxMinJinShenMap7->setEnabled(false);
        ui->checkBoxMinJinShenMap8->setEnabled(false);
        //列表
        ui->comboBoxMinJinShenList1->setEnabled(false);
        ui->comboBoxMinJinShenList2->setEnabled(false);
        ui->comboBoxMinJinShenList3->setEnabled(false);
        ui->comboBoxMinJinShenList4->setEnabled(false);
        ui->comboBoxMinJinShenList5->setEnabled(false);
        ui->comboBoxMinJinShenList6->setEnabled(false);
        ui->comboBoxMinJinShenList7->setEnabled(false);
        ui->comboBoxMinJinShenList8->setEnabled(false);
    }
}

void MainWindow::initBaGuaPage()
{
    //大号
    //地图
    ui->checkBoxMaxBaGuaMap1->setEnabled(true);
    ui->checkBoxMaxBaGuaMap2->setEnabled(true);
    ui->checkBoxMaxBaGuaMap3->setEnabled(true);
    ui->checkBoxMaxBaGuaMap4->setEnabled(true);
    ui->checkBoxMaxBaGuaMap5->setEnabled(true);
    //列表
    ui->comboBoxMaxBaGuaList1->setEnabled(true);
    ui->comboBoxMaxBaGuaList2->setEnabled(true);
    ui->comboBoxMaxBaGuaList3->setEnabled(true);
    ui->comboBoxMaxBaGuaList4->setEnabled(true);
    ui->comboBoxMaxBaGuaList5->setEnabled(true);
    //设置列表
    initBaGuaList(ui->comboBoxMaxBaGuaList1);
    initBaGuaList(ui->comboBoxMaxBaGuaList2);
    initBaGuaList(ui->comboBoxMaxBaGuaList3);
    initBaGuaList(ui->comboBoxMaxBaGuaList4);
    initBaGuaList(ui->comboBoxMaxBaGuaList5);

    if (mType == TYPE_ZHI_ZUN) {
        //小号
        //地图
        ui->checkBoxMinBaGuaMap1->setEnabled(true);
        ui->checkBoxMinBaGuaMap2->setEnabled(true);
        ui->checkBoxMinBaGuaMap3->setEnabled(true);
        ui->checkBoxMinBaGuaMap4->setEnabled(true);
        ui->checkBoxMinBaGuaMap5->setEnabled(true);
        //列表
        ui->comboBoxMinBaGuaList1->setEnabled(true);
        ui->comboBoxMinBaGuaList2->setEnabled(true);
        ui->comboBoxMinBaGuaList3->setEnabled(true);
        ui->comboBoxMinBaGuaList4->setEnabled(true);
        ui->comboBoxMinBaGuaList5->setEnabled(true);
        //设置列表
        initBaGuaList(ui->comboBoxMinBaGuaList1);
        initBaGuaList(ui->comboBoxMinBaGuaList2);
        initBaGuaList(ui->comboBoxMinBaGuaList3);
        initBaGuaList(ui->comboBoxMinBaGuaList4);
        initBaGuaList(ui->comboBoxMinBaGuaList5);
    } else {
        //小号
        //地图
        ui->checkBoxMinBaGuaMap1->setEnabled(false);
        ui->checkBoxMinBaGuaMap2->setEnabled(false);
        ui->checkBoxMinBaGuaMap3->setEnabled(false);
        ui->checkBoxMinBaGuaMap4->setEnabled(false);
        ui->checkBoxMinBaGuaMap5->setEnabled(false);
        //列表
        ui->comboBoxMinBaGuaList1->setEnabled(false);
        ui->comboBoxMinBaGuaList2->setEnabled(false);
        ui->comboBoxMinBaGuaList3->setEnabled(false);
        ui->comboBoxMinBaGuaList4->setEnabled(false);
        ui->comboBoxMinBaGuaList5->setEnabled(false);
    }
}

void MainWindow::initYouMingPage()
{
    if (mType == TYPE_ZHI_ZUN) {
        //大号
        //置顶
        ui->comboBoxMaxYouMingTop1->setEnabled(true);
        ui->comboBoxMaxYouMingTop2->setEnabled(true);
        ui->comboBoxMaxYouMingTop3->setEnabled(true);
        //置顶等级
        initComboBox(ui->comboBoxMaxYouMingTop1, 800, 1450);
        initComboBox(ui->comboBoxMaxYouMingTop2, 800, 1450);
        initComboBox(ui->comboBoxMaxYouMingTop3, 800, 1450);

        //地图
        ui->checkBoxMaxYouMingMap1->setEnabled(true);
        ui->checkBoxMaxYouMingMap2->setEnabled(true);
        ui->checkBoxMaxYouMingMap3->setEnabled(true);
        ui->checkBoxMaxYouMingMap4->setEnabled(true);
        ui->checkBoxMaxYouMingMap5->setEnabled(true);
        ui->checkBoxMaxYouMingMap6->setEnabled(true);
        ui->checkBoxMaxYouMingMap7->setEnabled(true);
        ui->checkBoxMaxYouMingMap8->setEnabled(true);
        //列表
        ui->comboBoxMaxYouMingList1->setEnabled(true);
        ui->comboBoxMaxYouMingList2->setEnabled(true);
        ui->comboBoxMaxYouMingList3->setEnabled(true);
        ui->comboBoxMaxYouMingList4->setEnabled(true);
        ui->comboBoxMaxYouMingList5->setEnabled(true);
        ui->comboBoxMaxYouMingList6->setEnabled(true);
        ui->comboBoxMaxYouMingList7->setEnabled(true);
        ui->comboBoxMaxYouMingList8->setEnabled(true);

        //小号
        //置顶
        ui->comboBoxMinYouMingTop1->setEnabled(true);
        ui->comboBoxMinYouMingTop2->setEnabled(true);
        ui->comboBoxMinYouMingTop3->setEnabled(true);
        //置顶等级
        initComboBox(ui->comboBoxMinYouMingTop1, 800, 1450);
        initComboBox(ui->comboBoxMinYouMingTop2, 800, 1450);
        initComboBox(ui->comboBoxMinYouMingTop3, 800, 1450);

        //地图
        ui->checkBoxMinYouMingMap1->setEnabled(true);
        ui->checkBoxMinYouMingMap2->setEnabled(true);
        ui->checkBoxMinYouMingMap3->setEnabled(true);
        ui->checkBoxMinYouMingMap4->setEnabled(true);
        ui->checkBoxMinYouMingMap5->setEnabled(true);
        ui->checkBoxMinYouMingMap6->setEnabled(true);
        ui->checkBoxMinYouMingMap7->setEnabled(true);
        ui->checkBoxMinYouMingMap8->setEnabled(true);
        //列表
        ui->comboBoxMinYouMingList1->setEnabled(true);
        ui->comboBoxMinYouMingList2->setEnabled(true);
        ui->comboBoxMinYouMingList3->setEnabled(true);
        ui->comboBoxMinYouMingList4->setEnabled(true);
        ui->comboBoxMinYouMingList5->setEnabled(true);
        ui->comboBoxMinYouMingList6->setEnabled(true);
        ui->comboBoxMinYouMingList7->setEnabled(true);
        ui->comboBoxMinYouMingList8->setEnabled(true);
    } else {
        //大号
        //置顶
        ui->comboBoxMaxYouMingTop1->setEnabled(false);
        ui->comboBoxMaxYouMingTop2->setEnabled(false);
        ui->comboBoxMaxYouMingTop3->setEnabled(false);
        //地图
        ui->checkBoxMaxYouMingMap1->setEnabled(false);
        ui->checkBoxMaxYouMingMap2->setEnabled(false);
        ui->checkBoxMaxYouMingMap3->setEnabled(false);
        ui->checkBoxMaxYouMingMap4->setEnabled(false);
        ui->checkBoxMaxYouMingMap5->setEnabled(false);
        ui->checkBoxMaxYouMingMap6->setEnabled(false);
        ui->checkBoxMaxYouMingMap7->setEnabled(false);
        ui->checkBoxMaxYouMingMap8->setEnabled(false);
        //列表
        ui->comboBoxMaxYouMingList1->setEnabled(false);
        ui->comboBoxMaxYouMingList2->setEnabled(false);
        ui->comboBoxMaxYouMingList3->setEnabled(false);
        ui->comboBoxMaxYouMingList4->setEnabled(false);
        ui->comboBoxMaxYouMingList5->setEnabled(false);
        ui->comboBoxMaxYouMingList6->setEnabled(false);
        ui->comboBoxMaxYouMingList7->setEnabled(false);
        ui->comboBoxMaxYouMingList8->setEnabled(false);

        //小号
        //置顶
        ui->comboBoxMinYouMingTop1->setEnabled(false);
        ui->comboBoxMinYouMingTop2->setEnabled(false);
        ui->comboBoxMinYouMingTop3->setEnabled(false);
        //地图
        ui->checkBoxMinYouMingMap1->setEnabled(false);
        ui->checkBoxMinYouMingMap2->setEnabled(false);
        ui->checkBoxMinYouMingMap3->setEnabled(false);
        ui->checkBoxMinYouMingMap4->setEnabled(false);
        ui->checkBoxMinYouMingMap5->setEnabled(false);
        ui->checkBoxMinYouMingMap6->setEnabled(false);
        ui->checkBoxMinYouMingMap7->setEnabled(false);
        ui->checkBoxMinYouMingMap8->setEnabled(false);
        //列表
        ui->comboBoxMinYouMingList1->setEnabled(false);
        ui->comboBoxMinYouMingList2->setEnabled(false);
        ui->comboBoxMinYouMingList3->setEnabled(false);
        ui->comboBoxMinYouMingList4->setEnabled(false);
        ui->comboBoxMinYouMingList5->setEnabled(false);
        ui->comboBoxMinYouMingList6->setEnabled(false);
        ui->comboBoxMinYouMingList7->setEnabled(false);
        ui->comboBoxMinYouMingList8->setEnabled(false);
    }
}

void MainWindow::initXunLongPage()
{
    if (mType == TYPE_ZHI_ZUN) {
        //大号
        //置顶
        ui->comboBoxMaxXunLongTop1->setEnabled(true);
        ui->comboBoxMaxXunLongTop2->setEnabled(true);
        ui->comboBoxMaxXunLongTop3->setEnabled(true);
        //置顶等级
        initComboBox(ui->comboBoxMaxXunLongTop1, 900, 1600);
        initComboBox(ui->comboBoxMaxXunLongTop2, 900, 1600);
        initComboBox(ui->comboBoxMaxXunLongTop3, 900, 1600);

        //地图
        ui->checkBoxMaxXunLongMap1->setEnabled(true);
        ui->checkBoxMaxXunLongMap2->setEnabled(true);
        ui->checkBoxMaxXunLongMap3->setEnabled(true);
        ui->checkBoxMaxXunLongMap4->setEnabled(true);
        ui->checkBoxMaxXunLongMap5->setEnabled(true);
        ui->checkBoxMaxXunLongMap6->setEnabled(true);
        ui->checkBoxMaxXunLongMap7->setEnabled(true);
        ui->checkBoxMaxXunLongMap8->setEnabled(true);
        //列表
        ui->comboBoxMaxXunLongList1->setEnabled(true);
        ui->comboBoxMaxXunLongList2->setEnabled(true);
        ui->comboBoxMaxXunLongList3->setEnabled(true);
        ui->comboBoxMaxXunLongList4->setEnabled(true);
        ui->comboBoxMaxXunLongList5->setEnabled(true);
        ui->comboBoxMaxXunLongList6->setEnabled(true);
        ui->comboBoxMaxXunLongList7->setEnabled(true);
        ui->comboBoxMaxXunLongList8->setEnabled(true);

        //小号
        //置顶
        ui->comboBoxMinXunLongTop1->setEnabled(true);
        ui->comboBoxMinXunLongTop2->setEnabled(true);
        ui->comboBoxMinXunLongTop3->setEnabled(true);
        //置顶等级
        initComboBox(ui->comboBoxMinXunLongTop1, 900, 1600);
        initComboBox(ui->comboBoxMinXunLongTop2, 900, 1600);
        initComboBox(ui->comboBoxMinXunLongTop3, 900, 1600);

        //地图
        ui->checkBoxMinXunLongMap1->setEnabled(true);
        ui->checkBoxMinXunLongMap2->setEnabled(true);
        ui->checkBoxMinXunLongMap3->setEnabled(true);
        ui->checkBoxMinXunLongMap4->setEnabled(true);
        ui->checkBoxMinXunLongMap5->setEnabled(true);
        ui->checkBoxMinXunLongMap6->setEnabled(true);
        ui->checkBoxMinXunLongMap7->setEnabled(true);
        ui->checkBoxMinXunLongMap8->setEnabled(true);
        //列表
        ui->comboBoxMinXunLongList1->setEnabled(true);
        ui->comboBoxMinXunLongList2->setEnabled(true);
        ui->comboBoxMinXunLongList3->setEnabled(true);
        ui->comboBoxMinXunLongList4->setEnabled(true);
        ui->comboBoxMinXunLongList5->setEnabled(true);
        ui->comboBoxMinXunLongList6->setEnabled(true);
        ui->comboBoxMinXunLongList7->setEnabled(true);
        ui->comboBoxMinXunLongList8->setEnabled(true);
    } else {
        //大号
        //置顶
        ui->comboBoxMaxXunLongTop1->setEnabled(false);
        ui->comboBoxMaxXunLongTop2->setEnabled(false);
        ui->comboBoxMaxXunLongTop3->setEnabled(false);
        //地图
        ui->checkBoxMaxXunLongMap1->setEnabled(false);
        ui->checkBoxMaxXunLongMap2->setEnabled(false);
        ui->checkBoxMaxXunLongMap3->setEnabled(false);
        ui->checkBoxMaxXunLongMap4->setEnabled(false);
        ui->checkBoxMaxXunLongMap5->setEnabled(false);
        ui->checkBoxMaxXunLongMap6->setEnabled(false);
        ui->checkBoxMaxXunLongMap7->setEnabled(false);
        ui->checkBoxMaxXunLongMap8->setEnabled(false);
        //列表
        ui->comboBoxMaxXunLongList1->setEnabled(false);
        ui->comboBoxMaxXunLongList2->setEnabled(false);
        ui->comboBoxMaxXunLongList3->setEnabled(false);
        ui->comboBoxMaxXunLongList4->setEnabled(false);
        ui->comboBoxMaxXunLongList5->setEnabled(false);
        ui->comboBoxMaxXunLongList6->setEnabled(false);
        ui->comboBoxMaxXunLongList7->setEnabled(false);
        ui->comboBoxMaxXunLongList8->setEnabled(false);

        //小号
        //置顶
        ui->comboBoxMinXunLongTop1->setEnabled(false);
        ui->comboBoxMinXunLongTop2->setEnabled(false);
        ui->comboBoxMinXunLongTop3->setEnabled(false);
        //地图
        ui->checkBoxMinXunLongMap1->setEnabled(false);
        ui->checkBoxMinXunLongMap2->setEnabled(false);
        ui->checkBoxMinXunLongMap3->setEnabled(false);
        ui->checkBoxMinXunLongMap4->setEnabled(false);
        ui->checkBoxMinXunLongMap5->setEnabled(false);
        ui->checkBoxMinXunLongMap6->setEnabled(false);
        ui->checkBoxMinXunLongMap7->setEnabled(false);
        ui->checkBoxMinXunLongMap8->setEnabled(false);
        //列表
        ui->comboBoxMinXunLongList1->setEnabled(false);
        ui->comboBoxMinXunLongList2->setEnabled(false);
        ui->comboBoxMinXunLongList3->setEnabled(false);
        ui->comboBoxMinXunLongList4->setEnabled(false);
        ui->comboBoxMinXunLongList5->setEnabled(false);
        ui->comboBoxMinXunLongList6->setEnabled(false);
        ui->comboBoxMinXunLongList7->setEnabled(false);
        ui->comboBoxMinXunLongList8->setEnabled(false);
    }
}

void MainWindow::initShenMoPage()
{
    if (mType == TYPE_ZHI_ZUN) {
        //大号
        //置顶
        ui->comboBoxMaxShenMoTop1->setEnabled(true);
        ui->comboBoxMaxShenMoTop2->setEnabled(true);
        ui->comboBoxMaxShenMoTop3->setEnabled(true);
        //置顶等级
        initComboBox(ui->comboBoxMaxShenMoTop1, 2000, 2800);
        initComboBox(ui->comboBoxMaxShenMoTop2, 2000, 2800);
        initComboBox(ui->comboBoxMaxShenMoTop3, 2000, 2800);

        //地图
        ui->checkBoxMaxShenMoMap1->setEnabled(true);
        ui->checkBoxMaxShenMoMap2->setEnabled(true);
        ui->checkBoxMaxShenMoMap3->setEnabled(true);
        ui->checkBoxMaxShenMoMap4->setEnabled(true);
        ui->checkBoxMaxShenMoMap5->setEnabled(true);
        ui->checkBoxMaxShenMoMap6->setEnabled(true);
        ui->checkBoxMaxShenMoMap7->setEnabled(true);
        ui->checkBoxMaxShenMoMap8->setEnabled(true);
        //列表
        ui->comboBoxMaxShenMoList1->setEnabled(true);
        ui->comboBoxMaxShenMoList2->setEnabled(true);
        ui->comboBoxMaxShenMoList3->setEnabled(true);
        ui->comboBoxMaxShenMoList4->setEnabled(true);
        ui->comboBoxMaxShenMoList5->setEnabled(true);
        ui->comboBoxMaxShenMoList6->setEnabled(true);
        ui->comboBoxMaxShenMoList7->setEnabled(true);
        ui->comboBoxMaxShenMoList8->setEnabled(true);

        //小号
        //置顶
        ui->comboBoxMinShenMoTop1->setEnabled(true);
        ui->comboBoxMinShenMoTop2->setEnabled(true);
        ui->comboBoxMinShenMoTop3->setEnabled(true);
        //置顶等级
        initComboBox(ui->comboBoxMinShenMoTop1, 2000, 2800);
        initComboBox(ui->comboBoxMinShenMoTop2, 2000, 2800);
        initComboBox(ui->comboBoxMinShenMoTop3, 2000, 2800);

        //地图
        ui->checkBoxMinShenMoMap1->setEnabled(true);
        ui->checkBoxMinShenMoMap2->setEnabled(true);
        ui->checkBoxMinShenMoMap3->setEnabled(true);
        ui->checkBoxMinShenMoMap4->setEnabled(true);
        ui->checkBoxMinShenMoMap5->setEnabled(true);
        ui->checkBoxMinShenMoMap6->setEnabled(true);
        ui->checkBoxMinShenMoMap7->setEnabled(true);
        ui->checkBoxMinShenMoMap8->setEnabled(true);
        //列表
        ui->comboBoxMinShenMoList1->setEnabled(true);
        ui->comboBoxMinShenMoList2->setEnabled(true);
        ui->comboBoxMinShenMoList3->setEnabled(true);
        ui->comboBoxMinShenMoList4->setEnabled(true);
        ui->comboBoxMinShenMoList5->setEnabled(true);
        ui->comboBoxMinShenMoList6->setEnabled(true);
        ui->comboBoxMinShenMoList7->setEnabled(true);
        ui->comboBoxMinShenMoList8->setEnabled(true);
    } else {
        //大号
        //置顶
        ui->comboBoxMaxShenMoTop1->setEnabled(false);
        ui->comboBoxMaxShenMoTop2->setEnabled(false);
        ui->comboBoxMaxShenMoTop3->setEnabled(false);
        //地图
        ui->checkBoxMaxShenMoMap1->setEnabled(false);
        ui->checkBoxMaxShenMoMap2->setEnabled(false);
        ui->checkBoxMaxShenMoMap3->setEnabled(false);
        ui->checkBoxMaxShenMoMap4->setEnabled(false);
        ui->checkBoxMaxShenMoMap5->setEnabled(false);
        ui->checkBoxMaxShenMoMap6->setEnabled(false);
        ui->checkBoxMaxShenMoMap7->setEnabled(false);
        ui->checkBoxMaxShenMoMap8->setEnabled(false);
        //列表
        ui->comboBoxMaxShenMoList1->setEnabled(false);
        ui->comboBoxMaxShenMoList2->setEnabled(false);
        ui->comboBoxMaxShenMoList3->setEnabled(false);
        ui->comboBoxMaxShenMoList4->setEnabled(false);
        ui->comboBoxMaxShenMoList5->setEnabled(false);
        ui->comboBoxMaxShenMoList6->setEnabled(false);
        ui->comboBoxMaxShenMoList7->setEnabled(false);
        ui->comboBoxMaxShenMoList8->setEnabled(false);

        //小号
        //置顶
        ui->comboBoxMinShenMoTop1->setEnabled(false);
        ui->comboBoxMinShenMoTop2->setEnabled(false);
        ui->comboBoxMinShenMoTop3->setEnabled(false);
        //地图
        ui->checkBoxMinShenMoMap1->setEnabled(false);
        ui->checkBoxMinShenMoMap2->setEnabled(false);
        ui->checkBoxMinShenMoMap3->setEnabled(false);
        ui->checkBoxMinShenMoMap4->setEnabled(false);
        ui->checkBoxMinShenMoMap5->setEnabled(false);
        ui->checkBoxMinShenMoMap6->setEnabled(false);
        ui->checkBoxMinShenMoMap7->setEnabled(false);
        ui->checkBoxMinShenMoMap8->setEnabled(false);
        //列表
        ui->comboBoxMinShenMoList1->setEnabled(false);
        ui->comboBoxMinShenMoList2->setEnabled(false);
        ui->comboBoxMinShenMoList3->setEnabled(false);
        ui->comboBoxMinShenMoList4->setEnabled(false);
        ui->comboBoxMinShenMoList5->setEnabled(false);
        ui->comboBoxMinShenMoList6->setEnabled(false);
        ui->comboBoxMinShenMoList7->setEnabled(false);
        ui->comboBoxMinShenMoList8->setEnabled(false);
    }
}

/**
 * @brief Widget::initComboBox  初始化置顶等级
 * @param pComboBox
 * @param start
 * @param end
 */
void MainWindow::initComboBox(QComboBox *pComboBox, int start, int end)
{
    pComboBox->clear();
    for (int i = start; i <= end; i = i + 50) {
        pComboBox->addItem(QString::number(i));
    }
    pComboBox->setCurrentIndex(-1);
}

void MainWindow::initBaGuaList(QComboBox *pComboBox)
{
    QStringList list = {"八卦1", "八卦2", "八卦3", "八卦4", "八卦5", "八卦6", "八卦7"};
    pComboBox->clear();
    pComboBox->addItems(list);
    pComboBox->setCurrentIndex(-1);
}

void MainWindow::resumeSettings()
{
    //基础页面
    pSettings->beginGroup("JiChu");
    //大号
    ui->checkBoxMaxZhenCe->setChecked(pSettings->value("maxZhenCe", false).toBool());
    ui->checkBoxMaxFuHuo->setChecked(pSettings->value("maxFuHuo", false).toBool());
    ui->checkBoxMaxChongLian->setChecked(pSettings->value("maxChongLian", false).toBool());
    ui->checkBoxMaxSuiJi->setChecked(pSettings->value("maxSuiJi", false).toBool());
    ui->checkBoxMaxZhuangBei->setChecked(pSettings->value("maxZhuangBei", false).toBool());
    ui->checkBoxMaxHangHuiMode->setChecked(pSettings->value("maxHangHuiMode", false).toBool());
    ui->checkBoxMaxXiuMian->setChecked(pSettings->value("maxXiuMian", false).toBool());
    xiuMianStartMax[0] = pSettings->value("maxStartTime1", 2).toInt();
    xiuMianStartMax[1] = pSettings->value("maxStartTime2", 50).toInt();
    xiuMianEndMax[0] = pSettings->value("maxEndTime1", 4).toInt();
    xiuMianEndMax[1] = pSettings->value("maxEndTime2", 10).toInt();
    QTime startTime;
    startTime.setHMS(xiuMianStartMax[0], xiuMianStartMax[1], 0);
    QTime endTime;
    endTime.setHMS(xiuMianEndMax[0], xiuMianEndMax[1], 0);
    ui->timeEditMaxStart->setTime(startTime);
    ui->timeEditMaxEnd->setTime(endTime);

    ui->checkBoxMaxMoLongBaoZang->setChecked(pSettings->value("maxMoLong", false).toBool());
    ui->checkBoxMaxShiJieBoss->setChecked(pSettings->value("maxShiJieBoss", false).toBool());
    ui->checkBoxMaxHuangJinShu->setChecked(pSettings->value("maxHuangJinShu", false).toBool());
    ui->checkBoxMaxHangHuiShiLian->setChecked(pSettings->value("maxHangHuiShiLian", false).toBool());

    ui->checkBoxMaxFenJieDouLi->setChecked(pSettings->value("maxFenJieDouLi", false).toBool());
    ui->checkBoxMaxFenJieHuDun->setChecked(pSettings->value("maxHuDun", false).toBool());
    ui->checkBoxMaxFenJieBaGua->setChecked(pSettings->value("maxBaGua", false).toBool());
    ui->checkBoxMaxFenJieBaGua->setChecked(pSettings->value("maxFenJieYouMing", false).toBool());

    if (mType == TYPE_ZHI_ZUN) {
        //小号
        ui->checkBoxMinZhenCe->setChecked(pSettings->value("minZhenCe", false).toBool());
        ui->checkBoxMinFuHuo->setChecked(pSettings->value("minFuHuo", false).toBool());
        ui->checkBoxMinChongLian->setChecked(pSettings->value("minChongLian", false).toBool());
        ui->checkBoxMinSuiJi->setChecked(pSettings->value("minSuiJi", false).toBool());
        ui->checkBoxMinZhuangBei->setChecked(pSettings->value("minZhuangBei", false).toBool());
        ui->checkBoxMinHangHuiMode->setChecked(pSettings->value("minHangHuiMode", false).toBool());
        ui->checkBoxMinXiuMian->setChecked(pSettings->value("minXiuMian", false).toBool());
        xiuMianStartMin[0] = pSettings->value("minStartTime1", 2).toInt();
        xiuMianStartMin[1] = pSettings->value("minStartTime2", 50).toInt();
        xiuMianEndMin[0] = pSettings->value("minEndTime1", 4).toInt();
        xiuMianEndMin[1] = pSettings->value("minEndTime2", 10).toInt();
        startTime.setHMS(xiuMianStartMin[0], xiuMianStartMin[1], 0);
        endTime.setHMS(xiuMianEndMin[0], xiuMianEndMin[1], 0);
        ui->timeEditMinStart->setTime(startTime);
        ui->timeEditMinEnd->setTime(endTime);

        ui->checkBoxMinMoLongBaoZang->setChecked(pSettings->value("minMoLong", false).toBool());
        ui->checkBoxMinShiJieBoss->setChecked(pSettings->value("minShiJieBoss", false).toBool());
        ui->checkBoxMinHuangJinShu->setChecked(pSettings->value("minHuangJinShu", false).toBool());
        ui->checkBoxMinHangHuiShiLian->setChecked(pSettings->value("minHangHuiShiLian", false).toBool());

        ui->checkBoxMinFenJieDouLi->setChecked(pSettings->value("minFenJieDouLi", false).toBool());
        ui->checkBoxMinFenJieHuDun->setChecked(pSettings->value("minHuDun", false).toBool());
        ui->checkBoxMinFenJieBaGua->setChecked(pSettings->value("minBaGua", false).toBool());
        ui->checkBoxMinFenJieBaGua->setChecked(pSettings->value("minFenJieYouMing", false).toBool());
    }
    pSettings->endGroup();

    //等级boss
    pSettings->beginGroup("DengJi");

    ui->comboBoxMaxDengJiTop1->setCurrentIndex(pSettings->value("maxTop1", -1).toInt());
    ui->comboBoxMaxDengJiTop2->setCurrentIndex(pSettings->value("maxTop2", -1).toInt());
    ui->comboBoxMaxDengJiTop3->setCurrentIndex(pSettings->value("maxTop3", -1).toInt());
    ui->checkBoxMaxDengJiMap1->setChecked(pSettings->value("maxMap1", false).toBool());
    ui->checkBoxMaxDengJiMap2->setChecked(pSettings->value("maxMap2", false).toBool());
    ui->checkBoxMaxDengJiMap3->setChecked(pSettings->value("maxMap3", false).toBool());
    ui->checkBoxMaxDengJiMap4->setChecked(pSettings->value("maxMap4", false).toBool());
    ui->checkBoxMaxDengJiMap5->setChecked(pSettings->value("maxMap5", false).toBool());
    ui->checkBoxMaxDengJiMap6->setChecked(pSettings->value("maxMap6", false).toBool());
    ui->checkBoxMaxDengJiMap7->setChecked(pSettings->value("maxMap7", false).toBool());
    ui->checkBoxMaxDengJiMap8->setChecked(pSettings->value("maxMap8", false).toBool());
    ui->comboBoxMaxDengJiList1->setCurrentIndex(pSettings->value("maxList1", -1).toInt());
    ui->comboBoxMaxDengJiList2->setCurrentIndex(pSettings->value("maxList2", -1).toInt());
    ui->comboBoxMaxDengJiList3->setCurrentIndex(pSettings->value("maxList3", -1).toInt());
    ui->comboBoxMaxDengJiList4->setCurrentIndex(pSettings->value("maxList4", -1).toInt());
    ui->comboBoxMaxDengJiList5->setCurrentIndex(pSettings->value("maxList5", -1).toInt());
    ui->comboBoxMaxDengJiList6->setCurrentIndex(pSettings->value("maxList6", -1).toInt());
    ui->comboBoxMaxDengJiList7->setCurrentIndex(pSettings->value("maxList7", -1).toInt());
    ui->comboBoxMaxDengJiList8->setCurrentIndex(pSettings->value("maxList8", -1).toInt());

    if (mType == TYPE_ZHI_ZUN) {
        //小号
        ui->comboBoxMinDengJiTop1->setCurrentIndex(pSettings->value("minTop1", -1).toInt());
        ui->comboBoxMinDengJiTop2->setCurrentIndex(pSettings->value("minTop2", -1).toInt());
        ui->comboBoxMinDengJiTop3->setCurrentIndex(pSettings->value("minTop3", -1).toInt());
        ui->checkBoxMinDengJiMap1->setChecked(pSettings->value("minMap1", false).toBool());
        ui->checkBoxMinDengJiMap2->setChecked(pSettings->value("minMap2", false).toBool());
        ui->checkBoxMinDengJiMap3->setChecked(pSettings->value("minMap3", false).toBool());
        ui->checkBoxMinDengJiMap4->setChecked(pSettings->value("minMap4", false).toBool());
        ui->checkBoxMinDengJiMap5->setChecked(pSettings->value("minMap5", false).toBool());
        ui->checkBoxMinDengJiMap6->setChecked(pSettings->value("minMap6", false).toBool());
        ui->checkBoxMinDengJiMap7->setChecked(pSettings->value("minMap7", false).toBool());
        ui->checkBoxMinDengJiMap8->setChecked(pSettings->value("minMap8", false).toBool());
        ui->comboBoxMinDengJiList1->setCurrentIndex(pSettings->value("minList1", -1).toInt());
        ui->comboBoxMinDengJiList2->setCurrentIndex(pSettings->value("minList2", -1).toInt());
        ui->comboBoxMinDengJiList3->setCurrentIndex(pSettings->value("minList3", -1).toInt());
        ui->comboBoxMinDengJiList4->setCurrentIndex(pSettings->value("minList4", -1).toInt());
        ui->comboBoxMinDengJiList5->setCurrentIndex(pSettings->value("minList5", -1).toInt());
        ui->comboBoxMinDengJiList6->setCurrentIndex(pSettings->value("minList6", -1).toInt());
        ui->comboBoxMinDengJiList7->setCurrentIndex(pSettings->value("minList7", -1).toInt());
        ui->comboBoxMinDengJiList8->setCurrentIndex(pSettings->value("minList8", -1).toInt());
    }
    pSettings->endGroup();

    //斗笠boss
    pSettings->beginGroup("DouLi");
    //大号
    ui->comboBoxMaxDouLiTop1->setCurrentIndex(pSettings->value("maxTop1", -1).toInt());
    ui->comboBoxMaxDouLiTop2->setCurrentIndex(pSettings->value("maxTop2", -1).toInt());
    ui->comboBoxMaxDouLiTop3->setCurrentIndex(pSettings->value("maxTop3", -1).toInt());
    ui->checkBoxMaxDouLiMap1->setChecked(pSettings->value("maxMap1", false).toBool());
    ui->checkBoxMaxDouLiMap2->setChecked(pSettings->value("maxMap2", false).toBool());
    ui->checkBoxMaxDouLiMap3->setChecked(pSettings->value("maxMap3", false).toBool());
    ui->checkBoxMaxDouLiMap4->setChecked(pSettings->value("maxMap4", false).toBool());
    ui->checkBoxMaxDouLiMap5->setChecked(pSettings->value("maxMap5", false).toBool());
    ui->checkBoxMaxDouLiMap6->setChecked(pSettings->value("maxMap6", false).toBool());
    ui->checkBoxMaxDouLiMap7->setChecked(pSettings->value("maxMap7", false).toBool());
    ui->checkBoxMaxDouLiMap8->setChecked(pSettings->value("maxMap8", false).toBool());
    ui->comboBoxMaxDouLiList1->setCurrentIndex(pSettings->value("maxList1", -1).toInt());
    ui->comboBoxMaxDouLiList2->setCurrentIndex(pSettings->value("maxList2", -1).toInt());
    ui->comboBoxMaxDouLiList3->setCurrentIndex(pSettings->value("maxList3", -1).toInt());
    ui->comboBoxMaxDouLiList4->setCurrentIndex(pSettings->value("maxList4", -1).toInt());
    ui->comboBoxMaxDouLiList5->setCurrentIndex(pSettings->value("maxList5", -1).toInt());
    ui->comboBoxMaxDouLiList6->setCurrentIndex(pSettings->value("maxList6", -1).toInt());
    ui->comboBoxMaxDouLiList7->setCurrentIndex(pSettings->value("maxList7", -1).toInt());
    ui->comboBoxMaxDouLiList8->setCurrentIndex(pSettings->value("maxList8", -1).toInt());

    if (mType == TYPE_ZHI_ZUN) {
        //小号
        ui->comboBoxMinDouLiTop1->setCurrentIndex(pSettings->value("minTop1", -1).toInt());
        ui->comboBoxMinDouLiTop2->setCurrentIndex(pSettings->value("minTop2", -1).toInt());
        ui->comboBoxMinDouLiTop3->setCurrentIndex(pSettings->value("minTop3", -1).toInt());
        ui->checkBoxMinDouLiMap1->setChecked(pSettings->value("minMap1", false).toBool());
        ui->checkBoxMinDouLiMap2->setChecked(pSettings->value("minMap2", false).toBool());
        ui->checkBoxMinDouLiMap3->setChecked(pSettings->value("minMap3", false).toBool());
        ui->checkBoxMinDouLiMap4->setChecked(pSettings->value("minMap4", false).toBool());
        ui->checkBoxMinDouLiMap5->setChecked(pSettings->value("minMap5", false).toBool());
        ui->checkBoxMinDouLiMap6->setChecked(pSettings->value("minMap6", false).toBool());
        ui->checkBoxMinDouLiMap7->setChecked(pSettings->value("minMap7", false).toBool());
        ui->checkBoxMinDouLiMap8->setChecked(pSettings->value("minMap8", false).toBool());
        ui->comboBoxMinDouLiList1->setCurrentIndex(pSettings->value("minList1", -1).toInt());
        ui->comboBoxMinDouLiList2->setCurrentIndex(pSettings->value("minList2", -1).toInt());
        ui->comboBoxMinDouLiList3->setCurrentIndex(pSettings->value("minList3", -1).toInt());
        ui->comboBoxMinDouLiList4->setCurrentIndex(pSettings->value("minList4", -1).toInt());
        ui->comboBoxMinDouLiList5->setCurrentIndex(pSettings->value("minList5", -1).toInt());
        ui->comboBoxMinDouLiList6->setCurrentIndex(pSettings->value("minList6", -1).toInt());
        ui->comboBoxMinDouLiList7->setCurrentIndex(pSettings->value("minList7", -1).toInt());
        ui->comboBoxMinDouLiList8->setCurrentIndex(pSettings->value("minList8", -1).toInt());
    }
    pSettings->endGroup();

    //护盾boss
    pSettings->beginGroup("HuDun");
    //大号
    ui->comboBoxMaxHuDunTop1->setCurrentIndex(pSettings->value("maxTop1", -1).toInt());
    ui->comboBoxMaxHuDunTop2->setCurrentIndex(pSettings->value("maxTop2", -1).toInt());
    ui->comboBoxMaxHuDunTop3->setCurrentIndex(pSettings->value("maxTop3", -1).toInt());
    ui->checkBoxMaxHuDunMap1->setChecked(pSettings->value("maxMap1", false).toBool());
    ui->checkBoxMaxHuDunMap2->setChecked(pSettings->value("maxMap2", false).toBool());
    ui->checkBoxMaxHuDunMap3->setChecked(pSettings->value("maxMap3", false).toBool());
    ui->checkBoxMaxHuDunMap4->setChecked(pSettings->value("maxMap4", false).toBool());
    ui->checkBoxMaxHuDunMap5->setChecked(pSettings->value("maxMap5", false).toBool());
    ui->checkBoxMaxHuDunMap6->setChecked(pSettings->value("maxMap6", false).toBool());
    ui->checkBoxMaxHuDunMap7->setChecked(pSettings->value("maxMap7", false).toBool());
    ui->checkBoxMaxHuDunMap8->setChecked(pSettings->value("maxMap8", false).toBool());
    ui->comboBoxMaxHuDunList1->setCurrentIndex(pSettings->value("maxList1", -1).toInt());
    ui->comboBoxMaxHuDunList2->setCurrentIndex(pSettings->value("maxList2", -1).toInt());
    ui->comboBoxMaxHuDunList3->setCurrentIndex(pSettings->value("maxList3", -1).toInt());
    ui->comboBoxMaxHuDunList4->setCurrentIndex(pSettings->value("maxList4", -1).toInt());
    ui->comboBoxMaxHuDunList5->setCurrentIndex(pSettings->value("maxList5", -1).toInt());
    ui->comboBoxMaxHuDunList6->setCurrentIndex(pSettings->value("maxList6", -1).toInt());
    ui->comboBoxMaxHuDunList7->setCurrentIndex(pSettings->value("maxList7", -1).toInt());
    ui->comboBoxMaxHuDunList8->setCurrentIndex(pSettings->value("maxList8", -1).toInt());

    if (mType == TYPE_ZHI_ZUN) {
        //小号
        ui->comboBoxMinHuDunTop1->setCurrentIndex(pSettings->value("minTop1", -1).toInt());
        ui->comboBoxMinHuDunTop2->setCurrentIndex(pSettings->value("minTop2", -1).toInt());
        ui->comboBoxMinHuDunTop3->setCurrentIndex(pSettings->value("minTop3", -1).toInt());
        ui->checkBoxMinHuDunMap1->setChecked(pSettings->value("minMap1", false).toBool());
        ui->checkBoxMinHuDunMap2->setChecked(pSettings->value("minMap2", false).toBool());
        ui->checkBoxMinHuDunMap3->setChecked(pSettings->value("minMap3", false).toBool());
        ui->checkBoxMinHuDunMap4->setChecked(pSettings->value("minMap4", false).toBool());
        ui->checkBoxMinHuDunMap5->setChecked(pSettings->value("minMap5", false).toBool());
        ui->checkBoxMinHuDunMap6->setChecked(pSettings->value("minMap6", false).toBool());
        ui->checkBoxMinHuDunMap7->setChecked(pSettings->value("minMap7", false).toBool());
        ui->checkBoxMinHuDunMap8->setChecked(pSettings->value("minMap8", false).toBool());
        ui->comboBoxMinHuDunList1->setCurrentIndex(pSettings->value("minList1", -1).toInt());
        ui->comboBoxMinHuDunList2->setCurrentIndex(pSettings->value("minList2", -1).toInt());
        ui->comboBoxMinHuDunList3->setCurrentIndex(pSettings->value("minList3", -1).toInt());
        ui->comboBoxMinHuDunList4->setCurrentIndex(pSettings->value("minList4", -1).toInt());
        ui->comboBoxMinHuDunList5->setCurrentIndex(pSettings->value("minList5", -1).toInt());
        ui->comboBoxMinHuDunList6->setCurrentIndex(pSettings->value("minList6", -1).toInt());
        ui->comboBoxMinHuDunList7->setCurrentIndex(pSettings->value("minList7", -1).toInt());
        ui->comboBoxMinHuDunList8->setCurrentIndex(pSettings->value("minList8", -1).toInt());
    }
    pSettings->endGroup();

    //星座boss
    pSettings->beginGroup("XingZuo");
    //大号
    ui->comboBoxMaxXingZuoTop1->setCurrentIndex(pSettings->value("maxTop1", -1).toInt());
    ui->comboBoxMaxXingZuoTop2->setCurrentIndex(pSettings->value("maxTop2", -1).toInt());
    ui->comboBoxMaxXingZuoTop3->setCurrentIndex(pSettings->value("maxTop3", -1).toInt());
    ui->checkBoxMaxXingZuoMap1->setChecked(pSettings->value("maxMap1", false).toBool());
    ui->checkBoxMaxXingZuoMap2->setChecked(pSettings->value("maxMap2", false).toBool());
    ui->checkBoxMaxXingZuoMap3->setChecked(pSettings->value("maxMap3", false).toBool());
    ui->checkBoxMaxXingZuoMap4->setChecked(pSettings->value("maxMap4", false).toBool());
    ui->checkBoxMaxXingZuoMap5->setChecked(pSettings->value("maxMap5", false).toBool());
    ui->checkBoxMaxXingZuoMap6->setChecked(pSettings->value("maxMap6", false).toBool());
    ui->checkBoxMaxXingZuoMap7->setChecked(pSettings->value("maxMap7", false).toBool());
    ui->checkBoxMaxXingZuoMap8->setChecked(pSettings->value("maxMap8", false).toBool());
    ui->comboBoxMaxXingZuoList1->setCurrentIndex(pSettings->value("maxList1", -1).toInt());
    ui->comboBoxMaxXingZuoList2->setCurrentIndex(pSettings->value("maxList2", -1).toInt());
    ui->comboBoxMaxXingZuoList3->setCurrentIndex(pSettings->value("maxList3", -1).toInt());
    ui->comboBoxMaxXingZuoList4->setCurrentIndex(pSettings->value("maxList4", -1).toInt());
    ui->comboBoxMaxXingZuoList5->setCurrentIndex(pSettings->value("maxList5", -1).toInt());
    ui->comboBoxMaxXingZuoList6->setCurrentIndex(pSettings->value("maxList6", -1).toInt());
    ui->comboBoxMaxXingZuoList7->setCurrentIndex(pSettings->value("maxList7", -1).toInt());
    ui->comboBoxMaxXingZuoList8->setCurrentIndex(pSettings->value("maxList8", -1).toInt());

    if (mType == TYPE_ZHI_ZUN) {
        //小号
        ui->comboBoxMinXingZuoTop1->setCurrentIndex(pSettings->value("minTop1", -1).toInt());
        ui->comboBoxMinXingZuoTop2->setCurrentIndex(pSettings->value("minTop2", -1).toInt());
        ui->comboBoxMinXingZuoTop3->setCurrentIndex(pSettings->value("minTop3", -1).toInt());
        ui->checkBoxMinXingZuoMap1->setChecked(pSettings->value("minMap1", false).toBool());
        ui->checkBoxMinXingZuoMap2->setChecked(pSettings->value("minMap2", false).toBool());
        ui->checkBoxMinXingZuoMap3->setChecked(pSettings->value("minMap3", false).toBool());
        ui->checkBoxMinXingZuoMap4->setChecked(pSettings->value("minMap4", false).toBool());
        ui->checkBoxMinXingZuoMap5->setChecked(pSettings->value("minMap5", false).toBool());
        ui->checkBoxMinXingZuoMap6->setChecked(pSettings->value("minMap6", false).toBool());
        ui->checkBoxMinXingZuoMap7->setChecked(pSettings->value("minMap7", false).toBool());
        ui->checkBoxMinXingZuoMap8->setChecked(pSettings->value("minMap8", false).toBool());
        ui->comboBoxMinXingZuoList1->setCurrentIndex(pSettings->value("minList1", -1).toInt());
        ui->comboBoxMinXingZuoList2->setCurrentIndex(pSettings->value("minList2", -1).toInt());
        ui->comboBoxMinXingZuoList3->setCurrentIndex(pSettings->value("minList3", -1).toInt());
        ui->comboBoxMinXingZuoList4->setCurrentIndex(pSettings->value("minList4", -1).toInt());
        ui->comboBoxMinXingZuoList5->setCurrentIndex(pSettings->value("minList5", -1).toInt());
        ui->comboBoxMinXingZuoList6->setCurrentIndex(pSettings->value("minList6", -1).toInt());
        ui->comboBoxMinXingZuoList7->setCurrentIndex(pSettings->value("minList7", -1).toInt());
        ui->comboBoxMinXingZuoList8->setCurrentIndex(pSettings->value("minList8", -1).toInt());
    }
    pSettings->endGroup();

    //金身boss

    if (mType == TYPE_ZHI_ZUN) {
        pSettings->beginGroup("JinShen");
        //大号
        ui->comboBoxMaxJinShenTop1->setCurrentIndex(pSettings->value("maxTop1", -1).toInt());
        ui->comboBoxMaxJinShenTop2->setCurrentIndex(pSettings->value("maxTop2", -1).toInt());
        ui->comboBoxMaxJinShenTop3->setCurrentIndex(pSettings->value("maxTop3", -1).toInt());
        ui->checkBoxMaxJinShenMap1->setChecked(pSettings->value("maxMap1", false).toBool());
        ui->checkBoxMaxJinShenMap2->setChecked(pSettings->value("maxMap2", false).toBool());
        ui->checkBoxMaxJinShenMap3->setChecked(pSettings->value("maxMap3", false).toBool());
        ui->checkBoxMaxJinShenMap4->setChecked(pSettings->value("maxMap4", false).toBool());
        ui->checkBoxMaxJinShenMap5->setChecked(pSettings->value("maxMap5", false).toBool());
        ui->checkBoxMaxJinShenMap6->setChecked(pSettings->value("maxMap6", false).toBool());
        ui->checkBoxMaxJinShenMap7->setChecked(pSettings->value("maxMap7", false).toBool());
        ui->checkBoxMaxJinShenMap8->setChecked(pSettings->value("maxMap8", false).toBool());
        ui->comboBoxMaxJinShenList1->setCurrentIndex(pSettings->value("maxList1", -1).toInt());
        ui->comboBoxMaxJinShenList2->setCurrentIndex(pSettings->value("maxList2", -1).toInt());
        ui->comboBoxMaxJinShenList3->setCurrentIndex(pSettings->value("maxList3", -1).toInt());
        ui->comboBoxMaxJinShenList4->setCurrentIndex(pSettings->value("maxList4", -1).toInt());
        ui->comboBoxMaxJinShenList5->setCurrentIndex(pSettings->value("maxList5", -1).toInt());
        ui->comboBoxMaxJinShenList6->setCurrentIndex(pSettings->value("maxList6", -1).toInt());
        ui->comboBoxMaxJinShenList7->setCurrentIndex(pSettings->value("maxList7", -1).toInt());
        ui->comboBoxMaxJinShenList8->setCurrentIndex(pSettings->value("maxList8", -1).toInt());

        //小号
        ui->comboBoxMinJinShenTop1->setCurrentIndex(pSettings->value("minTop1", -1).toInt());
        ui->comboBoxMinJinShenTop2->setCurrentIndex(pSettings->value("minTop2", -1).toInt());
        ui->comboBoxMinJinShenTop3->setCurrentIndex(pSettings->value("minTop3", -1).toInt());
        ui->checkBoxMinJinShenMap1->setChecked(pSettings->value("minMap1", false).toBool());
        ui->checkBoxMinJinShenMap2->setChecked(pSettings->value("minMap2", false).toBool());
        ui->checkBoxMinJinShenMap3->setChecked(pSettings->value("minMap3", false).toBool());
        ui->checkBoxMinJinShenMap4->setChecked(pSettings->value("minMap4", false).toBool());
        ui->checkBoxMinJinShenMap5->setChecked(pSettings->value("minMap5", false).toBool());
        ui->checkBoxMinJinShenMap6->setChecked(pSettings->value("minMap6", false).toBool());
        ui->checkBoxMinJinShenMap7->setChecked(pSettings->value("minMap7", false).toBool());
        ui->checkBoxMinJinShenMap8->setChecked(pSettings->value("minMap8", false).toBool());
        ui->comboBoxMinJinShenList1->setCurrentIndex(pSettings->value("minList1", -1).toInt());
        ui->comboBoxMinJinShenList2->setCurrentIndex(pSettings->value("minList2", -1).toInt());
        ui->comboBoxMinJinShenList3->setCurrentIndex(pSettings->value("minList3", -1).toInt());
        ui->comboBoxMinJinShenList4->setCurrentIndex(pSettings->value("minList4", -1).toInt());
        ui->comboBoxMinJinShenList5->setCurrentIndex(pSettings->value("minList5", -1).toInt());
        ui->comboBoxMinJinShenList6->setCurrentIndex(pSettings->value("minList6", -1).toInt());
        ui->comboBoxMinJinShenList7->setCurrentIndex(pSettings->value("minList7", -1).toInt());
        ui->comboBoxMinJinShenList8->setCurrentIndex(pSettings->value("minList8", -1).toInt());

        pSettings->endGroup();
    }

    //八卦
    pSettings->beginGroup("BaGua");
    //大号
    ui->checkBoxMaxBaGuaMap1->setChecked(pSettings->value("maxMap1", false).toBool());
    ui->checkBoxMaxBaGuaMap2->setChecked(pSettings->value("maxMap2", false).toBool());
    ui->checkBoxMaxBaGuaMap3->setChecked(pSettings->value("maxMap3", false).toBool());
    ui->checkBoxMaxBaGuaMap4->setChecked(pSettings->value("maxMap4", false).toBool());
    ui->checkBoxMaxBaGuaMap5->setChecked(pSettings->value("maxMap5", false).toBool());
    ui->comboBoxMaxBaGuaList1->setCurrentIndex(pSettings->value("maxList1", -1).toInt());
    ui->comboBoxMaxBaGuaList2->setCurrentIndex(pSettings->value("maxList2", -1).toInt());
    ui->comboBoxMaxBaGuaList3->setCurrentIndex(pSettings->value("maxList3", -1).toInt());
    ui->comboBoxMaxBaGuaList4->setCurrentIndex(pSettings->value("maxList4", -1).toInt());
    ui->comboBoxMaxBaGuaList5->setCurrentIndex(pSettings->value("maxList5", -1).toInt());

    if (mType == TYPE_ZHI_ZUN) {
        //小号
        ui->checkBoxMinBaGuaMap1->setChecked(pSettings->value("minMap1", false).toBool());
        ui->checkBoxMinBaGuaMap2->setChecked(pSettings->value("minMap2", false).toBool());
        ui->checkBoxMinBaGuaMap3->setChecked(pSettings->value("minMap3", false).toBool());
        ui->checkBoxMinBaGuaMap4->setChecked(pSettings->value("minMap4", false).toBool());
        ui->checkBoxMinBaGuaMap5->setChecked(pSettings->value("minMap5", false).toBool());
        ui->comboBoxMinBaGuaList1->setCurrentIndex(pSettings->value("minList1", -1).toInt());
        ui->comboBoxMinBaGuaList2->setCurrentIndex(pSettings->value("minList2", -1).toInt());
        ui->comboBoxMinBaGuaList3->setCurrentIndex(pSettings->value("minList3", -1).toInt());
        ui->comboBoxMinBaGuaList4->setCurrentIndex(pSettings->value("minList4", -1).toInt());
        ui->comboBoxMinBaGuaList5->setCurrentIndex(pSettings->value("minList5", -1).toInt());
    }
    pSettings->endGroup();

    //冥界-幽冥
    if (mType == TYPE_ZHI_ZUN) {
        //大号
        pSettings->beginGroup("YouMing");
        //大号
        ui->comboBoxMaxYouMingTop1->setCurrentIndex(pSettings->value("maxTop1", -1).toInt());
        ui->comboBoxMaxYouMingTop2->setCurrentIndex(pSettings->value("maxTop2", -1).toInt());
        ui->comboBoxMaxYouMingTop3->setCurrentIndex(pSettings->value("maxTop3", -1).toInt());
        ui->checkBoxMaxYouMingMap1->setChecked(pSettings->value("maxMap1", false).toBool());
        ui->checkBoxMaxYouMingMap2->setChecked(pSettings->value("maxMap2", false).toBool());
        ui->checkBoxMaxYouMingMap3->setChecked(pSettings->value("maxMap3", false).toBool());
        ui->checkBoxMaxYouMingMap4->setChecked(pSettings->value("maxMap4", false).toBool());
        ui->checkBoxMaxYouMingMap5->setChecked(pSettings->value("maxMap5", false).toBool());
        ui->checkBoxMaxYouMingMap6->setChecked(pSettings->value("maxMap6", false).toBool());
        ui->checkBoxMaxYouMingMap7->setChecked(pSettings->value("maxMap7", false).toBool());
        ui->checkBoxMaxYouMingMap8->setChecked(pSettings->value("maxMap8", false).toBool());
        ui->comboBoxMaxYouMingList1->setCurrentIndex(pSettings->value("maxList1", -1).toInt());
        ui->comboBoxMaxYouMingList2->setCurrentIndex(pSettings->value("maxList2", -1).toInt());
        ui->comboBoxMaxYouMingList3->setCurrentIndex(pSettings->value("maxList3", -1).toInt());
        ui->comboBoxMaxYouMingList4->setCurrentIndex(pSettings->value("maxList4", -1).toInt());
        ui->comboBoxMaxYouMingList5->setCurrentIndex(pSettings->value("maxList5", -1).toInt());
        ui->comboBoxMaxYouMingList6->setCurrentIndex(pSettings->value("maxList6", -1).toInt());
        ui->comboBoxMaxYouMingList7->setCurrentIndex(pSettings->value("maxList7", -1).toInt());
        ui->comboBoxMaxYouMingList8->setCurrentIndex(pSettings->value("maxList8", -1).toInt());

        //小号
        ui->comboBoxMinYouMingTop1->setCurrentIndex(pSettings->value("minTop1", -1).toInt());
        ui->comboBoxMinYouMingTop2->setCurrentIndex(pSettings->value("minTop2", -1).toInt());
        ui->comboBoxMinYouMingTop3->setCurrentIndex(pSettings->value("minTop3", -1).toInt());
        ui->checkBoxMinYouMingMap1->setChecked(pSettings->value("minMap1", false).toBool());
        ui->checkBoxMinYouMingMap2->setChecked(pSettings->value("minMap2", false).toBool());
        ui->checkBoxMinYouMingMap3->setChecked(pSettings->value("minMap3", false).toBool());
        ui->checkBoxMinYouMingMap4->setChecked(pSettings->value("minMap4", false).toBool());
        ui->checkBoxMinYouMingMap5->setChecked(pSettings->value("minMap5", false).toBool());
        ui->checkBoxMinYouMingMap6->setChecked(pSettings->value("minMap6", false).toBool());
        ui->checkBoxMinYouMingMap7->setChecked(pSettings->value("minMap7", false).toBool());
        ui->checkBoxMinYouMingMap8->setChecked(pSettings->value("minMap8", false).toBool());
        ui->comboBoxMinYouMingList1->setCurrentIndex(pSettings->value("minList1", -1).toInt());
        ui->comboBoxMinYouMingList2->setCurrentIndex(pSettings->value("minList2", -1).toInt());
        ui->comboBoxMinYouMingList3->setCurrentIndex(pSettings->value("minList3", -1).toInt());
        ui->comboBoxMinYouMingList4->setCurrentIndex(pSettings->value("minList4", -1).toInt());
        ui->comboBoxMinYouMingList5->setCurrentIndex(pSettings->value("minList5", -1).toInt());
        ui->comboBoxMinYouMingList6->setCurrentIndex(pSettings->value("minList6", -1).toInt());
        ui->comboBoxMinYouMingList7->setCurrentIndex(pSettings->value("minList7", -1).toInt());
        ui->comboBoxMinYouMingList8->setCurrentIndex(pSettings->value("minList8", -1).toInt());

        pSettings->endGroup();
    }

    //冥界-驯龙

    if (mType == TYPE_ZHI_ZUN) {
        //大号
        pSettings->beginGroup("XunLong");
        //大号
        ui->comboBoxMaxXunLongTop1->setCurrentIndex(pSettings->value("maxTop1", -1).toInt());
        ui->comboBoxMaxXunLongTop2->setCurrentIndex(pSettings->value("maxTop2", -1).toInt());
        ui->comboBoxMaxXunLongTop3->setCurrentIndex(pSettings->value("maxTop3", -1).toInt());
        ui->checkBoxMaxXunLongMap1->setChecked(pSettings->value("maxMap1", false).toBool());
        ui->checkBoxMaxXunLongMap2->setChecked(pSettings->value("maxMap2", false).toBool());
        ui->checkBoxMaxXunLongMap3->setChecked(pSettings->value("maxMap3", false).toBool());
        ui->checkBoxMaxXunLongMap4->setChecked(pSettings->value("maxMap4", false).toBool());
        ui->checkBoxMaxXunLongMap5->setChecked(pSettings->value("maxMap5", false).toBool());
        ui->checkBoxMaxXunLongMap6->setChecked(pSettings->value("maxMap6", false).toBool());
        ui->checkBoxMaxXunLongMap7->setChecked(pSettings->value("maxMap7", false).toBool());
        ui->checkBoxMaxXunLongMap8->setChecked(pSettings->value("maxMap8", false).toBool());
        ui->comboBoxMaxXunLongList1->setCurrentIndex(pSettings->value("maxList1", -1).toInt());
        ui->comboBoxMaxXunLongList2->setCurrentIndex(pSettings->value("maxList2", -1).toInt());
        ui->comboBoxMaxXunLongList3->setCurrentIndex(pSettings->value("maxList3", -1).toInt());
        ui->comboBoxMaxXunLongList4->setCurrentIndex(pSettings->value("maxList4", -1).toInt());
        ui->comboBoxMaxXunLongList5->setCurrentIndex(pSettings->value("maxList5", -1).toInt());
        ui->comboBoxMaxXunLongList6->setCurrentIndex(pSettings->value("maxList6", -1).toInt());
        ui->comboBoxMaxXunLongList7->setCurrentIndex(pSettings->value("maxList7", -1).toInt());
        ui->comboBoxMaxXunLongList8->setCurrentIndex(pSettings->value("maxList8", -1).toInt());

        //小号
        ui->comboBoxMinXunLongTop1->setCurrentIndex(pSettings->value("minTop1", -1).toInt());
        ui->comboBoxMinXunLongTop2->setCurrentIndex(pSettings->value("minTop2", -1).toInt());
        ui->comboBoxMinXunLongTop3->setCurrentIndex(pSettings->value("minTop3", -1).toInt());
        ui->checkBoxMinXunLongMap1->setChecked(pSettings->value("minMap1", false).toBool());
        ui->checkBoxMinXunLongMap2->setChecked(pSettings->value("minMap2", false).toBool());
        ui->checkBoxMinXunLongMap3->setChecked(pSettings->value("minMap3", false).toBool());
        ui->checkBoxMinXunLongMap4->setChecked(pSettings->value("minMap4", false).toBool());
        ui->checkBoxMinXunLongMap5->setChecked(pSettings->value("minMap5", false).toBool());
        ui->checkBoxMinXunLongMap6->setChecked(pSettings->value("minMap6", false).toBool());
        ui->checkBoxMinXunLongMap7->setChecked(pSettings->value("minMap7", false).toBool());
        ui->checkBoxMinXunLongMap8->setChecked(pSettings->value("minMap8", false).toBool());
        ui->comboBoxMinXunLongList1->setCurrentIndex(pSettings->value("minList1", -1).toInt());
        ui->comboBoxMinXunLongList2->setCurrentIndex(pSettings->value("minList2", -1).toInt());
        ui->comboBoxMinXunLongList3->setCurrentIndex(pSettings->value("minList3", -1).toInt());
        ui->comboBoxMinXunLongList4->setCurrentIndex(pSettings->value("minList4", -1).toInt());
        ui->comboBoxMinXunLongList5->setCurrentIndex(pSettings->value("minList5", -1).toInt());
        ui->comboBoxMinXunLongList6->setCurrentIndex(pSettings->value("minList6", -1).toInt());
        ui->comboBoxMinXunLongList7->setCurrentIndex(pSettings->value("minList7", -1).toInt());
        ui->comboBoxMinXunLongList8->setCurrentIndex(pSettings->value("minList8", -1).toInt());

        pSettings->endGroup();
    }

    //冥界-神魔
    if (mType == TYPE_ZHI_ZUN) {
        //大号
        pSettings->beginGroup("ShenMo");
        //大号
        ui->comboBoxMaxShenMoTop1->setCurrentIndex(pSettings->value("maxTop1", -1).toInt());
        ui->comboBoxMaxShenMoTop2->setCurrentIndex(pSettings->value("maxTop2", -1).toInt());
        ui->comboBoxMaxShenMoTop3->setCurrentIndex(pSettings->value("maxTop3", -1).toInt());
        ui->checkBoxMaxShenMoMap1->setChecked(pSettings->value("maxMap1", false).toBool());
        ui->checkBoxMaxShenMoMap2->setChecked(pSettings->value("maxMap2", false).toBool());
        ui->checkBoxMaxShenMoMap3->setChecked(pSettings->value("maxMap3", false).toBool());
        ui->checkBoxMaxShenMoMap4->setChecked(pSettings->value("maxMap4", false).toBool());
        ui->checkBoxMaxShenMoMap5->setChecked(pSettings->value("maxMap5", false).toBool());
        ui->checkBoxMaxShenMoMap6->setChecked(pSettings->value("maxMap6", false).toBool());
        ui->checkBoxMaxShenMoMap7->setChecked(pSettings->value("maxMap7", false).toBool());
        ui->checkBoxMaxShenMoMap8->setChecked(pSettings->value("maxMap8", false).toBool());
        ui->comboBoxMaxShenMoList1->setCurrentIndex(pSettings->value("maxList1", -1).toInt());
        ui->comboBoxMaxShenMoList2->setCurrentIndex(pSettings->value("maxList2", -1).toInt());
        ui->comboBoxMaxShenMoList3->setCurrentIndex(pSettings->value("maxList3", -1).toInt());
        ui->comboBoxMaxShenMoList4->setCurrentIndex(pSettings->value("maxList4", -1).toInt());
        ui->comboBoxMaxShenMoList5->setCurrentIndex(pSettings->value("maxList5", -1).toInt());
        ui->comboBoxMaxShenMoList6->setCurrentIndex(pSettings->value("maxList6", -1).toInt());
        ui->comboBoxMaxShenMoList7->setCurrentIndex(pSettings->value("maxList7", -1).toInt());
        ui->comboBoxMaxShenMoList8->setCurrentIndex(pSettings->value("maxList8", -1).toInt());

        //小号
        ui->comboBoxMinShenMoTop1->setCurrentIndex(pSettings->value("minTop1", -1).toInt());
        ui->comboBoxMinShenMoTop2->setCurrentIndex(pSettings->value("minTop2", -1).toInt());
        ui->comboBoxMinShenMoTop3->setCurrentIndex(pSettings->value("minTop3", -1).toInt());
        ui->checkBoxMinShenMoMap1->setChecked(pSettings->value("minMap1", false).toBool());
        ui->checkBoxMinShenMoMap2->setChecked(pSettings->value("minMap2", false).toBool());
        ui->checkBoxMinShenMoMap3->setChecked(pSettings->value("minMap3", false).toBool());
        ui->checkBoxMinShenMoMap4->setChecked(pSettings->value("minMap4", false).toBool());
        ui->checkBoxMinShenMoMap5->setChecked(pSettings->value("minMap5", false).toBool());
        ui->checkBoxMinShenMoMap6->setChecked(pSettings->value("minMap6", false).toBool());
        ui->checkBoxMinShenMoMap7->setChecked(pSettings->value("minMap7", false).toBool());
        ui->checkBoxMinShenMoMap8->setChecked(pSettings->value("minMap8", false).toBool());
        ui->comboBoxMinShenMoList1->setCurrentIndex(pSettings->value("minList1", -1).toInt());
        ui->comboBoxMinShenMoList2->setCurrentIndex(pSettings->value("minList2", -1).toInt());
        ui->comboBoxMinShenMoList3->setCurrentIndex(pSettings->value("minList3", -1).toInt());
        ui->comboBoxMinShenMoList4->setCurrentIndex(pSettings->value("minList4", -1).toInt());
        ui->comboBoxMinShenMoList5->setCurrentIndex(pSettings->value("minList5", -1).toInt());
        ui->comboBoxMinShenMoList6->setCurrentIndex(pSettings->value("minList6", -1).toInt());
        ui->comboBoxMinShenMoList7->setCurrentIndex(pSettings->value("minList7", -1).toInt());
        ui->comboBoxMinShenMoList8->setCurrentIndex(pSettings->value("minList8", -1).toInt());

        pSettings->endGroup();
    }
}

void MainWindow::initHwnd()
{
    //初始化大小号线程
    if (mPlatform == PLATFORM_DA_TING) {
        //游戏大厅
        //初始化大号
        if (!maxInited) {
            maxInited = true;
            pMaxWorker = new DaTingWorker();
            pMaxWorker->moveToThread(pMaxThread);
            connect(pMaxThread, &QThread::started, pMaxWorker, &MyWorker::doShuaTu);
        }
        //初始化小号
        if (!minInited) {
            minInited = true;
            pMinWorker = new DaTingWorker();
            pMinWorker->moveToThread(pMinThread);
            connect(pMinThread, &QThread::started, pMinWorker, &MyWorker::doShuaTu);
        }
    } else if (mPlatform == PLATFORM_ZHONG_XIN) {
        //游戏中心
        //初始化大号
        if (!maxInited) {
            maxInited = true;
            pMaxWorker = new ZhongXinWorker();
            pMaxWorker->moveToThread(pMaxThread);
            connect(pMaxThread, &QThread::started, pMaxWorker, &MyWorker::doShuaTu);
        }
        //初始化小号
        if (!minInited) {
            minInited = true;
            pMinWorker = new ZhongXinWorker();
            pMinWorker->moveToThread(pMinThread);
            connect(pMinThread, &QThread::started, pMinWorker, &MyWorker::doShuaTu);
        }
    }


    hwndList.clear();
    hwndNameList.clear();

    //获取桌面窗口句柄
    HWND hwnd = NULL;
    HWND hwndChild = NULL;

    hwnd = GetDesktopWindow();
    if (!IsWindow(hwnd)) {
        qDebug() << "initHwnd: 桌面窗口句柄获取失败";
        return;
    }

    // 初始化hWndChild为NULL，表示从第一个子窗口开始查找
    if (mPlatform == PLATFORM_DA_TING) {
        //游戏大厅
        hwndChild = FindWindowEx(hwnd, NULL, L"GLFW30", NULL);
    } else if (mPlatform == PLATFORM_ZHONG_XIN) {
        //游戏中心
        hwndChild = FindWindowEx(hwnd, NULL, L"Chrome_WidgetWin_1", L"QQGAME");
    }

    // 循环遍历所有子窗口
    while (hwndChild != NULL) {
        // 继续查找下一个子窗口
        if (mPlatform == PLATFORM_DA_TING) {
            //游戏大厅
            hwndList.append(hwndChild);
            hwndNameList.append(captureHiddenWindow(hwndChild));

            hwndChild = FindWindowEx(hwnd, hwndChild, L"GLFW30", NULL);
        } else if (mPlatform == PLATFORM_ZHONG_XIN) {
            //游戏中心
            HWND tempHwnd = FindWindowEx(hwndChild, NULL, L"Chrome_RenderWidgetHostHWND", L"Chrome Legacy Window");
            if (tempHwnd != NULL) {
                hwndList.append(tempHwnd);
                hwndNameList.append(captureHiddenWindow(tempHwnd));
            }
            hwndChild = FindWindowEx(hwnd, hwndChild, L"Chrome_WidgetWin_1", L"QQGAME");
        }
    }

    if (hwndList.empty()) {
        qWarning() << "initHwnd: 窗口句柄为空";
        return;
    }
    ui->comboBoxMaxId->clear();
    ui->comboBoxMinId->clear();

    for (int i = 0; i < hwndList.size(); i++) {
        ui->comboBoxMaxId->addItem(QString::number(reinterpret_cast<quintptr>(hwndList.at(i)), 16));
        if (mType == TYPE_ZHI_ZUN) {
            ui->comboBoxMinId->addItem(QString::number(reinterpret_cast<quintptr>(hwndList.at(i)), 16));
        }
    }
}

QPixmap MainWindow::captureHiddenWindow(HWND hwnd) {

    if (!IsWindow(hwnd)) {
        qWarning() << "captureHiddenWindow: 窗口不存在！";
        return QPixmap();
    }

    RECT rect;
    if (!GetWindowRect(hwnd, &rect)) {
        qWarning() << "captureHiddenWindow: 获取窗口矩形失败！";
        return QPixmap();
    }

    int width = rect.right - rect.left;
    int height = rect.bottom - rect.top;

    HDC hdcScreen = GetDC(hwnd);
    HDC hdcMem = CreateCompatibleDC(hdcScreen);
    HBITMAP hBitmap = CreateCompatibleBitmap(hdcScreen, width, height);
    SelectObject(hdcMem, hBitmap);

    // 使用 PrintWindow 输出被遮挡部分
    if (!PrintWindow(hwnd, hdcMem, PW_RENDERFULLCONTENT)) {
        qWarning() << "captureHiddenWindow: PrintWindow 失败！";
        DeleteObject(hBitmap);
        DeleteDC(hdcMem);
        ReleaseDC(hwnd, hdcScreen);
        return QPixmap();
    }

    // 将 HBITMAP 转换为 QImage
    BITMAP bmp;
    GetObject(hBitmap, sizeof(BITMAP), &bmp);
    QImage img(width, height, QImage::Format_RGB32);

    BITMAPINFOHEADER bi;
    ZeroMemory(&bi, sizeof(BITMAPINFOHEADER));
    bi.biSize = sizeof(BITMAPINFOHEADER);
    bi.biWidth = width;
    bi.biHeight = -height;  // 负数表示从顶向下存储
    bi.biPlanes = 1;
    bi.biBitCount = 32;
    bi.biCompression = BI_RGB;

    GetDIBits(hdcMem, hBitmap, 0, height, img.bits(), (BITMAPINFO*)&bi, DIB_RGB_COLORS);

    QPixmap pixmap = QPixmap::fromImage(img);
    //pixmap.save("screenshot.png");

    //qDebug() << "截图完成，保存为 screenshot.png";

    DeleteObject(hBitmap);
    DeleteDC(hdcMem);
    ReleaseDC(hwnd, hdcScreen);

    // 定义要截取的区域
    int x = 10;
    int y = 10;
    if (mPlatform == PLATFORM_DA_TING) {
        //游戏大厅
        if (QSysInfo::productVersion().toInt() < 11) {
            //win 10及以下
            if (this->width == 1920 && this->height == 1080) {
                x = 1390;
                y = 935;
            } else {
                x = 1037;
                y = 643;
            }
        } else {
            //win 11
            x = 1390;
            y = 928;
        }
    } else if (mPlatform == PLATFORM_ZHONG_XIN) {
        //游戏中心
        if (QSysInfo::productVersion().toInt() < 11) {
            //win 10及以下
            x = 1370;
            y = 931;
        } else {
            //win 11
            x = 1370;
            y = 930;
        }
    }
    QRect qrect(x, y, 100, 25);

    return pixmap.copy(qrect);
}

void MainWindow::showHwndInfo()
{
    ui->comboBoxMaxId->clear();
    ui->comboBoxMinId->clear();

    if (hwndList.isEmpty()) {
        qWarning() << "showHwndInfo: 窗口句柄列表为空!";
        return;
    }
    for (int i = 0; i < hwndList.size(); i++) {
        ui->comboBoxMaxId->addItem(QString::number(reinterpret_cast<quintptr>(hwndList.at(i)), 16));
        if (mType == TYPE_ZHI_ZUN) {
            ui->comboBoxMinId->addItem(QString::number(reinterpret_cast<quintptr>(hwndList.at(i)), 16));
        }
    }
}

/**
 * @brief backgroundClick   根据窗口句柄后台点击
 * @param hwnd  窗口句柄
 * @param point 点击坐标
 */
void MainWindow::backgroundClick(HWND hwnd, QPoint point)
{
    if (!IsWindow(hwnd)) {
        qWarning() << "backgroundClick: 窗口不存在!";
        return;
    }
    LPARAM lParam = MAKELPARAM(point.x(), point.y());
    PostMessage(hwnd, WM_MOUSEMOVE, 0, lParam);
    PostMessage(hwnd, WM_LBUTTONDOWN, MK_LBUTTON, lParam);
    PostMessage(hwnd, WM_LBUTTONUP, 0, lParam);
}

/**
 * @brief checkPixelColor   根据窗口句柄检查某一坐标是否是某颜色
 * @param hwnd  窗口句柄
 * @param point 检查的坐标
 * @param color 目标颜色
 * @return
 */
bool MainWindow::checkPixelColor(HWND hwnd, QPoint point, QColor color)
{
    if (!IsWindow(hwnd)) {
        qWarning() << "checkPixelColor: 窗口不存在!";
        return false;
    }

    //获取窗口上下文
    HDC hdc = GetDC(hwnd);
    if (hdc == NULL) {
        qWarning() << "checkPixelColor: hdc获取失败!";
        return false;
    }
    COLORREF colorREF = GetPixel(hdc, point.x(), point.y());

    //释放窗口上下文
    ReleaseDC(hwnd, hdc);

    unsigned char red = GetRValue(colorREF);
    unsigned char geen = GetGValue(colorREF);
    unsigned char blue = GetBValue(colorREF);
    //qDebug() << "R:" << red << ", G:" << geen << ", B:" << blue;

    if ((red > color.red() - 5 && red < color.red() + 5) && (geen > color.green() - 5 && geen < color.green() + 5) && (blue > color.blue() - 5 && blue < color.blue() + 5)) {
        return true;
    }
    return false;
}

void MainWindow::setMaxThreadParameter()
{
    int top[3] = {0};
    QStringList list;
    if (ui->checkBoxMaxEnable->isEnabled() && ui->checkBoxMaxEnable->isChecked()) {
        //初始化
        pMaxWorker->initThread(hwndList.at(ui->comboBoxMaxId->currentIndex()), pMapManager);
        //基础
        bool zhenCe = ui->checkBoxMaxZhenCe->isChecked();
        bool fuHuo = ui->checkBoxMaxFuHuo->isChecked();
        bool chongLian = ui->checkBoxMaxChongLian->isChecked();
        bool suiJi = ui->checkBoxMaxSuiJi->isChecked();
        bool zhuangBei = ui->checkBoxMaxZhuangBei->isChecked();
        bool hangHuiMode = ui->checkBoxMaxHangHuiMode->isChecked();
        pMaxWorker->setJiChu(zhenCe, fuHuo, chongLian, suiJi, zhuangBei, hangHuiMode);

        QTime startTime = ui->timeEditMaxStart->time();
        QTime endTime = ui->timeEditMaxEnd->time();
        xiuMianStartMax[0] = startTime.hour();
        xiuMianStartMax[1] = startTime.minute();
        xiuMianEndMax[0] = endTime.hour();
        xiuMianEndMax[1] = endTime.minute();

        startTimeMax = xiuMianStartMax[0] * 60 + xiuMianStartMax[1];
        endTimeMax = xiuMianEndMax[0] * 60 + xiuMianEndMax[1];
        xiuMianEnable[0] = ui->checkBoxMaxXiuMian->isChecked();

        //分解
        bool fenJie[4] = {false};
        if (ui->checkBoxMaxFenJieDouLi->isChecked()) {
            fenJie[0] = true;
        }
        if (ui->checkBoxMaxFenJieHuDun->isChecked()) {
            fenJie[1] = true;
        }
        if (ui->checkBoxMaxFenJieBaGua->isChecked()) {
            fenJie[2] = true;
        }
        if (ui->checkBoxMaxFenJieYouMing->isChecked()) {
            fenJie[3] = true;
        }
        pMaxWorker->setFenJie(fenJie, 4);

        //等级
        if (ui->comboBoxMaxDengJiTop1->currentIndex() == -1) {
            top[0] = 0;
        } else {
            top[0] = ui->comboBoxMaxDengJiTop1->currentText().toInt();
        }
        if (ui->comboBoxMaxDengJiTop2->currentIndex() == -1) {
            top[1] = 0;
        } else {
            top[1] = ui->comboBoxMaxDengJiTop2->currentText().toInt();
        }
        if (ui->comboBoxMaxDengJiTop3->currentIndex() == -1) {
            top[2] = 0;
        } else {
            top[2] = ui->comboBoxMaxDengJiTop3->currentText().toInt();
        }

        if (ui->checkBoxMaxDengJiMap1->isChecked() && ui->comboBoxMaxDengJiList1->currentIndex() > -1) {
            list.append(ui->comboBoxMaxDengJiList1->currentText());
        }
        if (ui->checkBoxMaxDengJiMap2->isChecked() && ui->comboBoxMaxDengJiList2->currentIndex() > -1) {
            list.append(ui->comboBoxMaxDengJiList2->currentText());
        }
        if (ui->checkBoxMaxDengJiMap3->isChecked() && ui->comboBoxMaxDengJiList3->currentIndex() > -1) {
            list.append(ui->comboBoxMaxDengJiList3->currentText());
        }
        if (ui->checkBoxMaxDengJiMap4->isChecked() && ui->comboBoxMaxDengJiList4->currentIndex() > -1) {
            list.append(ui->comboBoxMaxDengJiList4->currentText());
        }
        if (ui->checkBoxMaxDengJiMap5->isChecked() && ui->comboBoxMaxDengJiList5->currentIndex() > -1) {
            list.append(ui->comboBoxMaxDengJiList5->currentText());
        }
        if (ui->checkBoxMaxDengJiMap6->isChecked() && ui->comboBoxMaxDengJiList6->currentIndex() > -1) {
            list.append(ui->comboBoxMaxDengJiList6->currentText());
        }
        if (ui->checkBoxMaxDengJiMap7->isChecked() && ui->comboBoxMaxDengJiList7->currentIndex() > -1) {
            list.append(ui->comboBoxMaxDengJiList7->currentText());
        }
        if (ui->checkBoxMaxDengJiMap8->isChecked() && ui->comboBoxMaxDengJiList8->currentIndex() > -1) {
            list.append(ui->comboBoxMaxDengJiList8->currentText());
        }
        pMaxWorker->setDengJiParameter(top, 3, list);

        //斗笠
        if (ui->comboBoxMaxDouLiTop1->currentIndex() == -1) {
            top[0] = 0;
        } else {
            top[0] = ui->comboBoxMaxDouLiTop1->currentText().toInt();
        }
        if (ui->comboBoxMaxDouLiTop2->currentIndex() == -1) {
            top[1] = 0;
        } else {
            top[1] = ui->comboBoxMaxDouLiTop2->currentText().toInt();
        }
        if (ui->comboBoxMaxDouLiTop3->currentIndex() == -1) {
            top[2] = 0;
        } else {
            top[2] = ui->comboBoxMaxDouLiTop3->currentText().toInt();
        }

        list.clear();
        if (ui->checkBoxMaxDouLiMap1->isChecked() && ui->comboBoxMaxDouLiList1->currentIndex() > -1) {
            list.append(ui->comboBoxMaxDouLiList1->currentText());
        }
        if (ui->checkBoxMaxDouLiMap2->isChecked() && ui->comboBoxMaxDouLiList2->currentIndex() > -1) {
            list.append(ui->comboBoxMaxDouLiList2->currentText());
        }
        if (ui->checkBoxMaxDouLiMap3->isChecked() && ui->comboBoxMaxDouLiList3->currentIndex() > -1) {
            list.append(ui->comboBoxMaxDouLiList3->currentText());
        }
        if (ui->checkBoxMaxDouLiMap4->isChecked() && ui->comboBoxMaxDouLiList4->currentIndex() > -1) {
            list.append(ui->comboBoxMaxDouLiList4->currentText());
        }
        if (ui->checkBoxMaxDouLiMap5->isChecked() && ui->comboBoxMaxDouLiList5->currentIndex() > -1) {
            list.append(ui->comboBoxMaxDouLiList5->currentText());
        }
        if (ui->checkBoxMaxDouLiMap6->isChecked() && ui->comboBoxMaxDouLiList6->currentIndex() > -1) {
            list.append(ui->comboBoxMaxDouLiList6->currentText());
        }
        if (ui->checkBoxMaxDouLiMap7->isChecked() && ui->comboBoxMaxDouLiList7->currentIndex() > -1) {
            list.append(ui->comboBoxMaxDouLiList7->currentText());
        }
        if (ui->checkBoxMaxDouLiMap8->isChecked() && ui->comboBoxMaxDouLiList8->currentIndex() > -1) {
            list.append(ui->comboBoxMaxDouLiList8->currentText());
        }
        pMaxWorker->setDouLiParameter(top, 3, list);

        //护盾
        if (ui->comboBoxMaxHuDunTop1->currentIndex() == -1) {
            top[0] = 0;
        } else {
            top[0] = ui->comboBoxMaxHuDunTop1->currentText().toInt();
        }
        if (ui->comboBoxMaxHuDunTop2->currentIndex() == -1) {
            top[1] = 0;
        } else {
            top[1] = ui->comboBoxMaxHuDunTop2->currentText().toInt();
        }
        if (ui->comboBoxMaxHuDunTop3->currentIndex() == -1) {
            top[2] = 0;
        } else {
            top[2] = ui->comboBoxMaxHuDunTop3->currentText().toInt();
        }

        list.clear();
        if (ui->checkBoxMaxHuDunMap1->isChecked() && ui->comboBoxMaxHuDunList1->currentIndex() > -1) {
            list.append(ui->comboBoxMaxHuDunList1->currentText());
        }
        if (ui->checkBoxMaxHuDunMap2->isChecked() && ui->comboBoxMaxHuDunList2->currentIndex() > -1) {
            list.append(ui->comboBoxMaxHuDunList2->currentText());
        }
        if (ui->checkBoxMaxHuDunMap3->isChecked() && ui->comboBoxMaxHuDunList3->currentIndex() > -1) {
            list.append(ui->comboBoxMaxHuDunList3->currentText());
        }
        if (ui->checkBoxMaxHuDunMap4->isChecked() && ui->comboBoxMaxHuDunList4->currentIndex() > -1) {
            list.append(ui->comboBoxMaxHuDunList4->currentText());
        }
        if (ui->checkBoxMaxHuDunMap5->isChecked() && ui->comboBoxMaxHuDunList5->currentIndex() > -1) {
            list.append(ui->comboBoxMaxHuDunList5->currentText());
        }
        if (ui->checkBoxMaxHuDunMap6->isChecked() && ui->comboBoxMaxHuDunList6->currentIndex() > -1) {
            list.append(ui->comboBoxMaxHuDunList6->currentText());
        }
        if (ui->checkBoxMaxHuDunMap7->isChecked() && ui->comboBoxMaxHuDunList7->currentIndex() > -1) {
            list.append(ui->comboBoxMaxHuDunList7->currentText());
        }
        if (ui->checkBoxMaxHuDunMap8->isChecked() && ui->comboBoxMaxHuDunList8->currentIndex() > -1) {
            list.append(ui->comboBoxMaxHuDunList8->currentText());
        }
        pMaxWorker->setHuDunParameter(top, 3, list);

        //星座
        if (ui->comboBoxMaxXingZuoTop1->currentIndex() == -1) {
            top[0] = 0;
        } else {
            top[0] = ui->comboBoxMaxXingZuoTop1->currentText().toInt();
        }
        if (ui->comboBoxMaxXingZuoTop2->currentIndex() == -1) {
            top[1] = 0;
        } else {
            top[1] = ui->comboBoxMaxXingZuoTop2->currentText().toInt();
        }
        if (ui->comboBoxMaxXingZuoTop3->currentIndex() == -1) {
            top[2] = 0;
        } else {
            top[2] = ui->comboBoxMaxXingZuoTop3->currentText().toInt();
        }

        list.clear();
        if (ui->checkBoxMaxXingZuoMap1->isChecked() && ui->comboBoxMaxXingZuoList1->currentIndex() > -1) {
            list.append(ui->comboBoxMaxXingZuoList1->currentText());
        }
        if (ui->checkBoxMaxXingZuoMap2->isChecked() && ui->comboBoxMaxXingZuoList2->currentIndex() > -1) {
            list.append(ui->comboBoxMaxXingZuoList2->currentText());
        }
        if (ui->checkBoxMaxXingZuoMap3->isChecked() && ui->comboBoxMaxXingZuoList3->currentIndex() > -1) {
            list.append(ui->comboBoxMaxXingZuoList3->currentText());
        }
        if (ui->checkBoxMaxXingZuoMap4->isChecked() && ui->comboBoxMaxXingZuoList4->currentIndex() > -1) {
            list.append(ui->comboBoxMaxXingZuoList4->currentText());
        }
        if (ui->checkBoxMaxXingZuoMap5->isChecked() && ui->comboBoxMaxXingZuoList5->currentIndex() > -1) {
            list.append(ui->comboBoxMaxXingZuoList5->currentText());
        }
        if (ui->checkBoxMaxXingZuoMap6->isChecked() && ui->comboBoxMaxXingZuoList6->currentIndex() > -1) {
            list.append(ui->comboBoxMaxXingZuoList6->currentText());
        }
        if (ui->checkBoxMaxXingZuoMap7->isChecked() && ui->comboBoxMaxXingZuoList7->currentIndex() > -1) {
            list.append(ui->comboBoxMaxXingZuoList7->currentText());
        }
        if (ui->checkBoxMaxXingZuoMap8->isChecked() && ui->comboBoxMaxXingZuoList8->currentIndex() > -1) {
            list.append(ui->comboBoxMaxXingZuoList8->currentText());
        }
        pMaxWorker->setXingZuoParameter(top, 3, list);

        //八卦
        list.clear();
        if (ui->checkBoxMaxBaGuaMap1->isChecked() && ui->comboBoxMaxBaGuaList1->currentIndex() > -1) {
            list.append(ui->comboBoxMaxBaGuaList1->currentText());
        }
        if (ui->checkBoxMaxBaGuaMap2->isChecked() && ui->comboBoxMaxBaGuaList2->currentIndex() > -1) {
            list.append(ui->comboBoxMaxBaGuaList2->currentText());
        }
        if (ui->checkBoxMaxBaGuaMap3->isChecked() && ui->comboBoxMaxBaGuaList3->currentIndex() > -1) {
            list.append(ui->comboBoxMaxBaGuaList3->currentText());
        }
        if (ui->checkBoxMaxBaGuaMap4->isChecked() && ui->comboBoxMaxBaGuaList4->currentIndex() > -1) {
            list.append(ui->comboBoxMaxBaGuaList4->currentText());
        }
        if (ui->checkBoxMaxBaGuaMap5->isChecked() && ui->comboBoxMaxBaGuaList5->currentIndex() > -1) {
            list.append(ui->comboBoxMaxBaGuaList5->currentText());
        }
        pMaxWorker->setBaGuaParameter(list);

        //金身
        if (ui->comboBoxMaxJinShenTop1->currentIndex() == -1) {
            top[0] = 0;
        } else {
            top[0] = ui->comboBoxMaxJinShenTop1->currentText().toInt();
        }
        if (ui->comboBoxMaxJinShenTop2->currentIndex() == -1) {
            top[1] = 0;
        } else {
            top[1] = ui->comboBoxMaxJinShenTop2->currentText().toInt();
        }
        if (ui->comboBoxMaxJinShenTop3->currentIndex() == -1) {
            top[2] = 0;
        } else {
            top[2] = ui->comboBoxMaxJinShenTop3->currentText().toInt();
        }

        list.clear();
        if (ui->checkBoxMaxJinShenMap1->isChecked() && ui->comboBoxMaxJinShenList1->currentIndex() > -1) {
            list.append(ui->comboBoxMaxJinShenList1->currentText());
        }
        if (ui->checkBoxMaxJinShenMap2->isChecked() && ui->comboBoxMaxJinShenList2->currentIndex() > -1) {
            list.append(ui->comboBoxMaxJinShenList2->currentText());
        }
        if (ui->checkBoxMaxJinShenMap3->isChecked() && ui->comboBoxMaxJinShenList3->currentIndex() > -1) {
            list.append(ui->comboBoxMaxJinShenList3->currentText());
        }
        if (ui->checkBoxMaxJinShenMap4->isChecked() && ui->comboBoxMaxJinShenList4->currentIndex() > -1) {
            list.append(ui->comboBoxMaxJinShenList4->currentText());
        }
        if (ui->checkBoxMaxJinShenMap5->isChecked() && ui->comboBoxMaxJinShenList5->currentIndex() > -1) {
            list.append(ui->comboBoxMaxJinShenList5->currentText());
        }
        if (ui->checkBoxMaxJinShenMap6->isChecked() && ui->comboBoxMaxJinShenList6->currentIndex() > -1) {
            list.append(ui->comboBoxMaxJinShenList6->currentText());
        }
        if (ui->checkBoxMaxJinShenMap7->isChecked() && ui->comboBoxMaxJinShenList7->currentIndex() > -1) {
            list.append(ui->comboBoxMaxJinShenList7->currentText());
        }
        if (ui->checkBoxMaxJinShenMap8->isChecked() && ui->comboBoxMaxJinShenList8->currentIndex() > -1) {
            list.append(ui->comboBoxMaxJinShenList8->currentText());
        }
        pMaxWorker->setJinShenParameter(top, 3, list);

        //幽冥
        if (ui->comboBoxMaxYouMingTop1->currentIndex() == -1) {
            top[0] = 0;
        } else {
            top[0] = ui->comboBoxMaxYouMingTop1->currentText().toInt();
        }
        if (ui->comboBoxMaxYouMingTop2->currentIndex() == -1) {
            top[1] = 0;
        } else {
            top[1] = ui->comboBoxMaxYouMingTop2->currentText().toInt();
        }
        if (ui->comboBoxMaxYouMingTop3->currentIndex() == -1) {
            top[2] = 0;
        } else {
            top[2] = ui->comboBoxMaxYouMingTop3->currentText().toInt();
        }

        list.clear();
        if (ui->checkBoxMaxYouMingMap1->isChecked() && ui->comboBoxMaxYouMingList1->currentIndex() > -1) {
            list.append(ui->comboBoxMaxYouMingList1->currentText());
        }
        if (ui->checkBoxMaxYouMingMap2->isChecked() && ui->comboBoxMaxYouMingList2->currentIndex() > -1) {
            list.append(ui->comboBoxMaxYouMingList2->currentText());
        }
        if (ui->checkBoxMaxYouMingMap3->isChecked() && ui->comboBoxMaxYouMingList3->currentIndex() > -1) {
            list.append(ui->comboBoxMaxYouMingList3->currentText());
        }
        if (ui->checkBoxMaxYouMingMap4->isChecked() && ui->comboBoxMaxYouMingList4->currentIndex() > -1) {
            list.append(ui->comboBoxMaxYouMingList4->currentText());
        }
        if (ui->checkBoxMaxYouMingMap5->isChecked() && ui->comboBoxMaxYouMingList5->currentIndex() > -1) {
            list.append(ui->comboBoxMaxYouMingList5->currentText());
        }
        if (ui->checkBoxMaxYouMingMap6->isChecked() && ui->comboBoxMaxYouMingList6->currentIndex() > -1) {
            list.append(ui->comboBoxMaxYouMingList6->currentText());
        }
        if (ui->checkBoxMaxYouMingMap7->isChecked() && ui->comboBoxMaxYouMingList7->currentIndex() > -1) {
            list.append(ui->comboBoxMaxYouMingList7->currentText());
        }
        if (ui->checkBoxMaxYouMingMap8->isChecked() && ui->comboBoxMaxYouMingList8->currentIndex() > -1) {
            list.append(ui->comboBoxMaxYouMingList8->currentText());
        }
        pMaxWorker->setYouMingParameter(top, 3, list);

        //驯龙
        if (ui->comboBoxMaxXunLongTop1->currentIndex() == -1) {
            top[0] = 0;
        } else {
            top[0] = ui->comboBoxMaxXunLongTop1->currentText().toInt();
        }
        if (ui->comboBoxMaxXunLongTop2->currentIndex() == -1) {
            top[1] = 0;
        } else {
            top[1] = ui->comboBoxMaxXunLongTop2->currentText().toInt();
        }
        if (ui->comboBoxMaxXunLongTop3->currentIndex() == -1) {
            top[2] = 0;
        } else {
            top[2] = ui->comboBoxMaxXunLongTop3->currentText().toInt();
        }

        list.clear();
        if (ui->checkBoxMaxXunLongMap1->isChecked() && ui->comboBoxMaxXunLongList1->currentIndex() > -1) {
            list.append(ui->comboBoxMaxXunLongList1->currentText());
        }
        if (ui->checkBoxMaxXunLongMap2->isChecked() && ui->comboBoxMaxXunLongList2->currentIndex() > -1) {
            list.append(ui->comboBoxMaxXunLongList2->currentText());
        }
        if (ui->checkBoxMaxXunLongMap3->isChecked() && ui->comboBoxMaxXunLongList3->currentIndex() > -1) {
            list.append(ui->comboBoxMaxXunLongList3->currentText());
        }
        if (ui->checkBoxMaxXunLongMap4->isChecked() && ui->comboBoxMaxXunLongList4->currentIndex() > -1) {
            list.append(ui->comboBoxMaxXunLongList4->currentText());
        }
        if (ui->checkBoxMaxXunLongMap5->isChecked() && ui->comboBoxMaxXunLongList5->currentIndex() > -1) {
            list.append(ui->comboBoxMaxXunLongList5->currentText());
        }
        if (ui->checkBoxMaxXunLongMap6->isChecked() && ui->comboBoxMaxXunLongList6->currentIndex() > -1) {
            list.append(ui->comboBoxMaxXunLongList6->currentText());
        }
        if (ui->checkBoxMaxXunLongMap7->isChecked() && ui->comboBoxMaxXunLongList7->currentIndex() > -1) {
            list.append(ui->comboBoxMaxXunLongList7->currentText());
        }
        if (ui->checkBoxMaxXunLongMap8->isChecked() && ui->comboBoxMaxXunLongList8->currentIndex() > -1) {
            list.append(ui->comboBoxMaxXunLongList8->currentText());
        }
        pMaxWorker->setXunLongParameter(top, 3, list);

        //神魔
        if (ui->comboBoxMaxShenMoTop1->currentIndex() == -1) {
            top[0] = 0;
        } else {
            top[0] = ui->comboBoxMaxShenMoTop1->currentText().toInt();
        }
        if (ui->comboBoxMaxShenMoTop2->currentIndex() == -1) {
            top[1] = 0;
        } else {
            top[1] = ui->comboBoxMaxShenMoTop2->currentText().toInt();
        }
        if (ui->comboBoxMaxShenMoTop3->currentIndex() == -1) {
            top[2] = 0;
        } else {
            top[2] = ui->comboBoxMaxShenMoTop3->currentText().toInt();
        }

        list.clear();
        if (ui->checkBoxMaxShenMoMap1->isChecked() && ui->comboBoxMaxShenMoList1->currentIndex() > -1) {
            list.append(ui->comboBoxMaxShenMoList1->currentText());
        }
        if (ui->checkBoxMaxShenMoMap2->isChecked() && ui->comboBoxMaxShenMoList2->currentIndex() > -1) {
            list.append(ui->comboBoxMaxShenMoList2->currentText());
        }
        if (ui->checkBoxMaxShenMoMap3->isChecked() && ui->comboBoxMaxShenMoList3->currentIndex() > -1) {
            list.append(ui->comboBoxMaxShenMoList3->currentText());
        }
        if (ui->checkBoxMaxShenMoMap4->isChecked() && ui->comboBoxMaxShenMoList4->currentIndex() > -1) {
            list.append(ui->comboBoxMaxShenMoList4->currentText());
        }
        if (ui->checkBoxMaxShenMoMap5->isChecked() && ui->comboBoxMaxShenMoList5->currentIndex() > -1) {
            list.append(ui->comboBoxMaxShenMoList5->currentText());
        }
        if (ui->checkBoxMaxShenMoMap6->isChecked() && ui->comboBoxMaxShenMoList6->currentIndex() > -1) {
            list.append(ui->comboBoxMaxShenMoList6->currentText());
        }
        if (ui->checkBoxMaxShenMoMap7->isChecked() && ui->comboBoxMaxShenMoList7->currentIndex() > -1) {
            list.append(ui->comboBoxMaxShenMoList7->currentText());
        }
        if (ui->checkBoxMaxShenMoMap8->isChecked() && ui->comboBoxMaxShenMoList8->currentIndex() > -1) {
            list.append(ui->comboBoxMaxShenMoList8->currentText());
        }
        pMaxWorker->setShenMoParameter(top, 3, list);
    }
}

void MainWindow::setMinThreadParameter()
{
    int top[3] = {0};
    QStringList list;
    if (ui->checkBoxMinEnable->isEnabled() && ui->checkBoxMinEnable->isChecked()) {
        //初始化
        pMinWorker->initThread(hwndList.at(ui->comboBoxMinId->currentIndex()), pMapManager);
        //基础
        bool zhenCe = ui->checkBoxMinZhenCe->isChecked();
        bool fuHuo = ui->checkBoxMinFuHuo->isChecked();
        bool chongLian = ui->checkBoxMinChongLian->isChecked();
        bool suiJi = ui->checkBoxMinSuiJi->isChecked();
        bool zhuangBei = ui->checkBoxMinZhuangBei->isChecked();
        bool hangHuiMode = ui->checkBoxMinHangHuiMode->isChecked();
        pMinWorker->setJiChu(zhenCe, fuHuo, chongLian, suiJi, zhuangBei, hangHuiMode);

        QTime startTime = ui->timeEditMinStart->time();
        QTime endTime = ui->timeEditMinEnd->time();
        xiuMianStartMin[0] = startTime.hour();
        xiuMianStartMin[1] = startTime.minute();
        xiuMianEndMin[0] = endTime.hour();
        xiuMianEndMin[1] = endTime.minute();

        startTimeMin = xiuMianStartMin[0] * 60 + xiuMianStartMin[1];
        endTimeMin = xiuMianEndMin[0] * 60 + xiuMianEndMin[1];
        xiuMianEnable[1] = ui->checkBoxMinXiuMian->isChecked();

        //分解
        bool fenJie[4] = {false};
        if (ui->checkBoxMinFenJieDouLi->isChecked()) {
            fenJie[0] = true;
        }
        if (ui->checkBoxMinFenJieHuDun->isChecked()) {
            fenJie[1] = true;
        }
        if (ui->checkBoxMinFenJieBaGua->isChecked()) {
            fenJie[2] = true;
        }
        if (ui->checkBoxMinFenJieYouMing->isChecked()) {
            fenJie[3] = true;
        }
        pMinWorker->setFenJie(fenJie, 4);

        //等级
        if (ui->comboBoxMinDengJiTop1->currentIndex() == -1) {
            top[0] = 0;
        } else {
            top[0] = ui->comboBoxMinDengJiTop1->currentText().toInt();
        }
        if (ui->comboBoxMinDengJiTop2->currentIndex() == -1) {
            top[1] = 0;
        } else {
            top[1] = ui->comboBoxMinDengJiTop2->currentText().toInt();
        }
        if (ui->comboBoxMinDengJiTop3->currentIndex() == -1) {
            top[2] = 0;
        } else {
            top[2] = ui->comboBoxMinDengJiTop3->currentText().toInt();
        }

        if (ui->checkBoxMinDengJiMap1->isChecked() && ui->comboBoxMinDengJiList1->currentIndex() > -1) {
            list.append(ui->comboBoxMinDengJiList1->currentText());
        }
        if (ui->checkBoxMinDengJiMap2->isChecked() && ui->comboBoxMinDengJiList2->currentIndex() > -1) {
            list.append(ui->comboBoxMinDengJiList2->currentText());
        }
        if (ui->checkBoxMinDengJiMap3->isChecked() && ui->comboBoxMinDengJiList3->currentIndex() > -1) {
            list.append(ui->comboBoxMinDengJiList3->currentText());
        }
        if (ui->checkBoxMinDengJiMap4->isChecked() && ui->comboBoxMinDengJiList4->currentIndex() > -1) {
            list.append(ui->comboBoxMinDengJiList4->currentText());
        }
        if (ui->checkBoxMinDengJiMap5->isChecked() && ui->comboBoxMinDengJiList5->currentIndex() > -1) {
            list.append(ui->comboBoxMinDengJiList5->currentText());
        }
        if (ui->checkBoxMinDengJiMap6->isChecked() && ui->comboBoxMinDengJiList6->currentIndex() > -1) {
            list.append(ui->comboBoxMinDengJiList6->currentText());
        }
        if (ui->checkBoxMinDengJiMap7->isChecked() && ui->comboBoxMinDengJiList7->currentIndex() > -1) {
            list.append(ui->comboBoxMinDengJiList1->currentText());
        }
        if (ui->checkBoxMinDengJiMap8->isChecked() && ui->comboBoxMinDengJiList8->currentIndex() > -1) {
            list.append(ui->comboBoxMinDengJiList8->currentText());
        }
        pMinWorker->setDengJiParameter(top, 3, list);

        //斗笠
        if (ui->comboBoxMinDouLiTop1->currentIndex() == -1) {
            top[0] = 0;
        } else {
            top[0] = ui->comboBoxMinDouLiTop1->currentText().toInt();
        }
        if (ui->comboBoxMinDouLiTop2->currentIndex() == -1) {
            top[1] = 0;
        } else {
            top[1] = ui->comboBoxMinDouLiTop2->currentText().toInt();
        }
        if (ui->comboBoxMinDouLiTop3->currentIndex() == -1) {
            top[2] = 0;
        } else {
            top[2] = ui->comboBoxMinDouLiTop3->currentText().toInt();
        }

        list.clear();
        if (ui->checkBoxMinDouLiMap1->isChecked() && ui->comboBoxMinDouLiList1->currentIndex() > -1) {
            list.append(ui->comboBoxMinDouLiList1->currentText());
        }
        if (ui->checkBoxMinDouLiMap2->isChecked() && ui->comboBoxMinDouLiList2->currentIndex() > -1) {
            list.append(ui->comboBoxMinDouLiList2->currentText());
        }
        if (ui->checkBoxMinDouLiMap3->isChecked() && ui->comboBoxMinDouLiList3->currentIndex() > -1) {
            list.append(ui->comboBoxMinDouLiList3->currentText());
        }
        if (ui->checkBoxMinDouLiMap4->isChecked() && ui->comboBoxMinDouLiList4->currentIndex() > -1) {
            list.append(ui->comboBoxMinDouLiList4->currentText());
        }
        if (ui->checkBoxMinDouLiMap5->isChecked() && ui->comboBoxMinDouLiList5->currentIndex() > -1) {
            list.append(ui->comboBoxMinDouLiList5->currentText());
        }
        if (ui->checkBoxMinDouLiMap6->isChecked() && ui->comboBoxMinDouLiList6->currentIndex() > -1) {
            list.append(ui->comboBoxMinDouLiList6->currentText());
        }
        if (ui->checkBoxMinDouLiMap7->isChecked() && ui->comboBoxMinDouLiList7->currentIndex() > -1) {
            list.append(ui->comboBoxMinDouLiList7->currentText());
        }
        if (ui->checkBoxMinDouLiMap8->isChecked() && ui->comboBoxMinDouLiList8->currentIndex() > -1) {
            list.append(ui->comboBoxMinDouLiList8->currentText());
        }
        pMinWorker->setDouLiParameter(top, 3, list);

        //护盾
        if (ui->comboBoxMinHuDunTop1->currentIndex() == -1) {
            top[0] = 0;
        } else {
            top[0] = ui->comboBoxMinHuDunTop1->currentText().toInt();
        }
        if (ui->comboBoxMinHuDunTop2->currentIndex() == -1) {
            top[1] = 0;
        } else {
            top[1] = ui->comboBoxMinHuDunTop2->currentText().toInt();
        }
        if (ui->comboBoxMinHuDunTop3->currentIndex() == -1) {
            top[2] = 0;
        } else {
            top[2] = ui->comboBoxMinHuDunTop3->currentText().toInt();
        }

        list.clear();
        if (ui->checkBoxMinHuDunMap1->isChecked() && ui->comboBoxMinHuDunList1->currentIndex() > -1) {
            list.append(ui->comboBoxMinHuDunList1->currentText());
        }
        if (ui->checkBoxMinHuDunMap2->isChecked() && ui->comboBoxMinHuDunList2->currentIndex() > -1) {
            list.append(ui->comboBoxMinHuDunList2->currentText());
        }
        if (ui->checkBoxMinHuDunMap3->isChecked() && ui->comboBoxMinHuDunList3->currentIndex() > -1) {
            list.append(ui->comboBoxMinHuDunList3->currentText());
        }
        if (ui->checkBoxMinHuDunMap4->isChecked() && ui->comboBoxMinHuDunList4->currentIndex() > -1) {
            list.append(ui->comboBoxMinHuDunList4->currentText());
        }
        if (ui->checkBoxMinHuDunMap5->isChecked() && ui->comboBoxMinHuDunList5->currentIndex() > -1) {
            list.append(ui->comboBoxMinHuDunList5->currentText());
        }
        if (ui->checkBoxMinHuDunMap6->isChecked() && ui->comboBoxMinHuDunList6->currentIndex() > -1) {
            list.append(ui->comboBoxMinHuDunList6->currentText());
        }
        if (ui->checkBoxMinHuDunMap7->isChecked() && ui->comboBoxMinHuDunList7->currentIndex() > -1) {
            list.append(ui->comboBoxMinHuDunList7->currentText());
        }
        if (ui->checkBoxMinHuDunMap8->isChecked() && ui->comboBoxMinHuDunList8->currentIndex() > -1) {
            list.append(ui->comboBoxMinHuDunList8->currentText());
        }
        pMinWorker->setHuDunParameter(top, 3, list);

        //星座
        if (ui->comboBoxMinHuDunTop1->currentIndex() == -1) {
            top[0] = 0;
        } else {
            top[0] = ui->comboBoxMinHuDunTop1->currentText().toInt();
        }
        if (ui->comboBoxMinHuDunTop2->currentIndex() == -1) {
            top[1] = 0;
        } else {
            top[1] = ui->comboBoxMinHuDunTop2->currentText().toInt();
        }
        if (ui->comboBoxMinHuDunTop3->currentIndex() == -1) {
            top[2] = 0;
        } else {
            top[2] = ui->comboBoxMinHuDunTop3->currentText().toInt();
        }

        list.clear();
        if (ui->checkBoxMinXingZuoMap1->isChecked() && ui->comboBoxMinXingZuoList1->currentIndex() > -1) {
            list.append(ui->comboBoxMinXingZuoList1->currentText());
        }
        if (ui->checkBoxMinXingZuoMap2->isChecked() && ui->comboBoxMinXingZuoList2->currentIndex() > -1) {
            list.append(ui->comboBoxMinXingZuoList2->currentText());
        }
        if (ui->checkBoxMinXingZuoMap3->isChecked() && ui->comboBoxMinXingZuoList3->currentIndex() > -1) {
            list.append(ui->comboBoxMinXingZuoList3->currentText());
        }
        if (ui->checkBoxMinXingZuoMap4->isChecked() && ui->comboBoxMinXingZuoList4->currentIndex() > -1) {
            list.append(ui->comboBoxMinXingZuoList4->currentText());
        }
        if (ui->checkBoxMinXingZuoMap5->isChecked() && ui->comboBoxMinXingZuoList5->currentIndex() > -1) {
            list.append(ui->comboBoxMinXingZuoList5->currentText());
        }
        if (ui->checkBoxMinXingZuoMap6->isChecked() && ui->comboBoxMinXingZuoList6->currentIndex() > -1) {
            list.append(ui->comboBoxMinXingZuoList6->currentText());
        }
        if (ui->checkBoxMinXingZuoMap7->isChecked() && ui->comboBoxMinXingZuoList7->currentIndex() > -1) {
            list.append(ui->comboBoxMinXingZuoList7->currentText());
        }
        if (ui->checkBoxMinXingZuoMap8->isChecked() && ui->comboBoxMinXingZuoList8->currentIndex() > -1) {
            list.append(ui->comboBoxMinXingZuoList8->currentText());
        }
        pMinWorker->setXingZuoParameter(top, 3, list);

        //八卦
        list.clear();
        if (ui->checkBoxMinBaGuaMap1->isChecked() && ui->comboBoxMinBaGuaList1->currentIndex() > -1) {
            list.append(ui->comboBoxMinBaGuaList1->currentText());
        }
        if (ui->checkBoxMinBaGuaMap2->isChecked() && ui->comboBoxMinBaGuaList2->currentIndex() > -1) {
            list.append(ui->comboBoxMinBaGuaList2->currentText());
        }
        if (ui->checkBoxMinBaGuaMap3->isChecked() && ui->comboBoxMinBaGuaList3->currentIndex() > -1) {
            list.append(ui->comboBoxMinBaGuaList3->currentText());
        }
        if (ui->checkBoxMinBaGuaMap4->isChecked() && ui->comboBoxMinBaGuaList4->currentIndex() > -1) {
            list.append(ui->comboBoxMinBaGuaList4->currentText());
        }
        if (ui->checkBoxMinBaGuaMap5->isChecked() && ui->comboBoxMinBaGuaList5->currentIndex() > -1) {
            list.append(ui->comboBoxMinBaGuaList5->currentText());
        }
        pMinWorker->setBaGuaParameter(list);

        //金身
        if (ui->comboBoxMinJinShenTop1->currentIndex() == -1) {
            top[0] = 0;
        } else {
            top[0] = ui->comboBoxMinJinShenTop1->currentText().toInt();
        }
        if (ui->comboBoxMinJinShenTop2->currentIndex() == -1) {
            top[1] = 0;
        } else {
            top[1] = ui->comboBoxMinJinShenTop2->currentText().toInt();
        }
        if (ui->comboBoxMinJinShenTop3->currentIndex() == -1) {
            top[2] = 0;
        } else {
            top[2] = ui->comboBoxMinJinShenTop3->currentText().toInt();
        }

        list.clear();
        if (ui->checkBoxMinJinShenMap1->isChecked() && ui->comboBoxMinJinShenList1->currentIndex() > -1) {
            list.append(ui->comboBoxMinJinShenList1->currentText());
        }
        if (ui->checkBoxMinJinShenMap2->isChecked() && ui->comboBoxMinJinShenList2->currentIndex() > -1) {
            list.append(ui->comboBoxMinJinShenList2->currentText());
        }
        if (ui->checkBoxMinJinShenMap3->isChecked() && ui->comboBoxMinJinShenList3->currentIndex() > -1) {
            list.append(ui->comboBoxMinJinShenList3->currentText());
        }
        if (ui->checkBoxMinJinShenMap4->isChecked() && ui->comboBoxMinJinShenList4->currentIndex() > -1) {
            list.append(ui->comboBoxMinJinShenList4->currentText());
        }
        if (ui->checkBoxMinJinShenMap5->isChecked() && ui->comboBoxMinJinShenList5->currentIndex() > -1) {
            list.append(ui->comboBoxMinJinShenList5->currentText());
        }
        if (ui->checkBoxMinJinShenMap6->isChecked() && ui->comboBoxMinJinShenList6->currentIndex() > -1) {
            list.append(ui->comboBoxMinJinShenList6->currentText());
        }
        if (ui->checkBoxMinJinShenMap7->isChecked() && ui->comboBoxMinJinShenList7->currentIndex() > -1) {
            list.append(ui->comboBoxMinJinShenList7->currentText());
        }
        if (ui->checkBoxMinJinShenMap8->isChecked() && ui->comboBoxMinJinShenList8->currentIndex() > -1) {
            list.append(ui->comboBoxMinJinShenList8->currentText());
        }
        pMinWorker->setJinShenParameter(top, 3, list);

        //幽冥
        if (ui->comboBoxMinYouMingTop1->currentIndex() == -1) {
            top[0] = 0;
        } else {
            top[0] = ui->comboBoxMinYouMingTop1->currentText().toInt();
        }
        if (ui->comboBoxMinYouMingTop2->currentIndex() == -1) {
            top[1] = 0;
        } else {
            top[1] = ui->comboBoxMinYouMingTop2->currentText().toInt();
        }
        if (ui->comboBoxMinYouMingTop3->currentIndex() == -1) {
            top[2] = 0;
        } else {
            top[2] = ui->comboBoxMinYouMingTop3->currentText().toInt();
        }

        list.clear();
        if (ui->checkBoxMinYouMingMap1->isChecked() && ui->comboBoxMinYouMingList1->currentIndex() > -1) {
            list.append(ui->comboBoxMinYouMingList1->currentText());
        }
        if (ui->checkBoxMinYouMingMap2->isChecked() && ui->comboBoxMinYouMingList2->currentIndex() > -1) {
            list.append(ui->comboBoxMinYouMingList2->currentText());
        }
        if (ui->checkBoxMinYouMingMap3->isChecked() && ui->comboBoxMinYouMingList3->currentIndex() > -1) {
            list.append(ui->comboBoxMinYouMingList3->currentText());
        }
        if (ui->checkBoxMinYouMingMap4->isChecked() && ui->comboBoxMinYouMingList4->currentIndex() > -1) {
            list.append(ui->comboBoxMinYouMingList4->currentText());
        }
        if (ui->checkBoxMinYouMingMap5->isChecked() && ui->comboBoxMinYouMingList5->currentIndex() > -1) {
            list.append(ui->comboBoxMinYouMingList5->currentText());
        }
        if (ui->checkBoxMinYouMingMap6->isChecked() && ui->comboBoxMinYouMingList6->currentIndex() > -1) {
            list.append(ui->comboBoxMinYouMingList6->currentText());
        }
        if (ui->checkBoxMinYouMingMap7->isChecked() && ui->comboBoxMinYouMingList7->currentIndex() > -1) {
            list.append(ui->comboBoxMinYouMingList7->currentText());
        }
        if (ui->checkBoxMinYouMingMap8->isChecked() && ui->comboBoxMinYouMingList8->currentIndex() > -1) {
            list.append(ui->comboBoxMinYouMingList8->currentText());
        }
        pMinWorker->setYouMingParameter(top, 3, list);

        //驯龙
        if (ui->comboBoxMinXunLongTop1->currentIndex() == -1) {
            top[0] = 0;
        } else {
            top[0] = ui->comboBoxMinXunLongTop1->currentText().toInt();
        }
        if (ui->comboBoxMinXunLongTop2->currentIndex() == -1) {
            top[1] = 0;
        } else {
            top[1] = ui->comboBoxMinXunLongTop2->currentText().toInt();
        }
        if (ui->comboBoxMinXunLongTop3->currentIndex() == -1) {
            top[2] = 0;
        } else {
            top[2] = ui->comboBoxMinXunLongTop3->currentText().toInt();
        }

        list.clear();
        if (ui->checkBoxMinXunLongMap1->isChecked() && ui->comboBoxMinXunLongList1->currentIndex() > -1) {
            list.append(ui->comboBoxMinXunLongList1->currentText());
        }
        if (ui->checkBoxMinXunLongMap2->isChecked() && ui->comboBoxMinXunLongList2->currentIndex() > -1) {
            list.append(ui->comboBoxMinXunLongList2->currentText());
        }
        if (ui->checkBoxMinXunLongMap3->isChecked() && ui->comboBoxMinXunLongList3->currentIndex() > -1) {
            list.append(ui->comboBoxMinXunLongList3->currentText());
        }
        if (ui->checkBoxMinXunLongMap4->isChecked() && ui->comboBoxMinXunLongList4->currentIndex() > -1) {
            list.append(ui->comboBoxMinXunLongList4->currentText());
        }
        if (ui->checkBoxMinXunLongMap5->isChecked() && ui->comboBoxMinXunLongList5->currentIndex() > -1) {
            list.append(ui->comboBoxMinXunLongList5->currentText());
        }
        if (ui->checkBoxMinXunLongMap6->isChecked() && ui->comboBoxMinXunLongList6->currentIndex() > -1) {
            list.append(ui->comboBoxMinXunLongList6->currentText());
        }
        if (ui->checkBoxMinXunLongMap7->isChecked() && ui->comboBoxMinXunLongList7->currentIndex() > -1) {
            list.append(ui->comboBoxMinXunLongList7->currentText());
        }
        if (ui->checkBoxMinXunLongMap8->isChecked() && ui->comboBoxMinXunLongList8->currentIndex() > -1) {
            list.append(ui->comboBoxMinXunLongList8->currentText());
        }
        pMinWorker->setXunLongParameter(top, 3, list);

        //神魔
        if (ui->comboBoxMinShenMoTop1->currentIndex() == -1) {
            top[0] = 0;
        } else {
            top[0] = ui->comboBoxMinShenMoTop1->currentText().toInt();
        }
        if (ui->comboBoxMinShenMoTop2->currentIndex() == -1) {
            top[1] = 0;
        } else {
            top[1] = ui->comboBoxMinShenMoTop2->currentText().toInt();
        }
        if (ui->comboBoxMinShenMoTop3->currentIndex() == -1) {
            top[2] = 0;
        } else {
            top[2] = ui->comboBoxMinShenMoTop3->currentText().toInt();
        }

        list.clear();
        if (ui->checkBoxMinShenMoMap1->isChecked() && ui->comboBoxMinShenMoList1->currentIndex() > -1) {
            list.append(ui->comboBoxMinShenMoList1->currentText());
        }
        if (ui->checkBoxMinShenMoMap2->isChecked() && ui->comboBoxMinShenMoList2->currentIndex() > -1) {
            list.append(ui->comboBoxMinShenMoList2->currentText());
        }
        if (ui->checkBoxMinShenMoMap3->isChecked() && ui->comboBoxMinShenMoList3->currentIndex() > -1) {
            list.append(ui->comboBoxMinShenMoList3->currentText());
        }
        if (ui->checkBoxMinShenMoMap4->isChecked() && ui->comboBoxMinShenMoList4->currentIndex() > -1) {
            list.append(ui->comboBoxMinShenMoList4->currentText());
        }
        if (ui->checkBoxMinShenMoMap5->isChecked() && ui->comboBoxMinShenMoList5->currentIndex() > -1) {
            list.append(ui->comboBoxMinShenMoList5->currentText());
        }
        if (ui->checkBoxMinShenMoMap6->isChecked() && ui->comboBoxMinShenMoList6->currentIndex() > -1) {
            list.append(ui->comboBoxMinShenMoList6->currentText());
        }
        if (ui->checkBoxMinShenMoMap7->isChecked() && ui->comboBoxMinShenMoList7->currentIndex() > -1) {
            list.append(ui->comboBoxMinShenMoList7->currentText());
        }
        if (ui->checkBoxMinShenMoMap8->isChecked() && ui->comboBoxMinShenMoList8->currentIndex() > -1) {
            list.append(ui->comboBoxMinShenMoList8->currentText());
        }
        pMinWorker->setShenMoParameter(top, 3, list);
    }
}

void MainWindow::onTimerOut()
{
    QTime now = QTime::currentTime();
    int hour = now.hour();
    int minute = now.minute();
    int second = now.second();

    //暂停辅助避开游戏检测时间
    int result = hour * 60 + minute;
    //大号
    if (xiuMianEnable[0] && (result > startTimeMax - 1) && (result < endTimeMax)) {
        if (ui->checkBoxMaxEnable->isChecked() && maxStarted){
            //大号选中
            if (pMaxThread->isRunning()) {
                maxHuoDongStatus = -1;
                pMaxWorker->exitWorking();
                pMaxThread->quit();
                pMaxThread->wait();
                maxStarted = false;
                qDebug() << "onTimerOut: 大号开始休眠";
            }
        }
    }
    //小号
    if (xiuMianEnable[1] && (result > startTimeMin -1) && (result < endTimeMin)) {
        if (ui->checkBoxMinEnable->isChecked() && minStarted) {
            //小号选中
            if (pMinThread->isRunning()) {
                minHuoDongStatus = -1;
                pMinWorker->exitWorking();
                pMinThread->quit();
                pMinThread->wait();
                minStarted = false;
                qDebug() << "onTimerOut: 小号开始休眠";
            }
        }
    }

    //恢复辅助
    //大号
    if (xiuMianEnable[0] && result > endTimeMax) {
        if (ui->checkBoxMaxEnable->isChecked() && !maxStarted) {
            //大号选中了
            if (!pMaxThread->isRunning()) {
                setMaxThreadParameter();
                pMaxThread->start();
                ui->pushButtonStart->setEnabled(false);
                qDebug() << "onTimerOut: 大号恢复刷图";
            }
            maxStarted = true;
        }
    }
    //小号
    if (xiuMianEnable[1] && result > endTimeMin) {
        if (ui->checkBoxMinEnable->isChecked() && !minStarted) {
            //小号选中
            if (!pMinThread->isRunning()) {
                setMinThreadParameter();
                pMinThread->start();
                ui->pushButtonStart->setEnabled(false);
                qDebug() << "onTimerOut: 小号恢复刷图";
            }
            minStarted = true;
        }
    }

    //-1:停止 0:刷图    1:魔龙    2:黄金树   3:世界boss    4:行会试炼
    //魔龙    12:00-12:10   18:00-18:10
    if ((hour == 12 || hour == 18) && minute < 10 && second > 5) {
        //大号
        if (ui->checkBoxMaxMoLongBaoZang->isChecked() && IsWindow(hwndList.at(ui->comboBoxMaxId->currentIndex())) && !maxInHuoDong) {
            maxInHuoDong = true;
            if (pMaxThread->isRunning()) {
                pMaxWorker->huoDongStart(1);
                maxHuoDongStatus = 1;
            }
        }
        //小号
        if (ui->checkBoxMinMoLongBaoZang->isChecked() && IsWindow(hwndList.at(ui->comboBoxMinId->currentIndex())) && !minInHuoDong) {
            minInHuoDong = true;
            if (pMinThread->isRunning()) {
                pMinWorker->huoDongStart(1);
                minHuoDongStatus = 1;
            }
        }
    }

    //出魔龙
    if ((hour == 12 || hour == 18) && minute >= 10 && minute < 12 && second > 5) {
        //大号
        if (ui->checkBoxMaxMoLongBaoZang->isChecked() && IsWindow(hwndList.at(ui->comboBoxMaxId->currentIndex())) && maxInHuoDong) {
            maxInHuoDong = false;
            if (pMaxThread->isRunning()) {
                pMaxWorker->huoDongEnd();
                maxHuoDongStatus = 0;
            }
        }
        //小号
        if (ui->checkBoxMinMoLongBaoZang->isChecked() && IsWindow(hwndList.at(ui->comboBoxMinId->currentIndex())) && minInHuoDong) {
            minInHuoDong = false;
            if (pMinThread->isRunning()) {
                pMinWorker->huoDongEnd();
                minHuoDongStatus = 0;
            }
        }
    }

    //黄金树   15:00-15:15     21:10-21:25
    if ((hour == 15 && minute < 15 && second > 5) || (hour == 21 && minute > 10 && minute < 15 && second > 5)) {
        //大号
        if (ui->checkBoxMaxHuangJinShu->isChecked() && IsWindow(hwndList.at(ui->comboBoxMaxId->currentIndex())) && !maxInHuoDong) {
            maxInHuoDong = true;
            if (pMaxThread->isRunning()) {
                pMaxWorker->huoDongStart(2);
                maxHuoDongStatus = 2;
            }
        }
        //小号
        if (ui->checkBoxMinHuangJinShu->isChecked() && IsWindow(hwndList.at(ui->comboBoxMinId->currentIndex())) && !minInHuoDong) {
            minInHuoDong = true;
            if (pMinThread->isRunning()) {
                pMinWorker->huoDongStart(2);
                minHuoDongStatus = 2;
            }
        }
    }

    //出黄金树
    if ((hour == 15 && minute >= 15 && minute < 17 && second > 5) || (hour == 21 && minute >= 15 && minute < 17 && second > 5)) {
        //大号
        if (ui->checkBoxMaxHuangJinShu->isChecked() && IsWindow(hwndList.at(ui->comboBoxMaxId->currentIndex())) && maxInHuoDong) {
            maxInHuoDong = false;
            if (pMaxThread->isRunning()) {
                pMaxWorker->huoDongEnd();
                maxHuoDongStatus = 0;
            }
        }
        //小号
        if (ui->checkBoxMinHuangJinShu->isChecked() && IsWindow(hwndList.at(ui->comboBoxMinId->currentIndex())) && minInHuoDong) {
            minInHuoDong = false;
            if (pMinThread->isRunning()) {
                pMinWorker->huoDongEnd();
                minHuoDongStatus = 0;
            }
        }
    }

    //世界BOSS    16:00-16:10
    if (hour == 16 && minute < 10 && second > 5) {
        //大号
        if (ui->checkBoxMaxShiJieBoss->isChecked() && IsWindow(hwndList.at(ui->comboBoxMaxId->currentIndex())) && !maxInHuoDong) {
            maxInHuoDong = true;
            if (pMaxThread->isRunning()) {
                pMaxWorker->huoDongStart(3);
                maxHuoDongStatus = 3;
            }
        }
        //小号
        if (ui->checkBoxMinShiJieBoss->isChecked() && IsWindow(hwndList.at(ui->comboBoxMinId->currentIndex())) && !minInHuoDong) {
            minInHuoDong = true;
            if (pMinThread->isRunning()) {
                pMinWorker->huoDongStart(3);
                minHuoDongStatus = 3;
            }
        }
    }

    //出世界boss
    if (hour == 16 && minute >= 10 && minute < 12 && second > 5) {
        //大号
        if (ui->checkBoxMaxShiJieBoss->isChecked() && IsWindow(hwndList.at(ui->comboBoxMaxId->currentIndex())) && maxInHuoDong) {
            maxInHuoDong = false;
            if (pMaxThread->isRunning()) {
                pMaxWorker->huoDongEnd();
                maxHuoDongStatus = 0;
            }
        }
        //小号
        if (ui->checkBoxMinShiJieBoss->isChecked() && IsWindow(hwndList.at(ui->comboBoxMinId->currentIndex())) && minInHuoDong) {
            minInHuoDong = false;
            if (pMinThread->isRunning()) {
                pMinWorker->huoDongEnd();
                minHuoDongStatus = 0;
            }
        }
    }

    //行会试炼  12:30-13:00  18:30-19:00 21:30-22:00
    if ((hour == 12 && minute >= 30 && minute < 59 && second > 5) || (hour == 18 && minute >= 30 && minute < 59 && second > 5)
        || (hour == 21 && minute >= 30 && minute < 59 && second > 5)) {
        //大号
        if (ui->checkBoxMaxHangHuiShiLian->isChecked() && IsWindow(hwndList.at(ui->comboBoxMaxId->currentIndex())) && !maxInHuoDong) {
            maxInHuoDong = true;
            if (pMaxThread->isRunning()) {
                pMaxWorker->huoDongStart(4);
                maxHuoDongStatus = 4;
            }
        }
        //小号
        if (ui->checkBoxMinHangHuiShiLian->isChecked() && IsWindow(hwndList.at(ui->comboBoxMinId->currentIndex())) && !minInHuoDong) {
            minInHuoDong = true;
            if (pMinThread->isRunning()) {
                pMinWorker->huoDongStart(4);
                minHuoDongStatus = 4;
            }
        }
    }

    //出行会试炼
    if ((hour == 13 && minute < 2 && second) || (hour == 19 && minute < 2 && second < 5) || (hour == 22 && minute < 2 && second < 5)) {
        //大号
        if (ui->checkBoxMaxHangHuiShiLian->isChecked() && IsWindow(hwndList.at(ui->comboBoxMaxId->currentIndex())) && maxInHuoDong) {
            maxInHuoDong = false;
            if (pMaxThread->isRunning()) {
                pMaxWorker->huoDongEnd();
                maxHuoDongStatus = 0;
            }
        }
        //小号
        if (ui->checkBoxMinHangHuiShiLian->isChecked() && IsWindow(hwndList.at(ui->comboBoxMinId->currentIndex())) && minInHuoDong) {
            minInHuoDong = false;
            if (pMinThread->isRunning()) {
                pMinWorker->huoDongEnd();
                minHuoDongStatus = 0;
            }
        }
    }
}

void MainWindow::onBackButtonClicked()
{
    ui->pushButtonStop->setEnabled(false);
    if (pMaxThread->isRunning()) {
        maxHuoDongStatus = -1;
        pMaxWorker->exitWorking();
        pMaxThread->quit();
        pMaxThread->wait();
    }
    maxStarted = false;

    if (pMinThread->isRunning()) {
        minHuoDongStatus = -1;
        pMinWorker->exitWorking();
        pMinThread->quit();
        pMinThread->wait();
    }
    minStarted = false;

    ui->pushButtonStart->setEnabled(true);
    ui->pushButtonStop->setEnabled(true);
    if (pTimer->isActive()) {
        pTimer->stop();
    }
    this->hide();
    emit onBackPressed();
}

void MainWindow::onStartButtonClicked()
{
    if (ui->checkBoxMaxEnable->isChecked()) {
        if (!pMaxThread->isRunning()) {
            setMaxThreadParameter();
            pMaxThread->start();
            ui->pushButtonStart->setEnabled(false);
        }
        maxStarted = true;
    }
    if (ui->checkBoxMinEnable->isChecked()) {
        if (!pMinThread->isRunning()) {
            setMinThreadParameter();
            pMinThread->start();
            if (ui->pushButtonStart->isEnabled()) {
                ui->pushButtonStart->setEnabled(false);
            }
        }
        minStarted = true;
    }
    maxInHuoDong = false;
    minInHuoDong = false;
    if (!pTimer->isActive()) {
        pTimer->start();
    }
}

void MainWindow::onStopButtonClicked()
{
    ui->pushButtonStop->setEnabled(false);
    if (pMaxThread->isRunning()) {
        maxHuoDongStatus = -1;
        pMaxWorker->exitWorking();
        pMaxThread->quit();
        pMaxThread->wait();
    }
    maxStarted = false;

    if (pMinThread->isRunning()) {
        minHuoDongStatus = -1;
        pMinWorker->exitWorking();
        pMinThread->quit();
        pMinThread->wait();
    }
    maxStarted = false;

    ui->pushButtonStart->setEnabled(true);
    ui->pushButtonStop->setEnabled(true);
    if (pTimer->isActive()) {
        pTimer->stop();
    }
}

void MainWindow::onSaveButtonClicked()
{
    pSettings->beginGroup("JiChu");
    //大号
    pSettings->setValue("maxZhenCe", ui->checkBoxMaxZhenCe->isChecked());
    pSettings->setValue("maxFuHuo", ui->checkBoxMaxFuHuo->isChecked());
    pSettings->setValue("maxChongLian", ui->checkBoxMaxChongLian->isChecked());
    pSettings->setValue("maxSuiJi", ui->checkBoxMaxSuiJi->isChecked());
    pSettings->setValue("maxZhuangBei", ui->checkBoxMaxZhuangBei->isChecked());
    pSettings->setValue("maxMoLong", ui->checkBoxMaxMoLongBaoZang->isChecked());
    pSettings->setValue("maxShiJieBoss", ui->checkBoxMaxShiJieBoss->isChecked());
    pSettings->setValue("maxHuangJinShu", ui->checkBoxMaxHuangJinShu->isChecked());
    pSettings->setValue("maxHangHuiShiLian", ui->checkBoxMaxHangHuiShiLian->isChecked());
    pSettings->setValue("maxFenJieDouLi", ui->checkBoxMaxFenJieDouLi->isChecked());
    pSettings->setValue("maxFenJieHuDun", ui->checkBoxMaxFenJieDouLi->isChecked());
    pSettings->setValue("maxFenJieBaGua", ui->checkBoxMaxFenJieBaGua->isChecked());
    pSettings->setValue("maxFenJieYouMing", ui->checkBoxMaxFenJieYouMing->isChecked());
    pSettings->setValue("maxHangHuiMode", ui->checkBoxMaxHangHuiMode->isChecked());

    pSettings->setValue("maxXiuMian", ui->checkBoxMaxXiuMian->isChecked());
    pSettings->setValue("maxStartTime1", xiuMianStartMax[0]);
    pSettings->setValue("maxStartTime2", xiuMianStartMax[1]);
    pSettings->setValue("maxEndTime1", xiuMianEndMax[0]);
    pSettings->setValue("maxEndTime2", xiuMianEndMax[1]);

    //小号
    pSettings->setValue("minZhenCe", ui->checkBoxMinZhenCe->isChecked());
    pSettings->setValue("minFuHuo", ui->checkBoxMinFuHuo->isChecked());
    pSettings->setValue("minChongLian", ui->checkBoxMinChongLian->isChecked());
    pSettings->setValue("minSuiJi", ui->checkBoxMinSuiJi->isChecked());
    pSettings->setValue("minZhuangBei", ui->checkBoxMinZhuangBei->isChecked());
    pSettings->setValue("minMoLong", ui->checkBoxMinMoLongBaoZang->isChecked());
    pSettings->setValue("minShiJieBoss", ui->checkBoxMinShiJieBoss->isChecked());
    pSettings->setValue("minHuangJinShu", ui->checkBoxMinHuangJinShu->isChecked());
    pSettings->setValue("minHangHuiShiLian", ui->checkBoxMinHangHuiShiLian->isChecked());
    pSettings->setValue("minFenJieDouLi", ui->checkBoxMinFenJieDouLi->isChecked());
    pSettings->setValue("minFenJieHuDun", ui->checkBoxMinFenJieDouLi->isChecked());
    pSettings->setValue("minFenJieBaGua", ui->checkBoxMinFenJieBaGua->isChecked());
    pSettings->setValue("minFenJieYouMing", ui->checkBoxMinFenJieYouMing->isChecked());
    pSettings->setValue("minHangHuiMode", ui->checkBoxMinHangHuiMode->isChecked());

    pSettings->setValue("minXiuMian", ui->checkBoxMinXiuMian->isChecked());
    pSettings->setValue("minStartTime1", xiuMianStartMin[0]);
    pSettings->setValue("minStartTime2", xiuMianStartMin[1]);
    pSettings->setValue("minEndTime1", xiuMianEndMin[0]);
    pSettings->setValue("minEndTime2", xiuMianEndMin[1]);

    pSettings->endGroup();

    pSettings->beginGroup("DengJi");
    //大号
    pSettings->setValue("maxTop1", ui->comboBoxMaxDengJiTop1->currentIndex());
    pSettings->setValue("maxTop2", ui->comboBoxMaxDengJiTop2->currentIndex());
    pSettings->setValue("maxTop3", ui->comboBoxMaxDengJiTop3->currentIndex());
    pSettings->setValue("maxMap1", ui->checkBoxMaxDengJiMap1->isChecked());
    pSettings->setValue("maxMap2", ui->checkBoxMaxDengJiMap2->isChecked());
    pSettings->setValue("maxMap3", ui->checkBoxMaxDengJiMap3->isChecked());
    pSettings->setValue("maxMap4", ui->checkBoxMaxDengJiMap4->isChecked());
    pSettings->setValue("maxMap5", ui->checkBoxMaxDengJiMap5->isChecked());
    pSettings->setValue("maxMap6", ui->checkBoxMaxDengJiMap6->isChecked());
    pSettings->setValue("maxMap7", ui->checkBoxMaxDengJiMap7->isChecked());
    pSettings->setValue("maxMap8", ui->checkBoxMaxDengJiMap8->isChecked());
    pSettings->setValue("maxList1", ui->comboBoxMaxDengJiList1->currentIndex());
    pSettings->setValue("maxList2", ui->comboBoxMaxDengJiList2->currentIndex());
    pSettings->setValue("maxList3", ui->comboBoxMaxDengJiList3->currentIndex());
    pSettings->setValue("maxList4", ui->comboBoxMaxDengJiList4->currentIndex());
    pSettings->setValue("maxList5", ui->comboBoxMaxDengJiList5->currentIndex());
    pSettings->setValue("maxList6", ui->comboBoxMaxDengJiList6->currentIndex());
    pSettings->setValue("maxList7", ui->comboBoxMaxDengJiList7->currentIndex());
    pSettings->setValue("maxList8", ui->comboBoxMaxDengJiList8->currentIndex());
    //小号
    pSettings->setValue("minTop1", ui->comboBoxMinDengJiTop1->currentIndex());
    pSettings->setValue("minTop2", ui->comboBoxMinDengJiTop2->currentIndex());
    pSettings->setValue("minTop3", ui->comboBoxMinDengJiTop3->currentIndex());
    pSettings->setValue("minMap1", ui->checkBoxMinDengJiMap1->isChecked());
    pSettings->setValue("minMap2", ui->checkBoxMinDengJiMap2->isChecked());
    pSettings->setValue("minMap3", ui->checkBoxMinDengJiMap3->isChecked());
    pSettings->setValue("minMap4", ui->checkBoxMinDengJiMap4->isChecked());
    pSettings->setValue("minMap5", ui->checkBoxMinDengJiMap5->isChecked());
    pSettings->setValue("minMap6", ui->checkBoxMinDengJiMap6->isChecked());
    pSettings->setValue("minMap7", ui->checkBoxMinDengJiMap7->isChecked());
    pSettings->setValue("minMap8", ui->checkBoxMinDengJiMap8->isChecked());
    pSettings->setValue("minList1", ui->comboBoxMinDengJiList1->currentIndex());
    pSettings->setValue("minList2", ui->comboBoxMinDengJiList2->currentIndex());
    pSettings->setValue("minList3", ui->comboBoxMinDengJiList3->currentIndex());
    pSettings->setValue("minList4", ui->comboBoxMinDengJiList4->currentIndex());
    pSettings->setValue("minList5", ui->comboBoxMinDengJiList5->currentIndex());
    pSettings->setValue("minList6", ui->comboBoxMinDengJiList6->currentIndex());
    pSettings->setValue("minList7", ui->comboBoxMinDengJiList7->currentIndex());
    pSettings->setValue("minList8", ui->comboBoxMinDengJiList8->currentIndex());
    pSettings->endGroup();

    pSettings->beginGroup("DouLi");
    //大号
    pSettings->setValue("maxTop1", ui->comboBoxMaxDouLiTop1->currentIndex());
    pSettings->setValue("maxTop2", ui->comboBoxMaxDouLiTop2->currentIndex());
    pSettings->setValue("maxTop3", ui->comboBoxMaxDouLiTop3->currentIndex());
    pSettings->setValue("maxMap1", ui->checkBoxMaxDouLiMap1->isChecked());
    pSettings->setValue("maxMap2", ui->checkBoxMaxDouLiMap2->isChecked());
    pSettings->setValue("maxMap3", ui->checkBoxMaxDouLiMap3->isChecked());
    pSettings->setValue("maxMap4", ui->checkBoxMaxDouLiMap4->isChecked());
    pSettings->setValue("maxMap5", ui->checkBoxMaxDouLiMap5->isChecked());
    pSettings->setValue("maxMap6", ui->checkBoxMaxDouLiMap6->isChecked());
    pSettings->setValue("maxMap7", ui->checkBoxMaxDouLiMap7->isChecked());
    pSettings->setValue("maxMap8", ui->checkBoxMaxDouLiMap8->isChecked());
    pSettings->setValue("maxList1", ui->comboBoxMaxDouLiList1->currentIndex());
    pSettings->setValue("maxList2", ui->comboBoxMaxDouLiList2->currentIndex());
    pSettings->setValue("maxList3", ui->comboBoxMaxDouLiList3->currentIndex());
    pSettings->setValue("maxList4", ui->comboBoxMaxDouLiList4->currentIndex());
    pSettings->setValue("maxList5", ui->comboBoxMaxDouLiList5->currentIndex());
    pSettings->setValue("maxList6", ui->comboBoxMaxDouLiList6->currentIndex());
    pSettings->setValue("maxList7", ui->comboBoxMaxDouLiList7->currentIndex());
    pSettings->setValue("maxList8", ui->comboBoxMaxDouLiList8->currentIndex());
    //小号
    pSettings->setValue("minTop1", ui->comboBoxMinDouLiTop1->currentIndex());
    pSettings->setValue("minTop2", ui->comboBoxMinDouLiTop2->currentIndex());
    pSettings->setValue("minTop3", ui->comboBoxMinDouLiTop3->currentIndex());
    pSettings->setValue("minMap1", ui->checkBoxMinDouLiMap1->isChecked());
    pSettings->setValue("minMap2", ui->checkBoxMinDouLiMap2->isChecked());
    pSettings->setValue("minMap3", ui->checkBoxMinDouLiMap3->isChecked());
    pSettings->setValue("minMap4", ui->checkBoxMinDouLiMap4->isChecked());
    pSettings->setValue("minMap5", ui->checkBoxMinDouLiMap5->isChecked());
    pSettings->setValue("minMap6", ui->checkBoxMinDouLiMap6->isChecked());
    pSettings->setValue("minMap7", ui->checkBoxMinDouLiMap7->isChecked());
    pSettings->setValue("minMap8", ui->checkBoxMinDouLiMap8->isChecked());
    pSettings->setValue("minList1", ui->comboBoxMinDouLiList1->currentIndex());
    pSettings->setValue("minList2", ui->comboBoxMinDouLiList2->currentIndex());
    pSettings->setValue("minList3", ui->comboBoxMinDouLiList3->currentIndex());
    pSettings->setValue("minList4", ui->comboBoxMinDouLiList4->currentIndex());
    pSettings->setValue("minList5", ui->comboBoxMinDouLiList5->currentIndex());
    pSettings->setValue("minList6", ui->comboBoxMinDouLiList6->currentIndex());
    pSettings->setValue("minList7", ui->comboBoxMinDouLiList7->currentIndex());
    pSettings->setValue("minList8", ui->comboBoxMinDouLiList8->currentIndex());
    pSettings->endGroup();

    pSettings->beginGroup("HuDun");
    //大号
    pSettings->setValue("maxTop1", ui->comboBoxMaxHuDunTop1->currentIndex());
    pSettings->setValue("maxTop2", ui->comboBoxMaxHuDunTop2->currentIndex());
    pSettings->setValue("maxTop3", ui->comboBoxMaxHuDunTop3->currentIndex());
    pSettings->setValue("maxMap1", ui->checkBoxMaxHuDunMap1->isChecked());
    pSettings->setValue("maxMap2", ui->checkBoxMaxHuDunMap2->isChecked());
    pSettings->setValue("maxMap3", ui->checkBoxMaxHuDunMap3->isChecked());
    pSettings->setValue("maxMap4", ui->checkBoxMaxHuDunMap4->isChecked());
    pSettings->setValue("maxMap5", ui->checkBoxMaxHuDunMap5->isChecked());
    pSettings->setValue("maxMap6", ui->checkBoxMaxHuDunMap6->isChecked());
    pSettings->setValue("maxMap7", ui->checkBoxMaxHuDunMap7->isChecked());
    pSettings->setValue("maxMap8", ui->checkBoxMaxHuDunMap8->isChecked());
    pSettings->setValue("maxList1", ui->comboBoxMaxHuDunList1->currentIndex());
    pSettings->setValue("maxList2", ui->comboBoxMaxHuDunList2->currentIndex());
    pSettings->setValue("maxList3", ui->comboBoxMaxHuDunList3->currentIndex());
    pSettings->setValue("maxList4", ui->comboBoxMaxHuDunList4->currentIndex());
    pSettings->setValue("maxList5", ui->comboBoxMaxHuDunList5->currentIndex());
    pSettings->setValue("maxList6", ui->comboBoxMaxHuDunList6->currentIndex());
    pSettings->setValue("maxList7", ui->comboBoxMaxHuDunList7->currentIndex());
    pSettings->setValue("maxList8", ui->comboBoxMaxHuDunList8->currentIndex());
    //小号
    pSettings->setValue("minTop1", ui->comboBoxMinHuDunTop1->currentIndex());
    pSettings->setValue("minTop2", ui->comboBoxMinHuDunTop2->currentIndex());
    pSettings->setValue("minTop3", ui->comboBoxMinHuDunTop3->currentIndex());
    pSettings->setValue("minMap1", ui->checkBoxMinHuDunMap1->isChecked());
    pSettings->setValue("minMap2", ui->checkBoxMinHuDunMap2->isChecked());
    pSettings->setValue("minMap3", ui->checkBoxMinHuDunMap3->isChecked());
    pSettings->setValue("minMap4", ui->checkBoxMinHuDunMap4->isChecked());
    pSettings->setValue("minMap5", ui->checkBoxMinHuDunMap5->isChecked());
    pSettings->setValue("minMap6", ui->checkBoxMinHuDunMap6->isChecked());
    pSettings->setValue("minMap7", ui->checkBoxMinHuDunMap7->isChecked());
    pSettings->setValue("minMap8", ui->checkBoxMinHuDunMap8->isChecked());
    pSettings->setValue("minList1", ui->comboBoxMinHuDunList1->currentIndex());
    pSettings->setValue("minList2", ui->comboBoxMinHuDunList2->currentIndex());
    pSettings->setValue("minList3", ui->comboBoxMinHuDunList3->currentIndex());
    pSettings->setValue("minList4", ui->comboBoxMinHuDunList4->currentIndex());
    pSettings->setValue("minList5", ui->comboBoxMinHuDunList5->currentIndex());
    pSettings->setValue("minList6", ui->comboBoxMinHuDunList6->currentIndex());
    pSettings->setValue("minList7", ui->comboBoxMinHuDunList7->currentIndex());
    pSettings->setValue("minList8", ui->comboBoxMinHuDunList8->currentIndex());
    pSettings->endGroup();

    pSettings->beginGroup("XingZuo");
    //大号
    pSettings->setValue("maxTop1", ui->comboBoxMaxXingZuoTop1->currentIndex());
    pSettings->setValue("maxTop2", ui->comboBoxMaxXingZuoTop2->currentIndex());
    pSettings->setValue("maxTop3", ui->comboBoxMaxXingZuoTop3->currentIndex());
    pSettings->setValue("maxMap1", ui->checkBoxMaxXingZuoMap1->isChecked());
    pSettings->setValue("maxMap2", ui->checkBoxMaxXingZuoMap2->isChecked());
    pSettings->setValue("maxMap3", ui->checkBoxMaxXingZuoMap3->isChecked());
    pSettings->setValue("maxMap4", ui->checkBoxMaxXingZuoMap4->isChecked());
    pSettings->setValue("maxMap5", ui->checkBoxMaxXingZuoMap5->isChecked());
    pSettings->setValue("maxMap6", ui->checkBoxMaxXingZuoMap6->isChecked());
    pSettings->setValue("maxMap7", ui->checkBoxMaxXingZuoMap7->isChecked());
    pSettings->setValue("maxMap8", ui->checkBoxMaxXingZuoMap8->isChecked());
    pSettings->setValue("maxList1", ui->comboBoxMaxXingZuoList1->currentIndex());
    pSettings->setValue("maxList2", ui->comboBoxMaxXingZuoList2->currentIndex());
    pSettings->setValue("maxList3", ui->comboBoxMaxXingZuoList3->currentIndex());
    pSettings->setValue("maxList4", ui->comboBoxMaxXingZuoList4->currentIndex());
    pSettings->setValue("maxList5", ui->comboBoxMaxXingZuoList5->currentIndex());
    pSettings->setValue("maxList6", ui->comboBoxMaxXingZuoList6->currentIndex());
    pSettings->setValue("maxList7", ui->comboBoxMaxXingZuoList7->currentIndex());
    pSettings->setValue("maxList8", ui->comboBoxMaxXingZuoList8->currentIndex());
    //小号
    pSettings->setValue("minTop1", ui->comboBoxMinXingZuoTop1->currentIndex());
    pSettings->setValue("minTop2", ui->comboBoxMinXingZuoTop2->currentIndex());
    pSettings->setValue("minTop3", ui->comboBoxMinXingZuoTop3->currentIndex());
    pSettings->setValue("minMap1", ui->checkBoxMinXingZuoMap1->isChecked());
    pSettings->setValue("minMap2", ui->checkBoxMinXingZuoMap2->isChecked());
    pSettings->setValue("minMap3", ui->checkBoxMinXingZuoMap3->isChecked());
    pSettings->setValue("minMap4", ui->checkBoxMinXingZuoMap4->isChecked());
    pSettings->setValue("minMap5", ui->checkBoxMinXingZuoMap5->isChecked());
    pSettings->setValue("minMap6", ui->checkBoxMinXingZuoMap6->isChecked());
    pSettings->setValue("minMap7", ui->checkBoxMinXingZuoMap7->isChecked());
    pSettings->setValue("minMap8", ui->checkBoxMinXingZuoMap8->isChecked());
    pSettings->setValue("minList1", ui->comboBoxMinXingZuoList1->currentIndex());
    pSettings->setValue("minList2", ui->comboBoxMinXingZuoList2->currentIndex());
    pSettings->setValue("minList3", ui->comboBoxMinXingZuoList3->currentIndex());
    pSettings->setValue("minList4", ui->comboBoxMinXingZuoList4->currentIndex());
    pSettings->setValue("minList5", ui->comboBoxMinXingZuoList5->currentIndex());
    pSettings->setValue("minList6", ui->comboBoxMinXingZuoList6->currentIndex());
    pSettings->setValue("minList7", ui->comboBoxMinXingZuoList7->currentIndex());
    pSettings->setValue("minList8", ui->comboBoxMinXingZuoList8->currentIndex());
    pSettings->endGroup();

    pSettings->beginGroup("JinShen");
    //大号
    pSettings->setValue("maxTop1", ui->comboBoxMaxJinShenTop1->currentIndex());
    pSettings->setValue("maxTop2", ui->comboBoxMaxJinShenTop2->currentIndex());
    pSettings->setValue("maxTop3", ui->comboBoxMaxJinShenTop3->currentIndex());
    pSettings->setValue("maxMap1", ui->checkBoxMaxJinShenMap1->isChecked());
    pSettings->setValue("maxMap2", ui->checkBoxMaxJinShenMap2->isChecked());
    pSettings->setValue("maxMap3", ui->checkBoxMaxJinShenMap3->isChecked());
    pSettings->setValue("maxMap4", ui->checkBoxMaxJinShenMap4->isChecked());
    pSettings->setValue("maxMap5", ui->checkBoxMaxJinShenMap5->isChecked());
    pSettings->setValue("maxMap6", ui->checkBoxMaxJinShenMap6->isChecked());
    pSettings->setValue("maxMap7", ui->checkBoxMaxJinShenMap7->isChecked());
    pSettings->setValue("maxMap8", ui->checkBoxMaxJinShenMap8->isChecked());
    pSettings->setValue("maxList1", ui->comboBoxMaxJinShenList1->currentIndex());
    pSettings->setValue("maxList2", ui->comboBoxMaxJinShenList2->currentIndex());
    pSettings->setValue("maxList3", ui->comboBoxMaxJinShenList3->currentIndex());
    pSettings->setValue("maxList4", ui->comboBoxMaxJinShenList4->currentIndex());
    pSettings->setValue("maxList5", ui->comboBoxMaxJinShenList5->currentIndex());
    pSettings->setValue("maxList6", ui->comboBoxMaxJinShenList6->currentIndex());
    pSettings->setValue("maxList7", ui->comboBoxMaxJinShenList7->currentIndex());
    pSettings->setValue("maxList8", ui->comboBoxMaxJinShenList8->currentIndex());
    //小号
    pSettings->setValue("minTop1", ui->comboBoxMinJinShenTop1->currentIndex());
    pSettings->setValue("minTop2", ui->comboBoxMinJinShenTop2->currentIndex());
    pSettings->setValue("minTop3", ui->comboBoxMinJinShenTop3->currentIndex());
    pSettings->setValue("minMap1", ui->checkBoxMinJinShenMap1->isChecked());
    pSettings->setValue("minMap2", ui->checkBoxMinJinShenMap2->isChecked());
    pSettings->setValue("minMap3", ui->checkBoxMinJinShenMap3->isChecked());
    pSettings->setValue("minMap4", ui->checkBoxMinJinShenMap4->isChecked());
    pSettings->setValue("minMap5", ui->checkBoxMinJinShenMap5->isChecked());
    pSettings->setValue("minMap6", ui->checkBoxMinJinShenMap6->isChecked());
    pSettings->setValue("minMap7", ui->checkBoxMinJinShenMap7->isChecked());
    pSettings->setValue("minMap8", ui->checkBoxMinJinShenMap8->isChecked());
    pSettings->setValue("minList1", ui->comboBoxMinJinShenList1->currentIndex());
    pSettings->setValue("minList2", ui->comboBoxMinJinShenList2->currentIndex());
    pSettings->setValue("minList3", ui->comboBoxMinJinShenList3->currentIndex());
    pSettings->setValue("minList4", ui->comboBoxMinJinShenList4->currentIndex());
    pSettings->setValue("minList5", ui->comboBoxMinJinShenList5->currentIndex());
    pSettings->setValue("minList6", ui->comboBoxMinJinShenList6->currentIndex());
    pSettings->setValue("minList7", ui->comboBoxMinJinShenList7->currentIndex());
    pSettings->setValue("minList8", ui->comboBoxMinJinShenList8->currentIndex());
    pSettings->endGroup();

    pSettings->beginGroup("BaGua");
    //大号
    pSettings->setValue("maxMap1", ui->checkBoxMaxBaGuaMap1->isChecked());
    pSettings->setValue("maxMap2", ui->checkBoxMaxBaGuaMap2->isChecked());
    pSettings->setValue("maxMap3", ui->checkBoxMaxBaGuaMap3->isChecked());
    pSettings->setValue("maxMap4", ui->checkBoxMaxBaGuaMap4->isChecked());
    pSettings->setValue("maxMap5", ui->checkBoxMaxBaGuaMap5->isChecked());
    pSettings->setValue("maxList1", ui->comboBoxMaxBaGuaList1->currentIndex());
    pSettings->setValue("maxList2", ui->comboBoxMaxBaGuaList2->currentIndex());
    pSettings->setValue("maxList3", ui->comboBoxMaxBaGuaList3->currentIndex());
    pSettings->setValue("maxList4", ui->comboBoxMaxBaGuaList4->currentIndex());
    pSettings->setValue("maxList5", ui->comboBoxMaxBaGuaList5->currentIndex());
    //小号
    pSettings->setValue("minMap1", ui->checkBoxMinBaGuaMap1->isChecked());
    pSettings->setValue("minMap2", ui->checkBoxMinBaGuaMap2->isChecked());
    pSettings->setValue("minMap3", ui->checkBoxMinBaGuaMap3->isChecked());
    pSettings->setValue("minMap4", ui->checkBoxMinBaGuaMap4->isChecked());
    pSettings->setValue("minMap5", ui->checkBoxMinBaGuaMap5->isChecked());
    pSettings->setValue("minList1", ui->comboBoxMinBaGuaList1->currentIndex());
    pSettings->setValue("minList2", ui->comboBoxMinBaGuaList2->currentIndex());
    pSettings->setValue("minList3", ui->comboBoxMinBaGuaList3->currentIndex());
    pSettings->setValue("minList4", ui->comboBoxMinBaGuaList4->currentIndex());
    pSettings->setValue("minList5", ui->comboBoxMinBaGuaList5->currentIndex());
    pSettings->endGroup();

    pSettings->beginGroup("YouMing");
    //大号
    pSettings->setValue("maxTop1", ui->comboBoxMaxYouMingTop1->currentIndex());
    pSettings->setValue("maxTop2", ui->comboBoxMaxYouMingTop2->currentIndex());
    pSettings->setValue("maxTop3", ui->comboBoxMaxYouMingTop3->currentIndex());
    pSettings->setValue("maxMap1", ui->checkBoxMaxYouMingMap1->isChecked());
    pSettings->setValue("maxMap2", ui->checkBoxMaxYouMingMap2->isChecked());
    pSettings->setValue("maxMap3", ui->checkBoxMaxYouMingMap3->isChecked());
    pSettings->setValue("maxMap4", ui->checkBoxMaxYouMingMap4->isChecked());
    pSettings->setValue("maxMap5", ui->checkBoxMaxYouMingMap5->isChecked());
    pSettings->setValue("maxMap6", ui->checkBoxMaxYouMingMap6->isChecked());
    pSettings->setValue("maxMap7", ui->checkBoxMaxYouMingMap7->isChecked());
    pSettings->setValue("maxMap8", ui->checkBoxMaxYouMingMap8->isChecked());
    pSettings->setValue("maxList1", ui->comboBoxMaxYouMingList1->currentIndex());
    pSettings->setValue("maxList2", ui->comboBoxMaxYouMingList2->currentIndex());
    pSettings->setValue("maxList3", ui->comboBoxMaxYouMingList3->currentIndex());
    pSettings->setValue("maxList4", ui->comboBoxMaxYouMingList4->currentIndex());
    pSettings->setValue("maxList5", ui->comboBoxMaxYouMingList5->currentIndex());
    pSettings->setValue("maxList6", ui->comboBoxMaxYouMingList6->currentIndex());
    pSettings->setValue("maxList7", ui->comboBoxMaxYouMingList7->currentIndex());
    pSettings->setValue("maxList8", ui->comboBoxMaxYouMingList8->currentIndex());
    //小号
    pSettings->setValue("minTop1", ui->comboBoxMinYouMingTop1->currentIndex());
    pSettings->setValue("minTop2", ui->comboBoxMinYouMingTop2->currentIndex());
    pSettings->setValue("minTop3", ui->comboBoxMinYouMingTop3->currentIndex());
    pSettings->setValue("minMap1", ui->checkBoxMinYouMingMap1->isChecked());
    pSettings->setValue("minMap2", ui->checkBoxMinYouMingMap2->isChecked());
    pSettings->setValue("minMap3", ui->checkBoxMinYouMingMap3->isChecked());
    pSettings->setValue("minMap4", ui->checkBoxMinYouMingMap4->isChecked());
    pSettings->setValue("minMap5", ui->checkBoxMinYouMingMap5->isChecked());
    pSettings->setValue("minMap6", ui->checkBoxMinYouMingMap6->isChecked());
    pSettings->setValue("minMap7", ui->checkBoxMinYouMingMap7->isChecked());
    pSettings->setValue("minMap8", ui->checkBoxMinYouMingMap8->isChecked());
    pSettings->setValue("minList1", ui->comboBoxMinYouMingList1->currentIndex());
    pSettings->setValue("minList2", ui->comboBoxMinYouMingList2->currentIndex());
    pSettings->setValue("minList3", ui->comboBoxMinYouMingList3->currentIndex());
    pSettings->setValue("minList4", ui->comboBoxMinYouMingList4->currentIndex());
    pSettings->setValue("minList5", ui->comboBoxMinYouMingList5->currentIndex());
    pSettings->setValue("minList6", ui->comboBoxMinYouMingList6->currentIndex());
    pSettings->setValue("minList7", ui->comboBoxMinYouMingList7->currentIndex());
    pSettings->setValue("minList8", ui->comboBoxMinYouMingList8->currentIndex());
    pSettings->endGroup();

    pSettings->beginGroup("XunLong");
    //大号
    pSettings->setValue("maxTop1", ui->comboBoxMaxXunLongTop1->currentIndex());
    pSettings->setValue("maxTop2", ui->comboBoxMaxXunLongTop2->currentIndex());
    pSettings->setValue("maxTop3", ui->comboBoxMaxXunLongTop3->currentIndex());
    pSettings->setValue("maxMap1", ui->checkBoxMaxXunLongMap1->isChecked());
    pSettings->setValue("maxMap2", ui->checkBoxMaxXunLongMap2->isChecked());
    pSettings->setValue("maxMap3", ui->checkBoxMaxXunLongMap3->isChecked());
    pSettings->setValue("maxMap4", ui->checkBoxMaxXunLongMap4->isChecked());
    pSettings->setValue("maxMap5", ui->checkBoxMaxXunLongMap5->isChecked());
    pSettings->setValue("maxMap6", ui->checkBoxMaxXunLongMap6->isChecked());
    pSettings->setValue("maxMap7", ui->checkBoxMaxXunLongMap7->isChecked());
    pSettings->setValue("maxMap8", ui->checkBoxMaxXunLongMap8->isChecked());
    pSettings->setValue("maxList1", ui->comboBoxMaxXunLongList1->currentIndex());
    pSettings->setValue("maxList2", ui->comboBoxMaxXunLongList2->currentIndex());
    pSettings->setValue("maxList3", ui->comboBoxMaxXunLongList3->currentIndex());
    pSettings->setValue("maxList4", ui->comboBoxMaxXunLongList4->currentIndex());
    pSettings->setValue("maxList5", ui->comboBoxMaxXunLongList5->currentIndex());
    pSettings->setValue("maxList6", ui->comboBoxMaxXunLongList6->currentIndex());
    pSettings->setValue("maxList7", ui->comboBoxMaxXunLongList7->currentIndex());
    pSettings->setValue("maxList8", ui->comboBoxMaxXunLongList8->currentIndex());
    //小号
    pSettings->setValue("minTop1", ui->comboBoxMinXunLongTop1->currentIndex());
    pSettings->setValue("minTop2", ui->comboBoxMinXunLongTop2->currentIndex());
    pSettings->setValue("minTop3", ui->comboBoxMinXunLongTop3->currentIndex());
    pSettings->setValue("minMap1", ui->checkBoxMinXunLongMap1->isChecked());
    pSettings->setValue("minMap2", ui->checkBoxMinXunLongMap2->isChecked());
    pSettings->setValue("minMap3", ui->checkBoxMinXunLongMap3->isChecked());
    pSettings->setValue("minMap4", ui->checkBoxMinXunLongMap4->isChecked());
    pSettings->setValue("minMap5", ui->checkBoxMinXunLongMap5->isChecked());
    pSettings->setValue("minMap6", ui->checkBoxMinXunLongMap6->isChecked());
    pSettings->setValue("minMap7", ui->checkBoxMinXunLongMap7->isChecked());
    pSettings->setValue("minMap8", ui->checkBoxMinXunLongMap8->isChecked());
    pSettings->setValue("minList1", ui->comboBoxMinXunLongList1->currentIndex());
    pSettings->setValue("minList2", ui->comboBoxMinXunLongList2->currentIndex());
    pSettings->setValue("minList3", ui->comboBoxMinXunLongList3->currentIndex());
    pSettings->setValue("minList4", ui->comboBoxMinXunLongList4->currentIndex());
    pSettings->setValue("minList5", ui->comboBoxMinXunLongList5->currentIndex());
    pSettings->setValue("minList6", ui->comboBoxMinXunLongList6->currentIndex());
    pSettings->setValue("minList7", ui->comboBoxMinXunLongList7->currentIndex());
    pSettings->setValue("minList8", ui->comboBoxMinXunLongList8->currentIndex());
    pSettings->endGroup();

    pSettings->beginGroup("ShenMo");
    //大号
    pSettings->setValue("maxTop1", ui->comboBoxMaxShenMoTop1->currentIndex());
    pSettings->setValue("maxTop2", ui->comboBoxMaxShenMoTop2->currentIndex());
    pSettings->setValue("maxTop3", ui->comboBoxMaxShenMoTop3->currentIndex());
    pSettings->setValue("maxMap1", ui->checkBoxMaxShenMoMap1->isChecked());
    pSettings->setValue("maxMap2", ui->checkBoxMaxShenMoMap2->isChecked());
    pSettings->setValue("maxMap3", ui->checkBoxMaxShenMoMap3->isChecked());
    pSettings->setValue("maxMap4", ui->checkBoxMaxShenMoMap4->isChecked());
    pSettings->setValue("maxMap5", ui->checkBoxMaxShenMoMap5->isChecked());
    pSettings->setValue("maxMap6", ui->checkBoxMaxShenMoMap6->isChecked());
    pSettings->setValue("maxMap7", ui->checkBoxMaxShenMoMap7->isChecked());
    pSettings->setValue("maxMap8", ui->checkBoxMaxShenMoMap8->isChecked());
    pSettings->setValue("maxList1", ui->comboBoxMaxShenMoList1->currentIndex());
    pSettings->setValue("maxList2", ui->comboBoxMaxShenMoList2->currentIndex());
    pSettings->setValue("maxList3", ui->comboBoxMaxShenMoList3->currentIndex());
    pSettings->setValue("maxList4", ui->comboBoxMaxShenMoList4->currentIndex());
    pSettings->setValue("maxList5", ui->comboBoxMaxShenMoList5->currentIndex());
    pSettings->setValue("maxList6", ui->comboBoxMaxShenMoList6->currentIndex());
    pSettings->setValue("maxList7", ui->comboBoxMaxShenMoList7->currentIndex());
    pSettings->setValue("maxList8", ui->comboBoxMaxShenMoList8->currentIndex());
    //小号
    pSettings->setValue("minTop1", ui->comboBoxMinShenMoTop1->currentIndex());
    pSettings->setValue("minTop2", ui->comboBoxMinShenMoTop2->currentIndex());
    pSettings->setValue("minTop3", ui->comboBoxMinShenMoTop3->currentIndex());
    pSettings->setValue("minMap1", ui->checkBoxMinShenMoMap1->isChecked());
    pSettings->setValue("minMap2", ui->checkBoxMinShenMoMap2->isChecked());
    pSettings->setValue("minMap3", ui->checkBoxMinShenMoMap3->isChecked());
    pSettings->setValue("minMap4", ui->checkBoxMinShenMoMap4->isChecked());
    pSettings->setValue("minMap5", ui->checkBoxMinShenMoMap5->isChecked());
    pSettings->setValue("minMap6", ui->checkBoxMinShenMoMap6->isChecked());
    pSettings->setValue("minMap7", ui->checkBoxMinShenMoMap7->isChecked());
    pSettings->setValue("minMap8", ui->checkBoxMinShenMoMap8->isChecked());
    pSettings->setValue("minList1", ui->comboBoxMinShenMoList1->currentIndex());
    pSettings->setValue("minList2", ui->comboBoxMinShenMoList2->currentIndex());
    pSettings->setValue("minList3", ui->comboBoxMinShenMoList3->currentIndex());
    pSettings->setValue("minList4", ui->comboBoxMinShenMoList4->currentIndex());
    pSettings->setValue("minList5", ui->comboBoxMinShenMoList5->currentIndex());
    pSettings->setValue("minList6", ui->comboBoxMinShenMoList6->currentIndex());
    pSettings->setValue("minList7", ui->comboBoxMinShenMoList7->currentIndex());
    pSettings->setValue("minList8", ui->comboBoxMinShenMoList8->currentIndex());
    pSettings->endGroup();
    pSettings->sync();
}

void MainWindow::onCleanButtonClicked()
{
    pSettings->clear();
    pSettings->sync();

    initJiChuPage();
    initDengJiPage();
    initDouLiPage();
    initHuDunPage();
    initXingZuoPage();
    initJinShenPage();
    initBaGuaPage();
    initYouMingPage();
    initXunLongPage();
    initShenMoPage();

    //大号
    //基础
    ui->checkBoxMaxZhenCe->setChecked(false);
    ui->checkBoxMaxFuHuo->setChecked(false);
    ui->checkBoxMaxChongLian->setChecked(false);
    ui->checkBoxMaxSuiJi->setChecked(false);
    ui->checkBoxMaxZhuangBei->setChecked(false);
    ui->checkBoxMaxHangHuiMode->setChecked(false);

    ui->checkBoxMaxMoLongBaoZang->setChecked(false);
    ui->checkBoxMaxShiJieBoss->setChecked(false);
    ui->checkBoxMaxHuangJinShu->setChecked(false);
    ui->checkBoxMaxHangHuiShiLian->setChecked(false);

    ui->checkBoxMaxFenJieDouLi->setChecked(false);
    ui->checkBoxMaxFenJieHuDun->setChecked(false);
    ui->checkBoxMaxFenJieBaGua->setChecked(false);
    ui->checkBoxMaxFenJieYouMing->setChecked(false);
    //等级
    ui->checkBoxMaxDengJiMap1->setChecked(false);
    ui->checkBoxMaxDengJiMap2->setChecked(false);
    ui->checkBoxMaxDengJiMap3->setChecked(false);
    ui->checkBoxMaxDengJiMap4->setChecked(false);
    ui->checkBoxMaxDengJiMap5->setChecked(false);
    ui->checkBoxMaxDengJiMap6->setChecked(false);
    ui->checkBoxMaxDengJiMap7->setChecked(false);
    ui->checkBoxMaxDengJiMap8->setChecked(false);
    //斗笠
    ui->checkBoxMaxDouLiMap1->setChecked(false);
    ui->checkBoxMaxDouLiMap2->setChecked(false);
    ui->checkBoxMaxDouLiMap3->setChecked(false);
    ui->checkBoxMaxDouLiMap4->setChecked(false);
    ui->checkBoxMaxDouLiMap5->setChecked(false);
    ui->checkBoxMaxDouLiMap6->setChecked(false);
    ui->checkBoxMaxDouLiMap7->setChecked(false);
    ui->checkBoxMaxDouLiMap8->setChecked(false);
    //护盾
    ui->checkBoxMaxHuDunMap1->setChecked(false);
    ui->checkBoxMaxHuDunMap2->setChecked(false);
    ui->checkBoxMaxHuDunMap3->setChecked(false);
    ui->checkBoxMaxHuDunMap4->setChecked(false);
    ui->checkBoxMaxHuDunMap5->setChecked(false);
    ui->checkBoxMaxHuDunMap6->setChecked(false);
    ui->checkBoxMaxHuDunMap7->setChecked(false);
    ui->checkBoxMaxHuDunMap8->setChecked(false);
    //星座
    ui->checkBoxMaxXingZuoMap1->setChecked(false);
    ui->checkBoxMaxXingZuoMap2->setChecked(false);
    ui->checkBoxMaxXingZuoMap3->setChecked(false);
    ui->checkBoxMaxXingZuoMap4->setChecked(false);
    ui->checkBoxMaxXingZuoMap5->setChecked(false);
    ui->checkBoxMaxXingZuoMap6->setChecked(false);
    ui->checkBoxMaxXingZuoMap7->setChecked(false);
    ui->checkBoxMaxXingZuoMap8->setChecked(false);
    //八卦
    ui->checkBoxMaxBaGuaMap1->setChecked(false);
    ui->checkBoxMaxBaGuaMap2->setChecked(false);
    ui->checkBoxMaxBaGuaMap3->setChecked(false);
    ui->checkBoxMaxBaGuaMap4->setChecked(false);
    ui->checkBoxMaxBaGuaMap5->setChecked(false);

    if (mType == TYPE_ZHI_ZUN) {
        //大号
        //金身
        ui->checkBoxMaxJinShenMap1->setChecked(false);
        ui->checkBoxMaxJinShenMap2->setChecked(false);
        ui->checkBoxMaxJinShenMap3->setChecked(false);
        ui->checkBoxMaxJinShenMap4->setChecked(false);
        ui->checkBoxMaxJinShenMap5->setChecked(false);
        ui->checkBoxMaxJinShenMap6->setChecked(false);
        ui->checkBoxMaxJinShenMap7->setChecked(false);
        ui->checkBoxMaxJinShenMap8->setChecked(false);
        //幽冥
        ui->checkBoxMaxYouMingMap1->setChecked(false);
        ui->checkBoxMaxYouMingMap2->setChecked(false);
        ui->checkBoxMaxYouMingMap3->setChecked(false);
        ui->checkBoxMaxYouMingMap4->setChecked(false);
        ui->checkBoxMaxYouMingMap5->setChecked(false);
        ui->checkBoxMaxYouMingMap6->setChecked(false);
        ui->checkBoxMaxYouMingMap7->setChecked(false);
        ui->checkBoxMaxYouMingMap8->setChecked(false);
        //驯龙
        ui->checkBoxMaxXunLongMap1->setChecked(false);
        ui->checkBoxMaxXunLongMap2->setChecked(false);
        ui->checkBoxMaxXunLongMap3->setChecked(false);
        ui->checkBoxMaxXunLongMap4->setChecked(false);
        ui->checkBoxMaxXunLongMap5->setChecked(false);
        ui->checkBoxMaxXunLongMap6->setChecked(false);
        ui->checkBoxMaxXunLongMap7->setChecked(false);
        ui->checkBoxMaxXunLongMap8->setChecked(false);
        //神魔
        ui->checkBoxMaxShenMoMap1->setChecked(false);
        ui->checkBoxMaxShenMoMap2->setChecked(false);
        ui->checkBoxMaxShenMoMap3->setChecked(false);
        ui->checkBoxMaxShenMoMap4->setChecked(false);
        ui->checkBoxMaxShenMoMap5->setChecked(false);
        ui->checkBoxMaxShenMoMap6->setChecked(false);
        ui->checkBoxMaxShenMoMap7->setChecked(false);
        ui->checkBoxMaxShenMoMap8->setChecked(false);

        //小号
        //基础
        ui->checkBoxMinZhenCe->setChecked(false);
        ui->checkBoxMinFuHuo->setChecked(false);
        ui->checkBoxMinChongLian->setChecked(false);
        ui->checkBoxMinSuiJi->setChecked(false);
        ui->checkBoxMinZhuangBei->setChecked(false);
        ui->checkBoxMinHangHuiMode->setChecked(false);

        ui->checkBoxMinMoLongBaoZang->setChecked(false);
        ui->checkBoxMinShiJieBoss->setChecked(false);
        ui->checkBoxMinHuangJinShu->setChecked(false);
        ui->checkBoxMinHangHuiShiLian->setChecked(false);

        ui->checkBoxMinFenJieDouLi->setChecked(false);
        ui->checkBoxMinFenJieHuDun->setChecked(false);
        ui->checkBoxMinFenJieBaGua->setChecked(false);
        ui->checkBoxMinFenJieYouMing->setChecked(false);
        //等级
        ui->checkBoxMinDengJiMap1->setChecked(false);
        ui->checkBoxMinDengJiMap2->setChecked(false);
        ui->checkBoxMinDengJiMap3->setChecked(false);
        ui->checkBoxMinDengJiMap4->setChecked(false);
        ui->checkBoxMinDengJiMap5->setChecked(false);
        ui->checkBoxMinDengJiMap6->setChecked(false);
        ui->checkBoxMinDengJiMap7->setChecked(false);
        ui->checkBoxMinDengJiMap8->setChecked(false);
        //斗笠
        ui->checkBoxMinDouLiMap1->setChecked(false);
        ui->checkBoxMinDouLiMap2->setChecked(false);
        ui->checkBoxMinDouLiMap3->setChecked(false);
        ui->checkBoxMinDouLiMap4->setChecked(false);
        ui->checkBoxMinDouLiMap5->setChecked(false);
        ui->checkBoxMinDouLiMap6->setChecked(false);
        ui->checkBoxMinDouLiMap7->setChecked(false);
        ui->checkBoxMinDouLiMap8->setChecked(false);
        //护盾
        ui->checkBoxMinHuDunMap1->setChecked(false);
        ui->checkBoxMinHuDunMap2->setChecked(false);
        ui->checkBoxMinHuDunMap3->setChecked(false);
        ui->checkBoxMinHuDunMap4->setChecked(false);
        ui->checkBoxMinHuDunMap5->setChecked(false);
        ui->checkBoxMinHuDunMap6->setChecked(false);
        ui->checkBoxMinHuDunMap7->setChecked(false);
        ui->checkBoxMinHuDunMap8->setChecked(false);
        //星座
        ui->checkBoxMinXingZuoMap1->setChecked(false);
        ui->checkBoxMinXingZuoMap2->setChecked(false);
        ui->checkBoxMinXingZuoMap3->setChecked(false);
        ui->checkBoxMinXingZuoMap4->setChecked(false);
        ui->checkBoxMinXingZuoMap5->setChecked(false);
        ui->checkBoxMinXingZuoMap6->setChecked(false);
        ui->checkBoxMinXingZuoMap7->setChecked(false);
        ui->checkBoxMinXingZuoMap8->setChecked(false);
        //八卦
        ui->checkBoxMinBaGuaMap1->setChecked(false);
        ui->checkBoxMinBaGuaMap2->setChecked(false);
        ui->checkBoxMinBaGuaMap3->setChecked(false);
        ui->checkBoxMinBaGuaMap4->setChecked(false);
        ui->checkBoxMinBaGuaMap5->setChecked(false);
        //金身
        ui->checkBoxMinJinShenMap1->setChecked(false);
        ui->checkBoxMinJinShenMap2->setChecked(false);
        ui->checkBoxMinJinShenMap3->setChecked(false);
        ui->checkBoxMinJinShenMap4->setChecked(false);
        ui->checkBoxMinJinShenMap5->setChecked(false);
        ui->checkBoxMinJinShenMap6->setChecked(false);
        ui->checkBoxMinJinShenMap7->setChecked(false);
        ui->checkBoxMinJinShenMap8->setChecked(false);
        //幽冥
        ui->checkBoxMinYouMingMap1->setChecked(false);
        ui->checkBoxMinYouMingMap2->setChecked(false);
        ui->checkBoxMinYouMingMap3->setChecked(false);
        ui->checkBoxMinYouMingMap4->setChecked(false);
        ui->checkBoxMinYouMingMap5->setChecked(false);
        ui->checkBoxMinYouMingMap6->setChecked(false);
        ui->checkBoxMinYouMingMap7->setChecked(false);
        ui->checkBoxMinYouMingMap8->setChecked(false);
        //驯龙
        ui->checkBoxMinXunLongMap1->setChecked(false);
        ui->checkBoxMinXunLongMap2->setChecked(false);
        ui->checkBoxMinXunLongMap3->setChecked(false);
        ui->checkBoxMinXunLongMap4->setChecked(false);
        ui->checkBoxMinXunLongMap5->setChecked(false);
        ui->checkBoxMinXunLongMap6->setChecked(false);
        ui->checkBoxMinXunLongMap7->setChecked(false);
        ui->checkBoxMinXunLongMap8->setChecked(false);
        //神魔
        ui->checkBoxMinShenMoMap1->setChecked(false);
        ui->checkBoxMinShenMoMap2->setChecked(false);
        ui->checkBoxMinShenMoMap3->setChecked(false);
        ui->checkBoxMinShenMoMap4->setChecked(false);
        ui->checkBoxMinShenMoMap5->setChecked(false);
        ui->checkBoxMinShenMoMap6->setChecked(false);
        ui->checkBoxMinShenMoMap7->setChecked(false);
        ui->checkBoxMinShenMoMap8->setChecked(false);
    }

    ui->tabWidget->setCurrentIndex(0);
}

void MainWindow::onMaxWindowHwndChanged()
{
    if (ui->comboBoxMaxId->currentIndex() < 0) {
        return;
    }

    if (hwndNameList.isEmpty()) {
        return;
    }
    int index = ui->comboBoxMaxId->currentIndex();
    ui->labelMaxName->setPixmap(hwndNameList.at(index));
}

void MainWindow::onMinWindowHwndChanged()
{
    if (ui->comboBoxMinId->currentIndex() < 0) {
        return;
    }

    if (hwndNameList.isEmpty()) {
        return;
    }
    int index = ui->comboBoxMinId->currentIndex();
    ui->labelMinName->setPixmap(hwndNameList.at(index));
}

void MainWindow::onMaxDengJiTopChanged()
{
    int num;
    QStringList list;

    if (ui->comboBoxMaxDengJiTop1->currentIndex() > -1) {
        num = ui->comboBoxMaxDengJiTop1->currentText().toInt();
        list = pMapManager->getDengJiBossMapList(num);
    }

    if (ui->comboBoxMaxDengJiTop2->currentIndex() > -1) {
        num = ui->comboBoxMaxDengJiTop2->currentText().toInt();
        list = list + pMapManager->getDengJiBossMapList(num);
    }

    if (ui->comboBoxMaxDengJiTop3->currentIndex() > -1) {
        num = ui->comboBoxMaxDengJiTop3->currentText().toInt();
        list = list + pMapManager->getDengJiBossMapList(num);
    }

    if (list.isEmpty()) {
        return;
    }

    list.removeDuplicates();

    ui->comboBoxMaxDengJiList1->clear();
    ui->comboBoxMaxDengJiList1->addItems(list);
    ui->comboBoxMaxDengJiList1->setCurrentIndex(-1);
    ui->comboBoxMaxDengJiList2->clear();
    ui->comboBoxMaxDengJiList2->addItems(list);
    ui->comboBoxMaxDengJiList2->setCurrentIndex(-1);
    ui->comboBoxMaxDengJiList3->clear();
    ui->comboBoxMaxDengJiList3->addItems(list);
    ui->comboBoxMaxDengJiList3->setCurrentIndex(-1);
    ui->comboBoxMaxDengJiList4->clear();
    ui->comboBoxMaxDengJiList4->addItems(list);
    ui->comboBoxMaxDengJiList4->setCurrentIndex(-1);
    ui->comboBoxMaxDengJiList5->clear();
    ui->comboBoxMaxDengJiList5->addItems(list);
    ui->comboBoxMaxDengJiList5->setCurrentIndex(-1);
    ui->comboBoxMaxDengJiList6->clear();
    ui->comboBoxMaxDengJiList6->addItems(list);
    ui->comboBoxMaxDengJiList6->setCurrentIndex(-1);
    ui->comboBoxMaxDengJiList7->clear();
    ui->comboBoxMaxDengJiList7->addItems(list);
    ui->comboBoxMaxDengJiList7->setCurrentIndex(-1);
    ui->comboBoxMaxDengJiList8->clear();
    ui->comboBoxMaxDengJiList8->addItems(list);
    ui->comboBoxMaxDengJiList8->setCurrentIndex(-1);
}

void MainWindow::onMaxDouLiTopChanged()
{
    int num;
    QStringList list;

    if (ui->comboBoxMaxDouLiTop1->currentIndex() > -1) {
        num = ui->comboBoxMaxDouLiTop1->currentText().toInt();
        list = pMapManager->getDouLiBossMapList(num);
    }

    if (ui->comboBoxMaxDouLiTop2->currentIndex() > -1) {
        num = ui->comboBoxMaxDouLiTop2->currentText().toInt();
        list = list + pMapManager->getDouLiBossMapList(num);
    }

    if (ui->comboBoxMaxDouLiTop3->currentIndex() > -1) {
        num = ui->comboBoxMaxDouLiTop3->currentText().toInt();
        list = list + pMapManager->getDouLiBossMapList(num);
    }

    if (list.isEmpty()) {
        return;
    }

    list.removeDuplicates();

    ui->comboBoxMaxDouLiList1->clear();
    ui->comboBoxMaxDouLiList1->addItems(list);
    ui->comboBoxMaxDouLiList1->setCurrentIndex(-1);
    ui->comboBoxMaxDouLiList2->clear();
    ui->comboBoxMaxDouLiList2->addItems(list);
    ui->comboBoxMaxDouLiList2->setCurrentIndex(-1);
    ui->comboBoxMaxDouLiList3->clear();
    ui->comboBoxMaxDouLiList3->addItems(list);
    ui->comboBoxMaxDouLiList3->setCurrentIndex(-1);
    ui->comboBoxMaxDouLiList4->clear();
    ui->comboBoxMaxDouLiList4->addItems(list);
    ui->comboBoxMaxDouLiList4->setCurrentIndex(-1);
    ui->comboBoxMaxDouLiList5->clear();
    ui->comboBoxMaxDouLiList5->addItems(list);
    ui->comboBoxMaxDouLiList5->setCurrentIndex(-1);
    ui->comboBoxMaxDouLiList6->clear();
    ui->comboBoxMaxDouLiList6->addItems(list);
    ui->comboBoxMaxDouLiList6->setCurrentIndex(-1);
    ui->comboBoxMaxDouLiList7->clear();
    ui->comboBoxMaxDouLiList7->addItems(list);
    ui->comboBoxMaxDouLiList7->setCurrentIndex(-1);
    ui->comboBoxMaxDouLiList8->clear();
    ui->comboBoxMaxDouLiList8->addItems(list);
    ui->comboBoxMaxDouLiList8->setCurrentIndex(-1);
}

void MainWindow::onMaxHuDunTopChanged()
{
    int num;
    QStringList list;
    if (ui->comboBoxMaxHuDunTop1->currentIndex() > -1) {
        num = ui->comboBoxMaxHuDunTop1->currentText().toInt();
        list = pMapManager->getHuDunBossMapList(num);
    }

    if (ui->comboBoxMaxHuDunTop2->currentIndex() > -1) {
        num = ui->comboBoxMaxHuDunTop2->currentText().toInt();
        list = list + pMapManager->getHuDunBossMapList(num);
    }

    if (ui->comboBoxMaxHuDunTop3->currentIndex() > -1) {
        num = ui->comboBoxMaxHuDunTop3->currentText().toInt();
        list = list + pMapManager->getHuDunBossMapList(num);
    }

    if (list.isEmpty()) {
        return;
    }

    list.removeDuplicates();

    ui->comboBoxMaxHuDunList1->clear();
    ui->comboBoxMaxHuDunList1->addItems(list);
    ui->comboBoxMaxHuDunList1->setCurrentIndex(-1);
    ui->comboBoxMaxHuDunList2->clear();
    ui->comboBoxMaxHuDunList2->addItems(list);
    ui->comboBoxMaxHuDunList2->setCurrentIndex(-1);
    ui->comboBoxMaxHuDunList3->clear();
    ui->comboBoxMaxHuDunList3->addItems(list);
    ui->comboBoxMaxHuDunList3->setCurrentIndex(-1);
    ui->comboBoxMaxHuDunList4->clear();
    ui->comboBoxMaxHuDunList4->addItems(list);
    ui->comboBoxMaxHuDunList4->setCurrentIndex(-1);
    ui->comboBoxMaxHuDunList5->clear();
    ui->comboBoxMaxHuDunList5->addItems(list);
    ui->comboBoxMaxHuDunList5->setCurrentIndex(-1);
    ui->comboBoxMaxHuDunList6->clear();
    ui->comboBoxMaxHuDunList6->addItems(list);
    ui->comboBoxMaxHuDunList6->setCurrentIndex(-1);
    ui->comboBoxMaxHuDunList7->clear();
    ui->comboBoxMaxHuDunList7->addItems(list);
    ui->comboBoxMaxHuDunList7->setCurrentIndex(-1);
    ui->comboBoxMaxHuDunList8->clear();
    ui->comboBoxMaxHuDunList8->addItems(list);
    ui->comboBoxMaxHuDunList8->setCurrentIndex(-1);
}

void MainWindow::onMaxXingZuoTopChanged()
{
    int num;
    QStringList list;

    if (ui->comboBoxMaxXingZuoTop1->currentIndex() > -1) {
        num = ui->comboBoxMaxXingZuoTop1->currentText().toInt();
        list = pMapManager->getXingZuoBossMapList(num);
    }

    if (ui->comboBoxMaxXingZuoTop2->currentIndex() > -1) {
        num = ui->comboBoxMaxXingZuoTop2->currentText().toInt();
        list = list + pMapManager->getXingZuoBossMapList(num);
    }

    if (ui->comboBoxMaxXingZuoTop3->currentIndex() > -1) {
        num = ui->comboBoxMaxXingZuoTop3->currentText().toInt();
        list = list + pMapManager->getXingZuoBossMapList(num);
    }

    if (list.isEmpty()) {
        return;
    }

    list.removeDuplicates();

    ui->comboBoxMaxXingZuoList1->clear();
    ui->comboBoxMaxXingZuoList1->addItems(list);
    ui->comboBoxMaxXingZuoList1->setCurrentIndex(-1);
    ui->comboBoxMaxXingZuoList2->clear();
    ui->comboBoxMaxXingZuoList2->addItems(list);
    ui->comboBoxMaxXingZuoList2->setCurrentIndex(-1);
    ui->comboBoxMaxXingZuoList3->clear();
    ui->comboBoxMaxXingZuoList3->addItems(list);
    ui->comboBoxMaxXingZuoList3->setCurrentIndex(-1);
    ui->comboBoxMaxXingZuoList4->clear();
    ui->comboBoxMaxXingZuoList4->addItems(list);
    ui->comboBoxMaxXingZuoList4->setCurrentIndex(-1);
    ui->comboBoxMaxXingZuoList5->clear();
    ui->comboBoxMaxXingZuoList5->addItems(list);
    ui->comboBoxMaxXingZuoList5->setCurrentIndex(-1);
    ui->comboBoxMaxXingZuoList6->clear();
    ui->comboBoxMaxXingZuoList6->addItems(list);
    ui->comboBoxMaxXingZuoList6->setCurrentIndex(-1);
    ui->comboBoxMaxXingZuoList7->clear();
    ui->comboBoxMaxXingZuoList7->addItems(list);
    ui->comboBoxMaxXingZuoList7->setCurrentIndex(-1);
    ui->comboBoxMaxXingZuoList8->clear();
    ui->comboBoxMaxXingZuoList8->addItems(list);
    ui->comboBoxMaxXingZuoList8->setCurrentIndex(-1);
}

void MainWindow::onMaxJinShenTopChanged()
{
    int num;
    QStringList list;

    if (ui->comboBoxMaxJinShenTop1->currentIndex() > -1) {
        num = ui->comboBoxMaxJinShenTop1->currentText().toInt();
        list = pMapManager->getJinShenBossMapList(num);
    }

    if (ui->comboBoxMaxJinShenTop2->currentIndex() > -1) {
        num = ui->comboBoxMaxJinShenTop2->currentText().toInt();
        list = list + pMapManager->getJinShenBossMapList(num);
    }

    if (ui->comboBoxMaxJinShenTop3->currentIndex() > -1) {
        num = ui->comboBoxMaxJinShenTop3->currentText().toInt();
        list = list + pMapManager->getJinShenBossMapList(num);
    }

    if (list.isEmpty()) {
        return;
    }

    list.removeDuplicates();

    ui->comboBoxMaxJinShenList1->clear();
    ui->comboBoxMaxJinShenList1->addItems(list);
    ui->comboBoxMaxJinShenList1->setCurrentIndex(-1);
    ui->comboBoxMaxJinShenList2->clear();
    ui->comboBoxMaxJinShenList2->addItems(list);
    ui->comboBoxMaxJinShenList2->setCurrentIndex(-1);
    ui->comboBoxMaxJinShenList3->clear();
    ui->comboBoxMaxJinShenList3->addItems(list);
    ui->comboBoxMaxJinShenList3->setCurrentIndex(-1);
    ui->comboBoxMaxJinShenList4->clear();
    ui->comboBoxMaxJinShenList4->addItems(list);
    ui->comboBoxMaxJinShenList4->setCurrentIndex(-1);
    ui->comboBoxMaxJinShenList5->clear();
    ui->comboBoxMaxJinShenList5->addItems(list);
    ui->comboBoxMaxJinShenList5->setCurrentIndex(-1);
    ui->comboBoxMaxJinShenList6->clear();
    ui->comboBoxMaxJinShenList6->addItems(list);
    ui->comboBoxMaxJinShenList6->setCurrentIndex(-1);
    ui->comboBoxMaxJinShenList7->clear();
    ui->comboBoxMaxJinShenList7->addItems(list);
    ui->comboBoxMaxJinShenList7->setCurrentIndex(-1);
    ui->comboBoxMaxJinShenList8->clear();
    ui->comboBoxMaxJinShenList8->addItems(list);
    ui->comboBoxMaxJinShenList8->setCurrentIndex(-1);
}

void MainWindow::onMaxYouMingTopChanged()
{
    int num;
    QStringList list;
    if (ui->comboBoxMaxYouMingTop1->currentIndex() > -1) {
        num = ui->comboBoxMaxYouMingTop1->currentText().toInt();
        list = pMapManager->getYouMingBossMapList(num);
    }

    if (ui->comboBoxMaxYouMingTop2->currentIndex() > -1) {
        num = ui->comboBoxMaxYouMingTop2->currentText().toInt();
        list = list + pMapManager->getYouMingBossMapList(num);
    }

    if (ui->comboBoxMaxYouMingTop3->currentIndex() > -1) {
        num = ui->comboBoxMaxYouMingTop3->currentText().toInt();
        list = list + pMapManager->getYouMingBossMapList(num);
    }

    if (list.isEmpty()) {
        return;
    }

    list.removeDuplicates();

    ui->comboBoxMaxYouMingList1->clear();
    ui->comboBoxMaxYouMingList1->addItems(list);
    ui->comboBoxMaxYouMingList1->setCurrentIndex(-1);
    ui->comboBoxMaxYouMingList2->clear();
    ui->comboBoxMaxYouMingList2->addItems(list);
    ui->comboBoxMaxYouMingList2->setCurrentIndex(-1);
    ui->comboBoxMaxYouMingList3->clear();
    ui->comboBoxMaxYouMingList3->addItems(list);
    ui->comboBoxMaxYouMingList3->setCurrentIndex(-1);
    ui->comboBoxMaxYouMingList4->clear();
    ui->comboBoxMaxYouMingList4->addItems(list);
    ui->comboBoxMaxYouMingList4->setCurrentIndex(-1);
    ui->comboBoxMaxYouMingList5->clear();
    ui->comboBoxMaxYouMingList5->addItems(list);
    ui->comboBoxMaxYouMingList5->setCurrentIndex(-1);
    ui->comboBoxMaxYouMingList6->clear();
    ui->comboBoxMaxYouMingList6->addItems(list);
    ui->comboBoxMaxYouMingList6->setCurrentIndex(-1);
    ui->comboBoxMaxYouMingList7->clear();
    ui->comboBoxMaxYouMingList7->addItems(list);
    ui->comboBoxMaxYouMingList7->setCurrentIndex(-1);
    ui->comboBoxMaxYouMingList8->clear();
    ui->comboBoxMaxYouMingList8->addItems(list);
    ui->comboBoxMaxYouMingList8->setCurrentIndex(-1);
}

void MainWindow::onMaxXunLongTopChanged()
{
    int num;
    QStringList list;

    if (ui->comboBoxMaxXunLongTop1->currentIndex() > -1) {
        num = ui->comboBoxMaxXunLongTop1->currentText().toInt();
        list = pMapManager->getXunLongBossMapList(num);
    }

    if (ui->comboBoxMaxXunLongTop2->currentIndex() > -1) {
        num = ui->comboBoxMaxXunLongTop2->currentText().toInt();
        list = list + pMapManager->getXunLongBossMapList(num);
    }

    if (ui->comboBoxMaxXunLongTop3->currentIndex() > -1) {
        num = ui->comboBoxMaxXunLongTop3->currentText().toInt();
        list = list + pMapManager->getXunLongBossMapList(num);
    }

    if (list.isEmpty()) {
        return;
    }

    list.removeDuplicates();

    ui->comboBoxMaxXunLongList1->clear();
    ui->comboBoxMaxXunLongList1->addItems(list);
    ui->comboBoxMaxXunLongList1->setCurrentIndex(-1);
    ui->comboBoxMaxXunLongList2->clear();
    ui->comboBoxMaxXunLongList2->addItems(list);
    ui->comboBoxMaxXunLongList2->setCurrentIndex(-1);
    ui->comboBoxMaxXunLongList3->clear();
    ui->comboBoxMaxXunLongList3->addItems(list);
    ui->comboBoxMaxXunLongList3->setCurrentIndex(-1);
    ui->comboBoxMaxXunLongList4->clear();
    ui->comboBoxMaxXunLongList4->addItems(list);
    ui->comboBoxMaxXunLongList4->setCurrentIndex(-1);
    ui->comboBoxMaxXunLongList5->clear();
    ui->comboBoxMaxXunLongList5->addItems(list);
    ui->comboBoxMaxXunLongList5->setCurrentIndex(-1);
    ui->comboBoxMaxXunLongList6->clear();
    ui->comboBoxMaxXunLongList6->addItems(list);
    ui->comboBoxMaxXunLongList6->setCurrentIndex(-1);
    ui->comboBoxMaxXunLongList7->clear();
    ui->comboBoxMaxXunLongList7->addItems(list);
    ui->comboBoxMaxXunLongList7->setCurrentIndex(-1);
    ui->comboBoxMaxXunLongList8->clear();
    ui->comboBoxMaxXunLongList8->addItems(list);
    ui->comboBoxMaxXunLongList8->setCurrentIndex(-1);
}

void MainWindow::onMaxShenMoTopChanged()
{
    int num;
    QStringList list;

    if (ui->comboBoxMaxShenMoTop1->currentIndex() > -1) {
        num = ui->comboBoxMaxShenMoTop1->currentText().toInt();
        list = pMapManager->getShenMoBossMapList(num);
    }

    if (ui->comboBoxMaxShenMoTop2->currentIndex() > -1) {
        num = ui->comboBoxMaxShenMoTop2->currentText().toInt();
        list = list + pMapManager->getShenMoBossMapList(num);
    }

    if (ui->comboBoxMaxShenMoTop3->currentIndex() > -1) {
        num = ui->comboBoxMaxShenMoTop3->currentText().toInt();
        list = list + pMapManager->getShenMoBossMapList(num);
    }

    if (list.isEmpty()) {
        return;
    }

    list.removeDuplicates();

    ui->comboBoxMaxShenMoList1->clear();
    ui->comboBoxMaxShenMoList1->addItems(list);
    ui->comboBoxMaxShenMoList1->setCurrentIndex(-1);
    ui->comboBoxMaxShenMoList2->clear();
    ui->comboBoxMaxShenMoList2->addItems(list);
    ui->comboBoxMaxShenMoList2->setCurrentIndex(-1);
    ui->comboBoxMaxShenMoList3->clear();
    ui->comboBoxMaxShenMoList3->addItems(list);
    ui->comboBoxMaxShenMoList3->setCurrentIndex(-1);
    ui->comboBoxMaxShenMoList4->clear();
    ui->comboBoxMaxShenMoList4->addItems(list);
    ui->comboBoxMaxShenMoList4->setCurrentIndex(-1);
    ui->comboBoxMaxShenMoList5->clear();
    ui->comboBoxMaxShenMoList5->addItems(list);
    ui->comboBoxMaxShenMoList5->setCurrentIndex(-1);
    ui->comboBoxMaxShenMoList6->clear();
    ui->comboBoxMaxShenMoList6->addItems(list);
    ui->comboBoxMaxShenMoList6->setCurrentIndex(-1);
    ui->comboBoxMaxShenMoList7->clear();
    ui->comboBoxMaxShenMoList7->addItems(list);
    ui->comboBoxMaxShenMoList7->setCurrentIndex(-1);
    ui->comboBoxMaxShenMoList8->clear();
    ui->comboBoxMaxShenMoList8->addItems(list);
    ui->comboBoxMaxShenMoList8->setCurrentIndex(-1);
}


//小号等级
void MainWindow::onMinDengJiTopChanged()
{
    int num;
    QStringList list;

    if (ui->comboBoxMinDengJiTop1->currentIndex() > -1) {
        num = ui->comboBoxMinDengJiTop1->currentText().toInt();
        list = pMapManager->getDengJiBossMapList(num);
    }

    if (ui->comboBoxMinDengJiTop2->currentIndex() > -1) {
        num = ui->comboBoxMinDengJiTop2->currentText().toInt();
        list = list + pMapManager->getDengJiBossMapList(num);
    }

    if (ui->comboBoxMinDengJiTop3->currentIndex() > -1) {
        num = ui->comboBoxMinDengJiTop3->currentText().toInt();
        list = list + pMapManager->getDengJiBossMapList(num);
    }

    if (list.isEmpty()) {
        return;
    }

    list.removeDuplicates();

    ui->comboBoxMinDengJiList1->clear();
    ui->comboBoxMinDengJiList1->addItems(list);
    ui->comboBoxMinDengJiList1->setCurrentIndex(-1);
    ui->comboBoxMinDengJiList2->clear();
    ui->comboBoxMinDengJiList2->addItems(list);
    ui->comboBoxMinDengJiList2->setCurrentIndex(-1);
    ui->comboBoxMinDengJiList3->clear();
    ui->comboBoxMinDengJiList3->addItems(list);
    ui->comboBoxMinDengJiList3->setCurrentIndex(-1);
    ui->comboBoxMinDengJiList4->clear();
    ui->comboBoxMinDengJiList4->addItems(list);
    ui->comboBoxMinDengJiList4->setCurrentIndex(-1);
    ui->comboBoxMinDengJiList5->clear();
    ui->comboBoxMinDengJiList5->addItems(list);
    ui->comboBoxMinDengJiList5->setCurrentIndex(-1);
    ui->comboBoxMinDengJiList6->clear();
    ui->comboBoxMinDengJiList6->addItems(list);
    ui->comboBoxMinDengJiList6->setCurrentIndex(-1);
    ui->comboBoxMinDengJiList7->clear();
    ui->comboBoxMinDengJiList7->addItems(list);
    ui->comboBoxMinDengJiList7->setCurrentIndex(-1);
    ui->comboBoxMinDengJiList8->clear();
    ui->comboBoxMinDengJiList8->addItems(list);
    ui->comboBoxMinDengJiList8->setCurrentIndex(-1);
}

void MainWindow::onMinDouLiTopChanged()
{
    int num;
    QStringList list;

    if (ui->comboBoxMinDouLiTop1->currentIndex() > -1) {
        num = ui->comboBoxMinDouLiTop1->currentText().toInt();
        list = pMapManager->getDouLiBossMapList(num);
    }

    if (ui->comboBoxMinDouLiTop2->currentIndex() > -1) {
        num = ui->comboBoxMinDouLiTop2->currentText().toInt();
        list = list + pMapManager->getDouLiBossMapList(num);
    }

    if (ui->comboBoxMinDouLiTop3->currentIndex() > -1) {
        num = ui->comboBoxMinDouLiTop3->currentText().toInt();
        list = list + pMapManager->getDouLiBossMapList(num);
    }

    if (list.isEmpty()) {
        return;
    }

    list.removeDuplicates();

    ui->comboBoxMinDouLiList1->clear();
    ui->comboBoxMinDouLiList1->addItems(list);
    ui->comboBoxMinDouLiList1->setCurrentIndex(-1);
    ui->comboBoxMinDouLiList2->clear();
    ui->comboBoxMinDouLiList2->addItems(list);
    ui->comboBoxMinDouLiList2->setCurrentIndex(-1);
    ui->comboBoxMinDouLiList3->clear();
    ui->comboBoxMinDouLiList3->addItems(list);
    ui->comboBoxMinDouLiList3->setCurrentIndex(-1);
    ui->comboBoxMinDouLiList4->clear();
    ui->comboBoxMinDouLiList4->addItems(list);
    ui->comboBoxMinDouLiList4->setCurrentIndex(-1);
    ui->comboBoxMinDouLiList5->clear();
    ui->comboBoxMinDouLiList5->addItems(list);
    ui->comboBoxMinDouLiList5->setCurrentIndex(-1);
    ui->comboBoxMinDouLiList6->clear();
    ui->comboBoxMinDouLiList6->addItems(list);
    ui->comboBoxMinDouLiList6->setCurrentIndex(-1);
    ui->comboBoxMinDouLiList7->clear();
    ui->comboBoxMinDouLiList7->addItems(list);
    ui->comboBoxMinDouLiList7->setCurrentIndex(-1);
    ui->comboBoxMinDouLiList8->clear();
    ui->comboBoxMinDouLiList8->addItems(list);
    ui->comboBoxMinDouLiList8->setCurrentIndex(-1);
}

void MainWindow::onMinHuDunTopChanged()
{
    int num;
    QStringList list;

    if (ui->comboBoxMinHuDunTop1->currentIndex() > -1) {
        num = ui->comboBoxMinHuDunTop1->currentText().toInt();
        list = pMapManager->getHuDunBossMapList(num);
    }

    if (ui->comboBoxMinHuDunTop2->currentIndex() > -1) {
        num = ui->comboBoxMinHuDunTop2->currentText().toInt();
        list = list + pMapManager->getHuDunBossMapList(num);
    }

    if (ui->comboBoxMinHuDunTop3->currentIndex() > -1) {
        num = ui->comboBoxMinHuDunTop3->currentText().toInt();
        list = list + pMapManager->getHuDunBossMapList(num);
    }

    if (list.isEmpty()) {
        return;
    }

    list.removeDuplicates();

    ui->comboBoxMinHuDunList1->clear();
    ui->comboBoxMinHuDunList1->addItems(list);
    ui->comboBoxMinHuDunList1->setCurrentIndex(-1);
    ui->comboBoxMinHuDunList2->clear();
    ui->comboBoxMinHuDunList2->addItems(list);
    ui->comboBoxMinHuDunList2->setCurrentIndex(-1);
    ui->comboBoxMinHuDunList3->clear();
    ui->comboBoxMinHuDunList3->addItems(list);
    ui->comboBoxMinHuDunList3->setCurrentIndex(-1);
    ui->comboBoxMinHuDunList4->clear();
    ui->comboBoxMinHuDunList4->addItems(list);
    ui->comboBoxMinHuDunList4->setCurrentIndex(-1);
    ui->comboBoxMinHuDunList5->clear();
    ui->comboBoxMinHuDunList5->addItems(list);
    ui->comboBoxMinHuDunList5->setCurrentIndex(-1);
    ui->comboBoxMinHuDunList6->clear();
    ui->comboBoxMinHuDunList6->addItems(list);
    ui->comboBoxMinHuDunList6->setCurrentIndex(-1);
    ui->comboBoxMinHuDunList7->clear();
    ui->comboBoxMinHuDunList7->addItems(list);
    ui->comboBoxMinHuDunList7->setCurrentIndex(-1);
    ui->comboBoxMinHuDunList8->clear();
    ui->comboBoxMinHuDunList8->addItems(list);
    ui->comboBoxMinHuDunList8->setCurrentIndex(-1);
}

void MainWindow::onMinXingZuoTopChanged()
{
    int num;
    QStringList list;

    if (ui->comboBoxMinXingZuoTop1->currentIndex() > -1) {
        num = ui->comboBoxMinXingZuoTop1->currentText().toInt();
        list = pMapManager->getXingZuoBossMapList(num);
    }

    if (ui->comboBoxMinXingZuoTop2->currentIndex() > -1) {
        num = ui->comboBoxMinXingZuoTop2->currentText().toInt();
        list = list + pMapManager->getXingZuoBossMapList(num);
    }

    if (ui->comboBoxMinXingZuoTop3->currentIndex() > -1) {
        num = ui->comboBoxMinXingZuoTop3->currentText().toInt();
        list = list + pMapManager->getXingZuoBossMapList(num);
    }

    if (list.isEmpty()) {
        return;
    }

    list.removeDuplicates();

    ui->comboBoxMinXingZuoList1->clear();
    ui->comboBoxMinXingZuoList1->addItems(list);
    ui->comboBoxMinXingZuoList1->setCurrentIndex(-1);
    ui->comboBoxMinXingZuoList2->clear();
    ui->comboBoxMinXingZuoList2->addItems(list);
    ui->comboBoxMinXingZuoList2->setCurrentIndex(-1);
    ui->comboBoxMinXingZuoList3->clear();
    ui->comboBoxMinXingZuoList3->addItems(list);
    ui->comboBoxMinXingZuoList3->setCurrentIndex(-1);
    ui->comboBoxMinXingZuoList4->clear();
    ui->comboBoxMinXingZuoList4->addItems(list);
    ui->comboBoxMinXingZuoList4->setCurrentIndex(-1);
    ui->comboBoxMinXingZuoList5->clear();
    ui->comboBoxMinXingZuoList5->addItems(list);
    ui->comboBoxMinXingZuoList5->setCurrentIndex(-1);
    ui->comboBoxMinXingZuoList6->clear();
    ui->comboBoxMinXingZuoList6->addItems(list);
    ui->comboBoxMinXingZuoList6->setCurrentIndex(-1);
    ui->comboBoxMinXingZuoList7->clear();
    ui->comboBoxMinXingZuoList7->addItems(list);
    ui->comboBoxMinXingZuoList7->setCurrentIndex(-1);
    ui->comboBoxMinXingZuoList8->clear();
    ui->comboBoxMinXingZuoList8->addItems(list);
    ui->comboBoxMinXingZuoList8->setCurrentIndex(-1);
}

void MainWindow::onMinJinShenTopChanged()
{
    int num;
    QStringList list;

    if (ui->comboBoxMinJinShenTop1->currentIndex() > -1) {
        num = ui->comboBoxMaxJinShenTop1->currentText().toInt();
        list = pMapManager->getJinShenBossMapList(num);
    }

    if (ui->comboBoxMinJinShenTop2->currentIndex() > -1) {
        num = ui->comboBoxMaxJinShenTop2->currentText().toInt();
        list = list + pMapManager->getJinShenBossMapList(num);
    }

    if (ui->comboBoxMinJinShenTop3->currentIndex() > -1) {
        num = ui->comboBoxMinJinShenTop3->currentText().toInt();
        list = list + pMapManager->getJinShenBossMapList(num);
    }

    if (list.isEmpty()) {
        return;
    }

    list.removeDuplicates();

    ui->comboBoxMinJinShenList1->clear();
    ui->comboBoxMinJinShenList1->addItems(list);
    ui->comboBoxMinJinShenList1->setCurrentIndex(-1);
    ui->comboBoxMinJinShenList2->clear();
    ui->comboBoxMinJinShenList2->addItems(list);
    ui->comboBoxMinJinShenList2->setCurrentIndex(-1);
    ui->comboBoxMinJinShenList3->clear();
    ui->comboBoxMinJinShenList3->addItems(list);
    ui->comboBoxMinJinShenList3->setCurrentIndex(-1);
    ui->comboBoxMinJinShenList4->clear();
    ui->comboBoxMinJinShenList4->addItems(list);
    ui->comboBoxMinJinShenList4->setCurrentIndex(-1);
    ui->comboBoxMinJinShenList5->clear();
    ui->comboBoxMinJinShenList5->addItems(list);
    ui->comboBoxMinJinShenList5->setCurrentIndex(-1);
    ui->comboBoxMinJinShenList6->clear();
    ui->comboBoxMinJinShenList6->addItems(list);
    ui->comboBoxMinJinShenList6->setCurrentIndex(-1);
    ui->comboBoxMinJinShenList7->clear();
    ui->comboBoxMinJinShenList7->addItems(list);
    ui->comboBoxMinJinShenList7->setCurrentIndex(-1);
    ui->comboBoxMinJinShenList8->clear();
    ui->comboBoxMinJinShenList8->addItems(list);
    ui->comboBoxMinJinShenList8->setCurrentIndex(-1);
}

void MainWindow::onMinYouMingTopChanged()
{
    int num;
    QStringList list;

    if (ui->comboBoxMinYouMingTop1->currentIndex() > -1) {
        num = ui->comboBoxMinYouMingTop1->currentText().toInt();
        list = pMapManager->getYouMingBossMapList(num);
    }

    if (ui->comboBoxMinYouMingTop2->currentIndex() > -1) {
        num = ui->comboBoxMinYouMingTop2->currentText().toInt();
        list = list + pMapManager->getYouMingBossMapList(num);
    }

    if (ui->comboBoxMinYouMingTop3->currentIndex() > -1) {
        num = ui->comboBoxMinYouMingTop3->currentText().toInt();
        list = list + pMapManager->getYouMingBossMapList(num);
    }

    if (list.isEmpty()) {
        return;
    }

    list.removeDuplicates();

    ui->comboBoxMinYouMingList1->clear();
    ui->comboBoxMinYouMingList1->addItems(list);
    ui->comboBoxMinYouMingList1->setCurrentIndex(-1);
    ui->comboBoxMinYouMingList2->clear();
    ui->comboBoxMinYouMingList2->addItems(list);
    ui->comboBoxMinYouMingList2->setCurrentIndex(-1);
    ui->comboBoxMinYouMingList3->clear();
    ui->comboBoxMinYouMingList3->addItems(list);
    ui->comboBoxMinYouMingList3->setCurrentIndex(-1);
    ui->comboBoxMinYouMingList4->clear();
    ui->comboBoxMinYouMingList4->addItems(list);
    ui->comboBoxMinYouMingList4->setCurrentIndex(-1);
    ui->comboBoxMinYouMingList5->clear();
    ui->comboBoxMinYouMingList5->addItems(list);
    ui->comboBoxMinYouMingList5->setCurrentIndex(-1);
    ui->comboBoxMinYouMingList6->clear();
    ui->comboBoxMinYouMingList6->addItems(list);
    ui->comboBoxMinYouMingList6->setCurrentIndex(-1);
    ui->comboBoxMinYouMingList7->clear();
    ui->comboBoxMinYouMingList7->addItems(list);
    ui->comboBoxMinYouMingList7->setCurrentIndex(-1);
    ui->comboBoxMinYouMingList8->clear();
    ui->comboBoxMinYouMingList8->addItems(list);
    ui->comboBoxMinYouMingList8->setCurrentIndex(-1);
}

void MainWindow::onMinXunLongTopChanged()
{
    int num;
    QStringList list;

    if (ui->comboBoxMinXunLongTop1->currentIndex() > -1) {
        num = ui->comboBoxMinXunLongTop1->currentText().toInt();
        list = pMapManager->getXunLongBossMapList(num);
    }

    if (ui->comboBoxMinXunLongTop2->currentIndex() > -1) {
        num = ui->comboBoxMinXunLongTop2->currentText().toInt();
        list = list + pMapManager->getXunLongBossMapList(num);
    }

    if (ui->comboBoxMinXunLongTop3->currentIndex() > -1) {
        num = ui->comboBoxMinXunLongTop3->currentText().toInt();
        list = list + pMapManager->getXunLongBossMapList(num);
    }

    if (list.isEmpty()) {
        return;
    }

    list.removeDuplicates();

    ui->comboBoxMinXunLongList1->clear();
    ui->comboBoxMinXunLongList1->addItems(list);
    ui->comboBoxMinXunLongList1->setCurrentIndex(-1);
    ui->comboBoxMinXunLongList2->clear();
    ui->comboBoxMinXunLongList2->addItems(list);
    ui->comboBoxMinXunLongList2->setCurrentIndex(-1);
    ui->comboBoxMinXunLongList3->clear();
    ui->comboBoxMinXunLongList3->addItems(list);
    ui->comboBoxMinXunLongList3->setCurrentIndex(-1);
    ui->comboBoxMinXunLongList4->clear();
    ui->comboBoxMinXunLongList4->addItems(list);
    ui->comboBoxMinXunLongList4->setCurrentIndex(-1);
    ui->comboBoxMinXunLongList5->clear();
    ui->comboBoxMinXunLongList5->addItems(list);
    ui->comboBoxMinXunLongList5->setCurrentIndex(-1);
    ui->comboBoxMinXunLongList6->clear();
    ui->comboBoxMinXunLongList6->addItems(list);
    ui->comboBoxMinXunLongList6->setCurrentIndex(-1);
    ui->comboBoxMinXunLongList7->clear();
    ui->comboBoxMinXunLongList7->addItems(list);
    ui->comboBoxMinXunLongList7->setCurrentIndex(-1);
    ui->comboBoxMinXunLongList8->clear();
    ui->comboBoxMinXunLongList8->addItems(list);
    ui->comboBoxMinXunLongList8->setCurrentIndex(-1);
}

void MainWindow::onMinShenMoTopChanged()
{
    int num;
    QStringList list;

    if (ui->comboBoxMinShenMoTop1->currentIndex() > -1) {
        num = ui->comboBoxMinShenMoTop1->currentText().toInt();
        list = pMapManager->getShenMoBossMapList(num);
    }

    if (ui->comboBoxMinShenMoTop2->currentIndex() > -1) {
        num = ui->comboBoxMinShenMoTop2->currentText().toInt();
        list = list + pMapManager->getShenMoBossMapList(num);
    }

    if (ui->comboBoxMinShenMoTop3->currentIndex() > -1) {
        num = ui->comboBoxMinShenMoTop3->currentText().toInt();
        list = list + pMapManager->getShenMoBossMapList(num);
    }

    if (list.isEmpty()) {
        return;
    }

    list.removeDuplicates();

    ui->comboBoxMinShenMoList1->clear();
    ui->comboBoxMinShenMoList1->addItems(list);
    ui->comboBoxMinShenMoList1->setCurrentIndex(-1);
    ui->comboBoxMinShenMoList2->clear();
    ui->comboBoxMinShenMoList2->addItems(list);
    ui->comboBoxMinShenMoList2->setCurrentIndex(-1);
    ui->comboBoxMinShenMoList3->clear();
    ui->comboBoxMinShenMoList3->addItems(list);
    ui->comboBoxMinShenMoList3->setCurrentIndex(-1);
    ui->comboBoxMinShenMoList4->clear();
    ui->comboBoxMinShenMoList4->addItems(list);
    ui->comboBoxMinShenMoList4->setCurrentIndex(-1);
    ui->comboBoxMinShenMoList5->clear();
    ui->comboBoxMinShenMoList5->addItems(list);
    ui->comboBoxMinShenMoList5->setCurrentIndex(-1);
    ui->comboBoxMinShenMoList6->clear();
    ui->comboBoxMinShenMoList6->addItems(list);
    ui->comboBoxMinShenMoList6->setCurrentIndex(-1);
    ui->comboBoxMinShenMoList7->clear();
    ui->comboBoxMinShenMoList7->addItems(list);
    ui->comboBoxMinShenMoList7->setCurrentIndex(-1);
    ui->comboBoxMinShenMoList8->clear();
    ui->comboBoxMinShenMoList8->addItems(list);
    ui->comboBoxMinShenMoList8->setCurrentIndex(-1);
}
