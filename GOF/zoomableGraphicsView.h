#pragma once
#include <QGraphicsView>
#include <QWheelEvent>

class zoomableGraphicsView : public QGraphicsView
{
	Q_OBJECT

public:
	zoomableGraphicsView(QWidget* parent = nullptr);
	zoomableGraphicsView(QGraphicsScene* scene);
	virtual ~zoomableGraphicsView();

protected:
	virtual void wheelEvent(QWheelEvent* e) override;
	float zoomInFactor = 1.15;
	float zoomOutFactor = 1 / zoomInFactor;
};
