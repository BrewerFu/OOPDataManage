#include "CPoint.h"

GeometryType CPoint::GetType()const
{
	return GeometryType::Point;
}

CPoint::CPoint(double x, double y):m_X(x),m_Y(y)
{
	ID = GetNewID(this);
}

CPoint::CPoint():m_X(0),m_Y(0)
{
	ID = GetNewID(this);
}

CPoint::CPoint(const CPoint& c)
{
	ID = GetNewID(this);
	this->m_X = c.m_X;
	this->m_Y = c.m_Y;
}

CPoint::~CPoint()
{
	ReleaseID(ID);
}

CPoint CPoint::operator=(const CPoint& c)
{
	this->m_X = c.m_X;
	this->m_Y = c.m_Y;
	return *this;
}

CPoint CPoint::operator +(CPoint c)const
{
	return CPoint(m_X + c.m_X, m_Y + c.m_Y);
}

CPoint CPoint::operator-(CPoint c)const
{
	return CPoint(m_X - c.m_X, m_Y + c.m_Y);
}

CPoint& CPoint::operator+=(CPoint c)
{
	this->m_X += c.m_X;
	this->m_Y += c.m_Y;
	return *this;
}

CPoint& CPoint::operator-=(CPoint c)
{
	this->m_X -= c.m_X;
	this->m_Y -= c.m_Y;
	return *this;
}

double CPoint::operator*(CPoint c)const
{
	return this->m_X * c.m_X + this->m_Y * c.m_Y;
}

double CPoint::operator^(CPoint c)const
{
	return this->m_X * c.m_Y - this->m_Y * c.m_X;
}

bool CPoint::operator==(const CPoint& other) const
{
	if (this->m_X == other.m_X && this->m_Y == other.m_Y)
		return true;
	else
		return false;
}

bool CPoint::operator!=(CPoint c)const
{
	if (*this == c)
		return false;
	else
		return true;
}

double CPoint_Distance(const CPoint& c1, const CPoint& c2)
{
	double dx = c1.x() - c2.x();
	double dy = c1.y()- c2.y();
	return sqrt(dx*dx+dy*dy);
}

const char* CPoint::ToWKT()const
{
	std::ostringstream oss;
	oss << "POINT(" << m_X << " " << m_Y << ")";
	std::string wkt = oss.str();
	return wkt.c_str();
}

//TODO
const char* CPoint::ToGeojson()const
{
	std::ostringstream oss;
	oss << "{\"type\":\"Point\",\"coordinates\":[" << m_X << "," << m_Y << "]}";
	std::string geojson = oss.str();
	return geojson.c_str();
}
