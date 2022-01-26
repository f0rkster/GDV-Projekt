#pragma once

class CEntity
{
public:
	float m_Speed;
	float m_Translation[3];
	float m_Scale[3];
	float m_Rotation[3];


public:
	CEntity();

	virtual ~CEntity();

};

