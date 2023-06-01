#pragma once
#include<vector>
#include<string>
#include"CStyle.h"
#include<qobject.h>

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
	PolyGon,
	RectAngle,
	Circle,
	Section,
	Text,
	BitMap
};

//抽象几何
class CGeometry:public QObject
{
public:
	CGeometry() { isDelete = false; }

	CGeometry(const CGeometry& geo)
	{
		this->BorderColor = geo.BorderColor;
		this->BorderStyle = geo.BorderStyle;
		this->FillColor = geo.FillColor;
		this->FillStyle = geo.FillStyle;
		this->id = geo.id;
		this->isDelete = geo.isDelete;
		this->BoundingBox = geo.BoundingBox;
	}

	CGeometry& operator=(const CGeometry& geo)
	{
		this->BorderColor = geo.BorderColor;
		this->BorderStyle = geo.BorderStyle;
		this->FillColor = geo.FillColor;
		this->FillStyle = geo.FillStyle;
		this->id = geo.id;
		this->isDelete = geo.isDelete;
		this->BoundingBox = geo.BoundingBox;
		return *this;
	}

	//几何边界
	BBox BoundingBox;

	int id;

	//是否被删除
	bool isDelete;

	//获取几何类型
	virtual GeometryType GetType()=0;

	//获取WKT形式几何
	virtual const char* ToWKT() = 0;
	
	//获取GeoJson类型几何
	virtual const char* ToGeojson() = 0;
	
	//边框颜色
	CColor BorderColor;
	
	//填充颜色
	CColor FillColor;
	
	//边框样式
	CBorStyle BorderStyle;
	
	//填充样式
	CFilStyle FillStyle;

	//虚析构函数
	virtual ~CGeometry() {};

	//设置id
	void setId(int id){this->id=id;}

	//获取id
	int getId(){return id;}

signals:
	virtual void AimDestroy(GeometryType type,CGeometry* prt);
};



