//#include "GeometryManager.h"
//
////获取单例
//GeometryManager* GeometryManager::GetInstance()
//{
//	if (m_pGeometryManager != nullptr)
//		m_pGeometryManager = new GeometryManager();
//	else
//		return m_pGeometryManager;
//}
//
////释放单例
//void GeometryManager::DestroyInstance()
//{
//	if (m_pGeometryManager != nullptr)
//	{
//		delete m_pGeometryManager;
//		m_pGeometryManager = nullptr;
//	}
//}
//
//CGeometry* GeometryManager::CreateGeometry(GeometryType type)
//{
//	switch (type)
//	{
//	case GeometryType::Point:
//		return m_pPointFactory->CreateGeometry(type);
//	case GeometryType::PolyLine:
//		return m_pPolyLineFactory->CreateGeometry(type);
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
//GeometryManager::GeometryManager()
//{
//	m_pPointFactory = new CPointFactory();
//	m_pPolyLineFactory = new CPolyLineFactory();
//	m_pPolyGonFactory = new CPolyGonFactory();
//	m_pRectAngleFactory = new CRectAngleFactory();
//	m_pCircleFactory = new CCircleFactory();
//	m_pSectionFactory = new CSectionFactory();
//}
//
//GeometryManager::~GeometryManager()
//{
//	delete m_pPointFactory;
//	delete m_pPolyLineFactory;
//	delete m_pPolyGonFactory;
//	delete m_pRectAngleFactory;
//	delete m_pCircleFactory;
//	delete m_pSectionFactory;
//}
//
//void GeometryManager::OnGeometryDestory(GeometryType type, CGeometry* prt)
//{
//		switch (type)
//		{
//		case GeometryType::Point:
//			m_pPointFactory->DestroyGeometry(prt);
//			break;
//		case GeometryType::PolyLine:
//			m_pPolyLineFactory->DestroyGeometry(prt);
//			break;
//		case GeometryType::PolyGon:
//			m_pPolyGonFactory->DestroyGeometry(prt);
//			break;
//		case GeometryType::RectAngle:
//			m_pRectAngleFactory->DestroyGeometry(prt);
//			break;
//		case GeometryType::Circle:
//			m_pCircleFactory->DestroyGeometry(prt);
//			break;
//		case GeometryType::Section:
//			m_pSectionFactory->DestroyGeometry(prt);
//			break;
//		default:
//			break;
//		}
//}
//
//int GeometryFactory::getNextId()
//{
//	 if (m_unusedIds.empty())
//    {
//        // 如果没有未使用的 id，则分配一个新的 id
//        return m_map.size() + 1;
//    }
//    else
//    {
//        // 如果有未使用的 id，则返回最小的未使用的 id
//        int id = *m_unusedIds.begin();
//        m_unusedIds.erase(m_unusedIds.begin());
//        return id;
//    }
//}
//
//void GeometryFactory::releseId(int id)
//{
//	// 将 id 标记为未使用的
//	m_unusedIds.insert(id);
//}
//
//
//
//CGeometry* CPointFactory::CreateGeometry(GeometryType type)
//{
//	if (type == GeometryType::Point)
//	{
//		int id = getNextId();
//		CPoint* p = new CPoint();
//		p->setId(id);
//		m_map[id] = p;
//	}
//	else
//		return nullptr;
//}
//
//void CPointFactory::DestroyGeometry(CGeometry* pGeometry)
//{
//	int id = pGeometry->getId();
//	if (m_map.find(id) != m_map.end())
//	{
//		CGeometry* p = m_map[id];
//		m_map.erase(id);
//		releseId(id);
//		delete p;
//	}
//}
//
//CPointFactory::~CPointFactory()
//{
//	for(auto it = m_map.begin(); it != m_map.end(); it++)
//	{
//		delete it->second;
//	}
//	m_map.clear();
//}
//
//
//CGeometry* CPolyLineFactory::CreateGeometry(GeometryType type)
//{
//	if (type == GeometryType::PolyLine)
//	{
//		int id = getNextId();
//		CPolyLine* p = new CPolyLine();
//		p->setId(id);
//		m_map[id] = p;
//	}
//	else
//		return nullptr;
//}
//
//void CPolyLineFactory::DestroyGeometry(CGeometry* pGeometry)
//{
//	int id = pGeometry->getId();
//	if (m_map.find(id) != m_map.end())
//	{
//		CGeometry* p = m_map[id];
//		m_map.erase(id);
//		releseId(id);
//		delete p;
//	}
//}
//
//CPolyLineFactory::~CPolyLineFactory()
//{
//	for(auto it = m_map.begin(); it != m_map.end(); it++)
//	{
//		delete it->second;
//	}
//	m_map.clear();
//}
//
//
//CGeometry* CPolyGonFactory::CreateGeometry(GeometryType type)
//{
//	if (type == GeometryType::PolyGon)
//	{
//		int id = getNextId();
//		CGeometry* p = new CPolyGon();
//		p->setId(id);
//		m_map[id] = p;
//	}
//	else
//		return nullptr;
//}
//
//void CPolyGonFactory::DestroyGeometry(CGeometry* pGeometry)
//{
//	int id = pGeometry->getId();
//	if (m_map.find(id) != m_map.end())
//	{
//		CGeometry* p = m_map[id];
//		m_map.erase(id);
//		releseId(id);
//		delete p;
//	}
//}
//
//CPolyGonFactory::~CPolyGonFactory()
//{
//	for(auto it = m_map.begin(); it != m_map.end(); it++)
//	{
//		delete it->second;
//	}
//	m_map.clear();
//}
//
//
//CGeometry* CRectAngleFactory::CreateGeometry(GeometryType type)
//{
//	if (type == GeometryType::RectAngle)
//	{
//		int id = getNextId();
//		CGeometry* p = new CRectAngle();
//		p->setId(id);
//		m_map[id] = p;
//	}
//	else
//		return nullptr;
//}
//
//void CRectAngleFactory::DestroyGeometry(CGeometry* pGeometry)
//{
//	int id = pGeometry->getId();
//	if (m_map.find(id) != m_map.end())
//	{
//		CGeometry* p = m_map[id];
//		m_map.erase(id);
//		releseId(id);
//		delete p;
//	}
//}
//
//CRectAngleFactory::~CRectAngleFactory()
//{
//	for(auto it = m_map.begin(); it != m_map.end(); it++)
//	{
//		delete it->second;
//	}
//	m_map.clear();
//}
//
//
//CGeometry* CCircleFactory::CreateGeometry(GeometryType type)
//{
//	if (type == GeometryType::Circle)
//	{
//		int id = getNextId();
//		CGeometry* p = new CCircle();
//		p->setId(id);
//		m_map[id] = p;
//	}
//	else
//		return nullptr;
//}
//
//void CCircleFactory::DestroyGeometry(CGeometry* pGeometry)
//{
//	int id = pGeometry->getId();
//	if (m_map.find(id) != m_map.end())
//	{
//		CGeometry* p = m_map[id];
//		m_map.erase(id);
//		releseId(id);
//		delete p;
//	}
//}
//
//CCircleFactory::~CCircleFactory()
//{
//	for(auto it = m_map.begin(); it != m_map.end(); it++)
//	{
//		delete it->second;
//	}
//	m_map.clear();
//}
//
//
//CGeometry* CSectionFactory::CreateGeometry(GeometryType type)
//{
//	if (type == GeometryType::Section)
//	{
//		int id = getNextId();
//		CGeometry* p = new CSection();
//		p->setId(id);
//		m_map[id] = p;
//	}
//	else
//		return nullptr;
//}
//
//void CSectionFactory::DestroyGeometry(CGeometry* pGeometry)
//{
//	int id = pGeometry->getId();
//	if (m_map.find(id) != m_map.end())
//	{
//		CGeometry* p = m_map[id];
//		m_map.erase(id);
//		releseId(id);
//		delete p;
//	}
//}
//
//CSectionFactory::~CSectionFactory()
//{
//	for(auto it = m_map.begin(); it != m_map.end(); it++)
//	{
//		delete it->second;
//	}
//	m_map.clear();
//}
