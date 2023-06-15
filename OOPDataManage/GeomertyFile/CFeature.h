#pragma once
#include"CGeometry.h"
#include<vector>
#include<map>
#include<set>
#define GET_FEATURE_GEOMETRY_BY_ID(featureVar, derivedType, varName, id) \
    std::shared_ptr<derivedType> varName  = std::dynamic_pointer_cast<derivedType>(featureVar->GetGeometryByID(id)); \

#define GET_FEATURE_GEOMETRY_BY_INDEX(featureVar, derivedType, varName, index) \
	std::shared_ptr<derivedType> varName  = std::dynamic_pointer_cast<derivedType>(featureVar->GetGeometryByIndex(index)); \
//class CFeatureManager;
//
////观察者模式
//class Observer;
//
//class Subject 
//{
//public:
//	virtual void Attach(Observer* observer)=0;
//	virtual bool Detach(Observer* observer)=0;
//	virtual void Notify()=0;
//};
//
//class Observer
//{
//public:
//	virtual void Update(Subject* subject) = 0;
//};


//要素类
class CFeature
{
public:

	//获取几何对象的类型
	GeometryType GetType()const
	{
		return m_Type;
	}

	//添加几何对象
	bool AppendGeometry(std::shared_ptr<CGeometry> geo);

	//删除几何对象
	bool DeleteGeometry(std::shared_ptr<CGeometry> geo);

	//根据索引获取几何对象
	std::shared_ptr<CGeometry> GetGeometryByIndex(int index)const
	{
		return m_vector[index];
	}

	//根据ID获取几何对象
	std::shared_ptr<CGeometry> GetGeometryByID(int id)const
	{
		for (int i = 0; i < m_vector.size(); i++)
		{
			if (m_vector[i]->GetID() == id)
			{
				return m_vector[i];
			}
		}
		return nullptr;
	}

	//获取几何对象的数量
	int GetCount()const
	{
		return m_vector.size();
	}

	std::shared_ptr<CGeometry> operator[](int index)
	{
		return m_vector[index];
	}

	//判断是否为空
	bool IsEmpty()const
	{
		return m_vector.empty();
	}

	//获取要对象素的ID
	int GetID() { return m_ID; }

	//迭代器对象
	class iterator
	{
	public:
		iterator(const std::vector<std::shared_ptr<CGeometry>>::iterator& it): m_it(it) {}
		iterator& operator++() { ++m_it; return *this; }
		iterator operator++(int) { iterator tmp = *this; ++m_it; return tmp; }
		bool operator!=(const iterator& other) const { return m_it != other.m_it; }
		bool operator==(const iterator& other) const { return m_it == other.m_it; }
		std::shared_ptr<CGeometry> operator->() const { return *m_it; }
		std::shared_ptr<CGeometry> operator*() const { return *m_it; }
	private:
		std::vector<std::shared_ptr<CGeometry>>::iterator m_it;
	};

	//迭代器的begin和end
	iterator begin() { return iterator(m_vector.begin()); }
	iterator end() { return iterator(m_vector.end()); }

private:

	CFeature(GeometryType type) :m_Type(type), m_ID(-1),m_DBID(-1){};
	~CFeature()
	{
		m_vector.clear();
	};
	//检查几何对象的类型是否正确
	bool CheckCorrectType(GeometryType type);
	void SetID(int id) { m_ID = id; }


	int m_ID,m_DBID;
	GeometryType m_Type;
	std::vector<std::shared_ptr<CGeometry>> m_vector;
	/*std::vector<Observer*> m_observers;*/
	friend class CFeatureManager;
};


class CFeatureManager
{
public:
	static CFeatureManager& GetInstance()
	{
		static CFeatureManager instance;
		return instance;
	}

	CFeature* CreateFeature(GeometryType type);

	bool DestroyFeature(CFeature* feature);

private:
	//单例模式
	CFeatureManager() {};
	CFeatureManager(const CFeatureManager&) {};
	CFeatureManager& operator=(const CFeatureManager&) {};
	~CFeatureManager();

	int GetUnusedID();
	void RecycleID(int id);

	//存储未使用的id
	std::set<int> m_unusedIds;
	//存储id和和要素对象指针
	std::map<int, CFeature*> m_map;
};
