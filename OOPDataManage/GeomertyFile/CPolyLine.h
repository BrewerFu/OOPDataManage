#pragma once
#include"CGeometry.h"
#include"CPoint.h"
#include<stdexcept>


#define _PATHPRT std::shared_ptr<CPath> path = std::make_shared<CPath>();
#define _POLYLINEPRT std::shared_ptr<CPolyLine> polyline = std::make_shared<CPolyLine>();

//几何单折线
class CGEOMETRY_API CPath :public CGeometry,public IDManager<CPath>
{
public:
	//默认构造函数
	CPath();
	//复制构造函数
	CPath(const CPath& c);
	//赋值运算符重载，副本
	CPath& operator=(const CPath& c);
	//析构函数
	~CPath();


	GeometryType GetType()const override;
	const char* ToWKT()const override;
	const char* ToGeojson()const override;
	const char* ToDBIDText()const override;
	double Circum()const override;

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
	bool AlterPoint(int pos,std::shared_ptr<CPoint> c);

	//重载[]运算
	std::shared_ptr<CPoint> operator [](int pos);

	//重载==运算
	bool operator==(CPath c);
	//重载!=运算
	bool operator!=(CPath c);

	class iterator {
	public:
		iterator() = default;
		iterator(const std::vector<std::shared_ptr<CPoint>>::iterator& it) : m_it(it) {}
		iterator& operator++() { ++m_it; return *this; }
		iterator operator++(int) { iterator tmp = *this; ++m_it; return tmp; }
		bool operator!=(const iterator& other) const { return m_it != other.m_it; }
		bool operator==(const iterator& other) const{return m_it == other.m_it;}
		std::shared_ptr<CPoint> operator*() const { return *m_it; }
	private:
		std::vector<std::shared_ptr<CPoint>>::iterator m_it;
	};
	class const_iterator {
	public:
		const_iterator() = default;

		const_iterator(const std::vector<std::shared_ptr<CPoint>>::const_iterator& m_it): m_it(m_it){}
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

	iterator begin(){ return iterator(m_Pois.begin()); }
	iterator end() { return iterator(m_Pois.end()); }

protected:
	std::vector<std::shared_ptr<CPoint>> m_Pois;
	//检查是否有重复
	bool CheckDuplicate(std::shared_ptr<CPoint> c);
};

//几何折线
class CGEOMETRY_API CPolyLine:public CGeometry,public IDManager<CPolyLine>
{
public:
	CPolyLine();
	//复制构造函数，副本
	CPolyLine(const CPolyLine& c);
	//析构函数
	~CPolyLine();
	//赋值构造函数,副本
	CPolyLine& operator=(const CPolyLine& c);

	GeometryType GetType()const override;
	const char* ToWKT()const override;
	const char* ToGeojson()const override;
	double Circum()const override;

	//获取折线段数
	int GetCount()const { return m_Paths.size(); };

	//在最后添加一个单折线
	bool AppendPath(std::shared_ptr<CPath> c);

	//删除一条单折线
	bool DeletePath(std::shared_ptr<CPath> c);

	//查询位置在pos处的点
	std::shared_ptr<CPath> QureyPath(int pos)const;

	//改变位置在pos处的点
	bool AlterPath(int pos, std::shared_ptr<CPath> c);

	//重载[]运算
	std::shared_ptr<CPath> operator [](int pos);

	class iterator {
	public:
		iterator() = default;
		iterator(const std::vector<std::shared_ptr<CPath>>::iterator& it) : m_it(it) {}
		iterator& operator++() { ++m_it; return *this; }
		iterator operator++(int) { iterator tmp = *this; ++m_it; return tmp; }
		bool operator!=(const iterator& other) const { return m_it != other.m_it; }
		bool operator==(const iterator& other) const { return m_it == other.m_it; }
		std::shared_ptr<CPath> operator*() const { return *m_it; }
	private:
		std::vector<std::shared_ptr<CPath>>::iterator m_it;
	};

	iterator begin() { return iterator(m_Paths.begin()); }
	iterator end() { return iterator(m_Paths.end()); }

private:

	//数组成员
	std::vector<std::shared_ptr<CPath>> m_Paths;
	//检查是否有重复
	bool CheckDuplicate(std::shared_ptr<CPath> c)const;
};