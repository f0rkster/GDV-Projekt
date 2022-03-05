#pragma once

#include "yoshix_fix_function.h"

class CShapes {
public:
	float m_Translation[3] = { 0, 0, 0 };
	float m_Scale[3]       = { 1, 1, 1 };
	float m_Rotation[3]    = { 0, 0, 0 };

public:
	CShapes();
	~CShapes();
	virtual gfx::SMeshInfo getMeshInfo() = 0;
};