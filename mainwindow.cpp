#include "mainwindow.h"
#include<QRect>
#include<QPen>
#include<QTime>
#include<QDebug>
#include"math.h"
#include<windows.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    Sleep(1000);

    showInformationMsg1();
    showInformationMsg2();
    showInformationMsg3();

    //设置窗口名称
    setWindowTitle("Tank War");
    //设置窗口图标
    setWindowIcon(QIcon(":/new/icon/pixs/p1tankD.png"));

    QFont font;
    font.setPointSize(32);
    paint.setFont(font);
    paint.setPen(QColor(255,0,0));

    //初始化各个标签控件
    label1=new QLabel(this);
    label2=new QLabel(this);
    label3=new QLabel(this);
    label4=new QLabel(this);
    label5=new QLabel(this);
    label6=new QLabel(this);
    label7=new QLabel(this);
    label8=new QLabel(this);
    label9=new QLabel(this);

    //初始化玩家生命数
    glb.playerTanksNum=1;
    //初始化第一关的关卡数
    glb.stage=2;
    //初始化玩家生命数临时变量
    playerTankNumTmp=playerTankNum;
    //初始化总关卡数
    glb.stagesNum=20;
    //初始化全局结构体glb的成员
    initGame();

}

MainWindow::~MainWindow()
{
    timer->stop();
    delete timer;
}

void MainWindow::initGame()
{
    move(600,50);
    //初始化全局结构体
    glb.map=new fullMap();

    //初始化各种坦克的数量
    glb.enemy1TanksNum=1;
    glb.enemy2TanksNum=1;
    glb.enemy3TanksNum=1;

    glb.enemyTanksDestroyed=0;

    //加入玩家坦克
    glb.player=new Tank();
    //加入敌方坦克
    Tank *tmp=new Tank(0,0,Down,1,1);
    glb.enemytanks.append(tmp);
    tmp=new Tank(0,6,Down,2,1);
    glb.enemytanks.append(tmp);
    tmp=new Tank(0,12,Down,3,1);
    glb.enemytanks.append(tmp);
    //加入boss
    glb.boss=new Boss();

    //初始化图片
    glb.images[0].load(":/new/icon/pixs/1_1.png");
    glb.images[1].load(":/new/icon/pixs/2_1.png");
    glb.images[2].load(":/new/icon/pixs/3.png");
    glb.images[3].load(":/new/icon/pixs/4.png");
    glb.images[4].load(":/new/icon/pixs/5.png");

    glb.playerTank[0].load(":/new/icon/pixs/p1tankU.png");
    glb.playerTank[1].load(":/new/icon/pixs/p1tankD.png");
    glb.playerTank[2].load(":/new/icon/pixs/p1tankL.png");
    glb.playerTank[3].load(":/new/icon/pixs/p1tankR.png");

    glb.enemyTank1[0].load(":/new/icon/pixs/enemy1U.png");
    glb.enemyTank1[1].load(":/new/icon/pixs/enemy1D.png");
    glb.enemyTank1[2].load(":/new/icon/pixs/enemy1L.png");
    glb.enemyTank1[3].load(":/new/icon/pixs/enemy1R.png");

    glb.enemyTank2[0].load(":/new/icon/pixs/enemy2U.png");
    glb.enemyTank2[1].load(":/new/icon/pixs/enemy2D.png");
    glb.enemyTank2[2].load(":/new/icon/pixs/enemy2L.png");
    glb.enemyTank2[3].load(":/new/icon/pixs/enemy2R.png");

    glb.enemyTank3[0].load(":/new/icon/pixs/enemy3U.png");
    glb.enemyTank3[1].load(":/new/icon/pixs/enemy3D.png");
    glb.enemyTank3[2].load(":/new/icon/pixs/enemy3L.png");
    glb.enemyTank3[3].load(":/new/icon/pixs/enemy3R.png");

    glb.missile.load(":/new/icon/pixs/tankMissile.png");
    glb.bossPix.load(":/new/icon/pixs/boss.png");

    //加载地图块
    loadMapSeg();

    gameStatus=game;

    timer=new QTimer(this);
    timer->setInterval(TIME_INTERVAL);
    connect(timer,SIGNAL(timeout()),this,SLOT(timeFun()));
    timer->start();

}

void MainWindow::loadMapSeg()
{
    glb.map->loadMap();
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    setFixedSize(Width+160,Height);

    paint.begin(this);
    glb.map->display(paint);
    glb.boss->display(paint);
    glb.player->display(paint);

    for(int i=0;i<glb.enemytanks.count();++i)
    {
        glb.enemytanks.at(i)->display(paint);
    }

    this->showPlayerInfo();

    paint.end();

}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if(event->key()==Qt::Key_P)
    {
        gameStatus=pause;
        glb.player->stopMove();
        for(int i=0;i<glb.enemytanks.count();++i)
        {
            glb.enemytanks.at(i)->stopMove();
        }

        //显示暂停
        showInformationMsg7();
    }
    else if(event->key()==Qt::Key_G)
    {
        gameStatus=game;
        showInformationMsg8();
    }

    if(gameStatus==game)
    {
        if(event->key()==Qt::Key_W)
        {
            glb.player->setDirection(Up);
            glb.player->startMove();
        }
        else if(event->key()==Qt::Key_S)
        {
            glb.player->setDirection(Down);
            glb.player->startMove();
        }
        else if(event->key()==Qt::Key_A)
        {
            glb.player->setDirection(Left);
            glb.player->startMove();
        }
        else if(event->key()==Qt::Key_D)
        {
            glb.player->setDirection(Right);
            glb.player->startMove();
        }
        else if(event->key()==Qt::Key_J)
        {
            glb.player->startFire();
        }
    }

    update();

}

void MainWindow::keyReleaseEvent(QKeyEvent *event)
{
    if(event->key()==Qt::Key_J)
    {
        glb.player->stopFire();
    }
    else
    {
        glb.player->stopMove();
    }
}

void MainWindow::timeFun()
{
    if(gameStatus!=game)
        return;

    Direction tmpDir;
    int tmp;

    //判断是否有奖励
    bonusForAttack();

    //获取当前时间
    QTime time = QTime::currentTime();
    //设置随机数种子
    qsrand(time.msec()+time.second()*100000);

    //敌人坦克控制
    for(int i=0;i<glb.enemytanks.count();++i)
    {

        if(qrand()%5==0)
        {
            glb.enemytanks.at(i)->startMove();
            glb.enemytanks.at(i)->startFire();
        }

        if(qrand()%10==0)
        {
            glb.enemytanks.at(i)->stopMove();
        }

        if(qrand()%5==0)
        {
            glb.enemytanks.at(i)->stopFire();
        }

        if(qrand()%10==0)
        {
            tmp=qrand()%9;
            switch(tmp)
            {
            case 0:
                tmpDir=Up;
                break;
            case 1:
                tmpDir=Down;
                break;
            case 2:
                tmpDir=Left;
                break;
            case 3:
                tmpDir=Right;
                break;
            case 4:
                tmpDir=Down;
                break;
            case 5:
                tmpDir=Down;
                break;
            case 6:
                tmpDir=Down;
                break;
            case 7:
                tmpDir=Left;
                break;
            case 8:
                tmpDir=Right;
                break;
            default:
                break;
            }
            glb.enemytanks.at(i)->setDirection(tmpDir);
         }

    }
    //end

    glb.player->move();
    glb.player->fire();



    for(int i=0;i<glb.enemytanks.count();++i)
    {
        glb.enemytanks.at(i)->move();
        glb.enemytanks.at(i)->fire();
    }

    this->missileMeetMissile();

    //玩家坦克死后重生   
    if(glb.player->isDisappeared()&&glb.playerTanksNum<playerTankNumTmp)
    {
        glb.player=NULL;
        glb.player=new Tank();
        ++glb.playerTanksNum;
    }

    //敌方坦克死后重生
    for(int i=0;i<glb.enemytanks.count();++i)
    {
        if(glb.enemytanks.at(i)->isDisappeared())
        {
            int kindTmp=glb.enemytanks.at(i)->getKind();
            delete glb.enemytanks.at(i);
            glb.enemytanks.removeAt(i);

            Tank *tankTmp;
            switch(kindTmp)
            {
            case 1:
                if(glb.enemy1TanksNum<enemyTankNum)
                {
                    tankTmp=new Tank(0,0,Down,1,1);
                    ++glb.enemy1TanksNum;
                    glb.enemytanks.append(tankTmp);
                }
                break;
            case 2:
                if(glb.enemy2TanksNum<enemyTankNum)
                {
                    tankTmp=new Tank(0,6,Down,2,1);
                    ++glb.enemy2TanksNum;
                    glb.enemytanks.append(tankTmp);
                }
                break;
            case 3:
                if(glb.enemy3TanksNum<enemyTankNum)
                {
                    tankTmp=new Tank(0,12,Down,3,1);
                    ++glb.enemy3TanksNum;
                    glb.enemytanks.append(tankTmp);
                }
                break;
            }

        }
    }

    //过关后的到下一关的过渡
    if(this->isAllDisappeared()
            &&glb.enemy1TanksNum==enemyTankNum
            &&glb.enemy2TanksNum==enemyTankNum
            &&glb.enemy3TanksNum==enemyTankNum
            &&glb.stage<=glb.stagesNum)
    {
        gameStatus=pause;
        timer->stop();
        //显示下一关的信息
        showInformationMsg4();


        initGame();
        bonusForLife();
    }


    //通关后的信息提示和关闭窗口
    if(this->isAllDisappeared()&&glb.stage==glb.stagesNum+1)
    {
        gameStatus=pause;
        timer->stop();
        showInformationMsg9();

        //关闭游戏窗口
        this->close();

    }

    //判断游戏是否结束
    this->isGameOver();
    qDebug("time out");
    update();
}

void MainWindow::setGameStatus(GameStatus status)
{
    gameStatus=status;
}

void MainWindow::showInformationMsg1()
{
    setGeometry(880,350,200,150);
    QMessageBox::information(this,tr("版本信息"),
                             tr("Tank War v1.0"));
    return;
}

void MainWindow::showInformationMsg2()
{
    setGeometry(880,350,200,150);
    QMessageBox::information(this,tr("操作说明"),
                             tr("   w"
                              "\n asd  Control directions and move"
                              "\n\n    j    Fire"
                              "\n\n    p    Pause"
                              "\n\n    g    Resume"));
    return;
}

void MainWindow::showInformationMsg3()
{
    setGeometry(880,350,200,150);
    QMessageBox::information(this,tr("Tank War"),
                                   tr("Ready for Stage 1"));
    return;
}

void MainWindow::showInformationMsg4()
{
    setGeometry(605,83,200,150);
    QMessageBox::information(this,tr("Tank War"),
                                   tr("Congratulations!"
                                      "\n\nReady for next stage"));
    return;
}

void MainWindow::showInformationMsg5()
{
    setGeometry(605,83,200,150);

    QMessageBox::information(this,tr("Tank War"),
                                   tr("You lose!"
                                      "\nGame Over!"));
    return;
}

void MainWindow::showInformationMsg6()
{
    setGeometry(605,83,200,150);
    QMessageBox::information(this,tr("Tank War"),
                             tr("Ready for Stage 1"));

    return;
}

void MainWindow::showInformationMsg7()
{
    label9->setText(tr("PAUSE!"));
    label9->setGeometry(865,755,70,20);
}

void MainWindow::showInformationMsg8()
{
    label9->setText(tr(""));
    label9->setGeometry(800,300,10,20);
}

void MainWindow::showInformationMsg9()
{
    setGeometry(605,83,200,150);
    QMessageBox::information(this,tr("Tank War"),
                                   tr("Congratulations!"
                                      "\n\nYou win the war!"));
    return;
}

bool MainWindow::isAllDisappeared()const
{
    for(int i=0;i<glb.enemytanks.count();++i)
    {
        if(!glb.enemytanks.at(i)->isDisappeared())
        {
            return false;
        }
    }
    return true;
}

void MainWindow::missileMeetMissile()
{
    int missileNumOfPlayer=glb.player->missiles.count();

    if(missileNumOfPlayer==1)
    {
        for(int i=0;i<glb.enemytanks.count();++i)
                {
                    if(glb.enemytanks.at(i)->getIsFire()&&glb.player->missiles.at(0)->isCollision(*glb.enemytanks.at(i)->missiles.at(0)))
                    {
                        //玩家导弹消失
                        bool tmp=true;
                        glb.player->missiles.at(0)->setDisappear(tmp);
                        //敌方导弹消失
                        glb.enemytanks.at(i)->missiles.at(0)->setDisappear(tmp);

                        //恢复各坦克导弹数
                        glb.player->setMissileNum();
                        glb.enemytanks.at(i)->setMissileNum();

                        break;
                        //这里有一个不太完美的碰撞检验，因为有可能在下一个时钟周期后导弹已经飞过，
                        //没有碰撞检验的效果
                    }

                }
    }
}

void MainWindow::isGameOver()
{
    if(glb.boss->isDisappeared()
            ||(glb.player->isDisappeared()&&glb.playerTanksNum==playerTankNumTmp))
    {
        gameStatus=pause;
        timer->stop();
        showInformationMsg5();

        //删除敌方坦克
        for(int i=0;i<glb.enemytanks.count();++i)
        {
            bool tmp=true;
            glb.enemytanks.at(i)->setDisappear(tmp);
            delete glb.enemytanks.at(i);
            glb.enemytanks.removeAt(i);
        }
        //删除玩家坦克
        glb.player=NULL;
        for(int i=0;i<Row;++i)
        {
            for(int j=0;j<Col;++j)
            {
                *glb.map->getSeg(i,j)=NULL;
                delete glb.map->getSeg(i,j);
            }
        }

        this->close();
    }
}

void MainWindow::showPlayerInfo()
{
    //1、得分score的信息
    label2->setText(tr("Scores:"));
    QRect r1(790,90,80,20);
    label2->setGeometry(r1);

    QString tempStr1;
    label1->setText(tempStr1.setNum(glb.score));
    QRect r2(860,110,80,20);
    label1->setGeometry(r2);


    //2、剩下敌方坦克书的信息
    label3->setText(tr("Tanks Left:"));
    QRect r3(790,260,120,20);
    label3->setGeometry(r3);

    //总敌方坦克数
    int enemyTanksToTNum=3*enemyTankNum;
    //剩余敌方坦克数
    int enemyTanksLeft=enemyTanksToTNum-glb.enemyTanksDestroyed;

    QString tempStr2;
    label4->setText(tempStr2.setNum(enemyTanksLeft));
    QRect r4(890,280,80,20);
    label4->setGeometry(r4);

    //3、关卡数信息
    label5->setText(tr("Stages:"));
    QRect r5(790,450,80,25);
    label5->setGeometry(r5);

    QString tempStr3;
    label6->setText(tempStr3.setNum(glb.stage-1));
    QRect r6(860,470,80,20);
    label6->setGeometry(r6);

    //4、玩家生命数
    label7->setText(tr("Lives Left:"));
    QRect r7(790,650,100,20);
    label7->setGeometry(r7);

    QString tempStr4;
    label8->setText(tempStr4.setNum(playerTankNumTmp-glb.playerTanksNum));
    QRect r8(880,670,80,20);
    label8->setGeometry(r8);
}

void MainWindow::bonusForLife()
{
    if((glb.stage-2)%5==0)
    {
        ++playerTankNumTmp;
    }
}

void MainWindow::bonusForAttack()
{
    if(glb.player->getScoreForPerPlayer()>5000)
    {
        glb.player->setAttack();
    }
}

