#pragma once
#include"CPolyLine.h"

//几何多边形
class CPolyGon :public CPolyLine
{
public:
	//默认构造函数
	CPolyGon() {};

	virtual const char* GetType();
	virtual const char* ToWKT();
	virtual const char* ToGeojson();
	virtual float Circum();
	virtual float Area();
	
};

