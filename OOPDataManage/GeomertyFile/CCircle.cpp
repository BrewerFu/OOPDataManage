#include "CCircle.h"

//ͨ��Բ�ĺͰ뾶����
CCircle::CCircle(CPoint c, float r):m_C(c),m_R(r)
{
}

//��ȡԲ��
CPoint CCircle::GetC()
{
    return m_C;
}

//��ȡ��������
const char* CCircle::GetType()
{
    return "Circle";
}

//TODO
const char* CCircle::ToWKT()
{

}

//TODO
const char* CCircle::ToGeojson()
{

}

//�����ܳ�
float CCircle::Circum()
{
    return 2*std::acos(-1)*m_R;
}

//�������
float CCircle::Area()
{
    return std::acos(-1)*m_R*m_R;
}


//��ȡ�뾶
float CCircle::GetR()
{
    return m_R;
}

//����Բ��
void CCircle::C(CPoint c)
{
    m_C = c;
}

//���ð뾶
void CCircle::R(float r)
{
    m_R = r;
}

CCirclePoly CCircle::ToPolyGon(int n)
{
    CCirclePoly circlePoly;
    circlePoly.prt = this;
    circlePoly.polygon = CPolyGon();
    float  angle_increment = 2 * acos(-1) / n ;
    for (int i = 0; i < n; i++)
    {
        CPoint point;
        point.x(m_C.x() + m_R * cos(angle_increment * i));
        point.y(m_C.y() + m_R * sin(angle_increment * i));
        circlePoly.polygon.AppendPoint(point);
    }
    return circlePoly;
}