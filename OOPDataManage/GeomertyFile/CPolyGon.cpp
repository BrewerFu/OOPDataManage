#include "CPolyGon.h"

CRing::CRing(const CRing& ring)
{
	for(int i=0;i<ring.m_Pois.size();i++)
	{
		m_Pois.push_back(CPoint(ring.m_Pois[i]));
	}
}

GeometryType CRing::GetType()const
{
	return GeometryType::Ring;
}

const char* CRing::ToWKT()const
{
	return "TODO";
}

const char* CRing::ToGeojson()const
{
	return "TODO";
}

float CRing::Area()const
{
	float sum = 0;
	for (int i = 0; i < m_Pois.size()-1; i++)
	{
		sum += m_Pois[i] ^ m_Pois[i + 1];
	}
	sum += m_Pois[m_Pois.size() - 1] ^ m_Pois[0];
	return sum / 2;
}

float CRing::Circum()const
{
	float sum = CPath::Circum();
	sum += CPoint_Distance(m_Pois[0], m_Pois[m_Pois.size() - 1]);
	return sum;
}


/*--------------------------------------------------------------------------------*/

CPolyGon::CPolyGon(const CPolyGon& poly)
{
for (int i = 0; i < poly.m_Rings.size(); i++)
	{
		m_Rings.push_back(new CRing(*poly.m_Rings[i]));
	}
}

CPolyGon::~CPolyGon()
{
	for (int i = 0; i < m_Rings.size(); i++)
	{
		delete m_Rings[i];
	}
	m_Rings.clear();
}

GeometryType CPolyGon::GetType()const
{
	return GeometryType::PolyGon;
}

//TODO
const char* CPolyGon::ToWKT()const
{
	return "TODO";
}

//TODO
const char* CPolyGon::ToGeojson()const
{
	return "TODO";
}

bool CPolyGon::AppendRing(CRing* pRing)
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

bool CPolyGon::DeleteRing(CRing* pRing)
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

CRing* CPolyGon::QueryRing(int index)const
{
if (index < 0 || index >= m_Rings.size())
		return nullptr;
	else
		return m_Rings[index];
}

bool CPolyGon::AlterRing(int index, CRing* ring)
{
	//如果索引越界，返回false
	if (index < 0 || index >= m_Rings.size())
		return false;
	else
	{
		//删除原来的ring
		delete m_Rings[index];
		m_Rings[index] = ring;
		return true;
	}
}

bool CPolyGon::CheckDuplicate(CRing* pRing)
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

CRing* CPolyGon::operator[](int pos)
{
	return QueryRing(pos);
}