#include"TextWriter.h"

TextWriter::~TextWriter()
{
	Close();
}

bool TextWriter::Open(QString FileName)
{
	QFileInfo fileInfo(FileName);
	m_FileName = fileInfo.fileName();
	m_FilePath = fileInfo.path();

	try
	{
		//设置文件读取路径
		qfs.setFileName(m_FilePath+"/~"+m_FileName);
		//设置打开方式
		if (!qfs.open(QIODevice::WriteOnly))
			return false;
		if (!qfs.isOpen())
			return false;
		//设置文本流
		qts.setDevice(&qfs);
	}
	catch (std::exception e)
	{
		return false;
	}
	return true;
}

bool TextWriter::Write(CFeature* feature)
{
	if(!WriteHeader(feature))
		return false;

	GeometryType type = feature->GetType();
	for (CFeature::iterator iter = feature->begin(); iter != feature->end(); ++iter)
	{
		switch (type)
		{
		case GeometryType::Undefined:
			break;
		case GeometryType::Point:
			if (WritePoint(std::dynamic_pointer_cast<CPoint>(*iter)))
				break;
			else
				return false;
		case GeometryType::PolyLine:
			if (WritePolyLine(std::dynamic_pointer_cast<CPolyLine>(*iter)))
				break;
			else
				return false;
		case GeometryType::PolyGon:
			if (WritePolyGon(std::dynamic_pointer_cast<CPolyGon> (*iter)))
				break;
			else
				return false;
		case GeometryType::RectAngle:
			if (WriteRectAngle(std::dynamic_pointer_cast<CRectAngle>(*iter)))
				break;
			else
				return false;
		case GeometryType::Circle:
			if (WriteCircle(std::dynamic_pointer_cast<CCircle>(*iter)))
				break;
			else
				return false;
		case GeometryType::Section:
			if (WriteSection(std::dynamic_pointer_cast<CSection>(*iter)))
				break;
			else
				return false;
		default:
			return false;
		}
	}
	return true;
}

bool TextWriter::WriteHeader(const CFeature* feature)
{
	GeometryType type = feature->GetType();
	switch (type)
	{
	case GeometryType::Undefined:
		return false;
	case GeometryType::Point:
		qts << "CPoint" << "\n";
		break;
	case GeometryType::PolyLine:
		qts << "CPolyLine" << "\n";
		break;
	case GeometryType::PolyGon:
		qts << "CPolyGon" << "\n";
		break;
	case GeometryType::RectAngle:
		qts << "CRectAngle" << "\n";
		break;
	case GeometryType::Circle:
		qts << "CCircle" << "\n";
		break;
	case GeometryType::Section:
		qts << "CSection" << "\n";
		break;
	default:
		return false;
	}
	qts << "\n" << "Data" << "\n";
	return true;
}

bool TextWriter::WriterAttribute(const std::shared_ptr<CGeometry> geo)
{
	//写几何边界数据
	qts << "\tBoundary\n";
	qts << "\t\t" << "Color" << " " << geo->BoundaryColor.red() << " " << geo->BoundaryColor.green() << " " << geo->BoundaryColor.blue() << " " << geo->BoundaryColor.alpha() << "\n";
	qts << "\t\t" << "Style" << " " << geo->BoundaryStyle.m_Width << " " << QString::number(geo->BoundaryStyle.m_PenStyle) << "\n";

	//写几何填充数据
	qts << "\tFill\n";
	qts << "\t\t" << "Color" << " " << geo->FillColor.red() << " " << geo->FillColor.green() << " " << geo->FillColor.blue() << " " << geo->FillColor.alpha() << "\n";
	qts << "\t\t" << "Style" << " " << QString::number(geo->FillStyle.m_BrushStyle) << "\n";
	qts << "\n";
	return true;
}

bool TextWriter::WritePoint(const std::shared_ptr<CPoint> point)
{
	//写点标志和数据
	qts << "\tPoint\n";
	qts << "\t\t" << point->x() << " " << point->y() << "\n";
	
	WriterAttribute(point);
	return true;
}

bool TextWriter::WritePolyLine(std::shared_ptr<CPolyLine> polyline)
{
	//写多边形标志和折线数
	qts << "PolyLine" << " " << polyline->GetCount() << "\n";
	for (CPolyLine::iterator iter = polyline->begin(); iter != polyline->end(); ++iter)
	{
		//写单折线标志和点数
		qts<<"\tPath"<<" "<<(*iter)->GetCount()<<"\n";
		for (CPath::iterator iter1 = (*iter)->begin(); iter1 != (*iter)->end(); ++iter1)
		{
			qts << "\t\tPoint" << " " << (*iter1)->x() << " " << (*iter1)->y() << "\n";
		}
	}
	WriterAttribute(polyline);
	return true;
}

bool TextWriter::WritePolyGon(std::shared_ptr<CPolyGon> polygon)
{
	//写多边形标志和折线数
	qts << "PolyGon" << " " << polygon->GetCount() << "\n";
	for (CPolyGon::iterator iter = polygon->begin(); iter != polygon->end(); ++iter)
	{
		//写单环标志和点数
		qts << "\tRing" << " " << (*iter)->GetCount() << "\n";
		for(CRing::iterator iter1 = (*iter)->begin(); iter1 != (*iter)->end(); ++iter1)
		{
			qts << "\t\tPoint" << " " << (*iter1)->x() << " " << (*iter1)->y() << "\n";
		}
	}
	WriterAttribute(polygon);
	return true;
}

bool TextWriter::WriteRectAngle(const std::shared_ptr<CRectAngle> rectangle)
{
	//写矩形标志
	qts << "RectAngle" << "\n";
	//写矩形左上和右下两个点
	qts << "\tPoint" << " " << rectangle->GetLT()->x() << " " << rectangle->GetLT()->y() << "\n";
	qts << "\tPoint" << " " << rectangle->GetRB()->x() << " " << rectangle->GetRB()->y() << "\n";

	WriterAttribute(rectangle);
	return true;
}

bool TextWriter::WriteCircle(const std::shared_ptr<CCircle> circle)
{
	//写圆标志
	qts << "Circle" << "\n";
	//写圆心和半径
	qts << "\tPoint" << " " << circle->GetC()->x() << " " << circle->GetC()->y() << "\n";
	qts << "\tFloat" << " " << circle->GetR() << "\n";

	WriterAttribute(circle);
	return true;
}

bool TextWriter::WriteSection(const std::shared_ptr<CSection> section)
{
	//写扇形标志
	qts << "Section" << "\n";
	//写圆心和半径
	qts << "\tPoint" << " " << section->GetC()->x() << " " << section->GetC()->y() << "\n";
	qts << "\tFloat" << " " << section->GetR() << "\n";
	//写起始角和终止角
	qts << "\tPoint" << " " << section->GetSAngle() << "\n";
	qts << "\tPoint" << " " << section->GetEAngle() << "\n";

	WriterAttribute(section);
	return true;
}

