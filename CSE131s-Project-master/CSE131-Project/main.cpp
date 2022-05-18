#include <iostream>

#include "FileManager.h"
#include "ProgramLoop.h"

int main() {

	/*
		Welcome to our car renter program
		Happy reading :)

		NOTE: when writing data manually on the files, the national ID must be 14 number or else
		this data will be deleted and every national id must be used once.
		Also, when writing manually, every plate number must be only written once and cannot be used more than once'
		These rules don't apply on Age, name, car model, etc..
		If writing data is done through the program then the program will take care of that.

	*/

	ProgramLoop::run();
}
