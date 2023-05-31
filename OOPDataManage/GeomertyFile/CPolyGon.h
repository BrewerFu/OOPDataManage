#pragma once
#include"CPolyLine.h"

//几何多边形
class CPolyGon :public CPolyLine
{
public:
	//默认构造函数
	CPolyGon() {};

	GeometryType GetType()override;
	const char* ToWKT()override;
	const char* ToGeojson()override;
	virtual float Circum();
	virtual float Area();
	
};

