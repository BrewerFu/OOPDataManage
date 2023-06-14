#pragma once
#include "../GeomertyFile/CPolyGon.h"
#include"../GeomertyFile/CSection.h"
#include"../GeomertyFile/CRectAngle.h"
#include"../GeomertyFile/CFeature.h"
#include"../GeometryManager.h"
#include<qfile.h>
#include<qfileinfo.h>
#include<exception>



class GeoReaderFormat
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


class FileReader:public GeoReaderFormat
{
public:

	virtual bool Open(std::string FileName)
	{
		if (Open(FileName))
			return true;
		else
			return false; 
		Open(QString(FileName.c_str()));
	}

	virtual bool Open(QString FileName) = 0;

	virtual bool isNext()=0;

	virtual bool Close() { qfs.close(); return true; };

	virtual bool isOpen() { return qfs.isOpen(); };

	virtual ~FileReader() {};

protected:
	//qt文件读取
	QFile qfs;
	GeometryManager& gm = GeometryManager::GetInstance();
};


