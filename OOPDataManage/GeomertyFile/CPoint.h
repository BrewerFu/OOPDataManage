#pragma once
#include"CGeometry.h"

//几何点
class CPoint :public CGeometry
{
public:
	//构造函数
	CPoint(float x, float y);
	//默认构造函数
	CPoint();

	//获取x
	float x() { return m_X; };
	//获取y
	float y() { return m_Y; };

	//设置x
	void x(float x) { m_X = x; };
	//设置y
	void y(float y) { m_Y = y; };

	GeometryType GetType() override;
	const char* ToWKT()override;
	const char* ToGeojson() override;
	
	//重载+运算
	CPoint operator +(CPoint c);
	//重载+=运算
	CPoint& operator +=(CPoint c);
	//-=运算
	CPoint& operator -=(CPoint c);
	//重载-运算
	CPoint operator - (CPoint);
	//重载*点积运算
	float operator*(CPoint c);
	//重载^叉积运算
	float operator ^ (CPoint c);
	//判断点X、Y值是否相等
	bool operator==(CPoint c);
	//判断点X、Y值是否不等
	bool operator!=(CPoint);

private:
	//x坐标
	float m_X;
	//y坐标
	float m_Y;
};

//求两个点之间的距离
float CPoint_Distance(CPoint c1, CPoint c2);
