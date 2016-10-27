#ifndef RANDOM_HEIGHT_H
#define RANDOM_HEIGHT_H

class RandomHeight
{
public:
	RandomHeight(int maxLvl, float prob);
	int newLevel();

private:
	int		m_maxLevel;
	float	m_probability;
};

#endif