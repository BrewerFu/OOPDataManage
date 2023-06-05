#pragma once
#include"GeomertyFile/CFeature.h"
#include"FileReader/TextReader.h"
#include"FileReader/ShapeFileReader.h"

class FileManager
{
public:
	FileManager();
	FileManager(const char* FileName);
	~FileManager();
	//根据文件后缀创建不同的文件读取器
	bool Open(const char* FileName);

	CFeature Read();
	
	bool Write(CFeature feature);

	bool Close();

protected:
	CGeometry* GetGeometry(GeometryType type);
	FileReader* Reader;
	CPoint* m_Point;
	CPolyLine* m_PolyLine;
	CPolyGon* m_PolyGon;
	CRectAngle* m_RectAngle;
	CCircle* m_Circle;
	CSection* m_Section;
};




