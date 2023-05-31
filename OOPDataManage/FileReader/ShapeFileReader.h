#pragma once
#include"FileReader.h"


int Big2Little(int a);

class ShapeFileReader:public FileReader
{
public:
	ShapeFileReader(const char* name) { Open(name); };

	bool Open(const char* FileName) override;

	bool Write(CFeature feature) override;

	GeometryType GetType();

	int GetShape(CPoint& point) ;

	int GetShape(CPolyLine& Line);

	int GetShape(CPolyGon& Gon) ;

	int GetShape(CRectAngle& Rect) ;

	int GetShape(CCircle& Cir);

	int GetShape(CSection& Sec) ;

private:
	int m_cursur = 0;
};
