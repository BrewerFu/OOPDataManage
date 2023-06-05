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
	GeometryType GetType()const override;
	//转换为wkt
	const char* ToWKT()const override;
	//转换为geojson
	const char* ToGeojson()const override;
	//获取周长
	float Circum()const override;
	//获取面积
	float Area() const override;

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
	~CPolyGon();


	//获取环数
	int GetCount()const { return m_Rings.size(); };

	//添加环
	bool AppendRing(CRing* ring);

	//删除环,根据指针
	bool DeleteRing(CRing* pRing);

	//获取环,根据索引
	CRing* QueryRing(int index)const;

	//修改环,根据索引
	bool AlterRing(int index, CRing* ring);

	GeometryType GetType()const override;
	//转换为wkt
	const char* ToWKT()const override;
	//转换为geojson
	const char* ToGeojson()const override;
	//获取周长
	float Circum()const override;
	//获取面积
	float Area()const override;

	//重载[]运算符
	CRing* operator[](int pos);

	class iterator {
	public:
		iterator() = default;
		iterator(const std::vector<CRing*>::iterator& it) : m_it(it) {}
		iterator& operator++() { ++m_it; return *this; }
		iterator& operator++(int) { iterator tmp = *this; ++m_it; return tmp; }
		bool operator!=(const iterator& other) const { return m_it != other.m_it; }
		bool operator==(const iterator& other) const { return m_it == other.m_it; }
		CRing* operator*() const { return *m_it; }
	private:
		std::vector<CRing*>::iterator m_it;
	};
	iterator begin() { return iterator(m_Rings.begin()); }
	iterator end() { return iterator(m_Rings.end()); }

protected:
	std::vector<CRing*> m_Rings;
	bool CheckDuplicate(CRing* ring);
};
