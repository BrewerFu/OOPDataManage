#pragma once
#include"CGeometry.h"
#include<vector>

class CFeature
{
public:
	//默认构造函数
	CFeature(GeometryType type):Type(type){};
	//析构函数
	~CFeature() 
	{
		for (int i = 0; i < m_vector.size(); i++)
		{
			delete m_vector[i];
		}
		m_vector.clear();
	};

	//获取几何对象的类型
	GeometryType GetType()const
	{
		return Type;
	}

	//添加几何对象
	bool AppendGeometry(CGeometry* geo);

	//删除几何对象
	bool DeleteGeometry(CGeometry* geo);

	//根据索引获取几何对象
	CGeometry* GetGeometry(int index)const
	{
		return m_vector[index];
	}

	//获取几何对象的数量
	int GetCount()const
	{
		return m_vector.size();
	}

	//重载[]运算符
	CGeometry* operator[](int index)
	{
		return m_vector[index];
	}

	//判断是否为空
	bool IsEmpty()const
	{
		return m_vector.empty();
	}

	//迭代器对象
	class iterator
	{
	public:
		iterator(const std::vector<CGeometry*>::iterator& it): m_it(it) {}
		iterator& operator++() { ++m_it; return *this; }
		iterator operator++(int) { iterator tmp = *this; ++m_it; return tmp; }
		bool operator!=(const iterator& other) const { return m_it != other.m_it; }
		bool operator==(const iterator& other) const { return m_it == other.m_it; }
		CGeometry* operator->() const { return *m_it; }
		CGeometry* operator*() const { return *m_it; }
	private:
		std::vector<CGeometry*>::iterator m_it;
	};

	//迭代器的begin和end
	iterator begin() { return iterator(m_vector.begin()); }
	iterator end() { return iterator(m_vector.end()); }


private:
	//存储几何对象的容器
	std::vector<CGeometry*> m_vector;
	//检查几何对象的类型是否正确
	bool CheckCorrectType(GeometryType type);
	//存储几何对象的类型
	GeometryType Type;

};

