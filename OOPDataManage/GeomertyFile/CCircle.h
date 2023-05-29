#pragma once
#include"CGeometry.h"
#include"CPoint.h"
#include"CPolyGon.h"
#include<cmath>

//����Բ
class CCircle :public CGeometry
{
public:
	//Ĭ�Ϲ��캯��
	CCircle() {};
	//ͨ��Բ�ĺͰ뾶����
	CCircle(CPoint c, float r);

	//��ȡԲ��
	CPoint GetC();
	//��ȡ�뾶
	float GetR();

	//����Բ��
	void C(CPoint c);
	//���ð뾶
	void R(float r);
	
	virtual const char* GetType();
	virtual const char* ToWKT();
	virtual const char* ToGeojson();
	//�����ܳ�
	virtual float Circum();
	//�������
	virtual float Area();

	//ת��Ϊ�����
	//@param n:����α���
	//@return:��������κ�Բ�Ľṹ��
	CCirclePoly ToPolyGon(int n);

protected:
	//Բ��
	CPoint m_C;
	//�뾶
	float m_R;
};

//Բ�����
struct CCirclePoly
{
	//ָ��Բ��ָ��
	CCircle* prt;
	//�����
	CPolyGon polygon;
};
