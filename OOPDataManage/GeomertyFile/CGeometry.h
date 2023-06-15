#pragma once
#include<vector>
#include<map>
#include<set>
#include<memory>
#include<sstream>
#include<string>
#include"CStyle.h"

class CPoint;
class CPath;
class CPolyLine;
class CRing;
class CPolyGon;
class CRectAngle;
class CCircle;
class CSection;
class CText;
class CBitMap;
#define CREATE_GEOSHARED_PTR(type, var, ...) \
    std::shared_ptr<type> var = std::make_shared<type>(__VA_ARGS__)
#define GET_GEOSHAED_PRT_BYID(type, var, id) \
	std::shared_ptr<type> var = IDManager<type>::GetObjectByID(id)


//外包矩形
struct BBox
{
	//左上
	float LT;
	//右下
	float RB;
};

enum class GeometryType:int
{
	Undefined,
	Point,
	Path,
	PolyLine,
	Ring,
	PolyGon,
	RectAngle,
	Circle,
	Section,
	Text,
	BitMap
};

//抽象几何
class CGeometry
{
public:
	//构造函数
	CGeometry():ID(-1),DBID(-1),isDelete(false),BoundaryColor(QColor(0,0,0)),FillColor(QColor(255,255,255)){}
	//拷贝构造函数
	CGeometry(const CGeometry& geo) :ID(geo.ID), DBID(geo.DBID), isDelete(geo.isDelete), BoundaryColor(geo.BoundaryColor), FillColor(geo.FillColor), BoundaryStyle(geo.BoundaryStyle), FillStyle(geo.FillStyle) {}
	//赋值运算符重载
	CGeometry& operator=(const CGeometry& geo)
	{
		ID = geo.ID;
		DBID = geo.DBID;
		isDelete = geo.isDelete;
		BoundaryColor = geo.BoundaryColor;
		FillColor = geo.FillColor;
		BoundaryStyle = geo.BoundaryStyle;
		FillStyle = geo.FillStyle;
		return *this;
	}

	//构函数
	~CGeometry() {};

	/*-----------------------------------------------------------------------------------------------------------------------*/
	/*--------------------------------------------------------------虚基类接口-----------------------------------------------*/
	/*-----------------------------------------------------------------------------------------------------------------------*/

	//获取几何类型
	virtual GeometryType GetType()const =0;

	//获取WKT形式几何
	virtual const char* ToWKT()const = 0;
	
	//获取GeoJson类型几何
	virtual const char* ToGeojson()const = 0;

	//获取周长
	virtual float Circum()const { return 0; };
	//获取面积
	virtual float Area()const { return 0; };

	virtual const char* ToDBIDText()const { return NULL; };

	int GetID() { return ID; }
	
	void SetID(int id) { ID = id;}


	//数据库ID
	int DBID;

	/*-----------------------------------------------------------------------------------------------------------------------*/
	/*----------------------------------------------------------------成员变量-----------------------------------------------*/
	/*-----------------------------------------------------------------------------------------------------------------------*/


	//是否被删除
	bool isDelete;

	//边框颜色
	QColor BoundaryColor;

	//填充颜色
	QColor FillColor;
	
	//边框样式
	CBoundaryStyle BoundaryStyle;
	
	//填充样式
	CFillStyle FillStyle;

protected:
	//几何对象的ID
	int ID;
};



template<typename T>
class IDManager:public std::enable_shared_from_this<T>
{
public:
	IDManager() {};
	~IDManager() {};
	static std::shared_ptr<T> GetObjectByID(int id)
	{
		auto it = s_Ptrs.find(id);
		if (it != s_Ptrs.end())
		{
			return it->second->shared_from_this();
		}
		return nullptr;
	}

	static std::set<int> GetUsedID()
	{
		std::set<int> usedID;
		for (auto it = s_Ptrs.begin(); it != s_Ptrs.end(); it++)
		{
			usedID.insert(it->first);
		}
		return usedID;
	}


	IDManager(const IDManager&) = delete;
	IDManager& operator=(const IDManager&) = delete;


protected:
	static int GetNewID(T* prt)
	{
		int id = 0;

		if (!s_idPool.empty())
		{
			id = *s_idPool.begin();
			s_idPool.erase(s_idPool.begin());
		}
		else
		{
			id = ++s_idCounter;
		}
		AddPtr(id, prt);
		return id;
	}

	static void ReleaseID(int id)
	{
		s_idPool.insert(id);	//添加到ID池
		s_Ptrs.erase(id);	//删除对象指针
	}

	static void AddPtr(int id, T* sp)
	{
		s_Ptrs.insert(std::make_pair(id, sp));
	}

	static std::set<int> s_idPool;
	static std::map<int, T*> s_Ptrs;
	static int s_idCounter;

};

template<typename T>
int IDManager<T>::s_idCounter = 0;

template<typename T>
std::set<int> IDManager<T>::s_idPool;

template<typename T>
std::map<int, T*> IDManager<T>::s_Ptrs;