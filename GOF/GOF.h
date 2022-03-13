#pragma once
#include <QGraphicsitem.h>
#include <QtWidgets/QWidget>
#include "gameManager.h"
#include <QgraphicsScene>
#include <vector>
#include <qtimer>
#include <qgraphicsview>
#include "clickableGraphicRect.h"
#include <qboxlayout.h>
#include "pairCoordinate_hash.h"
#include <qlabel.h>


class GOF : public QWidget
{
    Q_OBJECT

public:
    GOF(size_t cols, size_t lines, QWidget *parent = Q_NULLPTR);
    void initialize(size_t cols, size_t lines);
public slots:
    void update();
    void start();
    void pause();
    void resume();
    void accelerate();
    void slowDown();
    void rectangleClicked();
protected:
    void switchColor(clickableGraphicRect* rectangle);
    void keyPressEvent(QKeyEvent* event) override;
private:
    QTimer* m_looper=nullptr;
    gameManagerAbs* m_gameManager=nullptr;
    bool isStarted = false;
    QGraphicsScene* m_scene=nullptr;
    QGraphicsView* m_view = nullptr;
    unsigned int SIZE = 10;
    QBoxLayout* m_layout = nullptr;
    bool isPaused = false;
    unsigned int looperStepSize = 50;
    QBrush blackBrush = QBrush(Qt::GlobalColor::black);
    QBrush whiteBrush = QBrush(Qt::GlobalColor::white);
    std::unordered_map<std::pair<size_t, size_t>, QGraphicsRectItem*> m_mapOfRectangle;
    QLabel* m_popLabel = nullptr;
    QLabel* m_actualGenLabel = nullptr;
    QBoxLayout* m_infoLayout = nullptr;
};
