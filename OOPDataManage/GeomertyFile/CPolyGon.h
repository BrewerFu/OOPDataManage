#pragma once
#include"CPolyLine.h"

//���ζ����
class CPolyGon :public CPolyLine
{
public:
	//Ĭ�Ϲ��캯��
	CPolyGon() {};

	virtual const char* GetType();
	virtual const char* ToWKT();
	virtual const char* ToGeojson();
	virtual float Circum();
	virtual float Area();
	
};

