#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

class FileManager
{
private:
	std::fstream fs;

	int filesize, patchnum, PATCHSIZE;
	const int PARTSIZE = 30;

public:

	std::string read(int patch, int patchPart = 0);
	void write(std::string data, int patch, int patchPart);
	void deletePatch(int patch);

	int getObjectNumber();
	int getIndex(std::string searchkey);

	FileManager(std::string filename, int patchsize);
	~FileManager();

};

