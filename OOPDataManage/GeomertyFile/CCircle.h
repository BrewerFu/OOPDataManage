#pragma once
#include"CGeometry.h"
#include"CPoint.h"
#include"CPolyGon.h"
#include<cmath>

#define _CIRCLEPRT std::shared_ptr<CCircle> = std::make_shared<CCircle>();

//几何圆
class CCircle :public CGeometry,public IDManager<CCircle>
{
public:
	//默认构造函数
	CCircle();
	//复制构造函数
	CCircle(const CCircle& c);
	//赋值运算符
	CCircle operator=(const CCircle& c);
	//通过圆心和半径构造
	CCircle(std::shared_ptr<CPoint> c, double r);

	//析构函数
	~CCircle();
	//获取圆心
	std::shared_ptr<CPoint> GetC()const;
	//获取半径
	double GetR()const;

	//设置圆心
	void SetC(std::shared_ptr<CPoint> c);
	//设置半径
	void SetR(double r);
	
	GeometryType GetType()const;
	const char* ToWKT()const override;
	const char* ToGeojson()const override;
	//计算周长
	double Circum()const override;
	//计算面积
	double Area()const override;

	//转换为多边形
	//@param n:多边形边数
	virtual std::shared_ptr<CPolyGon> ToPolyGon(int n)const;

protected:
	//圆心
	std::shared_ptr<CPoint> m_C=nullptr;
	//半径
	double m_R;
};
