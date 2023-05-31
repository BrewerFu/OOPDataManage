#include"ShapeFileReader.h"

int Big2Little(int a)
{
	char* pt = (char*)&a;
	int b;
	char* pt0 = (char*)&b;
	pt0[0] = pt[3];
	pt0[1] = pt[2];
	pt0[2] = pt[1];
	pt0[3] = pt[0];
	return b;
}

bool ShapeFileReader::Open(const char* FileName)
{
	try
	{
		ifs.open(FileName, std::ios_base::binary);
	}
	catch(std::exception)
	{
		return false;
	}
	//偏移100
	m_cursur = 100;
	return true;
}

bool ShapeFileReader::Write(CFeature feature)
{
	return false;
}

GeometryType ShapeFileReader::GetType()
{
	int Shapetype;
	//从32位开始读4个字节
	ifs.seekg(32, std::ios_base::beg);
	ifs.read((char*)&Shapetype, 4);
	//返回数字

	switch (Shapetype)
	{
	case 1:
		return GeometryType::Point;
	case 3:
		return GeometryType::PolyLine;
	case 5:
		return GeometryType::PolyGon;
	default:
		return GeometryType::Undefined;
	}

}

