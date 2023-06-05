#pragma once
#include"FileReader.h"

//大端转小端
int Big2Little(int a);

class ShapeFileReader:public FileReader
{
public:
	//默认构造函数
	ShapeFileReader():m_cursur(100){}
	ShapeFileReader(const char* name) { Open(name);};
	//析构函数
	~ShapeFileReader() { Close(); };

	bool Open(const char* FileName) override;

	bool isNext() override;

	bool Close() override;

	GeometryType GetType();

	int GetGeometry(CPoint& point) override;

	int GetGeometry(CPolyLine& Line) override;

	int GetGeometry(CPolyGon& Gon) override;

	int GetGeometry(CRectAngle& Rect)override { return 0; };

	int GetGeometry(CCircle& Cir)override { return 0; };

	int GetGeometry(CSection& Sec)override { return 0; };

private:
	int m_cursur = 0;
};
