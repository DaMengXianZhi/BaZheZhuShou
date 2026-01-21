#ifndef USERMANAGER_H
#define USERMANAGER_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QDate>
#include <QString>

class UserManager : public QObject
{
    Q_OBJECT
public:
    explicit UserManager(QObject *parent = nullptr);

    QString getMachineCode();
    void checkUserMessage(int type, int zoneId);
    void getNetworkDate();

signals:
    void onUserCheckResult(int code, QDate date);
    void onNetworkDate(QDate date);

private:
    QNetworkAccessManager *pManager;
    QNetworkReply *pUserReply;
    QNetworkReply *pDateReply;
    QDate *pDate;
    int zoneId;

    void onUserCheckFinished();
    void onNetworkDateFinished();

};

#endif // USERMANAGER_H
