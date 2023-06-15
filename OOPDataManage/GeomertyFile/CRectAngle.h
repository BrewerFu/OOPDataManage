#pragma once
#include"CGeometry.h"
#include"CPoint.h"
#include<stdexcept>
class CRectAngle;
#define _RECTANGLEPRT std::shared_ptr<CRectAngle> rectangle = std::make_shared<CRectAngle>();

//几何矩形
class CRectAngle :public CGeometry,public IDManager<CRectAngle>
{
public:
	//默认构造函数
	CRectAngle() {};

	//通过两个点构造
	CRectAngle(std::shared_ptr<CPoint> lefttop, std::shared_ptr<CPoint> rightbottom);

	//通过一个点和长宽构造
	CRectAngle(std::shared_ptr<CPoint> lefttop, float width, float height);

	//获取宽度
	float GetWidth()const;
	//获取高度
	float GetHeight()const;

	//获取左上角顶点
	std::shared_ptr<CPoint> GetLT()const;
	//获取右下角顶点
	std::shared_ptr<CPoint> GetRB()const;

	//设置左上角顶点
	void SetLT(std::shared_ptr<CPoint> c);
	//设置右下角顶点
	void SetRB(std::shared_ptr<CPoint> c);


	GeometryType GetType()const override;
	const char* ToWKT()const override;
	const char* ToGeojson()const override;
	//计算周长
	float Circum()const override;
	//计算面积
	float Area()const override;

private:
	//左上角顶点
	std::shared_ptr<CPoint> m_LT=nullptr;
	//右下角顶点
	std::shared_ptr<CPoint> m_RB=nullptr;
	//检查是否颠倒
	bool CheckReverse()const;
};
