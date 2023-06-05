#include "CFeature.h"


bool CFeature::AppendGeometry(CGeometry* geo)
{
	if (CheckCorrectType(geo->GetType()))
	{
		m_vector.push_back(geo);
		return true;
	}
	else
		return false;
}

bool CFeature::DeleteGeometry(CGeometry* geo)
{
	if (!CheckCorrectType(geo->GetType()))
		return false;
	for (int i = 0; i < m_vector.size(); i++)
	{
		if (m_vector[i] == geo)
		{
			delete m_vector[i];
			m_vector.erase(m_vector.begin() + i);
			return true;
		}
	}
}

bool CFeature::CheckCorrectType(GeometryType type)
{
	if (Type == type)
	{
		return true;
	}
	else
	{
		return false;
	}
}
