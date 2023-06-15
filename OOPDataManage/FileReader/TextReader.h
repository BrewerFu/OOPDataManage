#include"FileReader.h"
#include<qtextstream.h>


class TextReader : public FileReader
{
public:
	TextReader() {};
	TextReader(const char* name) { Open(name); };
	TextReader(std::string name) { Open(QString(name.c_str())); };
	TextReader(QString name) { Open(name); }

	~TextReader() { qfs.close(); };

	bool Open(QString FileName) override;

	bool isNext() override;

	bool Close() override;

	GeometryType GetType();

	int GetGeometry(CPoint& point) override;

	int GetGeometry(CPolyLine& Line) override;

	int GetGeometry(CPolyGon& Gon) override;

	int GetGeometry(CRectAngle& Rect)override;

	int GetGeometry(CCircle& Cir)override;

	int GetGeometry(CSection& Sec)override;


protected:
	//跳转到Data数据
	void ToData();
	//读取颜色
	QColor ReadColor();
	//读取边界样式
	CBoundaryStyle ReadBoundaryStyle();
	//读取填充样式
	CFillStyle ReadFillStyle();

	//读取点
	std::shared_ptr<CPoint> ReadPoint();

	//读取属性
	template<class T>
	bool ReadAttribute(T& t);

	bool HaveToData=false;
	QString qstr;
	QTextStream qts;
	QStringList qsl;
};

