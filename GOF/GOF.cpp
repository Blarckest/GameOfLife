#include "GOF.h"
#include <qdebug.h>
#include "zoomableGraphicsView.h"
#include <unordered_map>
#include <QString>

GOF::GOF(size_t cols, size_t lines, QWidget* parent)
	: QWidget(parent)
{
	m_scene = new QGraphicsScene();
	m_gameManager = new gameManager(cols, lines);
	m_view = new zoomableGraphicsView(m_scene);
	m_looper = new QTimer();
	m_popLabel = new QLabel("Population: 0");
	m_actualGenLabel = new QLabel("Generation: 0");
	m_infoLayout = new QHBoxLayout();
	m_layout = new QVBoxLayout();
	initialize(m_gameManager->getNbOfColumns(), m_gameManager->getNbOfLines());
	m_infoLayout->addWidget(m_popLabel);
	m_infoLayout->addSpacing(100);
	m_infoLayout->addWidget(m_actualGenLabel);
	m_layout->addLayout(m_infoLayout);
	m_layout->addWidget(m_view);
	setLayout(m_layout);
}

void GOF::initialize(size_t cols, size_t lines)
{
	for (size_t i = 0; i < cols * SIZE; i += SIZE)
	{
		for (size_t j = 0; j < lines * SIZE; j += SIZE)
		{
			auto coordinate = std::make_pair(i / SIZE, j / SIZE);
			auto pair = m_mapOfRectangle.find(coordinate);
			if (pair != m_mapOfRectangle.end())
			{
				pair->second->setPos(i / SIZE, j / SIZE);
				auto rect = static_cast<clickableGraphicRect*>(pair->second);
				rect->setOn(true);
				connect(rect, SIGNAL(clicked()), this, SLOT(rectangleClicked()));
			}
			else
			{
				auto rect = new clickableGraphicRect(i, j, SIZE, SIZE);
				rect->setPos(i / SIZE, j / SIZE);
				m_scene->addItem(rect);
				connect(rect, SIGNAL(clicked()), this, SLOT(rectangleClicked()));
			}
		}
	}
}

void GOF::update()
{
	auto genInfo = m_gameManager->nextGen();
	m_popLabel->setText("Population: " + QString::number(genInfo->getPopulation()));
 	m_actualGenLabel->setText("Generation: " + QString::number(genInfo->getGenNb()));
	for (auto& l : genInfo->getPointsToChange())
	{
		auto element = m_mapOfRectangle.find(l);
		if (element == m_mapOfRectangle.end())
		{
			auto rect = new clickableGraphicRect(l.first * SIZE, l.second * SIZE, SIZE, SIZE);
			rect->setOn(true);
			rect->setBrush(blackBrush);
			m_scene->addItem(rect);
			m_mapOfRectangle.insert(std::make_pair(l, rect));
		}
		else
		{
			m_scene->removeItem(element->second);
			m_mapOfRectangle.erase(element);
		}
	}

#ifdef _DEBUG
	for (size_t j = 0; j < m_gameManager->getNbOfLines(); j++)
	{
		std::string s = "";
		for (size_t i = 0; i < m_gameManager->getNbOfColumns(); i++)
		{
			s.append((m_gameManager->getAt(i, j) ? "1" : "0"));
			s += " ";
		}
		qDebug() << (s).c_str();
	}
	qDebug() << "\n";
#endif // DEBUG
}

void GOF::start()
{
	m_mapOfRectangle.clear();
	m_gameManager->resetGameBoard();
	auto list = m_scene->items();
	std::vector<std::pair<size_t, size_t>> rectToAdd;
	for (auto& o : list)
	{
		m_gameManager->initPoint((size_t)o->pos().toPoint().x(), (size_t)o->pos().toPoint().y(), static_cast<clickableGraphicRect*>(o)->isOn());
		if (static_cast<clickableGraphicRect*>(o)->isOn())
			rectToAdd.push_back(std::make_pair((size_t)o->pos().toPoint().x(), (size_t)o->pos().toPoint().y()));
	}
	m_scene->clear();
	for (auto& coordinate : rectToAdd)
	{
		auto rect = new clickableGraphicRect(coordinate.first * SIZE, coordinate.second * SIZE, SIZE, SIZE);
		rect->setOn(true);
		rect->setBrush(blackBrush);
		m_scene->addItem(rect);
		m_mapOfRectangle.insert(std::make_pair(coordinate, rect));
	}
	if (!isStarted)
	{
		m_looper->setInterval(250);
		m_looper->setSingleShot(false);
		connect(m_looper, SIGNAL(timeout()), this, SLOT(update()));
		m_looper->start();
	}
	isStarted = true;

#ifdef _DEBUG
	for (size_t j = 0; j < m_gameManager->getNbOfLines(); j++)
	{
		std::string s = "";
		for (size_t i = 0; i < m_gameManager->getNbOfColumns(); i++)
		{
			s.append((m_gameManager->getAt(i, j) ? "1" : "0"));
			s += " ";
		}
		qDebug() << (s).c_str();
	}
	qDebug() << "\n";

#endif // DEBUG
}

void GOF::pause()
{
	initialize(m_gameManager->getNbOfColumns(), m_gameManager->getNbOfLines());
	isPaused = true;
	m_looper->stop();
}

void GOF::resume()
{
	start();
	isPaused = false;
	m_looper->start();
}

void GOF::accelerate()
{
	if (m_looper->interval() > looperStepSize)
		m_looper->setInterval(m_looper->interval() - looperStepSize);
}

void GOF::slowDown()
{
	if (m_looper->interval() < UINT32_MAX - looperStepSize)
		m_looper->setInterval(m_looper->interval() + looperStepSize);
}

void GOF::rectangleClicked()
{
	if (!isStarted || isPaused)
	{
		auto rectangle = qobject_cast<clickableGraphicRect*>(sender());
		switchColor(rectangle);
		return;
	}
}

void GOF::switchColor(clickableGraphicRect* rectangle)
{
	if (rectangle->isOn())
	{
		rectangle->setBrush(whiteBrush);
		rectangle->setOn(false);
	}
	else
	{
		rectangle->setBrush(blackBrush);
		rectangle->setOn(true);
	}
	return;
}

void GOF::keyPressEvent(QKeyEvent* event)
{
	if (event->key() == Qt::Key_Space)
	{
		!isStarted ? start() : isPaused ? resume() : pause();
	}
	else if (event->key() == Qt::Key_Z)
	{
		accelerate();
	}
	else if (event->key() == Qt::Key_S)
	{
		slowDown();
	}
}
