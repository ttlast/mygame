#ifndef MapArea_H
#define MapArea_H
#include <QtGui/QImage>
#include <QtGui/QWidget>
#include <QtGui/QPalette>
#include <QtGui/QPainter>
#include <QtGui/QFileDialog>
#include <QtGui/QMessageBox>
#include <QTextStream>
#include "MapDef.h"



class MapArea :public QWidget
{
    typedef struct pos{
        int x,y;
    }pos;
    Q_OBJECT
public:
    MapArea(QWidget *parent = NULL);

    void paintEvent(QPaintEvent *);
    void imgClik(int row,int col,int wp);
    void SaveMap();
    void ReadMap();
    void initMap();

    int getMapv()
    {
        return v_nums;
    }
    int getMaph()
    {
        return h_nums;
    }

private:
    QImage *img_wall;
    QImage *img_tar;
    QImage *img_people;
    QImage *img_key[10];
    QImage *img_door[10];

    int h_nums;   //水平方向分块数
    int v_nums;   //垂直方向分块数

    int map[MAP_COL][MAP_ROW];

    pos start,tar;

};

#endif // MapArea_H
