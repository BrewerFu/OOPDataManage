#include "CPolyGon.h"

CRing::CRing()
{
	ID = GetNewID(this);
}

CRing::~CRing()
{

}

GeometryType CRing::GetType()const
{
	return GeometryType::Ring;
}

const char* CRing::ToWKT() const
{
	std::ostringstream oss;
	oss << "POLYGON (";
	oss << "(";
	for (int i = 0; i < GetCount(); ++i) 
	{
		oss << QureyPoint(i)->x() << " " << QureyPoint(i)->y();
		if (i != GetCount() - 1) 
		{
			oss << ", ";
		}
	}
	oss << ")";
	oss << ")";
	std::string wkt = oss.str();
	return wkt.c_str();
}

const char* CRing::ToGeojson() const
{
	std::ostringstream oss;
	oss << "{\"type\":\"Polygon\",\"coordinates\":[[";
	for (int i = 0; i < GetCount(); ++i) {
		oss << "[" << QureyPoint(i)->x() << "," << QureyPoint(i)->y() << "]";
		if (i != GetCount() - 1) {
			oss << ",";
		}
	}
	oss << "]]}";
	std::string geojson = oss.str();
	return geojson.c_str();
}

float CRing::Area()const
{
	float sum = 0;
	for (int i = 0; i < m_Pois.size()-1; i++)
	{
		sum += *m_Pois[i] ^ *m_Pois[i + 1];
	}
	sum += *m_Pois[m_Pois.size() - 1] ^ *m_Pois[0];
	return sum / 2;
}

float CRing::Circum()const
{
	float sum = 0;
	for (std::vector<std::shared_ptr<CPoint>>::const_iterator iter = m_Pois.begin(); iter != m_Pois.end() - 1; iter++)
	{
		sum += CPoint_Distance(**iter, **(iter + 1));
	}
	sum += CPoint_Distance(*m_Pois[0], *m_Pois[m_Pois.size() - 1]);
	return sum;
}

bool CRing::AppendPoint(std::shared_ptr<CPoint> c)
{
	if (!CheckDuplicate(c))
	{
		m_Pois.push_back(c);
		return true;
	}
	else
		return false;
}

bool CRing::InsertPoint(int pos, std::shared_ptr<CPoint> c)
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


bool CRing::DeletePoint(std::shared_ptr<CPoint> c)
{
	for (std::vector<std::shared_ptr<CPoint>>::iterator iter = m_Pois.begin(); iter != m_Pois.end(); iter++)
	{
		if (c == *iter)
		{
			iter = m_Pois.erase(iter);
			return true;
		}
	}
	return false;
}

bool CRing::DeletePoint(int pos)
{
	if (pos<0 || pos>m_Pois.size())
		return false;
	else
	{
		m_Pois.erase(m_Pois.begin() + pos);
		return true;
	}
}

std::shared_ptr<CPoint> CRing::QureyPoint(int pos)const
{
	if (pos<0 || pos>m_Pois.size())
		throw std::range_error("pos超出范围! ");
	else
	{
		return m_Pois[pos];
	}
}

bool CRing::AlterPoint(int pos, std::shared_ptr<CPoint> c)
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

bool CRing::CheckDuplicate(std::shared_ptr<CPoint> c)
{
	for (std::vector<std::shared_ptr<CPoint>>::const_iterator iter = m_Pois.begin(); iter != m_Pois.end(); iter++)
	{
		if (*c == **iter)
		{
			return true;
		}
	}
	return false;
}

bool CRing::operator==(CRing c)
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

bool CRing::operator!=(CRing c)
{
	if (m_Pois.size() != c.m_Pois.size())
		return false;
	else
	{
		for (int i = 0; i < m_Pois.size(); i++)
		{
			if (m_Pois[i] == c.m_Pois[i])
				return false;
		}
		return true;
	}
}

std::shared_ptr<CPoint> CRing::operator[](int pos)
{
	 if (pos<0 || pos>m_Pois.size())
		throw std::range_error("pos超出范围! ");
	 else
	 {
		return m_Pois[pos];
	}
}

/*--------------------------------------------------------------------------------*/



CPolyGon::CPolyGon()
{
	ID = GetNewID(this);
}

CPolyGon::~CPolyGon()
{
	ReleaseID(ID);
}

GeometryType CPolyGon::GetType()const
{
	return GeometryType::PolyGon;
}

const char* CPolyGon::ToWKT() const
{
	std::ostringstream oss;
	oss << "POLYGON (";
	for (int i = 0; i < GetCount(); ++i) 
	{
		std::shared_ptr<CRing> ring = QueryRing(i);
		oss << "(";
		for (int j = 0; j < ring->GetCount(); ++j) 
		{
			std::shared_ptr<CPoint> point = ring->QureyPoint(j);
			oss << point->x() << " " << point->y();
			if (j != ring->GetCount() - 1) 
			{
				oss << ", ";
			}
		}
		oss << ")";
		if (i != GetCount() - 1) 
		{
			oss << ", ";
		}
	}
	oss << ")";
	std::string wkt = oss.str();
	return wkt.c_str();
}

const char* CPolyGon::ToGeojson() const
{
	std::ostringstream oss;
	oss << "{\"type\":\"Polygon\",\"coordinates\":[";
	for (int i = 0; i < GetCount(); ++i) 
	{
		std::shared_ptr<CRing> ring = QueryRing(i);
		oss << "[";
		for (int j = 0; j < ring->GetCount(); ++j) 
		{
			std::shared_ptr<CPoint> point = ring->QureyPoint(j);
			oss << "[" << point->x() << "," << point->y() << "]";
			if (j != ring->GetCount() - 1) 
			{
				oss << ",";
			}
		}
		oss << "]";
		if (i != GetCount() - 1) 
		{
			oss << ",";
		}
	}
	oss << "]}";
	std::string geojson = oss.str();
	return geojson.c_str();
}

bool CPolyGon::AppendRing(std::shared_ptr<CRing> pRing)
{
	//如果指针为空，返回false
	if (pRing == nullptr)
		return false;
	//如果重复则，返回false
	if (CheckDuplicate(pRing))
	{
		m_Rings.push_back(pRing);
		return true;
	}
	else
		return false;
}

bool CPolyGon::DeleteRing(std::shared_ptr<CRing> pRing)
{
	if (pRing == nullptr)
		return false;
	for (int i = 0; i < m_Rings.size(); i++)
	{
		if (m_Rings[i] == pRing)
		{
			m_Rings.erase(m_Rings.begin() + i);
			return true;
		}
	}
	return false;
}

std::shared_ptr<CRing> CPolyGon::QueryRing(int index)const
{
if (index < 0 || index >= m_Rings.size())
		return nullptr;
	else
		return m_Rings[index];
}

bool CPolyGon::AlterRing(int index, std::shared_ptr<CRing> ring)
{
	//如果索引越界，返回false
	if (index < 0 || index >= m_Rings.size())
		return false;
	else
	{
		m_Rings[index] = ring;
		return true;
	}
}

bool CPolyGon::CheckDuplicate(std::shared_ptr<CRing> pRing)
{
	for (int i = 0; i < m_Rings.size(); i++)
	{
		if (m_Rings[i] == pRing)
			return false;
	}
	return true;
}

float CPolyGon::Area()const
{
	float sum = 0;
	for (int i = 0; i < m_Rings.size(); i++)
	{
		sum += m_Rings[i]->Area();
	}
	return sum;
}

float CPolyGon::Circum()const
{
	float sum = 0;
	for (int i = 0; i < m_Rings.size(); i++)
	{
		sum += m_Rings[i]->Circum();
	}
	return sum;
}

std::shared_ptr<CRing> CPolyGon::operator[](int pos)
{
	return QueryRing(pos);
}