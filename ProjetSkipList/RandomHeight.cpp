#include <stdlib.h>
#include <time.h>

#include "RandomHeight.h"

using namespace std;

RandomHeight::RandomHeight(int maxLvl, float prob):
	m_maxLevel(maxLvl),
	m_probability(prob)
{
	srand(time(NULL));
}

int RandomHeight::newLevel(void){
	int tmpLvl = 1;
	while (		((rand() % m_maxLevel + 1)	< m_probability ) 
			&&	(		tmpLvl				< m_maxLevel	)) {
		tmpLvl++;
	}
	return tmpLvl;
}