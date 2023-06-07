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
//	virtual void DestroyGeometry(CGeometry* pGeometry)=0;
//
//};
//
//class GeometryManager
//{
//public:
//	//创建几何管理器单例
//	static GeometryManager& GetInstance();
//	//摧毁几何管理器单例
//	static void DestroyInstance();
//
//	//根据几何类型创建几何对象
//	CGeometry* CreateGeometry(GeometryType type);
//
//	//根据几何类型销毁几何对象
//	void DestroyGeometry(CGeometry* pGeometry);
//
//
//protected slots:
//	//几何对象被销毁时，从集合中移除
//	void OnGeometryDestory(GeometryType type, CGeometry* prt);
//
//protected:
//	//该类的唯一实例
//	static GeometryManager* m_pGeometryManager;
//
//	//工厂实例
//	static CPointFactory* m_pPointFactory;
//	static CPolyLineFactory* m_pPolyLineFactory;
//	static CPolyGonFactory* m_pPolyGonFactory;
//	static CRectAngleFactory* m_pRectAngleFactory;
//	static CCircleFactory* m_pCircleFactory;
//	static CSectionFactory* m_pSectionFactory;
//
//	//私有构造函数，防止外部创建
//	GeometryManager();
//	//私有析构函数，防止外部销毁
//	~GeometryManager();
//};
//
//class CPointFactory :public GeometryFactory
//{
//public:
//	CGeometry* CreateGeometry(GeometryType type) override;
//	void DestroyGeometry(CGeometry* pGeometry) override;
//	~CPointFactory();
//};
//
//class CPolyLineFactory :public GeometryFactory
//{
//public:
//	CGeometry* CreateGeometry(GeometryType type) override;
//	void DestroyGeometry(CGeometry* pGeometry) override;
//	~CPolyLineFactory();
//};
//
//class CPolyGonFactory :public GeometryFactory
//{
//public:
//	CGeometry* CreateGeometry(GeometryType type) override;
//	void DestroyGeometry(CGeometry* pGeometry) override;
//	~CPolyGonFactory();
//};
//
//class CRectAngleFactory :public GeometryFactory
//{
//public:
//	CGeometry* CreateGeometry(GeometryType type) override;
//	void DestroyGeometry(CGeometry* pGeometry) override;
//	~CRectAngleFactory();
//};
//
//class CCircleFactory :public GeometryFactory
//{
//public:
//	CGeometry* CreateGeometry(GeometryType type) override;
//	void DestroyGeometry(CGeometry* pGeometry) override;
//	~CCircleFactory();
//};
//
//class CSectionFactory :public GeometryFactory
//{
//public:
//	CGeometry* CreateGeometry(GeometryType type) override;
//	void DestroyGeometry(CGeometry* pGeometry) override;
//	~CSectionFactory();
//};
//
