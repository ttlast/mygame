#ifndef MAPAREA_H
#define MAPAREA_H

#include <QWidget>
#include <QMessageBox>
#include <QHBoxLayout>
#include <QString>
#include <QFileDialog>
#include <QTextStream>
#include <QPainter>
#include <QQueue>
#include <stdlib.h>
#include "People.h"
#include "MapDef.h"

typedef struct CNode
{
    int x,y,key,ncount;
}CNode;

class MapArea : public QWidget
{
    Q_OBJECT
public:

    MapArea(QWidget *parent = 0);
    void paintEvent(QPaintEvent *);
    void timerEvent(QTimerEvent *);

    void drawPeople(QImage img); //画人物
    void initGame();  //初始化
    void startGame(); //开始
    void pauseGame();
    void ReadMap();

    void changeDirect(int key);  //人物更改方向
    void getKey(int row,int col);  //得到钥匙
    void openDoor(int row,int col);  //打开门

    bool safe(int x,int y);
    int bfs();  //搜索地图
    MoveState DirZ(int dir);
    void dfs(CNode tm);  //搜索路径

    bool isGameover();

private:
    QImage *img_wall;
    QImage *img_tar;
    QImage *img_people;
    QImage *img_key[10];
    QImage *img_door[10];


    int map[MAP_COL][MAP_ROW];  //存储地图信息
    int back_map[MAP_COL][MAP_ROW];
    int roadok,step;
    bool gamepause;
    bool gamestart;
    bool gameover;
    int time_no;

    Pos start,tar;
    People tt;
    int people_col;
};

#endif // MAPAREA_H
