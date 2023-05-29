#pragma once
#include"CCircle.h"

class CSection;

//几何扇形多边形
struct CSectionPoly
{
	CSection* prt;
	CPolyGon polygon;
};

//几何扇形
class CSection :public CCircle
{
public:
	//默认构造函数
	CSection():StartAngle(0),EndAngle(360){};

	//构造函数
	//@param startangle 角度,开始角度
	//@param endangle 角度,结束角度
	CSection(CPoint c, float r, float startangle, float endangle);

	//获取开始角度
	void SAngle(float startangle);
	//获取结束角度
	void EAngle(float endangle);

	//设置开始角度
	float SAngle();
	//设置结束角度
	float EAngle();

	virtual const char* GetType();
	virtual const char* ToWKT();
	virtual const char* ToGeojson();
	virtual float Circum();
	virtual float Area();

	CSectionPoly ToPolyGon(int n);

protected:
	//开始角度
	float StartAngle;
	//结束角度
	float EndAngle;
	//控制角度在0-360之间
	void CheckAngle();
};


