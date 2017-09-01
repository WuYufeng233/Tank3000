#ifndef DATA_H
#define DATA_H

#define Row 13//13行13列
#define Col 13
#define PixWidth 60//图片尺寸
#define PixHeight 60
#define SegWidth 60//地图分块尺寸
#define SegHeight 60
#define Width 60*13//全地图尺寸
#define Height 60*13
#define MissileWidth 17
#define MissileHeight 17

class fullMap;
class Tank;
class Base;
class Missile;
class Boss;
#include<QList>
#include<QImage>

struct Glb
{
    fullMap *map;
    Tank *player;
    Boss *boss;

    //npc坦克
    QList<Tank*>enemytanks;

    QList<Missile*>playerMissiles;

    //地图块图片
    QImage images[5];
    //坦克图片上下左右的图片
    QImage playerTank[4];
    QImage enemyTank1[4];
    QImage enemyTank2[4];
    QImage enemyTank3[4];

    QImage missile;
    QImage bossPix;

    //玩家总得分
    int score;
    //三个点的坦克数
    int enemy1TanksNum;
    int enemy2TanksNum;
    int enemy3TanksNum;
    //已击毁敌方坦克总数
    int enemyTanksDestroyed;

    //玩家坦克生命数
    int playerTanksNum;

    //当前关卡数
    int stage;
    //总关卡数
    int stagesNum;
};
extern Glb glb;


#endif // DATA_H
