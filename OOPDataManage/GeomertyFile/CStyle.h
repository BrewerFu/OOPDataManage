#define CSTYLE_EXPORTS
#pragma once
#include<string>
#include<qbrush.h>
#include<qpen.h>
#include<qcolor.h>

#ifdef CSTYLE_EXPORTS
#define CSTYLE_API __declspec(dllexport)
#else
#define CSTYLE_API __declspec(dllimport)
#endif // CSTYLE_EXPORTS


//边框样式
class CSTYLE_API CBoundaryStyle
{
public:
	//构造函数
	CBoundaryStyle()
	{
		m_Width = 1;
		m_PenStyle = Qt::SolidLine;
	}
	CBoundaryStyle(int width, Qt::PenStyle penStyle)
	{
		m_Width = width;
		m_PenStyle = penStyle;
	}
	//拷贝构造函数
	CBoundaryStyle(const CBoundaryStyle& boundaryStyle)
	{
		m_Width = boundaryStyle.m_Width;
		m_PenStyle = boundaryStyle.m_PenStyle;
	}
	//赋值运算符
	CBoundaryStyle& operator=(const CBoundaryStyle& boundaryStyle)
	{
		m_Width = boundaryStyle.m_Width;
		m_PenStyle = boundaryStyle.m_PenStyle;
		return *this;
	}
	std::string ToDBText()
	{
		return std::to_string(m_Width) + "," + QString::number(m_PenStyle).toStdString();
	}
	//宽度
	int m_Width;
	Qt::PenStyle m_PenStyle;
};

//填充样式
class CSTYLE_API CFillStyle
{
public:
	//构造函数
	CFillStyle()
	{
		m_BrushStyle = Qt::NoBrush;
	}
	CFillStyle(Qt::BrushStyle brushStyle)
	{
		m_BrushStyle = brushStyle;
	}
	//拷贝构造函数
	CFillStyle(const CFillStyle& fillStyle)
	{
		m_BrushStyle = fillStyle.m_BrushStyle;
	}
	//赋值运算符
	CFillStyle& operator=(const CFillStyle& fillStyle)
	{
		m_BrushStyle = fillStyle.m_BrushStyle;
		return *this;
	}

	Qt::BrushStyle m_BrushStyle;
};
