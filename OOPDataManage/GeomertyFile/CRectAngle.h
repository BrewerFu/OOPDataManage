#pragma once
#include"CGeometry.h"
#include"CPoint.h"
#include<stdexcept>

//���ξ���
class CRectAngle :public CGeometry
{
public:
	//Ĭ�Ϲ��캯��
	CRectAngle() {};

	//ͨ�������㹹��
	CRectAngle(CPoint lefttop, CPoint rightbottom);

	//ͨ��һ����ͳ�����
	CRectAngle(CPoint lefttop, float width, float height);


	//��ȡ���
	float GetWidth();
	//��ȡ�߶�
	float GetHeight();

	//��ȡ���ϽǶ���
	CPoint GetLT();
	//��ȡ���½Ƕ���
	CPoint GetRB();

	//�������ϽǶ���
	void LT(CPoint c);
	//�������½Ƕ���
	void RB(CPoint c);


	virtual const char* GetType();
	virtual const char* ToWKT();
	virtual const char* ToGeojson();
	//�����ܳ�
	virtual float Circum();
	//�������
	virtual float Area();

private:
	//���ϽǶ���
	CPoint m_LT;
	//���½Ƕ���
	CPoint m_RB;
	//����Ƿ�ߵ�
	bool CheckReverse();
};
