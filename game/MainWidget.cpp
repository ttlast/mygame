#include "MainWidget.h"


MainWidget::MainWidget(QWidget *parent) :
    QWidget(parent)
{
    QString title;
    map_area = new MapArea();
    QHBoxLayout *topLayout = new QHBoxLayout;
    QPushButton *startButton,*editButton,*pauseButton;
    title = title.fromLocal8Bit("开始");
    startButton = new QPushButton(title);

    title = title.fromLocal8Bit("暂停or继续");
    pauseButton = new QPushButton(title);

    title = title.fromLocal8Bit("加载地图");
    editButton = new QPushButton(title);

    topLayout->addWidget(startButton);
    topLayout->addWidget(pauseButton);
    topLayout->addWidget(editButton);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addLayout(topLayout);
    mainLayout->addWidget(map_area);

    setLayout(mainLayout);

    title = title.fromLocal8Bit("钥匙开门走迷宫  广州大学TT_last制作");
    setWindowTitle(title);

    setMinimumSize(MAP_COL*CELL_WIDTH+15,MAP_ROW*CELL_WIDTH+43);
    setMaximumSize(MAP_COL*CELL_WIDTH+15,MAP_ROW*CELL_WIDTH+43);

    connect(startButton,SIGNAL(clicked()),this,SLOT(slotStart()));
    connect(pauseButton,SIGNAL(clicked()),this,SLOT(slotPause()));
    connect(editButton,SIGNAL(clicked()),this,SLOT(slotLoad()));
}

void MainWidget::keyPressEvent(QKeyEvent * e)
{
    if(map_area->isGameover())
        return ;
    map_area->changeDirect(e->key());
}

void MainWidget::slotStart()
{
    map_area->startGame();
}

void MainWidget::slotPause()
{
    map_area->pauseGame();
}

void MainWidget::slotLoad()
{
    map_area->ReadMap();
}
