#ifndef LOGIN_H
#define LOGIN_H

#include <QDialog>
#include <QDate>

#include "UserManager.h"
#include "MainWindow.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class LogIn;
}
QT_END_NAMESPACE

class LogIn : public QDialog
{
    Q_OBJECT

public:
    LogIn(QWidget *parent = nullptr);
    ~LogIn();

private:
    Ui::LogIn *ui;

    UserManager *pUserManager;
    MainWindow *pWindow;

private slots:
    void onResume();
    void onCopyButtonClicked();
    void onCheckButtonClicked();

    void onCheckResult(int code, QDate date);
};
#endif // LOGIN_H
