#pragma once
#include "../GeomertyFile/CPolyGon.h"
#include"../GeomertyFile/CSection.h"
#include"../GeomertyFile/CRectAngle.h"
#include"../GeomertyFile/CFeature.h"
#include<fstream>
#include<exception>

class GeoFormat
{
public:
	virtual GeometryType GetType() = 0;

	virtual int GetShape(CPoint& point) = 0;

	virtual int GetShape(CPolyLine& Line) = 0;

	virtual int GetShape(CPolyGon& Gon) = 0;

	virtual int GetShape(CRectAngle& Rect) = 0;

	virtual int GetShape(CCircle& Cir) = 0;

	virtual int GetShape(CSection& Sec) = 0;

};


class FileReader:public GeoFormat
{
public:
	virtual bool Open(const char* FileName)=0;

	virtual bool Write(CFeature feature)=0;

	virtual bool isNext()=0;

	virtual bool Save()=0;

	virtual bool Close()=0;

protected:
	std::ifstream ifs;
	std::ofstream ofs;
};


