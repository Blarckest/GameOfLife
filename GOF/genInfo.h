#pragma once
#include <memory>
#include <unordered_set>
#include "pairCoordinate_hash.h"
class genInfo
{
public:
	genInfo(unsigned int genNb, unsigned int population, std::unique_ptr<std::unordered_set<std::pair<size_t, size_t>>>& pointsToChange);
	virtual ~genInfo();
	virtual const std::unordered_set<std::pair<size_t, size_t>>& getPointsToChange() const;
	virtual const unsigned int getGenNb()const;
	virtual const unsigned int getPopulation()const;
protected:
	unsigned int m_genNumber;
	unsigned int m_population;
	std::unique_ptr<std::unordered_set<std::pair<size_t, size_t>>> m_pointsToChange;
};

