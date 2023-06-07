#pragma once
#include<vector>
#include<sstream>
#include<string>
#include"CStyle.h"

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
	CGeometry() 
	{ 
		isDelete = false; 
		BoundaryColor = QColor(0, 0, 0);
		FillColor = QColor(255, 255, 255);
		BoundaryStyle = CBoundaryStyle();
		FillStyle = CFillStyle();
	};
	//拷贝构造函数
	CGeometry(const CGeometry& geo)
	{
		this->BoundaryColor = geo.BoundaryColor;
		this->BoundaryStyle = geo.BoundaryStyle;
		this->FillColor = geo.FillColor;
		this->FillStyle = geo.FillStyle;
		this->isDelete = geo.isDelete;
	}
	//赋值运算符重载
	CGeometry& operator=(const CGeometry& geo)
	{
		this->BoundaryColor = geo.BoundaryColor;
		this->BoundaryStyle = geo.BoundaryStyle;
		this->FillColor = geo.FillColor;
		this->FillStyle = geo.FillStyle;
		this->isDelete = geo.isDelete;
		return *this;
	}

	//虚析构函数
	virtual ~CGeometry() {};


	//是否被删除
	bool isDelete;

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
	
	//边框颜色
	QColor BoundaryColor;
	//填充颜色
	QColor FillColor;
	
	//边框样式
	CBoundaryStyle BoundaryStyle;
	
	//填充样式
	CFillStyle FillStyle;

};



