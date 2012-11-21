#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include <QKeyEvent>
#include <QVBoxLayout>
#include <QPushButton>
#include "MapArea.h"

class MainWidget : public QWidget
{
    Q_OBJECT
public:
    MainWidget(QWidget *parent = 0);
    void keyPressEvent(QKeyEvent *);

private:
    MapArea *map_area;
private slots:
    void slotStart();
    void slotPause();
    void slotLoad();
};

#endif // MAINWIDGET_H
