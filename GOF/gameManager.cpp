#include "gameManager.h"
#include <QtCore/qrect.h>

gameManager::gameManager(size_t columns, size_t lines):gameManagerAbs(columns,lines)
{
	livingPoints = new std::unordered_set<std::pair<size_t, size_t>>();
}

gameManager::~gameManager()
{
	delete livingPoints;
}

void gameManager::initPoint(size_t column, size_t line, bool newVal)
{
	if (newVal)
	{
		livingPoints->insert(std::pair(column, line));
	}
	gameManagerAbs::initPoint(column,line,newVal);
}

std::unique_ptr<genInfo> gameManager::nextGen()
{
	m_genNb++;
	auto pointsToChange = std::make_unique<std::unordered_set<std::pair<size_t, size_t>>>();
	auto newLivingPoints = new std::unordered_set<std::pair<size_t, size_t>>();
	gameBoard boardCpy(*(static_cast<gameBoard*>(m_gameBoard)));
	std::unordered_set<std::pair<size_t, size_t>> pointChecked;
	for (auto & p: *livingPoints)
	{
		size_t maxI = p.first + 1 < nbOfColumns ? p.first + 1 : p.first;
		for (size_t i = p.first > 0 ? p.first - 1 : p.first; i <= maxI; i++)
		{
			size_t maxJ = p.second + 1 < nbOfLines ? p.second + 1 : p.second;
			for (size_t j = p.second > 0 ? p.second - 1 : p.second; j <= maxJ; j++)
			{
				if (pointChecked.find(std::pair<size_t, size_t>(i, j))==pointChecked.end())
				{
					pointChecked.insert(std::pair<size_t, size_t>(i, j));
					bool willLive = isGoingTolive(i, j);
					if (willLive != m_gameBoard->getAt(i, j))
					{
						boardCpy.setAt(i, j, willLive);
						pointsToChange->insert(std::pair<size_t, size_t>(i, j));
					}
					if (willLive)
						newLivingPoints->insert(std::pair<size_t, size_t>(i, j));
				}
			}
		}
	}
	delete livingPoints;
	delete m_gameBoard;
	livingPoints = newLivingPoints;
	m_gameBoard = new gameBoard(std::move(boardCpy));
	return std::make_unique<genInfo>(m_genNb, livingPoints->size(), pointsToChange);
}

bool gameManager::isGoingTolive(size_t column, size_t line) const
{
	unsigned short int nbOfNeighbors = 0;

	size_t maxI = column + 1 < nbOfColumns ? column + 1 : column;
	for (size_t i = column > 0 ? column - 1 : column; i <= maxI; i++)
	{
		size_t maxJ = line+ 1 < nbOfLines ? line + 1 : line;
		for (size_t j = line > 0 ? line - 1 : line; j <= maxJ; j++)
		{
			if (m_gameBoard->getAt(i, j) && (i!=column || j!=line))
				nbOfNeighbors++;
		}
		if (nbOfNeighbors>3)
		{
			break;
		}
	}

	if (nbOfNeighbors == 3 || (m_gameBoard->getAt(column, line) && nbOfNeighbors == 2))
	{
		return true;
	}
	return false;
}
