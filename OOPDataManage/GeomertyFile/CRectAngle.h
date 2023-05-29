#pragma once
#include"CGeometry.h"
#include"CPoint.h"
#include<stdexcept>

//几何矩形
class CRectAngle :public CGeometry
{
public:
	//默认构造函数
	CRectAngle() {};

	//通过两个点构造
	CRectAngle(CPoint lefttop, CPoint rightbottom);

	//通过一个点和长宽构造
	CRectAngle(CPoint lefttop, float width, float height);


	//获取宽度
	float GetWidth();
	//获取高度
	float GetHeight();

	//获取左上角顶点
	CPoint GetLT();
	//获取右下角顶点
	CPoint GetRB();

	//设置左上角顶点
	void LT(CPoint c);
	//设置右下角顶点
	void RB(CPoint c);


	virtual const char* GetType();
	virtual const char* ToWKT();
	virtual const char* ToGeojson();
	//计算周长
	virtual float Circum();
	//计算面积
	virtual float Area();

private:
	//左上角顶点
	CPoint m_LT;
	//右下角顶点
	CPoint m_RB;
	//检查是否颠倒
	bool CheckReverse();
};
