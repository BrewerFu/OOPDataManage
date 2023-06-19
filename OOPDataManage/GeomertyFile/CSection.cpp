#include "CSection.h"

CSection::CSection() :m_C(nullptr), m_R(1), StartAngle(0), EndAngle(360)
{
    ID = GetNewID(this);
}


CSection::CSection(std::shared_ptr<CPoint> c, double r, double startangle, double endangle):m_R(1), StartAngle(startangle), EndAngle(endangle)
{
    ID = GetNewID(this);
    m_C = c -> shared_from_this();
}

CSection::CSection(const CSection& c) :m_R(c.m_R), StartAngle(c.StartAngle), EndAngle(c.EndAngle)
{
	ID = GetNewID(this);
	m_C = std::make_shared<CPoint>(*(c.m_C));
}

CSection CSection::operator=(const CSection& c)
{
    if (this != &c)
    {
        ID = GetNewID(this);
        m_C = std::make_shared<CPoint>(*(c.m_C));
        m_R = c.m_R;
        StartAngle = c.StartAngle;
        EndAngle = c.EndAngle;
    }
    return *this;
}


CSection::~CSection()
{
	ReleaseID(ID);
}

GeometryType CSection::GetType()const
{
    return GeometryType::Section;
}

const char* CSection::ToWKT()const
{
    return ToPolyGon(100)->ToWKT();
}

const char* CSection::ToGeojson()const
{
    return ToPolyGon(100)->ToGeojson();
}

double CSection::Circum()const
{
    return (double) (2 * std::acos(-1) * m_R * (double)fabs(EndAngle - StartAngle) / (360));
}

double CSection::Area()const
{
    return  (double)(std::acos(-1) * m_R * m_R * (double)fabs(EndAngle - StartAngle) / (360));
}

//获取圆心
std::shared_ptr<CPoint> CSection::GetC()const
{
    return m_C;
}

//获取半径
double CSection::GetR()const
{
    return m_R;
}

//设置圆心
void CSection::SetC(std::shared_ptr<CPoint> c)
{
    m_C = c;
}

//设置半径
void CSection::SetR(double r)
{
    m_R = r;
}



void CSection::SetSAngle(double startangle)
{
    StartAngle = startangle;
    CheckAngle();
}

void CSection::SetEAngle(double endangle)
{
    EndAngle = endangle;
    CheckAngle();
}

double CSection::GetSAngle()const
{
    return StartAngle;
}

double CSection::GetEAngle()const
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

std::shared_ptr<CPolyGon> CSection::ToPolyGon(int n)const
{
    std::shared_ptr<CRing> ring = std::make_shared<CRing>();
    std::shared_ptr<CPoint> point = std::make_shared<CPoint>();
    std::shared_ptr<CPolyGon> polygon = std::make_shared<CPolyGon>();

    //计算微分角度
    double dangle = (EndAngle - StartAngle) / n;
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