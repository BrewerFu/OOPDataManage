#pragma once
#include<string>
#include<qbrush.h>
#include<qpen.h>
#include<qcolor.h>
//颜色类
class CColor
{
public:
	//获取颜色名称
	const char* GetColorName();
	//从RGBA设置颜色
	void SetColorFromRGBA(int R, int G, int B, int A);
	//获得颜色的RGBA
	void GetColorRGBA(int &R,int &G,int &B,int &A);

protected:
	//R红色值
	int R;
	//G绿色值
	int G;
	//B蓝色值
	int B;
	//A透明度
	int Alpha;
	//名称
	char* name;
};


//边框样式
class CBoundaryStyle
{
public:
	//宽度
	int m_Width;
	Qt::PenStyle m_PenStyle;
};

//填充样式
class CFillStyle
{
public:
	Qt::BrushStyle m_BrushStyle;
};
