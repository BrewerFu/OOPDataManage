#include "CSection.h"

CSection::CSection(CPoint* c, float r, float startangle, float endangle):CCircle(c,r),StartAngle(startangle),EndAngle(endangle)
{

}

GeometryType CSection::GetType()const
{
    return GeometryType::Section;
}

const char* CSection::ToWKT()const
{
    CPolyGon* polygon = ToPolyGon(100);
    const char* wkt = polygon->ToWKT();
    gm.DestroyGeometry(polygon);
    return wkt;
}

const char* CSection::ToGeojson()const
{
    CPolyGon* polygon = ToPolyGon(100);
    const char* geojson = polygon->ToGeojson();
    gm.DestroyGeometry(polygon);
    return geojson;
}

float CSection::Circum()const
{
    return (float) CCircle::Circum() * (double)fabs(EndAngle - StartAngle) / (360);
}

float CSection::Area()const
{
    return  (float)CCircle::Area() * (double)fabs(EndAngle - StartAngle) / (360);
}

void CSection::SetSAngle(float startangle)
{
    StartAngle = startangle;
    CheckAngle();
}

void CSection::SetEAngle(float endangle)
{
    EndAngle = endangle;
    CheckAngle();
}

float CSection::GetSAngle()const
{
    return StartAngle;
}

float CSection::GetEAngle()const
{
    return EndAngle;
}

//检查角度是否在0-360之间
void CSection::CheckAngle()
{
    while (StartAngle <= 0 || StartAngle > 360)
    {
        if (StartAngle <= 0)
        {
            StartAngle += 360;
        }
        else if (StartAngle > 360)
        {
            StartAngle -= 360;
        }
    }
    while (EndAngle <= 0 || EndAngle > 360)
    {
        if (EndAngle <= 0)
        {
            EndAngle += 360;
        }
        else if (EndAngle > 360)
        {
            EndAngle -= 360;
        }
    }
}

CPolyGon* CSection::ToPolyGon(int n)const
{
    CGeometry* geo = gm.CreateGeometry(GeometryType::Ring);
    CRing* ring = dynamic_cast<CRing*>(geo);
    geo = gm.CreateGeometry(GeometryType::Point);
    CPoint* point = dynamic_cast<CPoint*>(geo);
    geo = gm.CreateGeometry(GeometryType::PolyGon);
    CPolyGon* polygon = dynamic_cast<CPolyGon*>(geo);

    //计算微分角度
    float dangle = (EndAngle - StartAngle) / n;
    //计算微分点
    for (int i = 0; i < n; i++)
    {
        point->x(m_C->x() + m_R * cos((StartAngle + dangle * i) * acos(-1) / 180));
        point->y(m_C->y() + m_R * sin((StartAngle + dangle * i) * acos(-1) / 180));
        ring->AppendPoint(point);
    }

    //添加圆心
    ring->AppendPoint(m_C);
    //添加环
    polygon->AppendRing(ring);
    return polygon;
}