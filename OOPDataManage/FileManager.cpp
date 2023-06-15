#include "FileManager.h"

FileManager::FileManager()
{
	Reader = nullptr;
	Writer = nullptr;
	m_Point = nullptr;
	m_PolyLine = nullptr;
	m_PolyGon = nullptr;
	m_RectAngle = nullptr;
	m_Circle = nullptr;
	m_Section = nullptr;
}

FileManager::~FileManager()
{
	//几何对象的析构工作交给了CFeature
	delete Reader;
	delete Writer;
}

int FileManager::Open(std::string FileName)
{
	return Open(FileName.c_str());
}

int FileManager::Open(const char* FileName)
{
	return Open(QString(FileName));
}

int FileManager::Open(QString FileName)
{
	m_FileName = FileName;
	QFileInfo fileInfo(FileName);

	//先关闭之前的文件
	delete Reader;
	delete Writer;

	if (fileInfo.suffix()=="txt")
	{
		Reader = new TextReader();
		Writer = new TextWriter();
		if (!Writer->Open(FileName))
			return 0;
		if (!Reader->Open(FileName))
			return 2;
	
	}
	else if (fileInfo.suffix() == "shp")
	{
		Reader = new ShapeFileReader();
		if(!Reader->Open(FileName))
			return 2;
	}
	else
		return 0;

	return 1;
}

bool FileManager::Close()
{
	delete Reader;
	delete Writer;
	Reader = nullptr;
	Writer = nullptr;
	return true;
}

bool FileManager::Save()
{
	Reader->Close();
	if (Writer->Save())
	{
		Reader->Open(m_FileName);
		return true;
	}
	else
	{
		Reader->Open(m_FileName);
		return false;
	}
}

CFeature* FileManager::Read()
{
	GeometryType type=Reader->GetType();
	if (type == GeometryType::Undefined)
		throw std::runtime_error("文件不包含几何类型声明，文件读取失败");

	CFeatureManager& featureManager = CFeatureManager::GetInstance();
	CFeature* feature = featureManager.CreateFeature(type);
	std::shared_ptr<CGeometry> geo;
	while (Reader->isNext())
	{
		geo = GetGeometry(type);
		feature->AppendGeometry(geo);
	}
	return feature;
}

bool FileManager::Write(CFeature* feature)
{
	if(Writer->Write(feature))
		return true;
	else
		return false;
}

std::shared_ptr<CGeometry> FileManager::GetGeometry(GeometryType type)
{
	switch (type)
	{
	case GeometryType::Point:
		m_Point = std::make_shared<CPoint>();
		Reader->GetGeometry(*m_Point);
		return m_Point;

	case GeometryType::PolyLine:
		m_PolyLine = std::make_shared<CPolyLine>();
		Reader->GetGeometry(*m_PolyLine);
		return m_PolyLine;

	case GeometryType::PolyGon:
		m_PolyGon = std::make_shared<CPolyGon>();
		Reader->GetGeometry(*m_PolyGon);
		return m_PolyGon;

	case GeometryType::RectAngle:
		m_RectAngle = std::make_shared<CRectAngle>();
		Reader->GetGeometry(*m_RectAngle);
		return m_RectAngle;

	case GeometryType::Circle:
		m_Circle = std::make_shared<CCircle>();
		Reader->GetGeometry(*m_Circle);
		return m_Circle;

	case GeometryType::Section:
		m_Section = std::make_shared<CSection>();
		Reader->GetGeometry(*m_Section);
		return m_Section;

	default:
		return nullptr;
	}
}