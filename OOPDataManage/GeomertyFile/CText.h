#pragma once
#include"CPoint.h"

class CText 
{
public:
	CPoint C;
	std::string Text;
	virtual const char* GetType();
	virtual const char* ToWKT();
	virtual const char* ToGeojson();
};

