#include "CPolyGon.h"

GeometryType CPolyGon::GetType()
{
	return GeometryType::PolyGon;
}

//TODO
const char* CPolyGon::ToWKT()
{
	return "TODO";
}

//TODO
const char* CPolyGon::ToGeojson()
{
	return "TODO";
}


float CPolyGon::Circum()
{
	float sum = CPolyLine::Circum();
	sum += CPoint_Distance(m_Pois[0], m_Pois[m_Pois.size()-1]);
	return sum;
}
float CPolyGon::Area()
{
	float sum = 0;
	for (std::vector<CPoint>::iterator iter = m_Pois.begin(); iter != m_Pois.end()-1; iter++)
	{
		sum += *iter ^ *(iter + 1);
	}
	sum += m_Pois[m_Pois.size()-1] ^ m_Pois[0];
	return 0.5 * sum;
}
