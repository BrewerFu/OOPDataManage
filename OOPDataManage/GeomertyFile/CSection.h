#pragma once
#include"CCircle.h"

class CSection;

//几何扇形
class CSection :public CCircle
{
public:
	//默认构造函数
	CSection():StartAngle(0),EndAngle(360){};

	//构造函数
	//@param startangle 角度,开始角度
	//@param endangle 角度,结束角度
	CSection(CPoint* c, float r, float startangle, float endangle);

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

	CPolyGon* ToPolyGon(int n)const;

protected:
	//开始角度
	float StartAngle;
	//结束角度
	float EndAngle;
	//控制角度在0-360之间
	void CheckAngle();
};


