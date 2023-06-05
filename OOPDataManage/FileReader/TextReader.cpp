#include"TextReader.h"

bool TextReader::Open(const char* FileName)
{
	try
	{
		//设置文件读取路径
		qfs.setFileName(FileName);
		//设置打开方式
		if (!qfs.open(QIODevice::ReadWrite))
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

bool TextReader::isNext()
{
	return !qts.atEnd();
}

bool TextReader::Close()
{
	qfs.close();
	return true;
}

GeometryType TextReader::GetType()
{
	qstr = qts.readLine();
	if (qstr == "CPoint")
		return GeometryType::Point;
	else if(qstr=="CPolyLine")
		return GeometryType::PolyLine;
	else if (qstr == "CPolyGon")
		return GeometryType::PolyGon;
	else if (qstr == "CRectAngle")
		return GeometryType::RectAngle;
	else if (qstr == "CCircle")
		return GeometryType::Circle;
	else if (qstr == "CSection")
		return GeometryType::Section;
	else
		return GeometryType::Undefined;
}

void TextReader::ToData()
{
	if (!HaveToData)
	{
		qts.seek(0);
		while (!qts.atEnd())
		{
			qstr = qts.readLine();
			if (qstr == "Data")
				break;
		}
		HaveToData = true;
	}
}

QColor TextReader::ReadColor()
{
	QColor color;
	QRgb rgb;
	qstr = qts.readLine().trimmed();
	qsl = qstr.split(" ");
	rgb = qRgba(qsl[1].toInt(), qsl[2].toInt(), qsl[3].toInt(),qsl[4].toInt());
	color.fromRgba(rgb);
	return color;
}

CBoundaryStyle TextReader::ReadBoundaryStyle()
{
	CBoundaryStyle boundary;
	qstr = qts.readLine().trimmed();
	qsl = qstr.split(" ");
	boundary.m_Width = qsl[1].toFloat();
	boundary.m_PenStyle = (Qt::PenStyle)qsl[2].toInt();
	return boundary;
}

template<class T>
bool TextReader::ReadAttribute(T& t)
{
	if(isNext())
		qstr = qts.readLine().trimmed();
	else
		return false;
	if (qstr == "Boundary")
	{
		t.BoundaryColor = ReadColor();
		t.BoundaryStyle = ReadBoundaryStyle();
		qstr = qts.readLine().trimmed();
	}
	//读取填充属性
	if (qstr == "Fill")
	{
		t.FillColor = ReadColor();
		t.FillStyle = ReadFillStyle();
	}
	return true;
}

CFillStyle TextReader::ReadFillStyle()
{
	CFillStyle fill;
	qstr = qts.readLine().trimmed();
	qsl = qstr.split(" ");
	fill.m_BrushStyle = (Qt::BrushStyle)qsl[1].toInt();
	return fill;
}

CPoint TextReader::ReadPoint()
{
	CPoint point;
	//读取Point坐标
	qstr = qts.readLine().trimmed();
	qsl = qstr.split(" ");
	if (qsl[0] == "Point")
	{
		point.x(qsl[1].toFloat());
		point.y(qsl[2].toFloat());
		return point;
	}
	else
		throw "读取Point坐标失败";
}

int TextReader::GetGeometry(CPoint& point)
{
	if (!HaveToData)
		ToData();

	//读取Point标志
	do
	{
		if (qts.atEnd())
			return 0;
		qstr = qts.readLine().trimmed();
	} while (qstr == "Point");

	//读取Point坐标
	qstr = qts.readLine().trimmed();
	qsl = qstr.split(" ");
	point.x(qsl[0].toFloat());
	point.y(qsl[1].toFloat());

	ReadAttribute(point);
	return 1;
}

int TextReader::GetGeometry(CPolyLine& Line)
{
	if (!HaveToData)
		ToData();

	//读取PolyLine标志
	do
	{
		if (qts.atEnd())
			return 0;
		qstr = qts.readLine().trimmed();
		qsl = qstr.split(" ");

	} while (qsl[0] != "PolyLine");

	//获取Cpath单折线数
	int pathCount = qsl[1].toInt();
	for (int i = 0; i < pathCount; i++)
	{
		do
		{
			if (qts.atEnd())
				return 0;
			qstr = qts.readLine().trimmed();
			qsl = qstr.split(" ");
		} while (qsl[0] != "Path");

		CPath* path = new CPath;
		//获取CPath点数
		int pointCount = qsl[1].toInt();
		for (int i = 0; i < pointCount; i++)
			*path += ReadPoint();
		//添加单折线
		Line.AppendPath(path);
	}

	ReadAttribute(Line);
	return 1;
}

int TextReader::GetGeometry(CPolyGon& Gon)
{
	
	if (!HaveToData)
		ToData();

	//读取PolyGon标志
	do
	{
		if (qts.atEnd())
			return 0;
		qstr = qts.readLine().trimmed();
		qsl = qstr.split(" ");

	} while (qsl[0] != "PolyGon");

	//获取CRing单环数
	int ringCount = qsl[1].toInt();
	for (int i = 0; i < ringCount; i++)
	{
		do
		{
			if (qts.atEnd())
				return 0;
			qstr = qts.readLine().trimmed();
			qsl = qstr.split(" ");
		} while (qsl[0] != "Ring");

		CRing* ring = new CRing;
		//获取CRing点数
		int pointCount = qsl[1].toInt();
		for (int i = 0; i < pointCount; i++)
			*ring += ReadPoint();
		//添加单环
		Gon.AppendRing(ring);
	}

	ReadAttribute(Gon);
	return 1;
}

int TextReader::GetGeometry(CRectAngle& Rect)
{
	if (!HaveToData)
		ToData();

	//读取RectAngle标志
	do
	{
		if (qts.atEnd())
			return 0;
		qstr = qts.readLine().trimmed();

	} while (qstr != "RectAngle");

	//读取RectAngle坐标
	Rect.LT(ReadPoint());
	Rect.RB(ReadPoint());


	ReadAttribute(Rect);
	return 1;
}

int TextReader::GetGeometry(CCircle& Cir)
{
	if (!HaveToData)
		ToData();

	//读取Circle标志
	do
	{
		if (qts.atEnd())
			return 0;
		qstr = qts.readLine().trimmed();

	} while (qstr != "Circle");

	//读取Circle坐标
	Cir.C(ReadPoint());
	//读取Circle半径
	qstr = qts.readLine().trimmed();
	qsl = qstr.split(" ");
	Cir.R(qsl[1].toFloat());

	ReadAttribute(Cir);
	return 1;
	
}

int TextReader::GetGeometry(CSection& Sec)
{
	if (!HaveToData)
		ToData();

	//读取Section标志
	do
	{
		if (qts.atEnd())
			return 0;
		qstr = qts.readLine().trimmed();

	} while (qstr != "Section");

	//读取Section坐标
	Sec.C(ReadPoint());
	//读取Section半径
	qstr = qts.readLine().trimmed();
	qsl = qstr.split(" ");
	Sec.R(qsl[1].toFloat());
	//读取Section起始角度
	qstr = qts.readLine().trimmed();
	qsl = qstr.split(" ");
	Sec.SAngle(qsl[1].toFloat());
	//读取Section终止角度
	qstr = qts.readLine().trimmed();
	qsl = qstr.split(" ");
	Sec.EAngle(qsl[1].toFloat());

	ReadAttribute(Sec);
	return 1;

}
