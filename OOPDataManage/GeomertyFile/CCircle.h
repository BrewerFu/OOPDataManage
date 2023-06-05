#pragma once
#include"CGeometry.h"
#include"CPoint.h"
#include"CPolyGon.h"
#include<cmath>

//声明圆
class CCircle;

//圆多边形
struct CCirclePoly
{
	//指向圆的指针
	CCircle* prt;
	//多边形
	CPolyGon polygon;
};

//几何圆
class CCircle :public CGeometry
{
public:
	//默认构造函数
	CCircle():m_R(0){};
	//通过圆心和半径构造
	CCircle(CPoint c, float r);
	//通过x、y坐标和半径构造
	CCircle(float x, float y, float r);
	//获取圆心
	CPoint GetC();
	//获取半径
	float GetR();

	//设置圆心
	void C(CPoint c);
	//设置半径
	void R(float r);
	
	GeometryType GetType();
	const char* ToWKT()override;
	const char* ToGeojson()override;
	//计算周长
	float Circum() override;
	//计算面积
	float Area() override;

	//转换为多边形
	//@param n:多边形边数
	//@return:包含多边形和圆的结构体
	CCirclePoly ToPolyGon(int n);

protected:
	//圆心
	CPoint m_C;
	//半径
	float m_R;
};
