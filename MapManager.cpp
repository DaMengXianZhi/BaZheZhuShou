#include "MapManager.h"
#include <QDebug>

MapManager::MapManager()
{
    isNewZone = true;
}

MapManager::~MapManager()
{

}

void MapManager::setNewZone(bool newZone)
{
    isNewZone = newZone;
}

QStringList MapManager::getDengJiBossMapList(int grade)
{
    QStringList list;
    switch (grade) {
    case 450:
        list = {"星云秘境2", "星云秘境1", "蛮荒海岛2", "蛮荒海岛1", "骷髅墓穴2", "骷髅墓穴1"};
        break;
    case 500:
        list = {"骷髅墓穴1", "骷髅墓穴2", "牛魔墓穴2", "牛魔墓穴1", "雷炎墓穴2", "雷炎墓穴1"};
        break;
    case 550:
        list = {"天海雪原1", "天海雪原2", "寻龙墓穴1", "寻龙墓穴2", "星空秘境2", "星空秘境1"};
        break;
    case 600:
        if (isNewZone) {
            list = {"寻龙墓穴2", "寻龙墓穴1", "星空秘境2", "星空秘境1", "海岛秘境1", "海岛秘境2"};
        } else {
            list = {"寻龙墓穴1", "星空秘境1", "海岛秘境1", "骷髅地牢1", "业火炼狱1", "葬龙陵墓1"};
        }
        break;
    case 650:
        if (isNewZone) {
            list = {"海岛秘境1", "海岛秘境2", "骷髅地牢2", "骷髅地牢1", "业火炼狱2", "业火炼狱1"};
        } else {
            list = {"海岛秘境1", "骷髅地牢1", "业火炼狱1", "葬龙陵墓1", "混沌地牢1", "魔龙秘境2"};
        }
        break;
    case 700:
        if (isNewZone) {
            list = {"业火炼狱2", "业火炼狱1", "葬龙陵墓1", "葬龙陵墓2", "混沌地牢1", "混沌地牢2"};
        } else {
            list = {"业火炼狱1", "葬龙陵墓1", "混沌地牢1", "魔龙秘境1", "魔龙秘境2", "狂暴魂殿2"};
        }
        break;
    case 750:
        if (isNewZone) {
            list = {"葬龙陵墓2", "葬龙陵墓1", "混沌地牢1", "混沌地牢2", "魔龙秘境2", "魔龙秘境1"};
        } else {
            list = {"葬龙陵墓1", "混沌地牢1", "魔龙秘境1", "魔龙秘境2", "狂暴魂殿1", "狂暴魂殿2"};
        }
        break;
    case 800:
        if (isNewZone) {
            list = {"魔龙秘境1", "魔龙秘境2", "狂暴魂殿2", "狂暴魂殿1", "云中圣地2", "云中圣地1"};
        } else {
            list = {"魔龙秘境1", "魔龙秘境2", "狂暴魂殿2", "狂暴魂殿1", "云中圣地2", "云中圣地1"};
        }
        break;
    case 850:
        list = {"云中圣地1", "云中圣地2", "幽冥圣域1", "幽冥圣域2", "魔域魂殿2", "魔域魂殿1"};
        break;
    case 900:
        list = {"幽冥圣域1", "幽冥圣域2", "魔域魂殿2", "魔域魂殿1", "神魔陵墓2", "神魔陵墓1"};
        break;
    case 950:
        list = {"神魔陵墓1", "神魔陵墓2", "天云秘境2", "天云秘境1", "暗影洞穴1", "暗影洞穴2"};
        break;
    case 1000:
        list = {"暗影洞穴1", "暗影洞穴2", "暗黑地牢1", "暗黑地牢2", "黑暗墓室1", "黑暗墓室2"};
        break;
    case 1050:
        list = {"暗黑地牢2", "暗黑地牢1", "黑暗墓室1", "黑暗墓室2", "石墓地窟2", "石墓地窟1", "*暗色殿堂1", "暗色殿堂2"};
        break;
    case 1100:
        list = {"烈焰之地1-跨服", "烈焰之地2-跨服", "血色秘境1-跨服", "血色秘境2-跨服", "火山地窟2-跨服", "火山地窟1-跨服"};
        break;
    case 1150:
        list = {"血色秘境1-跨服", "血色秘境2-跨服", "火山地窟1-跨服", "火山地窟2-跨服", "熔岩魔洞1-跨服", "熔岩魔洞2-跨服"};
        break;
    case 1200:
        list = {"火山地窟1-跨服", "火山地窟2-跨服", "熔岩魔洞2-跨服", "熔岩魔洞1-跨服"};
        break;
    default:
        list = {NULL};
        break;
    }
    return list;
}

QStringList MapManager::getDouLiBossMapList(int grade)
{
    QStringList list;
    switch (grade) {
    case 100:
        list = {"死亡深渊1", "死亡深渊2", "死亡深渊3"};
        break;
    case 150:
        list = {"死亡深渊2", "死亡深渊3", "死亡深渊4"};
        break;
    case 200:
        list = {"死亡深渊3", "死亡深渊4", "死亡深渊5"};
        break;
    case 250:
        list = {"死亡深渊4", "死亡深渊5", "死亡深渊6"};
        break;
    case 300:
        list = {"死亡深渊4", "死亡深渊5", "死亡深渊6", "死亡深渊7", "死亡深渊8", "死亡深渊9"};
        break;
    case 350:
        list = {"死亡深渊5", "死亡深渊6", "死亡深渊7", "死亡深渊8", "死亡深渊9", "死亡深渊10"};
        break;
    case 400:
        list = {"死亡深渊6", "死亡深渊7", "死亡深渊8", "死亡深渊9", "死亡深渊10", "死亡深渊11"};
        break;
    case 450:
        list = {"死亡深渊8", "死亡深渊9", "死亡深渊10", "死亡深渊11", "死亡深渊12", "死亡深渊13"};
        break;
    case 500:
        list = {"死亡深渊10", "死亡深渊11", "死亡深渊12", "死亡深渊13", "死亡深渊14", "死亡深渊15"};
        break;
    case 550:
        list = {"死亡深渊13", "死亡深渊14", "死亡深渊15", "死亡深渊16", "死亡深渊17", "死亡深渊18"};
        break;
    case 600:
        if (isNewZone) {
            list = {"死亡深渊14", "死亡深渊15", "死亡深渊16", "死亡深渊17", "死亡深渊18", "死亡深渊19"};
        } else {
            list = {"死亡深渊19", "死亡深渊20"};
        }
        break;
    case 650:
        if (isNewZone) {
            list = {"死亡深渊16", "死亡深渊17", "死亡深渊18", "死亡深渊19", "死亡深渊20", "死亡深渊21"};
        } else {
            list = {"死亡深渊19", "死亡深渊20", "死亡深渊21"};
        }
        break;
    case 700:
        if (isNewZone) {
            list = {"死亡深渊18", "死亡深渊19", "死亡深渊20", "死亡深渊21", "死亡深渊22", "死亡深渊23"};
        } else {
            list = {"死亡深渊19", "死亡深渊20", "死亡深渊21", "死亡深渊22"};
        }
        break;
    case 750:
        list = {"死亡深渊19", "死亡深渊20", "死亡深渊21", "死亡深渊22", "死亡深渊23", "死亡深渊24"};
        break;
    case 800:
        list = {"死亡深渊21", "死亡深渊22", "死亡深渊23", "死亡深渊24", "死亡深渊25"};
        break;
    case 850:
        list = {"死亡深渊23", "死亡深渊24", "死亡深渊25", "死亡深渊26", "死亡深渊27"};
        break;
    case 900:
        list = {"死亡深渊24", "死亡深渊25", "死亡深渊26", "死亡深渊27", "死亡深渊28"};
        break;
    case 950:
        list = {"死亡深渊25", "死亡深渊26", "死亡深渊27", "死亡深渊28", "死亡深渊29"};
        break;
    case 1000:
        list = {"死亡深渊27", "死亡深渊28", "死亡深渊29", "死亡深渊30", "死亡深渊31-跨服"};
        break;
    case 1050:
        list = {"死亡深渊28", "死亡深渊29", "死亡深渊30", "死亡深渊31-跨服", "死亡深渊32-跨服"};
        break;
    case 1100:
        list = {"死亡深渊31-跨服", "死亡深渊32-跨服", "死亡深渊33-跨服"};
        break;
    case 1150:
        list = {"死亡深渊32-跨服", "死亡深渊33-跨服", "死亡深渊34-跨服"};
        break;
    case 1200:
        list = {"死亡深渊33-跨服", "死亡深渊34-跨服"};
        break;
    default:
        list = {NULL};
        break;
    }
    return list;
}

QStringList MapManager::getHuDunBossMapList(int grade)
{
    QStringList list;
    switch (grade) {
    case 100:
        list = {"神魔遗迹1", "神魔遗迹2", "神魔遗迹3"};
        break;
    case 150:
        list = {"神魔遗迹2", "神魔遗迹3", "神魔遗迹4"};
        break;
    case 200:
        list = {"神魔遗迹3", "神魔遗迹4", "神魔遗迹5"};
        break;
    case 250:
        list = {"神魔遗迹4", "神魔遗迹5", "神魔遗迹6"};
        break;
    case 300:
        list = {"神魔遗迹4", "神魔遗迹5", "神魔遗迹6", "神魔遗迹7", "神魔遗迹8", "神魔遗迹9"};
        break;
    case 350:
        list = {"神魔遗迹5", "神魔遗迹6", "神魔遗迹7", "神魔遗迹8", "神魔遗迹9", "神魔遗迹10"};
        break;
    case 400:
        list = {"神魔遗迹6", "神魔遗迹7", "神魔遗迹8", "神魔遗迹9", "神魔遗迹10", "神魔遗迹11"};
        break;
    case 450:
        list = {"神魔遗迹8", "神魔遗迹9", "神魔遗迹10", "神魔遗迹11", "神魔遗迹12", "神魔遗迹13"};
        break;
    case 500:
        list = {"神魔遗迹10", "神魔遗迹11", "神魔遗迹12", "神魔遗迹13", "神魔遗迹14", "神魔遗迹15"};
        break;
    case 550:
        list = {"神魔遗迹13", "神魔遗迹14", "神魔遗迹15", "神魔遗迹16", "神魔遗迹17", "神魔遗迹18"};
        break;
    case 600:
        if (isNewZone) {
            list = {"神魔遗迹14", "神魔遗迹15", "神魔遗迹16", "神魔遗迹17", "神魔遗迹18", "神魔遗迹19"};
        } else {
            list = {"神魔遗迹19", "神魔遗迹20"};
        }
        break;
    case 650:
        if (isNewZone) {
            list = {"神魔遗迹16", "神魔遗迹17", "神魔遗迹18", "神魔遗迹19", "神魔遗迹20", "神魔遗迹21"};
        } else {
            list = {"神魔遗迹19", "神魔遗迹20", "神魔遗迹21"};
        }
        break;
    case 700:
        if (isNewZone) {
            list = {"神魔遗迹18", "神魔遗迹19", "神魔遗迹20", "神魔遗迹21", "神魔遗迹22", "神魔遗迹23"};
        } else {
            list = {"神魔遗迹19", "神魔遗迹20", "神魔遗迹21", "神魔遗迹22", "神魔遗迹23"};
        }
        break;
    case 750:
        list = {"神魔遗迹19", "神魔遗迹20", "神魔遗迹21", "神魔遗迹22", "神魔遗迹23", "神魔遗迹24"};
        break;
    case 800:
        list = {"神魔遗迹21", "神魔遗迹22", "神魔遗迹23", "神魔遗迹24", "神魔遗迹25"};
        break;
    case 850:
        list = {"神魔遗迹23", "神魔遗迹24", "神魔遗迹25", "神魔遗迹26", "神魔遗迹27"};
        break;
    case 900:
        list = {"神魔遗迹24", "神魔遗迹25", "神魔遗迹26", "神魔遗迹27", "神魔遗迹28"};
        break;
    case 950:
        list = {"神魔遗迹25", "神魔遗迹26", "神魔遗迹27", "神魔遗迹28", "神魔遗迹29"};
        break;
    case 1000:
        list = {"神魔遗迹27", "神魔遗迹28", "神魔遗迹29", "神魔遗迹30", "神魔遗迹31-跨服"};
        break;
    case 1050:
        list = {"神魔遗迹28", "神魔遗迹29", "神魔遗迹30", "神魔遗迹31-跨服", "神魔遗迹32-跨服"};
        break;
    case 1100:
        list = {"神魔遗迹31-跨服", "神魔遗迹32-跨服", "神魔遗迹33-跨服"};
        break;
    case 1150:
        list = {"神魔遗迹32-跨服", "神魔遗迹33-跨服", "神魔遗迹34-跨服"};
        break;
    case 1200:
        list = {"神魔遗迹33-跨服", "神魔遗迹34-跨服"};
        break;
    default:
        list = {NULL};
        break;
    }
    return list;
}

QStringList MapManager::getXingZuoBossMapList(int grade)
{
    QStringList list;
    switch (grade) {
    case 100:
        list = {"星座秘境1", "星座秘境2"};
        break;
    case 150:
        list = {"星座秘境1", "星座秘境2", "星座秘境3"};
        break;
    case 200:
        list = {"星座秘境1", "星座秘境2", "星座秘境3", "星座秘境4"};
        break;
    case 250:
        list = {"星座秘境2", "星座秘境3", "星座秘境4", "星座秘境5"};
        break;
    case 300:
        list = {"星座秘境3", "星座秘境4", "星座秘境5"};
        break;
    case 350:
        list = {"星座秘境4", "星座秘境5", "星座秘境6", "星座秘境7"};
        break;
    case 400:
        list = {"星座秘境5", "星座秘境6", "星座秘境7", "星座秘境8"};
        break;
    case 450:
        list = {"星座秘境6", "星座秘境7", "星座秘境8", "星座秘境9"};
        break;
    case 500:
        list = {"星座秘境7", "星座秘境8", "星座秘境9", "星座秘境10"};
        break;
    case 550:
        list = {"星座秘境8", "星座秘境9", "星座秘境10", "星座秘境11"};
        break;
    case 600:
        list = {"星座秘境9", "星座秘境10", "星座秘境11", "星座秘境12"};
        break;
    case 650:
        list = {"星座秘境10", "星座秘境11", "星座秘境12", "星座秘境13"};
        break;
    case 700:
        list = {"星座秘境11", "星座秘境12", "星座秘境13", "星座秘境14"};
        break;
    case 750:
        if (isNewZone) {
            list = {"星座秘境12", "星座秘境13", "星座秘境14", "星座秘境15"};
        } else {
            list = {"星座秘境15"};
        }
        break;
    case 800:
        if (isNewZone) {
            list = {"星座秘境13", "星座秘境14", "星座秘境15", "星座秘境16"};
        } else {
            list = {"星座秘境15", "星座秘境16"};
        }
        break;
    case 850:
        if (isNewZone) {
            list = {"星座秘境14", "星座秘境15", "星座秘境16", "星座秘境17"};
        } else {
            list = {"星座秘境15", "星座秘境16", "星座秘境17"};
        }
        break;
    case 900:
        list = {"星座秘境15", "星座秘境16", "星座秘境17", "星座秘境18"};
        break;
    case 950:
        list = {"星座秘境16", "星座秘境17", "星座秘境18", "星座秘境19"};
        break;
    case 1000:
        list = {"星座秘境17", "星座秘境18", "星座秘境19", "星座秘境20"};
        break;
    case 1050:
        list = {"星座秘境18", "星座秘境19", "星座秘境20", "星座秘境21-跨服"};
        break;
    case 1100:
        list = {"星座秘境21-跨服", "星座秘境22-跨服"};
        break;
    case 1150:
        list = {"星座秘境21-跨服", "星座秘境22-跨服"};
        break;
    case 1200:
        list = {"星座秘境22-跨服"};
        break;
    default:
        list = {NULL};
        break;
    }
    return list;
}

QStringList MapManager::getJinShenBossMapList(int grade)
{
    QStringList list;
    switch (grade) {
    case 2000:
        list = {"暗影魔渊1", "铁血魔宫1", "禁忌之地1", "混沌废墟1", "铁血魔宫2"};
        break;
    case 2050:
        list = {"混沌废墟1", "暗影魔渊1", "禁忌之地1", "暗影魔渊2", "禁忌之地2", "铁血魔宫2"};
        break;
    case 2100:
        list = {"混沌废墟1", "禁忌之地1", "暗影魔渊2", "禁忌之地2", "混沌废墟2", "暗影魔渊3"};
        break;
    case 2150:
        list = {"混沌废墟2", "禁忌之地2", "暗影魔渊3", "禁忌之地3", "混沌废墟3", "铁血魔宫4"};
        break;
    case 2200:
        list = {"禁忌之地3", "混沌废墟3", "禁忌之地4", "混沌废墟4", "铁血魔宫5", "铁血魔宫6"};
        break;
    case 2250:
        list = {"禁忌之地3", "禁忌之地4", "混沌废墟4", "禁忌之地5", "铁血魔宫6", "铁血魔宫7"};
        break;
    case 2300:
        list = {"禁忌之地4", "暗影魔渊5", "禁忌之地5", "混沌废墟5", "禁忌之地6", "铁血魔宫7"};
        break;
    case 2350:
        list = {"暗影魔渊5", "混沌废墟5", "禁忌之地5", "混沌废墟6", "禁忌之地6", "铁血魔宫8"};
        break;
    case 2400:
        list = {"暗影魔渊6", "禁忌之地6", "混沌废墟6", "禁忌之地7", "铁血魔宫9", "铁血魔宫10"};
        break;
    case 2450:
        list = {"暗影魔渊6", "混沌废墟6", "禁忌之地7", "混沌废墟7", "铁血魔宫10", "铁血魔宫11"};
        break;
    case 2500:
        list = {"禁忌之地7", "暗影魔渊7", "混沌废墟7", "禁忌之地8", "铁血魔宫11", "铁血魔宫12-跨服"};
        break;
    case 2550:
        list = {"混沌废墟7", "暗影魔渊7", "禁忌之地8", "混沌废墟8", "铁血魔宫12-跨服", "铁血魔宫13-跨服"};
        break;
    case 2600:
        list = {"暗影魔渊8", "混沌废墟8", "禁忌之地8", "禁忌之地9", "铁血魔宫13-跨服", "铁血魔宫14-跨服"};
        break;
    case 2650:
        list = {"混沌废墟8", "暗影魔渊8", "禁忌之地9", "混沌废墟9", "铁血魔宫14-跨服", "铁血魔宫15-跨服"};
        break;
    case 2700:
        list = {"暗影魔渊9", "禁忌之地9", "混沌废墟9", "禁忌之地10", "铁血魔宫15-跨服", "铁血魔宫16-跨服"};
        break;
    case 2750:
        list = {"禁忌之地10"};
        break;
    default:
        list = {NULL};
        break;
    }
    return list;
}

QStringList MapManager::getYouMingBossMapList(int grade)
{
    QStringList list;
    switch (grade) {
    case 800:
        list = {"冥界-入口", "冥界1"};
        break;
    case 850:
        list = {"冥界-入口", "冥界1", "冥界2"};
        break;
    case 900:
        list = {"冥界1", "冥界2", "冥界3"};
        break;
    case 950:
        list = {"冥界2", "冥界3", "冥界4"};
        break;
    case 1000:
        list = {"冥界3", "冥界4", "冥界5"};
        break;
    case 1050:
        list = {"冥界4", "冥界5", "冥界6"};
        break;
    case 1100:
        list = {"冥界5", "冥界6", "冥界7"};
        break;
    case 1150:
        list = {"冥界6", "冥界7", "冥界8"};
        break;
    case 1200:
        list = {"冥界7", "冥界8", "冥界9"};
        break;
    case 1250:
        list = {"冥界8", "冥界9", "冥界10-跨服"};
        break;
    case 1300:
        list = {"冥界9", "冥界10-跨服", "冥界11-跨服"};
        break;
    case 1350:
        list = {"冥界10-跨服", "冥界11-跨服", "冥界12-跨服"};
        break;
    case 1400:
        list = {"冥界11-跨服", "冥界12-跨服"};
        break;
    case 1450:
        list = {"冥界12-跨服"};
        break;
    default:
        list = {NULL};
        break;
    }
    return list;
}

QStringList MapManager::getXunLongBossMapList(int grade)
{
    QStringList list;
    switch (grade) {
    case 900:
        list = {"魔龙崖1"};
        break;
    case 950:
        list = {"魔龙崖1", "魔龙崖2"};
        break;
    case 1000:
        list = {"魔龙崖1", "魔龙崖2", "魔龙崖3"};
        break;
    case 1050:
        list = {"魔龙崖2", "魔龙崖3", "魔龙崖4"};
        break;
    case 1100:
        list = {"魔龙崖3", "魔龙崖4", "魔龙崖5"};
        break;
    case 1150:
        list = {"魔龙崖4", "魔龙崖5", "魔龙崖6"};
        break;
    case 1200:
        list = {"魔龙崖5", "魔龙崖6", "魔龙崖7"};
        break;
    case 1250:
        list = {"魔龙崖6", "魔龙崖7", "魔龙崖8"};
        break;
    case 1300:
        list = {"魔龙崖7", "魔龙崖8", "魔龙崖9"};
        break;
    case 1350:
        list = {"魔龙崖8", "魔龙崖9", "魔龙崖10"};
        break;
    case 1400:
        list = {"魔龙崖9", "魔龙崖10", "魔龙崖11"};
        break;
    case 1450:
        list = {"魔龙崖10", "魔龙崖11", "魔龙崖12-跨服"};
        break;
    case 1500:
        list = {"魔龙崖11", "魔龙崖12-跨服", "魔龙崖13-跨服"};
        break;
    case 1550:
        list = {"魔龙崖12-跨服", "魔龙崖13-跨服", "魔龙崖14-跨服"};
        break;
    case 1600:
        list = {"魔龙崖13-跨服", "魔龙崖14-跨服"};
        break;
    default:
        list = {NULL};
        break;
    }
    return list;
}

QStringList MapManager::getShenMoBossMapList(int grade)
{
    QStringList list;
    switch (grade) {
    case 2000:
        list = {"神魔废墟1", "炼狱秘境1", "神魔废墟2"};
        break;
    case 2050:
        list = {"炼狱秘境1", "神魔废墟2", "炼狱秘境2", "神魔废墟3"};
        break;
    case 2100:
        list = {"炼狱秘境1", "炼狱秘境2", "炼狱秘境3", "神魔废墟4", "神魔废墟5"};
        break;
    case 2150:
        list = {"炼狱秘境2", "炼狱秘境3", "炼狱秘境4", "神魔废墟5", "神魔废墟6"};
        break;
    case 2200:
        list = {"炼狱秘境3", "炼狱秘境4", "炼狱秘境5", "神魔废墟6", "神魔废墟7"};
        break;
    case 2250:
        list = {"炼狱秘境4", "炼狱秘境5", "神魔废墟7", "神魔废墟8"};
        break;
    case 2300:
        list = {"炼狱秘境5", "炼狱秘境6", "神魔废墟8", "神魔废墟9"};
        break;
    case 2350:
        list = {"炼狱秘境5", "炼狱秘境6", "炼狱秘境7-跨服", "神魔废墟9", "神魔废墟10-跨服"};
        break;
    case 2400:
        list = {"炼狱秘境6", "炼狱秘境7-跨服", "炼狱秘境8-跨服", "神魔废墟10-跨服"};
        break;
    case 2450:
        list = {"炼狱秘境6", "炼狱秘境7-跨服", "炼狱秘境8-跨服", "神魔废墟10-跨服", "神魔废墟11-跨服"};
        break;
    case 2500:
        list = {"炼狱秘境7-跨服", "炼狱秘境8-跨服", "炼狱秘境9-跨服", "神魔废墟11-跨服"};
        break;
    case 2550:
        list = {"炼狱秘境8-跨服", "炼狱秘境9-跨服", "神魔废墟11-跨服", "神魔废墟12-跨服"};
        break;
    case 2600:
        list = {"炼狱秘境9-跨服", "炼狱秘境10-跨服", "神魔废墟12-跨服", "神魔废墟13-跨服"};
        break;
    case 2650:
        list = {"炼狱秘境9-跨服", "炼狱秘境10-跨服", "神魔废墟13-跨服", "神魔废墟14-跨服"};
        break;
    case 2700:
        list = {"炼狱秘境10-跨服", "炼狱秘境11-跨服", "神魔废墟12-跨服", "神魔废墟14-跨服"};
        break;
    case 2750:
        list = {"炼狱秘境10-跨服", "炼狱秘境11-跨服", "炼狱秘境12-跨服", "神魔废墟14-跨服", "神魔废墟15-跨服"};
        break;
    case 2800:
        list = {"炼狱秘境11-跨服", "炼狱秘境12-跨服", "神魔废墟15-跨服"};
        break;
    default:
        list = {NULL};
        break;
    }
    return list;
}

QList<int> MapManager::getDengJiBossMapParameter(QString name, int top1, int top2, int top3)
{
    qDebug() << "getDengJiBossMapParameter: name=" << name << ", top1:" << top1 << ", top2:" << top2 << ", top3:" << top3;
    QList<int> list;
    QStringList mapList;
    bool found = false;
    int tableIndex = 0;
    if (top1 > 0) {
        mapList = getDengJiBossMapList(top1);
        for (int i = 0; i < mapList.size(); i++, tableIndex++) {
            if (mapList.at(i).startsWith("*")) {
                tableIndex = 6;
            }
            if (mapList.at(i) == name) {
                found = true;
                list << 0 << tableIndex;
                break;
            }
        }
    }
    if (!found && top2 > 0) {
        tableIndex = 0;
        mapList = getDengJiBossMapList(top2);
        for (int i = 0; i < mapList.size(); i++, tableIndex++) {
            if (mapList.at(i).startsWith("*")) {
                tableIndex = 6;
            }
            if (mapList.at(i) == name) {
                found = true;
                list << 1 << i;
                break;
            }
        }
    }
    if (!found && top3 > 0) {
        tableIndex = 0;
        mapList = getDengJiBossMapList(top3);
        for (int i = 0; i < mapList.size(); i++, tableIndex++) {
            if (mapList.at(i).startsWith("*")) {
                tableIndex = 6;
            }
            if (mapList.at(i) == name) {
                found = true;
                list << 2 << i;
                break;
            }
        }
    }
    if (found) {
        int num;
        if (name.endsWith("跨服")) {
            num = name.mid(4, name.length()-7).toInt() -1;
        } else {
            if (name.startsWith("*")) {
                num = name.mid(5, name.length() - 5).toInt() -1;
            } else {
                num = name.mid(4, name.length() - 4).toInt() -1;
            }
        }
        list << num;
    }
    return list;
}

QList<int> MapManager::getDouLiBossMapParameter(QString name, int top1, int top2, int top3)
{
    qDebug() << "getDouLiBossMapParameter: name=" << name << ", top1:" << top1 << ", top2:" << top2 << ", top3:" << top3;
    QList<int> list;
    QStringList mapList;
    bool found = false;
    if (top1 > 0) {
        mapList = getDouLiBossMapList(top1);
        for (int i = 0; i < mapList.size(); i++) {
            if (mapList.at(i) == name) {
                found = true;
                list << 0 << i;
                break;
            }
        }
    }
    if (!found && top2 > 0) {
        mapList = getDouLiBossMapList(top2);
        for (int i = 0; i < mapList.size(); i++) {
            if (mapList.at(i) == name) {
                found = true;
                list << 1 << i;
                break;
            }
        }
    }
    if (!found && top3 > 0) {
        mapList = getDouLiBossMapList(top3);
        for (int i = 0; i < mapList.size(); i++) {
            if (mapList.at(i) == name) {
                found = true;
                list << 2 << i;
                break;
            }
        }
    }
    if (found) {
        int num;
        if (name.endsWith("跨服")) {
            //跨服
            num = name.mid(4, name.length()-7).toInt();
        } else {
            //本区
            num = name.mid(4, name.length() - 4).toInt();
        }
        if (num < 6) {
            list << num - 1;
        } else if (num > 5 && num < 11) {
            list << num - 6;
        } else if (num > 10 && num < 15) {
            list << num - 11;
        } else if (num > 14 && num < 19) {
            list << num - 15;
        } else if (num > 18 && num < 23) {
            list << num - 19;
        } else if (num > 22 && num < 27) {
            list << num - 23;
        } else if (num > 26 && num < 31) {
            list << num - 27;
        } else if (num > 30 && num < 35) {
            list << num - 31;
        }
    }
    return list;
}

QList<int> MapManager::getHuDunBossMapParameter(QString name, int top1, int top2, int top3)
{
    qDebug() << "getHuDunBossMapParameter: name=" << name << ", top1:" << top1 << ", top2:" << top2 << ", top3:" << top3;
    QList<int> list;
    QStringList mapList;
    bool found = false;
    if (top1 > 0) {
        mapList = getHuDunBossMapList(top1);
        for (int i = 0; i < mapList.size(); i++) {
            if (mapList.at(i) == name) {
                found = true;
                list << 0 << i;
                break;
            }
        }
    }
    if (!found && top2 > 0) {
        mapList = getHuDunBossMapList(top2);
        for (int i = 0; i < mapList.size(); i++) {
            if (mapList.at(i) == name) {
                found = true;
                list << 1 << i;
                break;
            }
        }
    }
    if (!found && top3 > 0) {
        mapList = getHuDunBossMapList(top3);
        for (int i = 0; i < mapList.size(); i++) {
            if (mapList.at(i) == name) {
                found = true;
                list << 2 << i;
                break;
            }
        }
    }
    int num;
    if (name.endsWith("跨服")) {
        //跨服
        num = name.mid(4, name.length()-7).toInt();
    } else {
        //本区
        num = name.mid(4, name.length() - 4).toInt();
    }
    if (num < 6) {
        list << num - 1;
    } else if (num > 5 && num < 11) {
        list << num - 6;
    } else if (num > 10 && num < 15) {
        list << num - 11;
    } else if (num > 14 && num < 19) {
        list << num - 15;
    } else if (num > 18 && num < 23) {
        list << num - 19;
    } else if (num > 22 && num < 27) {
        list << num - 23;
    } else if (num > 26 && num < 31) {
        list << num - 27;
    } else if (num > 30 && num < 35) {
        list << num - 31;
    }
    return list;
}

QList<int> MapManager::getXingZuoBossMapParameter(QString name, int top1, int top2, int top3)
{
    qDebug() << "getXingZuoBossMapParameter: name=" << name << ", top1:" << top1 << ", top2:" << top2 << ", top3:" << top3;
    QList<int> list;
    QStringList mapList;
    bool found = false;
    if (top1 > 0) {
        mapList = getXingZuoBossMapList(top1);
        for (int i = 0; i < mapList.size(); i++) {
            if (mapList.at(i) == name) {
                found = true;
                list << 0 << i;
                break;
            }
        }
    }
    if (!found && top2 > 0) {
        mapList = getXingZuoBossMapList(top2);
        for (int i = 0; i < mapList.size(); i++) {
            if (mapList.at(i) == name) {
                found = true;
                list << 1 << i;
                break;
            }
        }
    }
    if (!found && top3 > 0) {
        mapList = getXingZuoBossMapList(top3);
        for (int i = 0; i < mapList.size(); i++) {
            if (mapList.at(i) == name) {
                found = true;
                list << 2 << i;
                break;
            }
        }
    }
    if (found) {
        int num;
        if (name.endsWith("跨服")) {
            //跨服
            num = name.mid(4, name.length()-7).toInt();
        } else {
            //本区
            num = name.mid(4, name.length() - 4).toInt();
        }
        if (num < 5) {
            list << num - 1;
        } else if (num > 4 && num < 9) {
            list << num - 5;
        } else if (num > 8 && num < 12) {
            list << num - 9;
        } else if (num > 11 && num < 15) {
            list << num - 12;
        } else if (num > 14 && num < 17) {
            list << num - 15;
        } else if (num > 16 && num < 19) {
            list << num - 17;
        } else if (num > 18 && num < 21) {
            list << num - 19;
        } else if (num > 20 && num < 23) {
            list << num - 21;
        }
    }
    return list;
}

QList<int> MapManager::getJinShenBossMapParameter(QString name, int top1, int top2, int top3)
{
    qDebug() << "getJinShenBossMapParameter: name=" << name << ", top1:" << top1 << ", top2:" << top2 << ", top3:" << top3;
    QList<int> list;
    QStringList mapList;
    bool found = false;
    if (top1 > 0) {
        mapList = getJinShenBossMapList(top1);
        for (int i = 0; i < mapList.size(); i++) {
            if (mapList.at(i) == name) {
                found = true;
                list << 0 << i;
                break;
            }
        }
    }
    if (!found && top2 > 0) {
        mapList = getJinShenBossMapList(top2);
        for (int i = 0; i < mapList.size(); i++) {
            if (mapList.at(i) == name) {
                found = true;
                list << 1 << i;
                break;
            }
        }
    }
    if (!found && top3 > 0) {
        mapList = getJinShenBossMapList(top3);
        for (int i = 0; i < mapList.size(); i++) {
            if (mapList.at(i) == name) {
                found = true;
                list << 2 << i;
                break;
            }
        }
    }
    if (found) {
        int num;
        if (name.endsWith("跨服")) {
            //跨服
            num = name.mid(4, name.length() - 7).toInt();
        } else {
            //本区
            num = name.mid(4, name.length() - 4).toInt();
        }

        if (num <= 10) {
            list << num - 1;
        } else if (num > 10 && num < 12) {
            list << num - 11;
        } else if (num >= 12) {
            list << num - 12;
        }
    }
    return list;
}

QList<int> MapManager::getYouMingBossMapParameter(QString name, int top1, int top2, int top3)
{
    qDebug() << "getYouMingBossMapParameter: name=" << name << ", top1:" << top1 << ", top2:" << top2 << ", top3:" << top3;
    QList<int> list;
    QStringList mapList;
    bool found = false;
    if (top1 > 0) {
        mapList = getYouMingBossMapList(top1);
        for (int i = 0; i < mapList.size(); i++) {
            if (mapList.at(i) == name) {
                found = true;
                list << 0 << i;
                break;
            }
        }
    }
    if (!found && top2 > 0) {
        mapList = getYouMingBossMapList(top2);
        for (int i = 0; i < mapList.size(); i++) {
            if (mapList.at(i) == name) {
                found = true;
                list << 1 << i;
                break;
            }
        }
    }
    if (!found && top3 > 0) {
        mapList = getYouMingBossMapList(top3);
        for (int i = 0; i < mapList.size(); i++) {
            if (mapList.at(i) == name) {
                found = true;
                list << 2 << i;
                break;
            }
        }
    }

    if (found) {
        int num;
        if (name.endsWith("跨服")) {
            //跨服
            num = name.mid(2, name.length() - 5).toInt();
        } else {
            //本区
            num = name.mid(2, name.length() - 2).toInt();
        }

        if (num < 10) {
            list << num - 1;
        } else {
            list << num - 10;
        }
    }

    return list;
}

QList<int> MapManager::getXunLongBossMapParameter(QString name, int top1, int top2, int top3)
{
    qDebug() << "getXunLongBossMapParameter: name=" << name << ", top1:" << top1 << ", top2:" << top2 << ", top3:" << top3;
    QList<int> list;
    QStringList mapList;
    bool found = false;
    if (top1 > 0) {
        mapList = getXunLongBossMapList(top1);
        for (int i = 0; i < mapList.size(); i++) {
            if (mapList.at(i) == name) {
                found = true;
                list << 0 << i;
                break;
            }
        }
    }
    if (!found && top2 > 0) {
        mapList = getXunLongBossMapList(top2);
        for (int i = 0; i < mapList.size(); i++) {
            if (mapList.at(i) == name) {
                found = true;
                list << 1 << i;
                break;
            }
        }
    }
    if (!found && top3 > 0) {
        mapList = getXunLongBossMapList(top3);
        for (int i = 0; i < mapList.size(); i++) {
            if (mapList.at(i) == name) {
                found = true;
                list << 2 << i;
                break;
            }
        }
    }
    if (found) {
        int num;
        if (name.endsWith("跨服")) {
            //跨服
            num = name.mid(3, name.length() - 6).toInt();
        } else {
            //本区
            num = name.mid(3, name.length() - 3).toInt();
        }

        if (num < 12) {
            list << num - 1;
        } else {
            list << num - 12;
        }
    }
    return list;
}

QList<int> MapManager::getShenMoBossMapPerameter(QString name, int top1, int top2, int top3)
{
    qDebug() << "getShenMoBossMapPerameter: name=" << name << ", top1:" << top1 << ", top2:" << top2 << ", top3:" << top3;
    QList<int> list;
    QStringList mapList;
    bool found = false;
    if (top1 > 0) {
        mapList = getShenMoBossMapList(top1);
        for (int i = 0; i < mapList.size(); i++) {
            if (mapList.at(i) == name) {
                found = true;
                list << 0 << i;
                break;
            }
        }
    }
    if (!found && top2 > 0) {
        mapList = getShenMoBossMapList(top2);
        for (int i = 0; i < mapList.size(); i++) {
            if (mapList.at(i) == name) {
                found = true;
                list << 1 << i;
                break;
            }
        }
    }
    if (!found && top3 > 0) {
        mapList = getShenMoBossMapList(top3);
        for (int i = 0; i < mapList.size(); i++) {
            if (mapList.at(i) == name) {
                found = true;
                list << 2 << i;
                break;
            }
        }
    }    if (found) {
        int num;
        if (name.endsWith("跨服")) {
            //炼狱秘境：7-12
            //神魔废墟：10-15
            num = name.mid(4, name.length()-7).toInt();
            if (name.startsWith("炼狱")) {
                num = num - 7;
            } else if (name.startsWith("神魔")) {
                num = num - 10;
            }
        } else {
            num = name.mid(4, name.length() - 4).toInt() -1;
        }
        list << num;
    }
    return list;
}
