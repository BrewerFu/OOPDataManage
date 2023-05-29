#pragma once
#include"CGeometry.h"
#include"CPoint.h"
#include<exception>

//��������
class CPolyLine :public CGeometry
{
public:
	//Ĭ�Ϲ��캯��
	CPolyLine() {};
	//���ƹ��캯��
	CPolyLine(const CPolyLine& c);

	std::vector<CPoint> m_Pois;
	virtual const char* GetType();
	virtual const char* ToWKT();
	virtual const char* ToGeojson();
	virtual float Circum();
	
	//��ȡ���ߵ���
	int GetCount() { return m_Pois.size(); };

	//�������ӵ�
	void AppendPoint(CPoint c);

	//��λ��pos����һ����
	bool InsertPoint(int pos, CPoint c);

	//ɾ����c
	bool DeletePoint(CPoint c);

	//ɾ��λ����pos�ĵ�
	bool DeletePoint(int pos);

	//��ѯλ����pos���ĵ�
	CPoint QureyPoint(int pos);

	//�ı�λ����pos���ĵ�
	void AlterPoint(int pos,CPoint c);

	//����+����
	CPolyLine operator +(CPoint c);
	//����-����
	CPolyLine operator - (CPoint c);

protected:
	//����Ƿ����ظ�
	bool CheckDuplicate(CPoint c);

};

