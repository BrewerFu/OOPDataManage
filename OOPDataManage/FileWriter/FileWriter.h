#include"../GeomertyFile/CFeature.h"
#include<qfile.h>


class FileWriter
{
public:
	virtual bool Open(const char* FileName) = 0;

	virtual bool Write(CFeature* feature) = 0;

	virtual bool isOpen() { return qfs.isOpen(); };

	virtual bool Close() { qfs.close(); return true; };

protected:
	//qt�ļ���ȡ
	QFile qfs;
};