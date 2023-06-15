#pragma once
#include"CCircle.h"
class CSection;
#define _SECTIONPRT std::shared_ptr<CSection> = std::make_shared<CSection>();

//几何扇形
class CSection :public CGeometry,public IDManager<CSection>
{
public:
	//默认构造函数
	CSection():m_C(nullptr),m_R(1),StartAngle(0), EndAngle(360) {};

	//构造函数
	//@param startangle 角度,开始角度
	//@param endangle 角度,结束角度
	CSection(std::shared_ptr<CPoint> c, float r, float startangle, float endangle);

	//获取圆心
	std::shared_ptr<CPoint> GetC()const;
	//获取半径
	float GetR()const;

	//设置圆心
	void SetC(std::shared_ptr<CPoint> c);
	//设置半径
	void SetR(float r);

	//设置开始角度
	void SetSAngle(float startangle);
	//设置结束角度
	
	void SetEAngle(float endangle);
	//获取开始角度

	float GetSAngle()const;
	//获取结束角度
	float GetEAngle()const;

	GeometryType GetType()const override;
	const char* ToWKT()const override;
	const char* ToGeojson()const  override;
	float Circum()const  override;
	float Area()const override;

	std::shared_ptr<CPolyGon> ToPolyGon(int n)const;

protected:
	//圆心
	std::shared_ptr<CPoint> m_C = nullptr;
	//半径
	float m_R;
	//开始角度
	float StartAngle;
	//结束角度
	float EndAngle;
	//控制角度在0-360之间
	void CheckAngle();
};


