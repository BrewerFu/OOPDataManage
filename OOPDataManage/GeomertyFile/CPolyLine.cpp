#include "CPolyLine.h"

CPolyLine::CPolyLine(const CPolyLine& c):m_Pois(c.m_Pois)
{

}

GeometryType CPolyLine::GetType()
{
	return GeometryType::PolyLine;
}

//TODO
const char* CPolyLine::ToWKT()
{
	return "TODO";
}

//TODO
const char* CPolyLine::ToGeojson()
{
	return "TODO";
}

float CPolyLine::Circum()
{
	float sum = 0;
	for (std::vector<CPoint>::iterator iter = m_Pois.begin(); iter != m_Pois.end() - 1; iter++)
	{
		sum += CPoint_Distance(*iter, *(iter + 1));
	}
	return sum;
}

void CPolyLine::AppendPoint(CPoint c)
{
	if(!CheckDuplicate(c))
		m_Pois.push_back(c);
}

bool CPolyLine::InsertPoint(int pos, CPoint c)
{
	if (pos<0 || pos>m_Pois.size())
		return false;
	else
	{
		if (CheckDuplicate(c))
		{
			m_Pois.insert(m_Pois.begin() + pos, c);
			return true;
		}
	}
}


bool CPolyLine::DeletePoint(CPoint c)
{
	for (std::vector<CPoint>::iterator iter = m_Pois.begin(); iter != m_Pois.end(); iter++)
	{
		if (c == *iter)
		{
			iter = m_Pois.erase(iter);
			return true;
		}
	}
	return false;
}

bool CPolyLine::DeletePoint(int pos)
{
	if (pos<0 || pos>m_Pois.size())
		return false;
	else
	{
		m_Pois.erase(m_Pois.begin() + pos);
		return true;
	}
}

CPoint CPolyLine::QureyPoint(int pos)
{
	if (pos<0 || pos>m_Pois.size())
		throw std::range_error("pos超出范围! ");
	else
	{
		return m_Pois[pos];
	}
}

void CPolyLine::AlterPoint(int pos, CPoint c)
{
	if (pos<0 || pos>m_Pois.size())
	{
		throw std::range_error("pos超出范围! ");
	}
	else if (CheckDuplicate(c))
	{
		throw std::logic_error("已经存在该点! ");
	}
	else
	{
		m_Pois[pos] = c;
	}
}

CPolyLine CPolyLine::operator +(CPoint c)
{
	CPolyLine copy(*this);
	copy.AppendPoint(c);
	return copy;
}

CPolyLine CPolyLine::operator - (CPoint c)
{
	CPolyLine copy(*this);
	copy.DeletePoint(c);
	return copy;
}

CPolyLine& CPolyLine::operator+=(CPoint c)
{
	this->AppendPoint(c);
	return *this;
}

CPolyLine& CPolyLine::operator -=(CPoint c)
{
	this->DeletePoint(c);
	return *this;
}

bool CPolyLine::CheckDuplicate(CPoint c)
{
	for (std::vector<CPoint>::iterator iter = m_Pois.begin(); iter != m_Pois.end(); iter++)
	{
		if (c == *iter)
		{
			return true;
		}
	}
	return false;
}