#include "mainwindow.h"
#include <QApplication>
#include<QPixmap>
#include<QSplashScreen>
#include<QPoint>

Glb glb;//全局结构体

int main(int argc, char *argv[])
{
    QPoint *p1;
    QPoint *p2;
    p1=new QPoint(700,200);
    p2=new QPoint(600,50);
    QApplication a(argc, argv);

    //设置全局字体
    QFont font("Microsoft YaHei UI",14);
    a.setFont(font);

    QPixmap pixmap(":/new/icon/pixs/start.png");
    QSplashScreen splash(pixmap);
    splash.move(*p1);
    splash.show();
    a.processEvents();

    MainWindow w;
    w.move(*p2);
    w.show();
    splash.finish(&w);

    return a.exec();
}
