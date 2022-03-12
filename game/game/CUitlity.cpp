#include "CUitlity.h"
#include <iostream>

//https://stackoverflow.com/questions/875103/how-do-i-erase-an-element-from-stdvector-by-index
//https://www.geeksforgeeks.org/how-to-find-index-of-a-given-element-in-a-vector-in-cpp/

int CUitlity::getVectorIndex(std::vector<CBullet*> v, CBullet* K)
{
	auto it = find(v.begin(), v.end(), K);

	// If element was found
	if (it != v.end())
	{

		// calculating the index
		// of K
		int index = it - v.begin();
		return index;
	}
	else {
		// If the element is not
		// present in the vector
		std::cout << "-1" << std::endl;
	}
}

int CUitlity::getVectorIndex(std::vector<CEnemy*> v, CEnemy* K)
{
	auto it = find(v.begin(), v.end(), K);

	// If element was found
	if (it != v.end())
	{

		// calculating the index
		// of K
		int index = it - v.begin();
		return index;
	}
	else {
		// If the element is not
		// present in the vector
		std::cout << "-1" << std::endl;
	}
}
