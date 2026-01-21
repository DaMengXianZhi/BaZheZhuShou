#include "LogIn.h"
#include "ui_LogIn.h"

#include <windows.h>
#include <QClipboard>
#include <QScreen>
#include <QMessageBox>

#include "Define.h"

LogIn::LogIn(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::LogIn)
{
    ui->setupUi(this);
    ui->lineEdit_id->setValidator(new QIntValidator(1, 999999, this));

    pUserManager = new UserManager(this);
    connect(pUserManager, &UserManager::onUserCheckResult, this, &LogIn::onCheckResult);

    pWindow = new MainWindow();
    connect(pWindow, &MainWindow::onBackPressed, this, &LogIn::onResume);

    //机器码
    ui->label_code->setText(pUserManager->getMachineCode());

    //系统版本
    QString version = QSysInfo::productVersion();
    ui->label_system->setText(QSysInfo::productType() + " " + version);
    qDebug() << "LogIn: 系统版本=" + QSysInfo::productType() + "-" + version;

    //游戏平台
    ui->comboBox_platform->addItem("QQ游戏大厅");
    ui->comboBox_platform->addItem("QQ游戏中心");

    //新老区
    ui->comboBox_zone->addItem("新区");
    ui->comboBox_zone->addItem("老区");

    //辅助类型
    ui->comboBox_type->addItem("至尊版");
    ui->comboBox_type->addItem("钻石版");
    ui->comboBox_type->addItem("铂金版");

    connect(ui->pushButton_copy, &QPushButton::clicked, this, &LogIn::onCopyButtonClicked);
    connect(ui->pushButton_check, &QPushButton::clicked, this, &LogIn::onCheckButtonClicked);
}

LogIn::~LogIn()
{
    delete ui;
}

void LogIn::onResume()
{
    this->show();
}

/**
 * @brief LogIn::onCopyButtonClicked
 * 拷贝机器码到粘贴板
 */
void LogIn::onCopyButtonClicked()
{
    auto clipboard = QGuiApplication::clipboard();
    clipboard->setText(ui->label_code->text());
}

/**
 * @brief LogIn::onCheckButtonClicked
 * 身份验证
 */
void LogIn::onCheckButtonClicked()
{
    //先确认分辨率是否1920x1080，并且是否100%缩放
    QScreen *screen = QGuiApplication::primaryScreen();
    if (screen == NULL) {
        //获取分辨率失败
        QMessageBox *messageBox = new QMessageBox(this);
        messageBox->setWindowTitle("警告");
        messageBox->setText("获取分辨率失败！鼠标右键以管理员身份运行。");
        messageBox->exec();
        return;
    }

    // 获取屏幕分辨率
    const QRect geometry = screen->geometry();
    int width = geometry.width();
    int height = geometry.height();

    qDebug() << "onCheckButtonClicked: 分辨率:" + QString::number(width) + " x " + QString::number(height);

    if ((width == 1366 && height == 768) || (width == 1920 && height == 1080)) {
        //1366x768
        //1920x1080
        qreal dotsPerInch = screen->logicalDotsPerInch();
        qDebug() << "onCheckButtonClicked: 缩放：" << dotsPerInch;
        if (dotsPerInch == 96) {
            //缩放100%
            ui->pushButton_check->setEnabled(false);
            QString strId = ui->lineEdit_id->text();
            int id = 1;
            if (!strId.isEmpty()) {
                id = strId.toInt();
            }
            pUserManager->checkUserMessage(ui->comboBox_type->currentIndex(), id);
        } else {
            QMessageBox *messageBox = new QMessageBox(this);
            messageBox->setWindowTitle("警告");
            messageBox->setText("请将屏幕设置为100%缩放");
            messageBox->exec();
        }
    } else {
        //分辨率不对
        QMessageBox *messageBox = new QMessageBox(this);
        messageBox->setWindowTitle("警告");
        messageBox->setText("请将分辨率设置成：1920x1080 或 1366x768");
        messageBox->exec();
    }
}

void LogIn::onCheckResult(int code, QDate date)
{
    //qDebug() << "onCheckResult: code=" << code << "date=" << date;
    ui->pushButton_check->setEnabled(true);
    if (code == RESULT_FAILED) {
        //网络请求失败
        QMessageBox *messageBox = new QMessageBox(this);
        messageBox->setWindowTitle("警告");
        messageBox->setText("访问服务器失败");
        messageBox->exec();
        return;
    } else if (code == RESULT_NOT_REGISTERED) {
        //没有注册
        QMessageBox *messageBox = new QMessageBox(this);
        messageBox->setWindowTitle("警告");
        messageBox->setText("请联系管理员（QQ：3965289963）进行注册");
        messageBox->exec();
        return;
    } else if (code == RESULT_TIME_OUT) {
        //超时了，请续费
        QMessageBox *messageBox = new QMessageBox(this);
        messageBox->setWindowTitle("警告");
        messageBox->setText("请联系管理员（QQ：3965289963）进行续费");
        messageBox->exec();
        return;
    } else if (code == RESULT_SUCCESS) {
        //成功
        int type = ui->comboBox_type->currentIndex();
        int platform = ui->comboBox_platform->currentIndex();
        int zone = ui->comboBox_zone->currentIndex();

        pWindow->initWindow(platform, type, zone, date);
        pWindow->show();
        this->hide();
    }
}
