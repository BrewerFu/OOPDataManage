#pragma once
#include"CPolyLine.h"


class CRing :public CPath
{
public:
	//默认构造函数
	CRing() {};

	//复制构造函数
	CRing(const CRing& ring);

	//析构函数
	~CRing(){};

	//获取类型
	GeometryType GetType()override;
	//转换为wkt
	const char* ToWKT()override;
	//转换为geojson
	const char* ToGeojson()override;
	//获取周长
	virtual float Circum();
	//获取面积
	virtual float Area();

};

//几何多边形
class CPolyGon :public CGeometry
{
public:
	//默认构造函数
	CPolyGon() {};
	//复制构造函数
	CPolyGon(const CPolyGon& poly);

	//析构函数
	~CPolyGon()
	{
		for(int i=0;i<m_Rings.size();i++)
		{
			delete m_Rings[i];
		}
	}

	std::vector<CRing*> m_Rings;

	//获取环数
	int GetCount() { return m_Rings.size(); };

	//添加环
	bool AppendRing(CRing* ring);

	//删除环,根据指针
	bool DeleteRing(CRing* pRing);

	//获取环,根据索引
	CRing* QueryRing(int index);

	//修改环,根据索引
	bool AlterRing(int index, CRing* ring);

	GeometryType GetType()override;
	//转换为wkt
	const char* ToWKT()override;
	//转换为geojson
	const char* ToGeojson()override;
	//获取周长
	virtual float Circum();
	//获取面积
	virtual float Area();

protected:
	bool CheckDuplicate(CRing* ring);
};
