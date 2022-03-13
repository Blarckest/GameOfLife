#pragma once
#include "gameManagerAbs.h"
#include <vector>
#include <memory>
#include <unordered_set>
#include "pairCoordinate_hash.h"
#include "genInfo.h"
class gameManager:public gameManagerAbs
{
public:
	gameManager(size_t columns, size_t lines);
	virtual ~gameManager();
	virtual void initPoint(size_t column, size_t line, bool newVal) override;
protected:
	// Inherited via gameManagerAbs
	virtual std::unique_ptr<genInfo> nextGen() override;

	// Inherited via gameManagerAbs
	virtual bool isGoingTolive(size_t column, size_t line) const override;
	std::unordered_set<std::pair<size_t, size_t>>* livingPoints;
	unsigned int m_genNb = 0;
};

