#pragma once
#include "../GeomertyFile/CPolyGon.h"
#include"../GeomertyFile/CSection.h"
#include"../GeomertyFile/CRectAngle.h"
#include"../GeomertyFile/CFeature.h"
#include<qfile.h>
#include<fstream>
#include<exception>

class GeoFormat
{
public:
	virtual GeometryType GetType() = 0;

	virtual int GetGeometry(CPoint& point) = 0;

	virtual int GetGeometry(CPolyLine& Line) = 0;

	virtual int GetGeometry(CPolyGon& Gon) = 0;

	virtual int GetGeometry(CRectAngle& Rect) = 0;

	virtual int GetGeometry(CCircle& Cir) = 0;

	virtual int GetGeometry(CSection& Sec) = 0;

};


class FileReader:public GeoFormat
{
public:
	virtual bool Open(const char* FileName)=0;

	virtual bool Write(CFeature feature)=0;

	virtual bool isNext()=0;

	virtual bool Save()=0;

	virtual bool Close()=0;

	virtual ~FileReader() {};

protected:
	//qt文件读取
	QFile qfs;
};


