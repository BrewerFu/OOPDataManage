#include"FileWriter.h"
#include"qtextstream.h"

class TextWriter :public FileWriter
{
public:
	TextWriter() {};
	TextWriter(const char* filename) { Open(filename); };
	TextWriter(std::string filename) { Open(QString(filename.c_str())); };
	TextWriter(QString filename) { Open(filename); };

	~TextWriter();

	bool Open(QString FileName) override;

	bool Write(CFeature* feature)override;

protected:
	QTextStream qts;

	bool WriteHeader(const CFeature* feature) override;
	bool WritePoint(const std::shared_ptr<CPoint> point) override;
	bool WritePolyLine(std::shared_ptr<CPolyLine> polyline) override;
	bool WritePolyGon(std::shared_ptr<CPolyGon> polygon) override;
	bool WriteRectAngle(const std::shared_ptr<CRectAngle> rectangle) override;
	bool WriteCircle(const std::shared_ptr<CCircle> circle) override;
	bool WriteSection(const std::shared_ptr<CSection> section) override;
	//写边界和填充数据
	bool WriterAttribute(const std::shared_ptr<CGeometry> geo);
};

