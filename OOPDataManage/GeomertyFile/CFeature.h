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
	GeometryType GetType()
	{
		return Type;
	}

	//添加几何对象
	bool AppendGeometry(CGeometry* geo);

	//删除几何对象
	bool DeleteGeometry(CGeometry* geo);

	//根据索引获取几何对象
	CGeometry* GetGeometry(int index)
	{
		return m_vector[index];
	}

	//获取几何对象的数量
	int GetGeometryCount()
	{
		return m_vector.size();
	}

	//重载[]运算符
	CGeometry* operator[](int index)
	{
		return m_vector[index];
	}
	

private:
	//存储几何对象的容器
	std::vector<CGeometry*> m_vector;
	//检查几何对象的类型是否正确
	bool CheckCorrectType(GeometryType type);
	//存储几何对象的类型
	GeometryType Type;

};


