#include "CPolyLine.h"

CPath::CPath(const CPath& c):m_Pois(c.m_Pois)
{
}

CPath& CPath::operator=(const CPath& c)
{
	m_Pois = c.m_Pois;
	return *this;
}

GeometryType CPath::GetType()
{
	return GeometryType::Path;
}

//TODO
const char* CPath::ToWKT()
{
	return "TODO";
}

//TODO
const char* CPath::ToGeojson()
{
	return "TODO";
}

float CPath::Circum()
{
	float sum = 0;
	for (std::vector<CPoint>::iterator iter = m_Pois.begin(); iter != m_Pois.end() - 1; iter++)
	{
		sum += CPoint_Distance(*iter, *(iter + 1));
	}
	return sum;
}

bool CPath::AppendPoint(CPoint c)
{
	if (!CheckDuplicate(c))
	{
		m_Pois.push_back(c);
		return true;
	}
	else
		return false;
}

bool CPath::InsertPoint(int pos, CPoint c)
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
		else
			return false;
	}
}


bool CPath::DeletePoint(CPoint c)
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

bool CPath::DeletePoint(int pos)
{
	if (pos<0 || pos>m_Pois.size())
		return false;
	else
	{
		m_Pois.erase(m_Pois.begin() + pos);
		return true;
	}
}

CPoint CPath::QureyPoint(int pos)
{
	if (pos<0 || pos>m_Pois.size())
		throw std::range_error("pos超出范围! ");
	else
	{
		return m_Pois[pos];
	}
}

bool CPath::AlterPoint(int pos, CPoint c)
{
	if (pos<0 || pos>m_Pois.size())
	{
		/*throw std::range_error("pos超出范围! ");*/
		return false;
	}
	else if (CheckDuplicate(c))
	{
		/*throw std::logic_error("已经存在该点! ");*/
		return false;
	}
	else
	{
		m_Pois[pos] = c;
		return true;
	}
}

CPath CPath::operator +(CPoint c)
{
	CPath copy(*this);
	copy.AppendPoint(c);
	return copy;
}

CPath CPath::operator - (CPoint c)
{
	CPath copy(*this);
	copy.DeletePoint(c);
	return copy;
}

CPath& CPath::operator+=(CPoint c)
{
	this->AppendPoint(c);
	return *this;
}

CPath& CPath::operator -=(CPoint c)
{
	this->DeletePoint(c);
	return *this;
}

bool CPath::CheckDuplicate(CPoint c)
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

bool CPath::operator==(CPath c)
{
	if (m_Pois.size() != c.m_Pois.size())
		return false;
	else
	{
		for (int i = 0; i < m_Pois.size(); i++)
		{
			if (m_Pois[i] != c.m_Pois[i])
				return false;
		}
		return true;
	}
}

bool CPath::operator!=(CPath c)
{
	return !(*this == c);
}

CPoint& CPath::operator[](int pos)
{
	 if (pos<0 || pos>m_Pois.size())
		throw std::range_error("pos超出范围! ");
	 else
	 {
		return m_Pois[pos];
	}
}

/*--------------------------------------------PolyLine实现------------------------------------------------------*/
/*----------------------------------------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------------------------------------*/


CPolyLine::CPolyLine(const CPolyLine& c)
{
	for (int i = 0; i < c.m_Paths.size(); i++)
	{
		CPath *p = new CPath(*c.m_Paths[i]);
		m_Paths.push_back(p);
	}
}

CPolyLine& CPolyLine::operator=(const CPolyLine& c)
{
	for (int i = 0; i < m_Paths.size(); i++)
	{
		delete m_Paths[i];
	}
	m_Paths.clear();
	for (int i = 0; i < c.m_Paths.size(); i++)
	{
		CPath *p = new CPath(*c.m_Paths[i]);
		m_Paths.push_back(p);
	}
	return *this;
}

CPolyLine::~CPolyLine()
{
	for (int i = 0; i < m_Paths.size(); i++)
	{
		delete m_Paths[i];
	}
	m_Paths.clear();
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
	for (std::vector<CPath*>::iterator iter = m_Paths.begin(); iter != m_Paths.end(); iter++)
	{
		sum += (*iter)->Circum();
	}
	return sum;
}

bool CPolyLine::AppendPath(CPath* c)
{
	if (!CheckDuplicate(c))
		{
			m_Paths.push_back(c);
			return true;
		}
		else
			return false;
}

bool CPolyLine::DeletePath(CPath* c)
{
	for (std::vector<CPath*>::iterator iter = m_Paths.begin(); iter != m_Paths.end(); iter++)
	{
		if (c == *iter)
		{
			iter = m_Paths.erase(iter);
			return true;
		}
	}
	return false;
}

CPath* CPolyLine::QureyPath(int pos)
{
	if (pos<0 || pos>m_Paths.size())
		throw std::range_error("pos超出范围! ");
	else
	{
		return m_Paths[pos];
	}
}

bool CPolyLine::AlterPath(int pos, CPath* c)
{
	if (pos<0 || pos>m_Paths.size())
	{
		/*throw std::range_error("pos超出范围! ");*/
		return false;
	}
	else if (CheckDuplicate(c))
	{
		/*throw std::logic_error("已经存在该点! ");*/
		return false;
	}
	else
	{
		delete m_Paths[pos];
		m_Paths[pos] = c;
		return true;
	}
}

CPath* CPolyLine::operator[](int pos)
{
	if (pos<0 || pos>m_Paths.size())
		throw std::range_error("pos超出范围! ");
	else
	{
		return m_Paths[pos];
	}
}

bool CPolyLine::CheckDuplicate(CPath* c)
{
	for (int i = 0; i < m_Paths.size(); i++)
	{
		if (*c == *m_Paths[i])
		{
			return true;
		}
	}
	return false;
}
