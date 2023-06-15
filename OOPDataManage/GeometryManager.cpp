//#include "GeometryManager.h"
//
//获取单例
//GeometryManager& GeometryManager::GetInstance()
//{
//	static GeometryManager geometryManager;
//	return geometryManager;
//}
//
//构造函数
//GeometryManager::GeometryManager()
//{
//}
//
//GeometryManager::~GeometryManager()
//{
//}
//
//CGeometry* GeometryManager::CreateGeometry(GeometryType type)
//{
//	switch (type)
//	{
//	case GeometryType::Point:
//		return m_pPointFactory->CreateGeometry(type);
//	case GeometryType::Path:
//		return m_pPathFactory->CreateGeometry(type);
//	case GeometryType::PolyLine:
//		return m_pPolyLineFactory->CreateGeometry(type);
//	case GeometryType::Ring:
//		return m_pRingFactory->CreateGeometry(type);
//	case GeometryType::PolyGon:
//		return m_pPolyGonFactory->CreateGeometry(type);
//	case GeometryType::RectAngle:
//		return m_pRectAngleFactory->CreateGeometry(type);
//	case GeometryType::Circle:
//		return m_pCircleFactory->CreateGeometry(type);
//	case GeometryType::Section:
//		return m_pSectionFactory->CreateGeometry(type);
//	default:
//		return nullptr;
//	}
//}
//
//
//void GeometryManager::DestroyGeometry(CGeometry* pGeometry)
//{
//	switch (pGeometry->GetType())
//	{
//	case GeometryType::Point:
//		m_pPointFactory->DestroyGeometry(pGeometry);
//		break;
//	case GeometryType::PolyLine:
//		m_pPolyLineFactory->DestroyGeometry(pGeometry);
//		break;
//	case GeometryType::PolyGon:
//		m_pPolyGonFactory->DestroyGeometry(pGeometry);
//		break;
//	case GeometryType::RectAngle:
//		m_pRectAngleFactory->DestroyGeometry(pGeometry);
//		break;
//	case GeometryType::Circle:
//		m_pCircleFactory->DestroyGeometry(pGeometry);
//		break;
//	case GeometryType::Section:
//		m_pSectionFactory->DestroyGeometry(pGeometry);
//		break;
//	default:
//		break;
//	}
//}
//
//int GeometryFactory::GetUnusedID()
//{
//	 if (m_unusedIds.empty())
//    {
//         如果没有未使用的 id，则分配一个新的 id
//        return m_map.size() + 1;
//    }
//    else
//    {
//         如果有未使用的 id，则返回最小的未使用的 id
//        int id = *m_unusedIds.begin();
//        m_unusedIds.erase(m_unusedIds.begin());
//        return id;
//    }
//}
//
//bool GeometryFactory::DestroyGeometry(CGeometry* pGeometry)
//{
//	int id = pGeometry->GetID();
//	if (m_map.find(id) != m_map.end())
//	{
//		CGeometry* p = m_map[id];
//		m_map.erase(id);
//		RecycleID(id);
//		delete p;
//		return true;
//	}
//	else
//		return false;
//}
//
//void GeometryFactory::RecycleID(int id)
//{
//	 将 id 标记为未使用的
//	m_unusedIds.insert(id);
//}
//
//GeometryFactory::~GeometryFactory()
//{
//	for(auto it = m_map.begin(); it != m_map.end(); it++)
//	{
//		delete it->second;
//	}
//	m_map.clear();
//}
//
//CGeometry* CPointFactory::CreateGeometry(GeometryType type)
//{
//	if (type == GeometryType::Point)
//	{
//		int id = GetUnusedID();
//		CPoint* p = new CPoint();
//		p->SetID(id);
//		m_map[id] = p;
//	}
//	else
//		return nullptr;
//}
//
//CGeometry* CPathFactory::CreateGeometry(GeometryType type)
//{
//	if (type == GeometryType::Path)
//	{
//		int id = GetUnusedID();
//		std::shared_ptr<CPath> p = new CPath();
//		p->SetID(id);
//		m_map[id] = p;
//	}
//	else
//		return nullptr;
//}
//
//CGeometry* CPolyLineFactory::CreateGeometry(GeometryType type)
//{
//	if (type == GeometryType::PolyLine)
//	{
//		int id = GetUnusedID();
//		CPolyLine* p = new CPolyLine();
//		p->SetID(id);
//		m_map[id] = p;
//	}
//	else
//		return nullptr;
//}
//
//CGeometry* CRingFactory::CreateGeometry(GeometryType type)
//{
//if (type == GeometryType::Ring)
//	{
//		int id = GetUnusedID();
//		CRing* p = new CRing();
//		p->SetID(id);
//		m_map[id] = p;
//	}
//	else
//		return nullptr;
//}
//
//CGeometry* CPolyGonFactory::CreateGeometry(GeometryType type)
//{
//	if (type == GeometryType::PolyGon)
//	{
//		int id = GetUnusedID();
//		CGeometry* p = new CPolyGon();
//		p->SetID(id);
//		m_map[id] = p;
//	}
//	else
//		return nullptr;
//}
//
//CGeometry* CRectAngleFactory::CreateGeometry(GeometryType type)
//{
//	if (type == GeometryType::RectAngle)
//	{
//		int id = GetUnusedID();
//		CGeometry* p = new CRectAngle();
//		p->SetID(id);
//		m_map[id] = p;
//	}
//	else
//		return nullptr;
//}
//
//CGeometry* CCircleFactory::CreateGeometry(GeometryType type)
//{
//	if (type == GeometryType::Circle)
//	{
//		int id = GetUnusedID();
//		CGeometry* p = new CCircle();
//		p->SetID(id);
//		m_map[id] = p;
//	}
//	else
//		return nullptr;
//}
//
//CGeometry* CSectionFactory::CreateGeometry(GeometryType type)
//{
//	if (type == GeometryType::Section)
//	{
//		int id = GetUnusedID();
//		CGeometry* p = new CSection();
//		p->SetID(id);
//		m_map[id] = p;
//	}
//	else
//		return nullptr;
//}
//
//bool CPointFactory::DestroyGeometry(CGeometry* pGeometry)
//{
//	if(pGeometry==nullptr)
//		return false;
//	if (pGeometry->GetType() != GeometryType::Point)
//		return false;
//	if(m_map.find(pGeometry->GetID()) == m_map.end())
//		return false;
//
//}