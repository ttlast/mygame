#include "MainWidget.h"


MainWidget::MainWidget(QWidget *parent) :
    QWidget(parent)
{
    QString title;
    map_area = new MapArea();
    QHBoxLayout *topLayout = new QHBoxLayout;
    QPushButton *startButton,*editButton,*pauseButton;
    title = title.fromLocal8Bit("��ʼ");
    startButton = new QPushButton(title);

    title = title.fromLocal8Bit("��ͣor����");
    pauseButton = new QPushButton(title);

    title = title.fromLocal8Bit("���ص�ͼ");
    editButton = new QPushButton(title);

    topLayout->addWidget(startButton);
    topLayout->addWidget(pauseButton);
    topLayout->addWidget(editButton);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addLayout(topLayout);
    mainLayout->addWidget(map_area);

    setLayout(mainLayout);

    title = title.fromLocal8Bit("Կ�׿������Թ�  ���ݴ�ѧTT_last����");
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
