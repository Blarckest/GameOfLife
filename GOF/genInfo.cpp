#include "genInfo.h"

genInfo::genInfo(unsigned int genNb, unsigned int population, std::unique_ptr<std::unordered_set<std::pair<size_t, size_t>>>& pointsToChange):m_genNumber(genNb),m_population(population), m_pointsToChange(pointsToChange.release())
{
}

genInfo::~genInfo()
{
}

const std::unordered_set<std::pair<size_t, size_t>>& genInfo::getPointsToChange() const
{
	return *(m_pointsToChange.get());
}

const unsigned int genInfo::getGenNb() const
{
	return m_genNumber;
}

const unsigned int genInfo::getPopulation() const
{
	return m_population;
}
