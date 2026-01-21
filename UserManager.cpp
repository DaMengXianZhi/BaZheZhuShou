#include "UserManager.h"

#include <windows.h>
#include <QProcess>
#include <QSettings>
#include <QJsonDocument>
#include <QJsonObject>

#include "Define.h"

UserManager::UserManager(QObject *parent)
    : QObject{parent}
{
    pManager = new QNetworkAccessManager(this);
    pDate = new QDate();
    zoneId = 0;
}

QString UserManager::getMachineCode()
{
    //获取硬盘系列号
    //LPTSTR lpRootPathName = "C:\\";
    DWORD VolumeSerialNumber;
    GetVolumeInformation(TEXT("C:\\"), NULL, 0, &VolumeSerialNumber, NULL, NULL, NULL, 0);
    QString str = QString::number(VolumeSerialNumber, 16).toUpper();
    //将硬盘系列号进行哈希
    QByteArray hash = QCryptographicHash::hash((str + "ding502dage").toUtf8(), QCryptographicHash::Md5);
    return hash.toHex().toUpper();
}
/**
 * @brief checkUserMessage
 * @param type 1:至尊, 2:钻石, 3铂金
 */
void UserManager::checkUserMessage(int type, int zoneId)
{
    this->zoneId = zoneId;
    QUrl *pUrl;
    if (type == TYPE_ZHI_ZUN) {
        pUrl = new QUrl(LINK_ZHI_ZUN);
    } else if (type == TYPE_ZUAN_SHI) {
        pUrl = new QUrl(LINK_ZUAN_SHI);
    } else {
        pUrl = new QUrl(LINK_BO_JIN);
    }
    QNetworkRequest request(*pUrl);
    pUserReply = pManager->get(request);
    connect(pUserReply, &QNetworkReply::finished, this, &UserManager::onUserCheckFinished);
}

void UserManager::getNetworkDate()
{
    QUrl *pUrl = new QUrl("http://quan.suning.com/getSysTime.do");
    QNetworkRequest request(*pUrl);
    pDateReply = pManager->get(request);
    connect(pDateReply, &QNetworkReply::finished, this, &UserManager::onNetworkDateFinished);
}

void UserManager::onUserCheckFinished()
{
    if (pUserReply->error() == QNetworkReply::NoError) {
        //success
        QString currentDate = pUserReply->rawHeader("Date");
        //qDebug() << "currentDate=" << currentDate;

        QString data = pUserReply->readAll().data();
        //qDebug() << "data:" << data.toStdU32String();
        int start = data.lastIndexOf("html_content") + 23;
        QString temp = data.mid(start, -1);
        int end = temp.indexOf("item_markdown");
        bool found = false;

        QString target = temp.mid(0, end);
        //qDebug() << "data:" << target;
        QString machineCode = getMachineCode();
        QStringList userList = target.split("|");
        QString endDate;

        QStringList currentList;
        for (QString str : userList) {
            currentList = str.split(":");
            if (currentList.size() < 3) {
                continue;
            }
            if ((currentList.at(0).toInt() == zoneId) && (currentList.at(1) == machineCode)) {
                found = true;
                endDate = currentList.at(2);
                break;
            }
        }

        if (found) {
            int year = currentDate.mid(12, 4).toInt();
            QString strMonth = currentDate.mid(8, 3);
            QVector<QString> months = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
            int month;
            if (months.contains(strMonth)) {
                month = months.indexOf(strMonth) + 1;
            }
            int day = strMonth.mid(5, 2).toInt();
            QDate sDate(year, month, day);
            QDate eDate = QDate::fromString(endDate, "yyyy-MM-dd");
            if (sDate <= eDate) {
                emit onUserCheckResult(RESULT_SUCCESS, eDate);
            } else {
                emit onUserCheckResult(RESULT_TIME_OUT, eDate);
            }
        } else {
            emit onUserCheckResult(RESULT_NOT_REGISTERED, QDate());
        }
    } else {
        emit onUserCheckResult(RESULT_FAILED, QDate());
    }
    pUserReply->deleteLater();
}

void UserManager::onNetworkDateFinished()
{
    if (pDateReply->error() == QNetworkReply::NoError) {
        QByteArray respose = pDateReply->readAll();
        //将响应解析为json
        QJsonParseError parseError;
        QJsonDocument jsonDoc = QJsonDocument::fromJson(respose, &parseError);
        if (parseError.error != QJsonParseError::NoError) {
            qDebug() << "onNetworkDateFinished: JSON解析错误：" << parseError.errorString();
            return;
        }
        QJsonObject obj = jsonDoc.object();
        QString dateStr = obj.value("sysTime2").toString().split(" ").at(0);
        qDebug() << "dateStr=" << dateStr;
        QStringList dateList = dateStr.split("-");

        QDate date;
        //QString dateStr = timeStr.split(" ").at(0);
        //date.setDate(dateStr.split("-").at(0), dateStr.split(i))
    } else {
        qDebug() << "onNetworkDateFinished: reply network date failed:" << pDateReply->errorString();
    }
    pDateReply->deleteLater();
}
