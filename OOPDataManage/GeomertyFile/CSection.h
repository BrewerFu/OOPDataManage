#pragma once
#include"CCircle.h"
class CSection;
#define _SECTIONPRT std::shared_ptr<CSection> = std::make_shared<CSection>();

//几何扇形
class CSection :public CGeometry,public IDManager<CSection>
{
public:
	//默认构造函数
	CSection();

	//构造函数
	//@param startangle 角度,开始角度
	//@param endangle 角度,结束角度
	CSection(std::shared_ptr<CPoint> c, double r, double startangle, double endangle);

	//复制构造函数
	CSection(const CSection& c);

	//赋值运算符重载
	CSection operator=(const CSection& c);

	//析构函数
	~CSection();
	//获取圆心
	std::shared_ptr<CPoint> GetC()const;
	//获取半径
	double GetR()const;

	//设置圆心
	void SetC(std::shared_ptr<CPoint> c);
	//设置半径
	void SetR(double r);

	//设置开始角度
	void SetSAngle(double startangle);
	//设置结束角度
	
	void SetEAngle(double endangle);
	//获取开始角度

	double GetSAngle()const;
	//获取结束角度
	double GetEAngle()const;

	GeometryType GetType()const override;
	const char* ToWKT()const override;
	const char* ToGeojson()const  override;
	double Circum()const  override;
	double Area()const override;

	std::shared_ptr<CPolyGon> ToPolyGon(int n)const;

protected:
	//圆心
	std::shared_ptr<CPoint> m_C = nullptr;
	//半径
	double m_R;
	//开始角度
	double StartAngle;
	//结束角度
	double EndAngle;
	//控制角度在0-360之间
	void CheckAngle();
};


