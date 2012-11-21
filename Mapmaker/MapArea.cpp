#include "MapArea.h"
#include <time.h>
#include <stdlib.h>

MapArea::MapArea(QWidget *parent)
    :QWidget(parent)
{
    QPalette p = QPalette();
    p.setColor(QPalette::Window,Qt::white);
    setPalette(p);
    setAutoFillBackground(true);

    img_people = new QImage(":/images/people.png");
    img_wall = new QImage(":/images/wall.png");
    img_tar = new QImage(":/images/tar.png");

    img_key[0] = new QImage(":/images/key0.png");
    img_key[1] = new QImage(":/images/key1.png");
    img_key[2] = new QImage(":/images/key2.png");
    img_key[3] = new QImage(":/images/key3.png");
    img_key[4] = new QImage(":/images/key4.png");

    img_door[0] = new QImage(":/images/door0.png");
    img_door[1] = new QImage(":/images/door1.png");
    img_door[2] = new QImage(":/images/door2.png");
    img_door[3] = new QImage(":/images/door3.png");
    img_door[4] = new QImage(":/images/door4.png");

    h_nums = MAP_COL;
    v_nums = MAP_ROW;

    setMinimumSize(h_nums*CELL_WIDTH+5,v_nums*CELL_WIDTH + 5);
    setMaximumSize(h_nums*CELL_WIDTH+5,v_nums*CELL_WIDTH + 5);

    initMap();
    update();
}

void MapArea::paintEvent(QPaintEvent *)
{
    QPainter p(this);

    QPoint start_point, end_point;
    int i, j;

    // 绘制每块的图像
    for(i = 0;i < v_nums;i ++)
    {
        for(j = 0;j < h_nums;j ++)
        {
            QPoint cell_topleft = QPoint(CELL_WIDTH*j, CELL_WIDTH*i);
            QRect img_rect = QRect(QPoint(0,0),QSize(CELL_WIDTH,CELL_WIDTH));
            if(map[j][i] == WALL)
            {
                p.drawImage(cell_topleft, *img_wall, img_rect);
            }else if(map[j][i] == TAR)
            {
                p.drawImage(cell_topleft, *img_tar, img_rect);
            }else if(map[j][i] == STAR)
            {
                p.drawImage(cell_topleft,*img_people, img_rect);
            }else if(map[j][i] >= KEY && map[j][i] <= KEY2)
            {
                p.drawImage(cell_topleft,*img_key[map[j][i]-KEY],img_rect);
            }else if(map[j][i] >= DOOR && map[j][i] <= DOOR2)
            {
                p.drawImage(cell_topleft,*img_door[map[j][i]-DOOR],img_rect);
            }
        }
    }
    // 绘制横向直线
    for (i = 0; i <= v_nums; i++)
    {
        start_point = QPoint(0, CELL_WIDTH*i);
        end_point = QPoint(h_nums*CELL_WIDTH, CELL_WIDTH*i);
        p.drawLine(start_point, end_point);
    }
    // 绘制纵向直线
    for (j = 0; j <= h_nums; j++)
    {
        start_point = QPoint(CELL_WIDTH*j, 0);
        end_point = QPoint(CELL_WIDTH*j,v_nums*CELL_WIDTH);
        p.drawLine(start_point, end_point);
    }
}


void MapArea::imgClik(int row,int col,int wp)
{
    if(map[col][row] == STAR)
    {
        start.x = start.y = -1;
    }
    if(map[col][row] == TAR)
    {
        tar.x = tar.y = -1;
    }
    if(wp == STAR)
    {
        if(start.x != -1) map[start.x][start.y] = NOTHING;
        start.x = col; start.y = row;
    }
    if(wp == TAR)
    {
        if(tar.x != -1) map[tar.x][tar.y] = NOTHING;
        tar.x = col; tar.y = row;
    }
    map[col][row] = wp;
    update();
}

void MapArea::initMap()
{
    int i,j;
    for(i = 0;i < MAP_ROW;i ++)
        for(j = 0;j < MAP_COL;j ++)
            if(i == 0 || j == 0 || i == MAP_ROW - 1 || j == MAP_COL - 1)
                map[j][i] = WALL;
            else map[j][i] = NOTHING;
    map[1][1] = STAR;
    map[MAP_COL - 2][MAP_ROW - 2] = TAR;
    start.x =  start.y = 1;
    tar.x = MAP_COL - 2;
    tar.y = MAP_ROW - 2;
}

void MapArea::ReadMap()
{
    QString s = QFileDialog::getOpenFileName(
                this,
                "open GameMap",
                "/",
                "all(*.*);;Map files(*.map);;txt files(*.txt)"
                );
    QFile file(s);
    if(!file.open(QIODevice::ReadWrite))
    {
        return ;
    }
    QTextStream stream(&file);
    QString line;
    int row,col;

    stream >> start.x >> start.y;
    stream >> tar.x >> tar.y;
    for(row = 0;row < MAP_ROW;row ++)
        for(col = 0;col < MAP_COL;col ++)
        {
            stream >> map[col][row];
        }
    file.close();
    update();
}

void MapArea::SaveMap()
{
    if(start.x == -1 || tar.x == -1)
    {
        QString message,title;
        title = title.fromLocal8Bit("提示");
        message = message.fromLocal8Bit("还没有设置出发点、结束点");
        QMessageBox::warning(this,title,message);
        return ;
    }
    QString s = QFileDialog::getSaveFileName(
                this,
                "Save GameMap",
                "/",
                "all(*.*);;Map files(*.map);;txt files(*.txt)"
                );
    QFile file(s);
    if(!file.open(QIODevice::ReadWrite))
    {
        return ;
    }
    QTextStream stream(&file);
    QString line;
    int row,col;

    stream << start.x << " " << start.y;
    stream << " " << tar.x << " " << tar.y << endl;
    for(row = 0;row < MAP_ROW;row ++)
    {
        for(col = 0;col < MAP_COL;col ++)
        {
            stream << map[col][row] << " ";
        }
        stream<<endl;
    }
    file.close();
}
