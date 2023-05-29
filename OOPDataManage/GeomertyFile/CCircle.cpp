#include "CCircle.h"

//通过圆心和半径构造
CCircle::CCircle(CPoint c, float r):m_C(c),m_R(r)
{
}

CCircle::CCircle(float x, float y, float r):m_C(x, y), m_R(r)
{
}

//获取圆心
CPoint CCircle::GetC()
{
    return m_C;
}

//获取几何类型
const char* CCircle::GetType()
{
    return "Circle";
}

//TODO
const char* CCircle::ToWKT()
{
    return "TODO";
}

//TODO
const char* CCircle::ToGeojson()
{
    return "TODO";
}

//计算周长
float CCircle::Circum()
{
    return 2*std::acos(-1)*m_R;
}

//计算面积
float CCircle::Area()
{
    return std::acos(-1)*m_R*m_R;
}


//获取半径
float CCircle::GetR()
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