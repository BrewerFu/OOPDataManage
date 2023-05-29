#include "CSection.h"

CSection::CSection(CPoint c, float r, float startangle, float endangle):CCircle(c,r),StartAngle(startangle),EndAngle(endangle)
{

}

const char* CSection::GetType()
{
    return "Section";
}

const char* CSection::ToWKT()
{
    char* wkt = new char[100];
    sprintf(wkt, "Section((%f,%f),%f,%f,%f)", m_C.x(), m_C.y(), m_R, StartAngle, EndAngle);
    return wkt;
}

const char* CSection::ToGeojson()
{
    char* geojson = new char[100];
    sprintf(geojson, "{\"type\":\"Section\",\"coordinates\":[[%f,%f],%f,%f,%f]}", m_C.x(), m_C.y(), m_R, StartAngle, EndAngle);
    return geojson;
}

float CSection::Circum()
{
    return CCircle::Circum() * (EndAngle - StartAngle) / (2 * acos(-1));
}

float CSection::Area()
{
    return  CCircle::Area() * (EndAngle - StartAngle) / (2 * acos(-1));
}

void CSection::SAngle(float startangle)
{
    StartAngle = startangle;
    CheckAngle();
}

void CSection::EAngle(float endangle)
{
    EndAngle = endangle;
    CheckAngle();
}

float CSection::SAngle()
{
    return StartAngle;
}

float CSection::EAngle()
{
    return EndAngle;
}

//���Ƕ��Ƿ���0-360֮��
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

CSectionPoly CSection::ToPolyGon(int n)
{
    CSectionPoly sectionpoly;
    sectionpoly.prt = this;
    sectionpoly.polygon = CPolyGon();
    //����΢�ֽǶ�
    float dangle = (EndAngle - StartAngle) / n;
    //����΢�ֵ�
    for (int i = 0; i < n; i++)
    {
        CPoint point;
        point.x(m_C.x() + m_R * cos((StartAngle + dangle * i) * acos(-1) / 180));
        point.y(m_C.y() + m_R * sin((StartAngle + dangle * i) * acos(-1) / 180));
        sectionpoly.polygon.AppendPoint(point);
    }
    //���Բ��
    sectionpoly.polygon.AppendPoint(m_C);
    return sectionpoly; 
}