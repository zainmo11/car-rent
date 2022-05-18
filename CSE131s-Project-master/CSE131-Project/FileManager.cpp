#include "FileManager.h"

FileManager::FileManager(std::string filename, int patchsize) {
	fs.open(filename.c_str());

	//Every file has patches of data (each patch is one line). We have to define how many bytes of data is in every line of the file
	//This number must be the same for every line
	PATCHSIZE = patchsize;

	//Gives an error if file is not found
	if (!fs) {
		std::cout << "[ERROR]: file not found" << std::endl;
		return;
	}

	fs.seekg(0, std::ios::end);
	filesize = fs.tellg();
	patchnum = filesize / PATCHSIZE;

	//This line was just for debugging
	//std::cout << "File has " << filesize << " bytes and " << patchnum << " objects" << std::endl;

}

std::string FileManager::read(int patch, int place) {
	//Reserve part of memory for reading
	std::string buffer;

	//Read the whole line
	fs.seekg((patch * PATCHSIZE), std::ios::beg);
	std::getline(fs, buffer);

	//Detect end of string if double space is found it means end of string
	std::string part = buffer.substr(place * PARTSIZE, PARTSIZE);
	for (int i = 0; i < part.length() - 1; i++) {
		if (part.substr(i, 2) == "  ")
			return part.substr(0, i);
	}

	if (part[14] == ' ')
		return part.substr(0, 14);

	//If the double space is not found then it will return the whole string
	return part;
}

/*
	Function made to search for certain unique word in the database
	and return its line index.
	Used nainly to search for data that is not used twice
	like: National ID and car plate number


	@param Searchkey, the word to search word, if this word is used twice it will return the first one found
	@return index if line, if word not found will return -1
*/
int FileManager::getIndex(std::string searchkey) {
	std::string buffer;

	for (int i = 0; i < patchnum; i++) {
		fs.seekg((i * PATCHSIZE), std::ios::beg);
		std::getline(fs, buffer);

		for (int j = 0; j < PATCHSIZE - PARTSIZE; j += PARTSIZE) {
			if (buffer.substr(j, searchkey.length()) == searchkey)
				return i;
		}
	}

	return -1;
}

/*
	Procedure used to write data in the file

	@params Data to write
	@params Patch, line index
	@params place, where in the line to write
*/
void FileManager::write(std::string data, int patch, int place) {
	std::string bufferdata(PARTSIZE, ' ');

	for (int i = 0; i < data.length(); i++)
		bufferdata[i] = data[i];
	
	//If the line of the writing process is a new line it will check if there is a deleted line
	//so it can be overwridden on top of the deleted part (I'm tired :))
	if (this->getObjectNumber() == patch) {
		int deletedIndex = this->getIndex("DELETED");
		if (deletedIndex != -1) patch = deletedIndex;
	}

	fs.seekp((patch * PATCHSIZE) + (place * PARTSIZE), std::ios::beg);

	if ((PATCHSIZE / PARTSIZE) - 1 == place)
		fs << bufferdata << std::endl;
	else
		fs << bufferdata;
}

//This procedure is used to delete whole lines of data
void FileManager::deletePatch(int patch) {
	std::string deletestr(PARTSIZE, ' ');
	std::string deletiontext = "DELETED";

	for (int i = 0; i < deletiontext.length(); i++)
		deletestr[i] = deletiontext[i];

	fs.seekp(patch * PATCHSIZE, std::ios::beg);
	
	for (int i = 0; i < (PATCHSIZE / PARTSIZE); i++) {
		if ((PATCHSIZE / PARTSIZE) - 1 == i)
			fs << deletestr << std::endl;
		else
			fs << deletestr;
	}
}

//Return number of objects or lines in file
int FileManager::getObjectNumber()  {
	fs.seekg(0, std::ios::end);
	filesize = fs.tellg();
	patchnum = filesize / PATCHSIZE;
	return patchnum;
}

//Destructor to close the file
FileManager::~FileManager() { fs.close(); }
