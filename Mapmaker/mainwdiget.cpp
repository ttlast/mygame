#include "mainwdiget.h"

mainwdiget::mainwdiget(QWidget *parent) :
    QWidget(parent)
{
    QString str;
    wp = WALL;
    mapArea = new MapArea;


    // 布局
    char i;
    QHBoxLayout *topLayout = new QHBoxLayout;
    QHBoxLayout *keyLayout = new QHBoxLayout;
    QHBoxLayout *doorLayout = new QHBoxLayout;
    QPushButton *readMap,*saveMap;
    QPushButton *setstart,*settar,*setwall,*setroad;
    QPushButton *key[5],*door[5];
    str = str.fromLocal8Bit("打开地图");
    readMap = new QPushButton(str);
    topLayout->addWidget(readMap);

    str = str.fromLocal8Bit("保存地图");
    saveMap = new QPushButton(str);
    topLayout->addWidget(saveMap);

    str = str.fromLocal8Bit("设置出发点");
    setstart = new QPushButton(str);
    topLayout->addWidget(setstart);

    str = str.fromLocal8Bit("设置终点");
    settar = new QPushButton(str);
    topLayout->addWidget(settar);

    str = str.fromLocal8Bit("设置道路");
    setroad = new QPushButton(str);
    topLayout->addWidget(setroad);

    str = str.fromLocal8Bit("设置墙");
    setwall = new QPushButton(str);
    topLayout->addWidget(setwall);

    for(i = 0;i < 5;i ++)
    {
        str = str.fromLocal8Bit("钥匙");
        str = str.append(i);
        key[i] = new QPushButton(str);
        keyLayout->addWidget(key[i]);
    }
    for(i = 0;i < 5;i ++)
    {
        str = str.fromLocal8Bit("门");
        door[i] = new QPushButton(str);
        doorLayout->addWidget(door[i]);
    }

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(mapArea);

    mainLayout->addLayout(topLayout);
    mainLayout->addLayout(keyLayout);
    mainLayout->addLayout(doorLayout);
    //mainLayout->addWidget(staticImageArea);
    //mainLayout->setMargin(10);
    //mainLayout->setSpacing(10);

    setLayout(mainLayout);

    setMinimumSize(CELL_WIDTH*MAP_COL + 20 ,CELL_WIDTH*MAP_ROW + 150);
    setMaximumSize(CELL_WIDTH*MAP_COL + 20 ,CELL_WIDTH*MAP_ROW + 150);

    str = str.fromLocal8Bit("寻路游戏地图编辑器");
    setWindowTitle(str);

    connect(readMap,SIGNAL(clicked()),this,SLOT(slotReadMap()));
    connect(saveMap,SIGNAL(clicked()),this,SLOT(slotSaveMap()));
    connect(setstart,SIGNAL(clicked()),this,SLOT(slotsetStart()));
    connect(settar,SIGNAL(clicked()),this,SLOT(slotsetTar()));
    connect(setwall,SIGNAL(clicked()),this,SLOT(slotsetWall()));
    connect(setroad,SIGNAL(clicked()),this,SLOT(slotsetRoad()));
    connect(key[0],SIGNAL(clicked()),this,SLOT(slotsetKey0()));
    connect(key[1],SIGNAL(clicked()),this,SLOT(slotsetKey1()));
    connect(key[2],SIGNAL(clicked()),this,SLOT(slotsetKey2()));
    connect(key[3],SIGNAL(clicked()),this,SLOT(slotsetKey3()));
    connect(key[4],SIGNAL(clicked()),this,SLOT(slotsetKey4()));
    connect(door[0],SIGNAL(clicked()),this,SLOT(slotsetDoor0()));
    connect(door[1],SIGNAL(clicked()),this,SLOT(slotsetDoor1()));
    connect(door[2],SIGNAL(clicked()),this,SLOT(slotsetDoor2()));
    connect(door[3],SIGNAL(clicked()),this,SLOT(slotsetDoor3()));
    connect(door[4],SIGNAL(clicked()),this,SLOT(slotsetDoor4()));
}


void mainwdiget::mousePressEvent(QMouseEvent *e)
{

    if (e->button() == Qt::LeftButton)
    {
        int x = e->x() - 10;
        int y = e->y() - 10;
        int row = y / CELL_WIDTH;
        int col = x / CELL_WIDTH;
        if(row >= 0 && row < MAP_ROW && col >= 0 && col < MAP_COL)
            mapArea->imgClik(row,col,wp);
    }
}

void mainwdiget::slotReadMap()
{
    mapArea->ReadMap();
}

void mainwdiget::slotSaveMap()
{
    mapArea->SaveMap();
}

void mainwdiget::slotsetStart()
{
    wp = STAR;
}

void mainwdiget::slotsetTar()
{
    wp = TAR;
}

void mainwdiget::slotsetWall()
{
    wp = WALL;
}

void mainwdiget::slotsetRoad()
{
    wp = NOTHING;
}

void mainwdiget::slotsetKey0()
{
    wp = KEY + 0;
}

void mainwdiget::slotsetKey1()
{
    wp = KEY + 1;
}

void mainwdiget::slotsetKey2()
{
    wp = KEY + 2;
}

void mainwdiget::slotsetKey3()
{
    wp = KEY + 3;
}

void mainwdiget::slotsetKey4()
{
    wp = KEY + 4;
}

void mainwdiget::slotsetDoor0()
{
    wp = DOOR + 0;
}

void mainwdiget::slotsetDoor1()
{
    wp = DOOR + 1;
}

void mainwdiget::slotsetDoor2()
{
    wp = DOOR + 2;
}

void mainwdiget::slotsetDoor3()
{
    wp = DOOR + 3;
}

void mainwdiget::slotsetDoor4()
{
    wp = DOOR + 4;
}
