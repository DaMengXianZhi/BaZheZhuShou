#ifndef MAPMANAGER_H
#define MAPMANAGER_H

#include <QString>
#include <QStringList>
#include <QList>
#include <windows.h>

class MapManager
{
public:
    MapManager();
    ~MapManager();

    void setNewZone(bool newZone);

    QStringList getDengJiBossMapList(int grade);
    QStringList getDouLiBossMapList(int grade);
    QStringList getHuDunBossMapList(int grade);
    QStringList getXingZuoBossMapList(int grade);
    QStringList getJinShenBossMapList(int grade);
    QStringList getYouMingBossMapList(int grade);
    QStringList getXunLongBossMapList(int grade);
    QStringList getShenMoBossMapList(int grade);

    QList<int> getDengJiBossMapParameter(QString name, int top1, int top2, int top3);
    QList<int> getDouLiBossMapParameter(QString name, int top1, int top2, int top3);
    QList<int> getHuDunBossMapParameter(QString name, int top1, int top2, int top3);
    QList<int> getXingZuoBossMapParameter(QString name, int top1, int top2, int top3);
    QList<int> getJinShenBossMapParameter(QString name, int top1, int top2, int top3);
    QList<int> getYouMingBossMapParameter(QString name, int top1, int top2, int top3);
    QList<int> getXunLongBossMapParameter(QString name, int top1, int top2, int top3);
    QList<int> getShenMoBossMapPerameter(QString name, int top1, int top2, int top3);

private:
    bool isNewZone;
};

#endif // MAPMANAGER_H
