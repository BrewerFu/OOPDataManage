#pragma once
#include"GeomertyFile/CFeature.h"
#include"FileReader/TextReader.h"
#include"FileReader/ShapeFileReader.h"
#include"FileWriter/TextWriter.h"

//单例模式
//文件管理类，用于管理文件的读取和写入
class FileManager
{
public:
	//获取唯一实例
	static FileManager* GetInstance()
	{
		instance = new FileManager();
		return instance;
	}
	static FileManager* GetInstance(const char* FileName)
	{
		instance = new FileManager(FileName);
		return instance;
	}
	//销毁唯一实例
	static void DestoryInstance()
	{
		if (instance != nullptr)
		{
			delete instance;
			instance = nullptr;
		}
	}
	FileManager(const FileManager&) = delete;	//禁止拷贝构造函数
	FileManager& operator=(const FileManager&) = delete;	//禁止赋值运算符

	bool Open(const char* FileName);

	CFeature Read();
	
	bool Write(CFeature* feature);

	bool Close();

protected:
	FileManager();	//私有构造函数，防止类外部创建实例
	FileManager(const char* FileName);
	~FileManager();	//私有析构函数，防止类外部删除实例
	static FileManager* instance;	//唯一实例

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




