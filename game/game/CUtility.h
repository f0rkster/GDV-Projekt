#pragma once
#include "CBullet.h"
#include "CEnemy.h"
#include "CShield.h"
#include <vector>

class CUtility
{
public:
	static int getVectorIndex(std::vector<CBullet*> v, CBullet* K);
	static int getVectorIndex(std::vector<CEnemy*> v, CEnemy* K);
	static int getVectorIndex(std::vector<CShield*> v, CShield* K);
};

