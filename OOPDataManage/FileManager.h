#define FILEMANAGER_EXPORTS

#pragma once
#include"GeomertyFile/CFeature.h"
#include"FileReader/TextReader.h"
#include"FileReader/ShapeFileReader.h"
#include"FileWriter/TextWriter.h"
#include"qfileinfo.h"
#include<stdexcept>

#ifdef FILEMANAGER_EXPORTS
#define FILEMANAGER_API __declspec(dllexport)
#else
#define FILEMANAGER_API __declspec(dllimport)
#endif // FILEMANAGER_EXPORTS


//单例模式
//文件管理类，用于管理文件的读取和写入
class FILEMANAGER_API FileManager
{
public:
	//获取唯一实例
	static FileManager& GetInstance() {
		static FileManager instance;
		return instance;
	}
	FileManager(const FileManager&) = delete;	//禁止拷贝构造函数
	FileManager& operator=(const FileManager&) = delete;	//禁止赋值运算符

	int Open(const char* FileName);

	int Open(std::string FileName);


	int Open(QString FileName);		//0为不能读写，1为可读写,2为可写

	CFeature* Read();

	bool Write(CFeature* feature);

	bool Save();

	bool Close();

protected:
	FileManager();	//私有构造函数，防止类外部创建实例
	~FileManager();	//私有析构函数，防止类外部删除实例
	static FileManager instance;	//唯一实例
	QString m_FileName;

	std::shared_ptr<CGeometry> GetGeometry(GeometryType type);
	FileReader* Reader;
	FileWriter* Writer;
	std::shared_ptr<CPoint> m_Point;
	std::shared_ptr<CPolyLine> m_PolyLine;
	std::shared_ptr<CPolyGon> m_PolyGon;
	std::shared_ptr<CRectAngle> m_RectAngle;
	std::shared_ptr<CCircle> m_Circle;
	std::shared_ptr<CSection> m_Section;
};
