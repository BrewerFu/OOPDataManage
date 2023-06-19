#include "CCircle.h"

CCircle::CCircle() :m_R(1)
{
    ID = GetNewID(this);
}

CCircle::CCircle(const CCircle& c): m_R(c.m_R)
{
    ID = GetNewID(this);
    m_C = std::make_shared<CPoint>(*(c.m_C));
}

CCircle CCircle::operator=(const CCircle& c)
{
    if (this != &c)
    {
        this->m_C = std::make_shared<CPoint>(*(c.m_C));
        this->m_R = c.m_R;
    }
	return *this;
}

//通过圆心和半径构造
CCircle::CCircle(std::shared_ptr<CPoint> c, double r):m_R(r)
{
    m_C = c->shared_from_this();
	ID = GetNewID(this);
}

CCircle::~CCircle()
{
   ReleaseID(ID);
}

//获取圆心
std::shared_ptr<CPoint> CCircle::GetC()const
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
    return ToPolyGon(100)->ToWKT();
}


const char* CCircle::ToGeojson()const
{
    return ToPolyGon(100)->ToGeojson();
}

//计算周长
double CCircle::Circum()const
{
    return 2*std::acos(-1)*m_R;
}

//计算面积
double CCircle::Area()const
{
    return std::acos(-1)*m_R*m_R;
}


//获取半径
double CCircle::GetR()const
{
    return m_R;
}

//设置圆心
void CCircle::SetC(std::shared_ptr<CPoint> c)
{
    m_C = c;
}

//设置半径
void CCircle::SetR(double r)
{
    m_R = r;
}

std::shared_ptr<CPolyGon> CCircle::ToPolyGon(int n)const
{
    std::shared_ptr<CRing> ring = std::make_shared<CRing>();
    std::shared_ptr<CPoint> point = std::make_shared<CPoint>();
    std::shared_ptr<CPolyGon> polygon = std::make_shared<CPolyGon>();

    double  angle_increment = 2 * acos(-1) / n ;
    for (int i = 0; i < n; i++)
    {
        point->x(m_C->x() + m_R * cos(angle_increment * i));
        point->y(m_C->y() + m_R * sin(angle_increment * i));
        ring->AppendPoint(point);
    }

    polygon->AppendRing(ring);
    return polygon;
}