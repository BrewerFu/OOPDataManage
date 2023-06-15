#include"../GeomertyFile/CFeature.h"
#include"../GeomertyFile/CPolyGon.h"
#include"../GeomertyFile/CRectAngle.h"
#include"../GeomertyFile/CCircle.h"
#include"../GeomertyFile/CSection.h"
#include<qfile.h>
#include<qfileinfo.h>

class GeoWriterFormat
{
public:
	virtual bool WriteHeader(const CFeature* feature) = 0;

	virtual bool WritePoint(const std::shared_ptr<CPoint> point) =0;

	virtual bool WritePolyLine(std::shared_ptr<CPolyLine> polyline) =0;

	virtual bool WritePolyGon(std::shared_ptr<CPolyGon> polygon) =0;

	virtual bool WriteRectAngle(const std::shared_ptr<CRectAngle> rectangle) =0;

	virtual bool WriteCircle(const std::shared_ptr<CCircle> circle) =0;

	virtual bool WriteSection(const std::shared_ptr<CSection> section) =0;

};

class FileWriter:public GeoWriterFormat
{
public:
	//打开文件

	virtual bool Open(QString FileName) = 0;

	//写入文件
	virtual bool Write(CFeature* feature) = 0;

	//判断文件是否打开
	virtual bool isOpen() { return qfs.isOpen();};

	//关闭文件
	virtual bool Close() { qfs.close(); return true; };

	virtual bool Save() 
	{
		qfs.setFileName(m_FilePath + "/" + m_FileName);
		if (qfs.exists())
		{
			if(!qfs.remove())
				return false;
		}
		if (!qfs.rename(m_FilePath + "/~" + m_FileName, m_FilePath + "/" + m_FileName))
		{
			return false;
		}
		else
		{
			this->Open(m_FilePath + "/" + m_FileName);
			return true;
		}
	};

protected:
	//qt文件读取
	QFile qfs;
	QString m_FileName, m_FilePath;

};