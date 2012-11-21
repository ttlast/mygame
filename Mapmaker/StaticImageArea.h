#ifndef StaticImageArea_H
#define StaticImageArea_H
#include <QtGui/QWidget>
#include <QtGui/QPainter>

class StaticImageArea :public QWidget
{
    Q_OBJECT
public:
    StaticImageArea(QWidget *parent = NULL);

    void paintEvent(QPaintEvent *);
private:
    QImage *img;
};

#endif // StaticImageArea_H
