#pragma once
#include"CGeometry.h"
class CPoint;
#define _POINTPRT std::shared_ptr<CPoint> point = std::make_shared<CPoint>();


//几何点
class CPoint :public CGeometry,public IDManager<CPoint>
{
public:
	//构造函数
	CPoint(double x, double y);
	//默认构造函数
	CPoint();
	//拷贝构造函数
	CPoint(const CPoint& c);
	//赋值运算符重载
	CPoint operator=(const CPoint& c);
	//析构函数
	~CPoint();

	//获取x
	double x()const { return m_X; };
	//获取y
	double y()const { return m_Y; };

	//设置x
	void x(double x) { m_X = x; };
	//设置y
	void y(double y) { m_Y = y; };

	GeometryType GetType()const override;
	const char* ToWKT()const override;
	const char* ToGeojson()const  override;
	
	//重载+运算
	CPoint operator +(CPoint c)const;
	//重载+=运算
	CPoint& operator +=(CPoint c);
	//-=运算
	CPoint& operator -=(CPoint c);
	//重载-运算
	CPoint operator - (CPoint)const;
	//重载*点积运算
	double operator*(CPoint c)const;
	//重载^叉积运算
	double operator ^ (CPoint c)const;
	//判断点X、Y值是否相等
	bool operator==(const CPoint& other) const;
	//判断点X、Y值是否不等
	bool operator!=(CPoint)const;

protected:
	//x坐标
	double m_X;
	//y坐标
	double m_Y;

};

//求两个点之间的距离
double CPoint_Distance(const CPoint& c1, const CPoint& c2);

