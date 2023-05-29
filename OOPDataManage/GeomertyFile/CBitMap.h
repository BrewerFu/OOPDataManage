#pragma once
#include"CPoint.h"

class CBitMap 
{
public:
	CPoint C;
	int m_Height;
	int m_Width;
	long m_PiexLen;
	unsigned char* m_prtPixels;
	virtual const char* GetType();
	virtual const char* ToWKT();
	virtual const char* ToGeojson();

};
