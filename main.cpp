#include "LogIn.h"

#include <QApplication>
#include <QFile>
#include <QTextStream>

// 自定义日志处理器
void customMessageHandler(QtMsgType type, const QMessageLogContext& context, const QString& msg) {
    // 获取时间戳
    QString timestamp = QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss.zzz");

    // 获取日志级别
    QString logLevel;
    switch (type) {
    case QtDebugMsg:
        logLevel = "DEBUG";
        break;
    case QtWarningMsg:
        logLevel = "WARNING";
        break;
    case QtCriticalMsg:
        logLevel = "CRITICAL";
        break;
    case QtFatalMsg:
        logLevel = "FATAL";
        break;
    }

    // 获取文件名、行号、函数名
    QString fileName = context.file;
    int lineNumber = context.line;
    QString functionName = context.function;

    // 格式化日志信息
    QString logMessage = QString("[%1] [%2] [%3:%4 - %5] %6")
                             .arg(timestamp)
                             .arg(logLevel)
                             .arg(fileName)
                             .arg(lineNumber)
                             .arg(functionName)
                             .arg(msg);

    // 输出到文件
    QFile logFile("logcat.txt");
    if (logFile.open(QIODevice::Append | QIODevice::Text)) {
        QTextStream out(&logFile);
        out << logMessage << Qt::endl; // 使用 Qt::endl
        logFile.close();
    }

    // 也可以将日志输出到控制台
    // qDebug() << logMessage;
}

void initLogFile() {
    // 输出到文件
    QFile logFile("logcat.txt");
    if (logFile.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate)) {
        QTextStream out(&logFile);
        out << "==========start==========" << Qt::endl; // 使用 Qt::endl
        logFile.close();
    }
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //初始化log文件
    initLogFile();
    //安装自定义的日志处理器
    qInstallMessageHandler(customMessageHandler);

    LogIn w;
    w.show();
    return a.exec();
}
