#include "CPoint.h"

GeometryType CPoint::GetType()const
{
	return GeometryType::Point;
}

CPoint::CPoint(float x, float y):m_X(x),m_Y(y)
{
}

CPoint::CPoint():m_X(0),m_Y(0)
{
}

CPoint::CPoint(const CPoint& c)
{
	this->m_X = c.m_X;
	this->m_Y = c.m_Y;
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

float CPoint::operator*(CPoint c)const
{
	return this->m_X * c.m_X + this->m_Y * c.m_Y;
}

float CPoint::operator^(CPoint c)const
{
	return this->m_X * c.m_Y - this->m_Y * c.m_X;
}

bool CPoint::operator==(CPoint c)const
{
	if (this->m_X == c.m_X && this->m_Y == c.m_Y)
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

float CPoint_Distance(const CPoint& c1, const CPoint& c2)
{
	float dx = c1.x() - c2.x();
	float dy = c1.y()- c2.y();
	return sqrt(dx*dx+dy*dy);
}

const char* CPoint::ToWKT()const
{
	return "POINT(" + (char)m_X + ' ' + (char)m_Y + ')';
}

//TODO
const char* CPoint::ToGeojson()const
{
	return " TODO";
}