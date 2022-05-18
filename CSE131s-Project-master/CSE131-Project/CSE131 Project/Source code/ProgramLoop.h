#pragma once

#include "CarsData.h"
#include "Renter.h"
#include "FileManager.h"

#include <vector>
#include <string>

namespace ProgramLoop {
	
	void run();
	bool rent(std::string plate, long long id, std::vector<CarsData>& cars, std::vector<Renter>& renters, FileManager &fs, FileManager &fs2);
	void hire(FileManager& fs2, std::vector<CarsData>& cars);
	std::string hireRenter(FileManager& fs2, std::vector<Renter>& renters, std::string id = "");
}
