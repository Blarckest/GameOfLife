#include "zoomableGraphicsView.h"
#include <QRectF>

zoomableGraphicsView::zoomableGraphicsView(QWidget *parent)
	: QGraphicsView(parent)
{
	setCacheMode(CacheNone);
}

zoomableGraphicsView::zoomableGraphicsView(QGraphicsScene* scene):QGraphicsView(scene)
{
}

zoomableGraphicsView::~zoomableGraphicsView()
{
}

void zoomableGraphicsView::wheelEvent(QWheelEvent* e)
{
	QGraphicsView::wheelEvent(e);
	if (e->angleDelta().y() != 0 && e->modifiers().testFlag(Qt::ControlModifier))
	{
		auto oldPos = mapToScene(e->pos());
		if (e->angleDelta().y() > 0)
		{
			scale(zoomInFactor, zoomInFactor);
		}
		else
		{
			scale(zoomOutFactor, zoomOutFactor);
		}
		auto newPos = mapToScene(e->pos());
		auto delta = newPos - oldPos;
		translate(delta.x(), delta.y());
	}
	scene()->invalidate(sceneRect());
}
