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
	return false;
}

bool CFeature::CheckCorrectType(GeometryType type)
{
	if (m_Type == type)
	{
		return true;
	}
	else
	{
		return false;
	}
}

//void CFeature::Attach(Observer* observer)
//{
//	m_observers.push_back(observer);
//}

//bool CFeature::Detach(Observer* observer)
//{
//	for (int i = 0; i < m_observers.size(); i++)
//	{
//		if (m_observers[i] == observer)
//		{
//			m_observers.erase(m_observers.begin() + i);
//			return true;
//		}
//	}
//	return false;
//}

//void CFeature::Notify()
//{
//	for (int i = 0; i < m_observers.size(); i++)
//	{
//		m_observers[i]->Update(this);
//	}
//}

CFeatureManager::~CFeatureManager()
{
	for (auto it = m_map.begin(); it != m_map.end(); it++)
	{
		delete it->second;
	}
	m_map.clear();
}

CFeature* CFeatureManager::CreateFeature(GeometryType type)
{
	switch (type)
	{
	case GeometryType::Undefined:
		return nullptr;
	case GeometryType::Text:
		return nullptr;
	case GeometryType::BitMap:
		return nullptr;
	default:
		break;
	}
	int id = GetUnusedID();
	CFeature* feature = new CFeature(type);
	feature->SetID(id);
	/*feature->Attach(this);*/
	m_map.insert(std::make_pair(id, feature));
	return feature;

}

bool CFeatureManager::DestroyFeature(CFeature* feature)
{
	if (feature == nullptr)
		return false;
	int del_id = feature->GetID();
	if (m_map.find(del_id) == m_map.end())
		return false;
	m_map.erase(del_id);
	RecycleID(del_id);
	delete feature;
	return true;
}

int CFeatureManager::GetUnusedID()
{
	if (m_unusedIds.empty())
	{
		// 如果没有未使用的 id，则分配一个新的 id
		return m_map.size() + 1;
	}
	else
	{
		// 如果有未使用的 id，则返回最小的未使用的 id
		int id = *m_unusedIds.begin();
		m_unusedIds.erase(m_unusedIds.begin());
		return id;
	}
}

void CFeatureManager::RecycleID(int id)
{
	//将 id 标记为未使用的
	m_unusedIds.insert(id);
}

//void CFeatureManager::Update(Subject* subject)
//{
//	CFeature* feature = dynamic_cast<CFeature*>(subject);
//	if (feature == nullptr)
//		return;
//
//}