#pragma once
#include"GeomertyFile/CFeature.h"
#include"FileReader/TextReader.h"
#include"FileReader/ShapeFileReader.h"
#include"FileWriter/TextWriter.h"
#include"qfileinfo.h"
#include<stdexcept>

//单例模式
//文件管理类，用于管理文件的读取和写入
class FileManager
{
public:
	//获取唯一实例
	static FileManager& GetInstance() {
		static FileManager instance;
		return instance;
	}
	FileManager(const FileManager&) = delete;	//禁止拷贝构造函数
	FileManager& operator=(const FileManager&) = delete;	//禁止赋值运算符

	bool Open(const char* FileName);

	bool Open(std::string FileName);

	bool Open(QString FileName);

	CFeature* Read();

	bool Write(CFeature* feature);

	bool Save();

	bool Close();

protected:
	FileManager();	//私有构造函数，防止类外部创建实例
	~FileManager();	//私有析构函数，防止类外部删除实例
	static FileManager instance;	//唯一实例
	QString m_FileName;

	CGeometry* GetGeometry(GeometryType type);
	FileReader* Reader;
	FileWriter* Writer;
	CPoint* m_Point;
	CPolyLine* m_PolyLine;
	CPolyGon* m_PolyGon;
	CRectAngle* m_RectAngle;
	CCircle* m_Circle;
	CSection* m_Section;
};
