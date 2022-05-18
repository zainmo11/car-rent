#include "CarsData.h"
#include <iostream>

using namespace std;

CarsData::CarsData(string model, string license_plate, string owner, string renter) {
	car_model = model;
	Owner = owner;
	Renter = renter;
	license_plates_number = license_plate;
}

string CarsData::get_car_model() const
{
	return car_model;
}

void CarsData::set_car_model(string model)
{
	car_model=model;
}

string CarsData::get_owner() const
{
	return Owner;
}
string CarsData::get_renter() const
{
	return Renter;
}
string CarsData::get_license_plates_number() const
{
	return license_plates_number;
}
void CarsData::set_license_plates_number(string number)
{
	license_plates_number = number;
}
void CarsData::set_Owner(string owner)
{
	Owner = owner;
}
void CarsData::set_Renter(string renter)
{
	Renter = renter;
}