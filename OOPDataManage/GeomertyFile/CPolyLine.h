#pragma once
#include"CGeometry.h"
#include"CPoint.h"
#include<stdexcept>


//几何单折线
class CPath :public CGeometry
{
public:
	//默认构造函数
	CPath() {};
	//复制构造函数
	CPath(const CPath& c);
	//析构函数
	~CPath() {};

	std::vector<CPoint> m_Pois;
	GeometryType GetType() override;
	const char* ToWKT() override;
	const char* ToGeojson() override;
	virtual float Circum();
	
	//获取单折线点数
	int GetCount() { return m_Pois.size(); };

	//在最后添加点
	bool AppendPoint(CPoint c);

	//在位置pos插入一个点
	bool InsertPoint(int pos, CPoint c);

	//删除点c
	bool DeletePoint(CPoint c);

	//删除位置在pos的点
	bool DeletePoint(int pos);

	//查询位置在pos处的点
	CPoint QureyPoint(int pos);

	//改变位置在pos处的点
	bool AlterPoint(int pos,CPoint c);

	//重载+运算
	CPath operator +(CPoint c);
	//重载-运算
	CPath operator - (CPoint c);
	//重载+=运算
	CPath& operator +=(CPoint c);
	//重载-=运算
	CPath& operator -=(CPoint c);

	//重载==运算
	bool operator==(CPath c);

	//重载!=运算
	bool operator!=(CPath c);

protected:
	//检查是否有重复
	bool CheckDuplicate(CPoint c);
};

//几何折线
class CPolyLine:public CGeometry
{
public:
	//默认构造函数
	CPolyLine() {};

	//复制构造函数
	CPolyLine(const CPolyLine& c);
	
	//析构函数
	~CPolyLine()
	{
		for (int i = 0; i < m_Paths.size(); i++)
		{
			delete m_Paths[i];
		}
	};

	//数组成员
	std::vector<CPath*> m_Paths;

	GeometryType GetType() override;
	const char* ToWKT() override;
	const char* ToGeojson() override;
	virtual float Circum();

	//获取折线段数
	int GetCount() { return m_Paths.size(); };

	//在最后添加一个单折线
	bool AppendPath(CPath* c);

	//删除一条单折线
	bool DeletePath(CPath* c);

	//查询位置在pos处的点
	CPath* QureyPath(int pos);

	//改变位置在pos处的点
	bool AlterPath(int pos, CPath* c);

	////重载+运算
	//CPolyLine operator +(CPath c);
	////重载-运算
	//CPolyLine operator - (CPath c);
	////重载+=运算
	//CPolyLine & operator +=(CPath c);
	////重载-=运算
	//CPolyLine & operator -=(CPath c);

private:
//检查是否有重复
	bool CheckDuplicate(CPath* c);
};