#pragma once
#include<string>

//颜色类
class CColor
{
public:
	//获取颜色名称
	const char* GetColor();
	//从RGBA设置颜色
	void SetColorFromRGBA(int R, int G, int B, int A);
	//获得颜色的RGBA
	void GetColorRGBA(int &R,int &G,int *B,int &A);

private:
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


//线条样式可选项
enum LineStyle
{
	SolidLine,
	DashLine,
	DotLine,
	DashDotLine,
	DashDotDotLine
};

//边框样式
class CBorStyle
{
public:
	//宽度
	int m_Width;
	//线条样式
	LineStyle m_Style;
	//线条形状

};

//填充样式
class CFilStyle
{

};
