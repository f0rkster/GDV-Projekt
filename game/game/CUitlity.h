#pragma once
#include "CBullet.h"
#include "CEnemy.h"
#include <vector>

class CUitlity
{
public:
	static int getVectorIndex(std::vector<CBullet*> v, CBullet* K);
	static int getVectorIndex(std::vector<CEnemy*> v, CEnemy* K);
};

