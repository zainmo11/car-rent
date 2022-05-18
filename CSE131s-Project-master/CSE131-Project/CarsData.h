#pragma once
#include <string>

using namespace std;

class CarsData
{
public:
	CarsData(string model, string license_plate, string owner, string renter);
	string get_car_model()const;
	string get_owner()const;
	string get_renter()const;
	string get_license_plates_number()const;
	void set_car_model(string model);
	void set_license_plates_number(string number);
	void set_Owner(string owner);
	void set_Renter(string renter);

private:
	string car_model;
	string license_plates_number;
	string Owner;
	string Renter;
};

