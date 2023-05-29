#pragma once
#include<string>

//��ɫ��
class CColor
{
public:
	//��ȡ��ɫ����
	const char* GetColor();
	//��RGBA������ɫ
	void SetColorFromRGBA(int R, int G, int B, int A);
	//�����ɫ��RGBA
	void GetColorRGBA(int &R,int &G,int *B,int &A);

private:
	//R��ɫֵ
	int R;
	//G��ɫֵ
	int G;
	//B��ɫֵ
	int B;
	//A͸����
	int Alpha;
	//����
	char* name;
};


//������ʽ��ѡ��
enum LineStyle
{
	SolidLine,
	DashLine,
	DotLine,
	DashDotLine,
	DashDotDotLine
};

//�߿���ʽ
class CBorStyle
{
public:
	//���
	int m_Width;
	//������ʽ
	LineStyle m_Style;
	//������״

};

//�����ʽ
class CFilStyle
{

};
