#pragma once
#include"CGeometry.h"
#include<vector>

class CFeature
{
public:
	std::vector<CGeometry*> m_vector;
	const char* GetType();

};


