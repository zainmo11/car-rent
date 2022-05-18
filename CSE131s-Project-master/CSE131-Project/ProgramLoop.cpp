#include "ProgramLoop.h"

#include <iostream>

//Function used to rent a car
bool ProgramLoop::rent(std::string plate, long long id, std::vector<CarsData>& cars, std::vector<Renter>& renters, FileManager& fs, FileManager& fs2) {
	int carIndex = -1;

	//Search the car by the plate number
	for (int i = 0; i < cars.size(); i++) {
		if (cars[i].get_license_plates_number() == plate)
			carIndex = i;
	}

	//If car not found it will return false
	if (carIndex == -1) {
		std::cout << "Car not available in not on our database, can not rent" << std::endl;
		return false;
	}

	//If car is found but it is already rented then it will return false
	else if (carIndex != -1 && cars[carIndex].get_renter() != "not rented") {
		std::cout << "This car is already rented, can not rent" << std::endl;
		return false;
	}

	//IF found and it is not rented and the user is already in the databse it will assign the renter to the car
	//and edit it in the database
	for (int i = 0; i < renters.size(); i++) {
		if (renters[i].get_National_ID() == id) {
			cars[carIndex].set_Renter(renters[i].get_Name());
			fs2.write(renters[i].get_Name(), fs2.getIndex(cars[carIndex].get_license_plates_number()), 3);
			return true;
		}
	}

	//If the id of the user was not found it will create a new profile for him and rent the car
	std::cout << "You are a new renter, ";
	std::string name = hireRenter(fs, renters, std::to_string(id));
	
	//If every thing works succesfully it will rent the car and return true
	if (name != " ") {
		cars[carIndex].set_Renter(name);
		fs2.write(name, fs2.getIndex(cars[carIndex].get_license_plates_number()), 3);

		return true;
	}

	//Else it returns false
	return false;
}

//Procedure used to hire a new car
void ProgramLoop::hire(FileManager& fs2, std::vector<CarsData>& cars) {

	//It will ask for all the following information
	std::cout << "Please fill the following information: " << std::endl;
	std::cout << "name : " << std::endl;
	std::string name;
	std::getline(std::cin, name);
	std::cout << "car model : " << std::endl;
	std::string car_model;
	std::getline(std::cin, car_model);
	std::cout << "license plates number : " << std::endl;

	std::string  license_plates_number;
	std::getline(std::cin, license_plates_number);

	//If plate is already used it will prompt the user to write it again
	while (fs2.getIndex(license_plates_number) != -1) {
		std::cout << "this license plates number is already used" << "\n" << "please enter new license plates number" << "\n";
		std::getline(std::cin, license_plates_number);
	}

	//Write all data on the database and psh it to the vector
	fs2.write(car_model, fs2.getObjectNumber(), 0);
	fs2.write(license_plates_number, fs2.getObjectNumber(), 1);
	fs2.write(name, fs2.getObjectNumber(), 2);
	fs2.write("not rented", fs2.getObjectNumber(), 3);
	CarsData new_car(car_model, license_plates_number, name, "not rented");
	cars.push_back(new_car);
}

/*
	Procedure used to create a new renter profile
	
	@return Name of the new renter if everything worked succesfully else return " " (Empty string)
*/
std::string ProgramLoop::hireRenter(FileManager& fs2, std::vector<Renter>& renters, std::string id) {
	std::cout << "Please fill the following information: " << std::endl;

	//If the id is not given it will ask for it
	if (id == "") {
		std::cout << "ID: " << std::endl;
		std::string idstr;
		std::getline(std::cin, idstr);
		id = idstr;

		while(id.length() != 14) {
			std::cout << "National ID is incorrect, please try again" << std::endl;
			std::getline(std::cin, idstr);
			id = idstr;
		}
	}

	//If id is already found on database it will stop the registration process
	for (int i = 0; i < renters.size(); i++) {
		if (renters[i].get_National_ID() == std::stoll(id)) {
			std::cout << "This ID is already available on our database" << std::endl;
			return " ";
		}
	}

	//Then it will ask for normal information
	std::cout << "Name: " << std::endl;
	std::string name;
	std::getline(std::cin, name);
	std::cout << "Gender: " << std::endl;
	std::string gender;
	std::getline(std::cin, gender);
	std::cout << "age: " << std::endl;
	std::string age;
	std::getline(std::cin, age);

	//Will not accept if age is less than 18 years
	if (std::stoi(age) < 18) {
		std::cout << "User too young and can not create renter profile" << std::endl;
		return " ";
	}

	std::cout << "Licence number: " << std::endl;
	std::string licence;
	std::getline(std::cin, licence);

	//Will not accept if the licencenumber is not 10 number or is already used
	while (licence.length() != 10) {
		std::cout << "Licence is incorrect, please try again" << std::endl;
		std::getline(std::cin, licence);
	}

	for (int i = 0; i < renters.size(); i++) {
		if (renters[i].get_License_Number() == std::stoll(licence)) {
			std::cout << "This licence is already available on our database" << std::endl;
			return " ";
		}
	}


	//If everything went succesfully the renter object will be created and and written on the database
	//and pushed in the vector.
	Renter newRenter(std::stoll(id), name, gender, std::stoi(age), std::stoll(licence));
	renters.push_back(newRenter);
	fs2.write(id, fs2.getObjectNumber(), 0);
	fs2.write(name, fs2.getObjectNumber(), 1);
	fs2.write(gender, fs2.getObjectNumber(), 2);
	fs2.write(age, fs2.getObjectNumber(), 3);
	fs2.write(licence, fs2.getObjectNumber(), 4);

	std::cout << "Succesfully registered" << std::endl;
	return name;
}

/*
	The main block of code where the magic happens :D
*/

void ProgramLoop::run() {
	//Since the program is always running we will make a boolean that is true once the program starts
	bool running = true;

	//Declare the vectors and the command string
	std::vector<Renter> renters;
	std::vector<CarsData> cars;
	std::string command;

	//Create a filemanager object for the two file and assign the line length or data patch size
	FileManager driversData("driversData.csv", 152);
	FileManager carsData("carsData.csv", 122);

	std::cout << "Welcome to the car renter program, Version: 1.0" << std::endl;

	//Importing the data from the files and insert them in their corresponding vectors
	for (int i = 0; i < driversData.getObjectNumber(); i++) {

		//Do not import deleted data and delete incorrect data like incorrect national id or age
		if (driversData.read(i, 0) == "DELETED") continue;
		if (std::stoi(driversData.read(i, 3)) < 18) {
			driversData.deletePatch(i);
			std::cout << "One of the renters was too young, deleted from database" << std::endl;
			continue;
		}
		else if (driversData.read(i, 0).length() != 14) {
			driversData.deletePatch(i);
			std::cout << "Invalid Data found on database, deleted" << std::endl;
			continue;
		}
		else if (driversData.read(i, 4).length() != 10) {
			driversData.deletePatch(i);
			std::cout << "Invalid Data found on database, deleted" << std::endl;
			continue;
		}

		//Create the renter object and push it data to the vector
		Renter newRenter(std::stoll(driversData.read(i, 0)), driversData.read(i, 1), driversData.read(i, 2), std::stoi(driversData.read(i, 3)), std::stoll (driversData.read(i, 4)));
		renters.push_back(newRenter);
	}

	//The same thing happens for the cars file
	for (int i = 0; i < carsData.getObjectNumber(); i++) {
		if (carsData.read(i, 0) == "DELETED") continue;
		CarsData newCar(carsData.read(i, 0), carsData.read(i, 1), carsData.read(i, 2), carsData.read(i, 3));
		cars.push_back(newCar);
	}

	//The main program loop
	while (running) {
		std::cout << "Please enter your command, for help type '?' (Commands are case sensitive)" << std::endl;
		std::getline(std::cin, command);

		//Check the command every loop
		if (command == "rent") {

			//Rent the car by plate number
			std::cout << "Please select on of the following cars by plate number: " << std::endl;

			//Search for the car
			int index = 0;
			for (int i = 0; i < cars.size(); i++) {
				if (cars[i].get_renter() == "not rented") {
					index++;
					std::cout << index << ". model: " << cars[i].get_car_model() << setw(15 + (20 - cars[i].get_car_model().length())) << ", plate number: " << cars[i].get_license_plates_number() << setw(10 + (20 - cars[i].get_license_plates_number().length())) << " , owner name : " << cars[i].get_owner() << std::endl;
				}
			}

			if (index != 0) {
				std::string plate;
				std::getline(std::cin, plate);

				std::cout << "Please enter your National ID: " << std::endl;
				std::string id;
				std::getline(std::cin, id);

				if (rent(plate, std::stoll(id), cars, renters, driversData, carsData)) std::cout << "rented succesfully" << std::endl;
			}

			//If there is no cars available it will tell the user
			else std::cout << "No cars available, please check later" << std::endl;

		}

		//used to shoe rented cars
		else if (command == "rented cars") {
			std::cout << "the rented cars are :" << endl;
			int index = 0;
			for (int i = 0; i < cars.size(); i++) {
				if (cars[i].get_renter() != "not rented") {
					index++;
					std::cout << index << ". model: " << cars[i].get_car_model() << std::setw(10 + (20 - cars[i].get_car_model().length())) << " , Owner: " << cars[i].get_owner() << std::setw(10 + (35 - cars[i].get_owner().length())) << " , plate number: " << cars[i].get_license_plates_number() << std::endl; 
				}
			}

			if (index == 0) std::cout << "There are no any rented cars" << std::endl;
		}
		//Used to hire a new car
		else if (command == "hire a car") {
			hire(carsData, cars);
		}

		//Create a new renter profile
		else if (command == "new renter") {
			hireRenter(driversData, renters);
		}

		//List all the available commands
		else if (command == "?") {
			std::cout << "The commands are: " << std::endl;
			std::cout << "1. rented cars: to show currently rented cars " << std::endl;
			std::cout << "2. rent: to rent  car" << std::endl;
			std::cout << "3. new renter: to create a new renter profile, automatically created if you are going to rent " << std::endl;
			std::cout << "4. hire a car: to create a new car profile, so yo can gain profit with your car " << std::endl;
			std::cout << "5. delete user: to delete your account from our database" << std::endl;
			std::cout << "6. end car contract: to remove your car form our database and end the contract" << std::endl;
			std::cout << "7. exit: to close the program " << std::endl;
		}

		//Delete a car and the contract and remove it form the database
		else if (command == "end car contract") {
			std::cout << "Please enter your car's plate number: " << std::endl;
			std::string platenum;
			std::getline(std::cin, platenum);

			int carIndex = -1;
			for (int i = 0; i < cars.size(); i++) {
				if (cars[i].get_license_plates_number() == platenum)
					carIndex = i;
			}

			if (carIndex != -1) {
				cars.erase(cars.begin() + carIndex);
				carsData.deletePatch(carsData.getIndex(platenum));
				std::cout << "Car contract ended" << std::endl;
			}
			else {
				std::cout << "Car is not available on our database, please check your plate number again" << std::endl;
			}

		}

		//Delete a user profile
		else if (command == "delete user") {
			std::cout << "Please enter your National ID: " << std::endl;
			std::string NationalID;
			std::getline(std::cin, NationalID);

			while (NationalID.length() < 14) {
				std::cout << "Incorrect national ID, please try again" << std::endl;
				std::getline(std::cin, NationalID);
			}

			int userIndex = -1;
			for (int i = 0; i < renters.size(); i++) {
				if (renters[i].get_National_ID() == std::stoll(NationalID))
					userIndex = i;
			}

			if (userIndex != -1) {
				renters.erase(renters.begin() + userIndex);
				driversData.deletePatch(driversData.getIndex(NationalID));
				std::cout << "User deleted" << std::endl;
			}
			else {
				std::cout << "Your national ID was not found on our database" << std::endl;
			}
		}

		//Used to exit the program
		else if (command == "exit")
			running = false;
		else std::cout << "Unknown command" << std::endl;
	}

}
