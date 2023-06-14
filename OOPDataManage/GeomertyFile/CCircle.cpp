#include "CCircle.h"

//通过圆心和半径构造
CCircle::CCircle(CPoint* c, float r):m_C(c),m_R(r)
{
}

//获取圆心
CPoint* CCircle::GetC()const
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
    CPolyGon* polygon = ToPolyGon(100);
    const char* wkt = polygon->ToWKT();
    gm.DestroyGeometry(polygon);
    return wkt;
}


const char* CCircle::ToGeojson()const
{
    CPolyGon* polygon = ToPolyGon(100);
    const char* geojson = polygon->ToGeojson();
    gm.DestroyGeometry(polygon);
    return geojson;
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
void CCircle::SetC(CPoint* c)
{
    m_C = c;
}

//设置半径
void CCircle::SetR(float r)
{
    m_R = r;
}

CPolyGon* CCircle::ToPolyGon(int n)const
{
    CGeometry* geo = gm.CreateGeometry(GeometryType::Ring);
    CRing* ring = dynamic_cast<CRing*>(geo);
    geo = gm.CreateGeometry(GeometryType::Point);
    CPoint* point = dynamic_cast<CPoint*>(geo);
    geo = gm.CreateGeometry(GeometryType::PolyGon);
    CPolyGon* polygon = dynamic_cast<CPolyGon*>(geo);

    float  angle_increment = 2 * acos(-1) / n ;
    for (int i = 0; i < n; i++)
    {
        point->x(m_C->x() + m_R * cos(angle_increment * i));
        point->y(m_C->y() + m_R * sin(angle_increment * i));
        ring->AppendPoint(point);
    }

    polygon->AppendRing(ring);
    return polygon;
}