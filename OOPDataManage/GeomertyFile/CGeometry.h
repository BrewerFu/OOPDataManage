#define CGEOMETRY_EXPORTS

#pragma once
#include<vector>
#include<map>
#include<set>
#include<memory>
#include<sstream>
#include<string>
#include"CStyle.h"

//定义导入导出宏
#ifdef CGEOMETRY_EXPORTS
#define CGEOMETRY_API __declspec(dllexport)
#else
#define CGEOMETRY_API __declspec(dllimport)
#endif // CGEOMETRY_EXPORTS

//几何对象前置声明
class CGEOMETRY_API CPoint;
class CGEOMETRY_API CPath;
class CGEOMETRY_API CPolyLine;
class CGEOMETRY_API CRing;
class CGEOMETRY_API CPolyGon;
class CGEOMETRY_API CRectAngle;
class CGEOMETRY_API CCircle;
class CGEOMETRY_API CSection;
class CGEOMETRY_API CText;
class CGEOMETRY_API CBitMap;

//创建几何对象智能指针宏
#define CREATE_GEOSHARED_PTR(type, var, ...) \
    std::shared_ptr<type> var = std::make_shared<type>(__VA_ARGS__)
#define GET_GEOSHAED_PRT_BYID(type, var, id) \
	std::shared_ptr<type> var = IDManager<type>::GetObjectByID(id)
	
//外包矩形
struct CGEOMETRY_API BBox
{
	//左上
	double LT;
	//右下
	double RB;
};

//几何类型
enum CGEOMETRY_API GeometryType:int
{
	Undefined=0,
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

//根据几何类型获取字符串
inline std::string CGEOMETRY_API GeometryTypeToString(GeometryType type)
{
	switch (type)
	{
	case GeometryType::Undefined:
		return "Undefined";
	case GeometryType::Point:
		return "Point";
	case GeometryType::Path:
		return "Path";
	case GeometryType::PolyLine:
		return "PolyLine";
	case GeometryType::Ring:
		return "Ring";
	case GeometryType::PolyGon:
		return "PolyGon";
	case GeometryType::RectAngle:
		return "RectAngle";
	case GeometryType::Circle:
		return "Circle";
	case GeometryType::Section:
		return "Section";
	case GeometryType::Text:
		return "Text";
	case GeometryType::BitMap:
		return "BitMap";
	default:
		return "Undefined";
	}

}

//根据字符串获取几何类型
inline GeometryType CGEOMETRY_API StringToGemetryType(std::string type)
{
	if(type=="Point")
		return GeometryType::Point;
	else if (type == "Path")
		return GeometryType::Path;
	else if (type == "PolyLine")
		return GeometryType::PolyLine;
	else if (type == "Ring")
		return GeometryType::Ring;
	else if (type == "PolyGon")
		return GeometryType::PolyGon;
	else if (type == "RectAngle")
		return GeometryType::RectAngle;
	else if (type == "Circle")
		return GeometryType::Circle;
	else if (type == "Section")
		return GeometryType::Section;
	else if (type == "Text")
		return GeometryType::Text;
	else if (type == "BitMap")
		return GeometryType::BitMap;
	else
		return GeometryType::Undefined;
}

//抽象几何
class CGEOMETRY_API CGeometry
{
public:
	//构造函数
	CGeometry():ID(-1),DBID(-1),isDelete(false),BoundaryColor(QColor(0,0,0)),FillColor(QColor(255,255,255)),p_x(0),p_y(0){}
	//拷贝构造函数
	CGeometry(const CGeometry& geo) :ID(geo.ID), DBID(geo.DBID), isDelete(geo.isDelete), BoundaryColor(geo.BoundaryColor), FillColor(geo.FillColor), BoundaryStyle(geo.BoundaryStyle), FillStyle(geo.FillStyle), p_x(geo.p_x),p_y(geo.p_y) {}
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
	virtual double Circum()const { return 0; };
	//获取面积
	virtual double Area()const { return 0; };

	//转为数据存储格式，为PolyLine、Path、Ring、PolyGon设计
	virtual const char* ToDBIDText()const { return NULL; };

	//获取程序ID
	int GetID() { return ID; }
	
	//设置程序ID
	void SetID(int id) { ID = id;}



	/*-----------------------------------------------------------------------------------------------------------------------*/
	/*----------------------------------------------------------------成员变量-----------------------------------------------*/
	/*-----------------------------------------------------------------------------------------------------------------------*/


	//数据库ID
	int DBID;

	//中心点x坐标
	int p_x;
	//中心点y坐标
	int p_y;

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


//对象模板，派生或单例以管理ID
template<typename T>
class IDManager:public std::enable_shared_from_this<T>
{
public:
	IDManager() {};
	~IDManager() {};

	//通过id获取对象智能指针
	static std::shared_ptr<T> GetObjectByID(int id)
	{
		auto it = s_Ptrs.find(id);
		if (it != s_Ptrs.end())
		{
			return it->second->shared_from_this();
		}
		return nullptr;
	}

	//获取正在使用的ID
	static std::set<int> GetUsedID()
	{
		std::set<int> usedID;
		for (auto it = s_Ptrs.begin(); it != s_Ptrs.end(); it++)
		{
			usedID.insert(it->first);
		}
		return usedID;
	}

	//删除构造与赋值运算符重载，防止复制
	IDManager(const IDManager&) = delete;
	IDManager& operator=(const IDManager&) = delete;


protected:
	//派生类调用，为对象分配I新D
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

	//派生类调用，释放ID
	static void ReleaseID(int id)
	{
		s_idPool.insert(id);	//添加到ID池
		s_Ptrs.erase(id);	//删除对象指针
	}

	//添加一个对象到ID管理器中
	static void AddPtr(int id, T* sp)
	{
		s_Ptrs.insert(std::make_pair(id, sp));
	}


	static std::set<int> s_idPool;	//id池
	static std::map<int, T*> s_Ptrs;	//指针集合
	static int s_idCounter;	//计数器

};


/*初始化模板类静态对象*/

template<typename T>
int IDManager<T>::s_idCounter = 0;

template<typename T>
std::set<int> IDManager<T>::s_idPool;

template<typename T>
std::map<int, T*> IDManager<T>::s_Ptrs;