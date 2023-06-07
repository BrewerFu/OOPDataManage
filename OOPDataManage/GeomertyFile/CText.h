#pragma once
#include"CPoint.h"

class CGEOMETRY_API CText
{
public:
	CPoint C;
	std::string Text;
	GeometryType GetType();
};

