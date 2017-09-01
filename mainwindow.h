#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QPainter>
#include"data.h"
#include"fullmap.h"
#include<QKeyEvent>
#include<QPainter>
#include<QTimer>
#include"tank.h"
#include"missile.h"
#include"boss.h"
#include<QMessageBox>
#include<QCloseEvent>
#include<QLabel>

const int TIME_INTERVAL=70;
const int enemyTankNum=2;
const int playerTankNum=3;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

    enum GameStatus{game,pause,over};
    void initGame();
    void loadMapSeg();
    bool isAllDisappeared()const;

    //导弹相撞互相消失
    void missileMeetMissile();

    //判断游戏是否结束
    void isGameOver();
    int getGameStatus()const;

    //窗口右侧显示玩家信息
    void showPlayerInfo();

private slots:
    void paintEvent(QPaintEvent *event);
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);
    void timeFun();

    //信息一：启动界面，版本信息
    void showInformationMsg1();
    //信息二：操作提示
    void showInformationMsg2();
    //信息三：提示进入第一关
    void showInformationMsg3();
    //信息四：提示进入下一关
    void showInformationMsg4();
    //信息五：游戏中途终结提醒
    void showInformationMsg5();
    //信息六：与信息三一样
    void showInformationMsg6();


    //信息七：标签label：暂停消息
    void showInformationMsg7();
    void showInformationMsg8();

    //信息八：游戏通关结束信息提示
    void showInformationMsg9();


private:
    void setGameStatus(GameStatus status);//设置游戏状态
    GameStatus gameStatus;
    fullMap map;//实例化全地图

    QTimer *timer;
    QPainter paint;

    //窗口右侧显示信息控件
    //得分
    QLabel *label1,*label2;
    //剩余坦克数
    QLabel *label3,*label4;
    //关卡数
    QLabel *label5,*label6;
    //剩下生命数
    QLabel *label7,*label8;
    //暂停pause
    QLabel *label9;

    int playerTankNumTmp;

    //奖励：每过五关增加一条生命
    void bonusForLife();
    //每得五千分导弹威力翻倍
    void bonusForAttack();

};

#endif // MAINWINDOW_H
