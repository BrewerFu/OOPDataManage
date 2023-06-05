#include "FileManager.h"

FileManager::FileManager()
{
	Reader = nullptr;
	m_Point = nullptr;
	m_PolyLine = nullptr;
	m_PolyGon = nullptr;
	m_RectAngle = nullptr;
	m_Circle = nullptr;
	m_Section = nullptr;
}

FileManager::FileManager(const char* FileName)
{
	Reader = nullptr;
	m_Point = nullptr;
	m_PolyLine = nullptr;
	m_PolyGon = nullptr;
	m_RectAngle = nullptr;
	m_Circle = nullptr;
	m_Section = nullptr;
	Open(FileName);
}

FileManager::~FileManager()
{
	//几何对象的析构工作交给了CFeature
	delete Reader;
}

bool FileManager::Open(const char* FileName)
{
	std::string str = FileName;
	if (str.substr(str.find_last_of(".") + 1) == "txt")
	{
		delete Reader;
		Reader = new TextReader(FileName);
	}
	else if (str.substr(str.find_last_of(".") + 1) == "shp")
	{
		delete Reader;
		Reader = new ShapeFileReader(FileName);
	}
	else
	{
		return false;
	}
}

CFeature FileManager::Read()
{
	GeometryType type=Reader->GetType();
	CFeature feature(type);
	CGeometry* geo;
	while (Reader->isNext())
	{
		geo = GetGeometry(type);
		feature.AppendGeometry(geo);
	}
	return feature;
}

CGeometry* FileManager::GetGeometry(GeometryType type)
{
	switch (type)
	{
	case GeometryType::Point:
		m_Point = new CPoint();
		Reader->GetGeometry(*m_Point);
		return m_Point;

	case GeometryType::PolyLine:
		m_PolyLine = new CPolyLine();
		Reader->GetGeometry(*m_PolyLine);
		return m_PolyLine;

	case GeometryType::PolyGon:
		m_PolyGon = new CPolyGon();
		Reader->GetGeometry(*m_PolyGon);
		return m_PolyGon;

	case GeometryType::RectAngle:
		m_RectAngle = new CRectAngle();
		Reader->GetGeometry(*m_RectAngle);
		return m_RectAngle;

	case GeometryType::Circle:
		m_Circle = new CCircle();
		Reader->GetGeometry(*m_Circle);
		return m_Circle;

	case GeometryType::Section:
		m_Section = new CSection();
		Reader->GetGeometry(*m_Section);
		return m_Section;

	default:
		return nullptr;
	}
}