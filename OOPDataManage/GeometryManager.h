//#pragma once
//#include<map>
//#include<set>
//#include"GeomertyFile/CPoint.h"
//#include"GeomertyFile/CPolyline.h"
//#include"GeomertyFile/CPolygon.h"
//#include"GeomertyFile/CRectAngle.h"
//#include"GeomertyFile/CCircle.h"
//#include"GeomertyFile/CSection.h"
//
//
////几何工厂纯虚基类
//class GeometryFactory
//{
//public:
//	//根据几何类型创建几何对象
//	virtual CGeometry* CreateGeometry(GeometryType type)=0;
//
//	//根据几何类型销毁几何对象
//	virtual bool DestroyGeometry(CGeometry* pGeometry);
//
//	virtual ~GeometryFactory();
//
//protected:
//	//获取下一个可用的id
//	int GetUnusedID();
//
//	//释放id
//	void RecycleID(int id);
//
//	//存储未使用的id
//	std::set<int> m_unusedIds;
//	//存储id和和几何对象指针
//	std::map<int,CGeometry*> m_map;
//
//};
//
//class CPointFactory :public GeometryFactory
//{
//public:
//	static CPointFactory& GetInstance()
//	{
//		static CPointFactory instance;
//		return instance;
//	}
//	CGeometry* CreateGeometry(GeometryType type) override;
//	bool DestroyGeometry(CGeometry* pGeometry) override;
//protected:
//	CPointFactory() {};
//	~CPointFactory() {};
//};
//
//class CPathFactory :public GeometryFactory
//{
//public:
//	static CPathFactory& GetInstance()
//	{
//		static CPathFactory instance;
//			return instance;
//	}
//	CGeometry* CreateGeometry(GeometryType type) override;
//	bool DestroyGeometry(CGeometry* pGeometry) override;
//protected:
//	CPathFactory() {};
//	~CPathFactory() {};
//};
//
//class CPolyLineFactory :public GeometryFactory
//{
//public:
//	static CPolyLineFactory& GetInstance()
//	{
//		static CPolyLineFactory instance;
//		return instance;
//	}
//	CGeometry* CreateGeometry(GeometryType type) override;
//	bool DestroyGeometry(CGeometry* pGeometry) override;
//protected:
//	CPolyLineFactory() {};
//	~CPolyLineFactory() {};
//};
//
//class CRingFactory :public GeometryFactory
//{
//public:
//	static CRingFactory& GetInstance()
//	{
//		static CRingFactory instance;
//		return instance;
//	}
//	CGeometry* CreateGeometry(GeometryType type) override;
//	bool DestroyGeometry(CGeometry* pGeometry) override;
//protected:
//	CRingFactory() {};
//	~CRingFactory() {};
//};
//
//class CPolyGonFactory :public GeometryFactory
//{
//public:
//static CPolyGonFactory& GetInstance()
//	{
//		static CPolyGonFactory instance;
//		return instance;
//	}
//	CGeometry* CreateGeometry(GeometryType type) override;
//	bool DestroyGeometry(CGeometry* pGeometry) override;
//protected:
//	CPolyGonFactory() {};
//	~CPolyGonFactory() {};
//};
//
//class CRectAngleFactory :public GeometryFactory
//{
//public:
//	static CRectAngleFactory& GetInstance()
//	{
//		static CRectAngleFactory instance;
//		return instance;
//	}
//	CGeometry* CreateGeometry(GeometryType type) override;
//	bool DestroyGeometry(CGeometry* pGeometry) override;
//protected:
//	CRectAngleFactory() {};
//	~CRectAngleFactory() {};
//};
//
//class CCircleFactory :public GeometryFactory
//{
//public:
//	static CCircleFactory& GetInstance()
//	{
//		static CCircleFactory instance;
//		return instance;
//	}
//	CGeometry* CreateGeometry(GeometryType type) override;
//	bool DestroyGeometry(CGeometry* pGeometry) override;
//protected:
//	CCircleFactory() {};
//	~CCircleFactory() {};
//};
//
//class CSectionFactory :public GeometryFactory
//{
//public:
//	static CSectionFactory& GetInstance()
//	{
//		static CSectionFactory instance;
//		return instance;
//	}
//	CGeometry* CreateGeometry(GeometryType type) override;
//	bool DestroyGeometry(CGeometry* pGeometry) override;
//protected:
//	CSectionFactory() {};
//	~CSectionFactory() {};
//};
//
//
//class GeometryManager
//{
//public:
//	//创建几何管理器单例
//	static GeometryManager& GetInstance();
//
//	//根据几何类型创建几何对象
//	CGeometry* CreateGeometry(GeometryType type);
//
//	//根据几何类型销毁几何对象
//	void DestroyGeometry(CGeometry* pGeometry);
//
//protected:
//
//	//工厂实例
//	CPointFactory& m_pPointFactory= CPointFactory::GetInstance();
//	CPathFactory& m_pPathFactory= CPathFactory::GetInstance();
//	CPolyLineFactory& m_pPolyLineFactory= CPolyLineFactory::GetInstance();
//	CRingFactory& m_pRingFactory= CRingFactory::GetInstance();
//	CPolyGonFactory& m_pPolyGonFactory= CPolyGonFactory::GetInstance();
//	CRectAngleFactory& m_pRectAngleFactory= CRectAngleFactory::GetInstance();
//	CCircleFactory& m_pCircleFactory= CCircleFactory::GetInstance();
//	CSectionFactory& m_pSectionFactory= CSectionFactory::GetInstance();
//
//	//私有构造函数，防止外部创建
//	GeometryManager();
//	//私有析构函数，防止外部销毁
//	~GeometryManager();
//};
//
//
