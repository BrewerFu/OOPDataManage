#include "CCircle.h"

//通过圆心和半径构造
CCircle::CCircle(CPoint c, float r):m_C(c),m_R(r)
{
}

CCircle::CCircle(float x, float y, float r):m_C(x, y), m_R(r)
{
}

//获取圆心
CPoint CCircle::GetC()const
{
    return m_C;
}

//获取几何类型
GeometryType CCircle::GetType()const
{
    return GeometryType::Circle;
}


const char* CCircle::ToWKT()const
{
    return this->ToPolyGon(100).ToWKT();
}


const char* CCircle::ToGeojson()const
{
    return this->ToPolyGon(100).ToWKT();
}

//计算周长
float CCircle::Circum()const
{
    return 2*std::acos(-1)*m_R;
}

//计算面积
float CCircle::Area()const
{
    return std::acos(-1)*m_R*m_R;
}


//获取半径
float CCircle::GetR()const
{
    return m_R;
}

//设置圆心
void CCircle::C(CPoint c)
{
    m_C = c;
}

//设置半径
void CCircle::R(float r)
{
    m_R = r;
}

CPolyGon CCircle::ToPolyGon(int n)const
{
    CRing* ring = new CRing;
    CPoint point;
    CPolyGon polygon = CPolyGon();

    float  angle_increment = 2 * acos(-1) / n ;
    for (int i = 0; i < n; i++)
    {
        point.x(m_C.x() + m_R * cos(angle_increment * i));
        point.y(m_C.y() + m_R * sin(angle_increment * i));
        *ring+=point;
    }

    polygon.AppendRing(ring);
    return polygon;
}