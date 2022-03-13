#include "clickableGraphicRect.h"

clickableGraphicRect::clickableGraphicRect(size_t x, size_t y, size_t width, size_t height):QGraphicsRectItem(x,y,width,height)
{
	on = false;
}

bool clickableGraphicRect::isOn()
{
	return on;
}

void clickableGraphicRect::setOn(bool state)
{
	on = state;
}

void clickableGraphicRect::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
	emit clicked();
	QGraphicsRectItem::mousePressEvent(event);
}
