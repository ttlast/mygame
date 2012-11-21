#ifndef MAINWDIGET_H
#define MAINWDIGET_H

#include <QtGui/QHBoxLayout>
#include <QtGui/QVBoxLayout>
#include <QPushButton>
#include <QtGui>
#include <QWidget>
#include "MapArea.h"

class mainwdiget : public QWidget
{
    typedef struct pos{
        int x,y;
    }pos;
    Q_OBJECT
public:
    mainwdiget(QWidget *parent = 0);
    void mousePressEvent(QMouseEvent *);

    void createMenus();
    int wp;
private:
    MapArea *mapArea;
private slots:

    void slotReadMap();
    void slotSaveMap();
    void slotsetStart();
    void slotsetTar();
    void slotsetRoad();
    void slotsetWall();
    void slotsetKey0();
    void slotsetKey1();
    void slotsetKey2();
    void slotsetKey3();
    void slotsetKey4();
    void slotsetDoor0();
    void slotsetDoor1();
    void slotsetDoor2();
    void slotsetDoor3();
    void slotsetDoor4();
};

#endif // MAINWDIGET_H
