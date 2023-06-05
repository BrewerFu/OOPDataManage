#include"FileWriter.h"
#include"qtextstream.h"

class TextWriter :public FileWriter
{
public:
	TextWriter() {};
	TextWriter(const char* filename);
	~TextWriter();

	bool Open(const char* FileName);

	bool Write(CFeature* feature);

protected:
	QTextStream qts;

	bool WriteHeader(const CFeature* feature) override;
	bool WritePoint(const CPoint* point) override;
	bool WritePolyLine(CPolyLine* polyline) override;
	bool WritePolyGon(CPolyGon* polygon) override;
	bool WriteRectAngle(const CRectAngle* rectangle) override;
	bool WriteCircle(const CCircle* circle) override;
	bool WriteSection(const CSection* section) override;
	//写边界和填充数据
	bool WriterAttribute(const CGeometry* geo);
};

