#pragma once
#include<vector>
#include<string>
#include"CStyle.h"

//�������
struct BBox
{
	//����
	float LT;
	//����
	float RB;
};

//���󼸺�
class CGeometry
{
public:
	//���α߽�
	BBox BoundingBox;

	int id;

	//�Ƿ�ɾ��
	bool isDelete;

	//��ȡ��������
	virtual const char* GetType()=0;

	//��ȡWKT��ʽ����
	virtual const char* ToWKT() = 0;
	
	//��ȡGeoJson���ͼ���
	virtual const char* ToGeojson() = 0;
	
	//�߿���ɫ
	CColor BorderColor;
	
	//�����ɫ
	CColor FillColor;
	
	//�߿���ʽ
	CBorStyle BorderStyle;
	
	//�����ʽ
	CFilStyle FillStyle;

	//����������
	virtual ~CGeometry();
};



