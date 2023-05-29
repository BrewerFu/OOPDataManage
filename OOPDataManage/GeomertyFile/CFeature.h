#pragma once
#include"CGeometry.h"
#include<vector>

template<class T>
class CFeature
{
public:
	std::vector<T> m_vector;
	const char* GetType();
	void Append();
	void Insert(int pos);
	void Erase(int pos);
	void Alter(int pos, T c);
	void Qurey(int pos, T c);
};

