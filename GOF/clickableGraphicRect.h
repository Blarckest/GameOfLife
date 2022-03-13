#pragma once
#include <QGraphicsItem>
#include <QMouseEvent>
class clickableGraphicRect :
   public QObject, public QGraphicsRectItem
{
    Q_OBJECT
public:
    clickableGraphicRect(size_t x, size_t y, size_t width, size_t height);
    bool isOn();
    void setOn(bool state);
signals:
    void clicked();
protected:
    virtual void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
    bool on=false;
};

