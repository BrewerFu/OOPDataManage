#pragma once
#include"CGeometry.h"
#include"CPoint.h"
#include<exception>

//几何折线
class CPolyLine :public CGeometry
{
public:
	//默认构造函数
	CPolyLine() {};
	//复制构造函数
	CPolyLine(const CPolyLine& c);

	std::vector<CPoint> m_Pois;
	virtual const char* GetType();
	virtual const char* ToWKT();
	virtual const char* ToGeojson();
	virtual float Circum();
	
	//获取折线点数
	int GetCount() { return m_Pois.size(); };

	//在最后添加点
	void AppendPoint(CPoint c);

	//在位置pos插入一个点
	bool InsertPoint(int pos, CPoint c);

	//删除点c
	bool DeletePoint(CPoint c);

	//删除位置在pos的点
	bool DeletePoint(int pos);

	//查询位置在pos处的点
	CPoint QureyPoint(int pos);

	//改变位置在pos处的点
	void AlterPoint(int pos,CPoint c);

	//重载+运算
	CPolyLine operator +(CPoint c);
	//重载-运算
	CPolyLine operator - (CPoint c);

protected:
	//检查是否有重复
	bool CheckDuplicate(CPoint c);

};

