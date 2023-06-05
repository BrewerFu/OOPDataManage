#include"ShapeFileReader.h"

int Big2Little(int a)
{
	char* pt = (char*)&a;
	int b;
	char* pt0 = (char*)&b;
	pt0[0] = pt[3];
	pt0[1] = pt[2];
	pt0[2] = pt[1];
	pt0[3] = pt[0];
	return b;
}

bool ShapeFileReader::Open(const char* FileName)
{
	try
	{
		qfs.setFileName(FileName);
		if(!qfs.open(QIODevice::ReadOnly))
			return false;
		if(!qfs.isOpen())
			return false;
	}
	catch(std::exception e)
	{
		return false;
	}
	//偏移100
	m_cursur = 100;
	return true;
}

bool ShapeFileReader::isNext()
{
	return !qfs.atEnd();
}

bool ShapeFileReader::Close()
{
	qfs.close();
	return true;
}


GeometryType ShapeFileReader::GetType()
{
	int Shapetype;
	//从32位开始读4个字节
	qfs.seek(32);
	qfs.read((char*)&Shapetype, 4);

	//返回数字

	switch (Shapetype)
	{
	case 1:
		return GeometryType::Point;
	case 3:
		return GeometryType::PolyLine;
	case 5:
		return GeometryType::PolyGon;
	default:
		return GeometryType::Undefined;
	}
}

//读取点
int ShapeFileReader::GetGeometry(CPoint& point)
{
	//跳过记录号
	qfs.seek(m_cursur + 4);
	//读取内容长度
	int len;
	qfs.read((char*)&len, 4);
	len = Big2Little(len) * 2;

	char* ptBuf = new char[len];
	qfs.read(ptBuf, len);

	double* pt = (double*)(ptBuf + 4);
	point= CPoint(pt[0], pt[1]);
	
	//移动游标
	m_cursur += 4 + 4 + len;

	return 1;
}

//读取线
int ShapeFileReader::GetGeometry(CPolyLine& Line)
{
	//跳过记录号
	qfs.seek(m_cursur + 4);
	//读取内容长度
	int len;
	qfs.read((char*)&len, 4);

	len = Big2Little(len) * 2;

	char* ptBuf = new char[len];
	qfs.read(ptBuf, len);


	int partNum = *(int*)(ptBuf + 36);
	int pointNum = *(int*)(ptBuf + 40);
	int* start = (int*)(ptBuf + 44);
	double* pnts = (double*)(ptBuf + 44 + partNum * 4);


	for (int i = 0; i < partNum; i++)
	{
		int end = (i == partNum - 1) ? pointNum : start[i + 1];
		//新建一个折线
		CPath* path = new CPath;
		for (int j = start[i]; j < end; j++)
		{
			CPoint point(pnts[2 * j], pnts[2 * j + 1]);
			*path+=point;
		}
		//加入折线
		Line.AppendPath(path);
	}
	//释放内存
	delete[]ptBuf;
	//移动游标
	m_cursur += 4 + 4 + len;

	return 1;
}

//读取面
int ShapeFileReader::GetGeometry(CPolyGon& Gon)
{
	//跳过记录号
	qfs.seek(m_cursur + 4);
	//读取内容长度
	int len;
	qfs.read((char*)&len, 4);

	len = Big2Little(len) * 2;
	char* ptBuf = new char[len];
	qfs.read(ptBuf, len);

	int partNum = *(int*)(ptBuf + 36);
	int pointNum = *(int*)(ptBuf + 40);
	int* start = (int*)(ptBuf + 44);
	double* pnts = (double*)(ptBuf + 44 + partNum * 4);

	for (int i = 0; i < partNum; i++)
	{
		int end = (i == partNum - 1) ? pointNum : start[i + 1];
		//新建一个线环
		CRing* ring = new CRing;
		for (int j = start[i]; j < end; j++)
		{
			CPoint point(pnts[2 * j], pnts[2 * j + 1]);
			*ring+= point;
		}
		//线环加入多边形
		Gon.AppendRing(ring);
	}

	//释放内存
	delete[]ptBuf;
	//移动游标
	m_cursur += 4 + 4 + len;
	return 1;
}

