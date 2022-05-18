#include "Renter.h"
#include <iostream>

using namespace std;


Renter::Renter(long long id, string name, string gender, int age, long long licence_number) {
	National_ID = id;
	Name = name;
	Age = age;
	Gender = gender;
	License_Number = licence_number;
}

void Renter::set_National_ID (int id){
	if (id <= 10000000000000 && id>=99999999999999) {
		National_ID = id;
	}
	else {
		cout << "please Enter your 14-digit ID number";
		return;
	}
}

void Renter::set_Name(string name) {
	Name = name;
}

void Renter::set_Age(int age) {
	if (age < 21) {
		cout << "You are under the age required to drive a car";
		return;
	}
	Age = age; 

}
void Renter::set_Gender(string gender) {
	if(gender=="Male" || gender == "Female"){
		Gender = gender;
	}
	else {
		cout << "Incorrect type";
		return;
	}
}

void Renter::set_License_Number(int number) {
	License_Number = number;
}

long long Renter::get_National_ID() {
	return National_ID;
}

int Renter::get_Age() {
	return Age;
}

long long Renter::get_License_Number() {
	return License_Number;
}

string Renter::get_Name(){
	return Name;
}

string Renter::get_Gender(){
	return Gender;
}


