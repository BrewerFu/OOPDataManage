#include "FileManager.h"

bool FileManager::Open(const char* FileName)
{
	if (this->Reader->Open(FileName))
		return true;
	else
		return false;
}

CFeature FileManager::Read()
{
	CFeature feature;
	while (Reader->isNext())
	{
		return feature;
	}
}