#pragma once
#include"CCircle.h"

//��������
class CSection :public CCircle
{
public:
	//Ĭ�Ϲ��캯��
	CSection(){};

	//���캯��
	//@param startangle �Ƕ�,��ʼ�Ƕ�
	//@param endangle �Ƕ�,�����Ƕ�
	CSection(CPoint c, float r, float startangle, float endangle);

	//��ȡ��ʼ�Ƕ�
	void SAngle(float startangle);
	//��ȡ�����Ƕ�
	void EAngle(float endangle);

	//���ÿ�ʼ�Ƕ�
	float SAngle();
	//���ý����Ƕ�
	float EAngle();

	virtual const char* GetType();
	virtual const char* ToWKT();
	virtual const char* ToGeojson();
	virtual float Circum();
	virtual float Area();

	CSectionPoly ToPolyGon(int n);

protected:
	//��ʼ�Ƕ�
	float StartAngle;
	//�����Ƕ�
	float EndAngle;
	//���ƽǶ���0-360֮��
	void CheckAngle();
};

//�������ζ����
struct CSectionPoly
{
	CSection* prt;
	CPolyGon polygon;
};


