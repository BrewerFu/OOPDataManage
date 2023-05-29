#pragma once
#include<vector>
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

//抽象几何
class CGeometry
{
public:
	//几何边界
	BBox BoundingBox;

	int id;

	//是否被删除
	bool isDelete;

	//获取几何类型
	virtual const char* GetType()=0;

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
	virtual ~CGeometry();
};



