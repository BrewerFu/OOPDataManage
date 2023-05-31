#pragma once
#include"GeomertyFile/CFeature.h"
#include"FileReader/FileReader.h"


class FileManager
{
public:
	bool Open(const char* FileName);

	CFeature Read();
	
	bool Write(CFeature feature);

	bool Close();

protected:
	FileReader* Reader;
};




