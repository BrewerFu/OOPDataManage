#pragma once
#include"CPolyLine.h"
class CRing;
class CPolyGon;
#define _RINGPRT std::shared_ptr<CRing> ring = std::make_shared<CRing>();
#define _POLYGONPRT std::shared_ptr<CPolyGon> polygon = std::make_shared<CPolyGon>();

class CRingFactory;
class CPolyGonFactory;

class CRing :public CGeometry,public IDManager<CRing>
{
public:;
	//复制构造函数,副本
	  CRing(const CRing& ring) {};
	//默认构造函数
	CRing();
	//析构函数
	~CRing();

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

	//获取单折线点数
	int GetCount()const { return m_Pois.size(); };

	//在最后添加点
	bool AppendPoint(std::shared_ptr<CPoint> c);

	//在位置pos插入一个点
	bool InsertPoint(int pos, std::shared_ptr<CPoint> c);

	//删除点c
	bool DeletePoint(std::shared_ptr<CPoint> c);

	//删除位置在pos的点
	bool DeletePoint(int pos);

	//查询位置在pos处的点
	std::shared_ptr<CPoint> QureyPoint(int pos)const;

	//改变位置在pos处的点
	bool AlterPoint(int pos, std::shared_ptr<CPoint> c);

	//重载[]运算
	std::shared_ptr<CPoint> operator [](int pos);

	//重载==运算
	bool operator==(CRing c);
	//重载!=运算
	bool operator!=(CRing c);

	class iterator {
	public:
		iterator() = default;
		iterator(const std::vector<std::shared_ptr<CPoint>>::iterator& it) : m_it(it) {}
		iterator& operator++() { ++m_it; return *this; }
		iterator& operator++(int) { iterator tmp = *this; ++m_it; return tmp; }
		bool operator!=(const iterator& other) const { return m_it != other.m_it; }
		bool operator==(const iterator& other) const { return m_it == other.m_it; }
		std::shared_ptr<CPoint> operator*() const { return *m_it; }
	private:
		std::vector<std::shared_ptr<CPoint>>::iterator m_it;
	};
	class const_iterator {
	public:
		const_iterator() = default;

		const_iterator(const std::vector<std::shared_ptr<CPoint>>::const_iterator& m_it) : m_it(m_it) {}
		const_iterator(const std::vector<std::shared_ptr<CPoint>>::iterator& it) : m_it(it) {}
		const_iterator& operator++() { ++m_it; return *this; }
		const_iterator& operator++(int) { const_iterator tmp = *this; ++m_it; return tmp; }
		bool operator!=(const const_iterator& other) const { return m_it != other.m_it; }
		bool operator==(const const_iterator& other) const { return m_it == other.m_it; }
		std::shared_ptr<CPoint> operator*() const { return *m_it; }
	private:
		std::vector<std::shared_ptr<CPoint>>::const_iterator m_it;
	public:

	};

	iterator begin() { return iterator(m_Pois.begin()); }
	iterator end() { return iterator(m_Pois.end()); }

protected:
	std::vector<std::shared_ptr<CPoint>> m_Pois;
	//检查是否有重复
	bool CheckDuplicate(std::shared_ptr<CPoint> c);

friend class CRingFactory;
};

//几何多边形
class CPolyGon :public CGeometry,public IDManager<CPolyGon>
{
public:
	//默认构造函数
	CPolyGon();

	//复制构造函数,副本
	CPolyGon(const CPolyGon& poly) {};

	//析构函数
	~CPolyGon();

	//获取环数
	int GetCount()const { return m_Rings.size(); };

	//添加环
	bool AppendRing(std::shared_ptr<CRing> ring);

	//删除环,根据指针
	bool DeleteRing(std::shared_ptr<CRing> pRing);

	//获取环,根据索引
	std::shared_ptr<CRing> QueryRing(int index)const;

	//修改环,根据索引
	bool AlterRing(int index, std::shared_ptr<CRing> ring);

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
	std::shared_ptr<CRing> operator[](int pos);

	class iterator {
	public:
		iterator() = default;
		iterator(const std::vector<std::shared_ptr<CRing>>::iterator& it) : m_it(it) {}
		iterator& operator++() { ++m_it; return *this; }
		iterator& operator++(int) { iterator tmp = *this; ++m_it; return tmp; }
		bool operator!=(const iterator& other) const { return m_it != other.m_it; }
		bool operator==(const iterator& other) const { return m_it == other.m_it; }
		std::shared_ptr<CRing> operator*() const { return *m_it; }
	private:
		std::vector<std::shared_ptr<CRing>>::iterator m_it;
	};
	iterator begin() { return iterator(m_Rings.begin()); }
	iterator end() { return iterator(m_Rings.end()); }

protected:
	std::vector<std::shared_ptr<CRing>> m_Rings;
	bool CheckDuplicate(std::shared_ptr<CRing> ring);

friend class CPolyGonFactory;
};
