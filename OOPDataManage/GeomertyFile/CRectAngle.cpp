#include "CRectAngle.h"

//通过两个点构造
CRectAngle::CRectAngle(CPoint* lefttop, CPoint* rightbottom):m_LT(lefttop),m_RB(rightbottom)
{
	if (CheckReverse())
		throw std::logic_error("顶点不符合规范");
}


//通过一个点和长宽构造
CRectAngle::CRectAngle(CPoint* lefttop, float width, float height):m_LT(lefttop),m_RB(m_RB = &CPoint(lefttop->x() + width, lefttop->y() - height))
{
}

//获取几何类型
GeometryType CRectAngle::GetType()const
{
	return GeometryType::RectAngle;
}


const char* CRectAngle::ToWKT() const
{
	std::ostringstream oss;
	oss << "POLYGON ((";
	oss << m_LT->x() << " " << m_LT->y() << ", ";
	oss << m_RB->x() << " " << m_LT->y() << ", ";
	oss << m_RB->x() << " " << m_RB->y() << ", ";
	oss << m_LT->x() << " " << m_RB->y() << ", ";
	oss << m_LT->x() << " " << m_LT->y();
	oss << "))";
	std::string wkt = oss.str();
	return wkt.c_str();
}

const char* CRectAngle::ToGeojson() const
{
	std::ostringstream oss;
	oss << "{\"type\":\"Polygon\",\"coordinates\":[[[";
	oss << m_LT->x() << "," << m_LT->y() << "],[";
	oss << m_RB->x() << "," << m_LT->y() << "],[";
	oss << m_RB->x() << "," << m_RB->y() << "],[";
	oss << m_LT->x() << "," << m_RB->y() << "],[";
	oss << m_LT->x() << "," << m_LT->y();
	oss << "]]]}";
	std::string geojson = oss.str();
	return geojson.c_str();
}


//计算周长
float CRectAngle::Circum()const
{
	return CPoint_Distance(*m_LT, CPoint(m_LT->x(), m_RB->y())) * 2 + CPoint_Distance(*m_LT, CPoint(m_RB->x(), m_LT->y())) * 2;
}

//计算面积
float CRectAngle::Area()const
{
	return CPoint_Distance(*m_LT, CPoint(m_LT->x(), m_RB->y())) * CPoint_Distance(*m_LT, CPoint(m_RB->x(), m_LT->y()));
}

//获取宽度
float CRectAngle::GetWidth()const
{
	return m_RB->x() - m_LT->x();
}

//获取高度
float CRectAngle::GetHeight()const
{
	return m_LT->y() - m_RB->y();
}

//获取左上角顶点
CPoint* CRectAngle::GetLT()const
{
	return m_LT;
}

//获取右下角顶点
CPoint* CRectAngle::GetRB()const
{
	return m_RB;
}

//设置左上角顶点
void CRectAngle::SetLT(CPoint* c)
{
	if(c->x() > m_RB->x() || c->y() < m_RB->y())
		throw std::logic_error("顶点不符合规范");
}
//设置右下角顶点
void CRectAngle::SetRB(CPoint* c)
{
	if (c->x() < m_LT->x() || c->y() > m_LT->y())
		throw std::logic_error("顶点不符合规范");
}

//检查是否颠倒
bool CRectAngle::CheckReverse()const
{
	//如果左上角的x大于右下角的x或者左上角的y小于右下角的y，则颠倒
	if (m_LT->x() > m_RB->x() || m_LT->y() < m_RB->y())
		return true;
	else
		return false;
}
