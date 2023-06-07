#pragma once
#include"CGeometry.h"
#include"CPoint.h"
#include"CPolyGon.h"
#include<cmath>


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
	CPoint GetC()const;
	//获取半径
	float GetR()const;

	//设置圆心
	void C(CPoint c);
	//设置半径
	void R(float r);
	
	GeometryType GetType()const;
	const char* ToWKT()const override;
	const char* ToGeojson()const override;
	//计算周长
	float Circum()const override;
	//计算面积
	float Area()const override;

	//转换为多边形
	//@param n:多边形边数
	CPolyGon ToPolyGon(int n)const;

protected:
	//圆心
	CPoint m_C;
	//半径
	float m_R;
};
