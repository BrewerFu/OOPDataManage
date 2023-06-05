#include"../GeomertyFile/CFeature.h"
#include"../GeomertyFile/CPolyGon.h"
#include"../GeomertyFile/CRectAngle.h"
#include"../GeomertyFile/CCircle.h"
#include"../GeomertyFile/CSection.h"
#include<qfile.h>


class GeoWriterFormat
{
public:
	virtual bool WriteHeader(const CFeature* feature) = 0;

	virtual bool WritePoint(const CPoint* point) =0;

	virtual bool WritePolyLine(CPolyLine* polyline) =0;

	virtual bool WritePolyGon(CPolyGon* polygon) =0;

	virtual bool WriteRectAngle(const CRectAngle* rectangle) =0;

	virtual bool WriteCircle(const CCircle* circle) =0;

	virtual bool WriteSection(const CSection* section) =0;

};

class FileWriter:public GeoWriterFormat
{
public:
	//打开文件
	virtual bool Open(const char* FileName) = 0;

	//写入文件
	virtual bool Write(CFeature* feature) = 0;

	//判断文件是否打开
	virtual bool isOpen() { return qfs.isOpen();};

	//关闭文件
	virtual bool Close() { qfs.close(); return true; };

protected:
	//qt文件读取
	QFile qfs;

};