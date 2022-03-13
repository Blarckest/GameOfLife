#include "gameManagerAbs.h"

gameManagerAbs::gameManagerAbs(size_t columns, size_t lines)
{
	m_gameBoard = new gameBoard(columns, lines);
	nbOfColumns = m_gameBoard->getNbOfcolumns();
	nbOfLines = m_gameBoard->getNbOfLines();
}

void gameManagerAbs::modifyAt(size_t column, size_t line, bool newVal)
{
	m_gameBoard->setAt(column, line, newVal);
}

void gameManagerAbs::initPoint(size_t column, size_t line, bool newVal)
{
	modifyAt(column, line, newVal);
}

bool gameManagerAbs::getAt(size_t column, size_t line) const
{
	return m_gameBoard->getAt(column,line);
}

const size_t gameManagerAbs::getNbOfLines() const
{
	return nbOfLines;
}

const size_t gameManagerAbs::getNbOfColumns() const
{
	return nbOfColumns;
}

void gameManagerAbs::resetGameBoard()
{
	delete m_gameBoard;
	m_gameBoard = new gameBoard(nbOfColumns, nbOfLines);
}

gameManagerAbs::~gameManagerAbs()
{
	delete m_gameBoard;
}