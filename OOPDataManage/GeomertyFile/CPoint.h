#pragma once
#include"CGeometry.h"

//���ε�
class CPoint :public CGeometry
{
public:
	//���캯��
	CPoint(float x, float y);
	//Ĭ�Ϲ��캯��
	CPoint();

	//��ȡx
	float x() { return m_X; };
	//��ȡy
	float y() { return m_Y; };

	//����x
	void x(float x) { m_X = x; };
	//����y
	void y(float y) { m_Y = y; };

	virtual const char* GetType();
	virtual const char* ToWKT();
	virtual const char* ToGeojson();
	
	//����+����
	CPoint operator +(CPoint c);
	//����+=����
	CPoint& operator +=(CPoint c);
	//����-����
	CPoint operator - (CPoint);
	//����*�������
	float operator*(CPoint c);
	//����^�������
	float operator ^ (CPoint c);
	//�жϵ�X��Yֵ�Ƿ����
	bool operator==(CPoint c);
	//�жϵ�X��Yֵ�Ƿ񲻵�
	bool operator!=(CPoint);

private:
	//x����
	float m_X;
	//y����
	float m_Y;
};

//��������֮��ľ���
float CPoint_Distance(CPoint c1, CPoint c2);
