#pragma once
#include"CPoint.h"

class CGEOMETRY_API CBitMap
{
public:
	CPoint C;
	int m_Height;
	int m_Width;
	long m_PiexLen;
	unsigned char* m_prtPixels;

	GeometryType GetType();

};
