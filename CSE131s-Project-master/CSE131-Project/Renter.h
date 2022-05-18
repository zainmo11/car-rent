#pragma once
#include<string>
using namespace std;
class Renter
{
public:
	Renter(long long id, string name, string gender, int age, long long licence_number);
	void set_National_ID(int id);
	void set_Name(string name);
	void set_Age(int age);
	void set_Gender(string gender);
	void set_License_Number(int number);
	long long get_National_ID();
	int get_Age();
	long long get_License_Number();
	string get_Name();
	string get_Gender();
private:
	long long National_ID;
	string Name;
	int Age;
	string Gender;
	long long License_Number;
	
};

