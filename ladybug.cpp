#include "ladybug.hpp"
#include "location.hpp"
#include <fstream>
#include <string>

#include "stdio.h"
/*
int main (int argc, char const *argv[])
{
	LadyBug *ladybug = new LadyBug("", "/Users/asai/Desktop/gps.txt");
	
	delete ladybug;
	
	return 0;
}
*/

std::vector<Location *> *LadyBug::getLocations() {
    return this->locations;
}

LadyBug::LadyBug(std::string pgrFile, std::string gpsFile) {
	this->pgrFile = new std::string(pgrFile);
	this->locations = new std::vector<Location *>();
	
	std::string str;
	std::ifstream gpsStream;
	gpsStream.open(gpsFile.c_str(), std::ios::in);
	while ( gpsStream && getline(gpsStream, str) ) {
		this->locations->push_back(new Location(this, str));
	}
}

LadyBug::~LadyBug() {
	for ( unsigned int i = 0; i < this->locations->size(); i++ ) {
		delete this->locations->at(i);
	}
	delete this->pgrFile;
	delete this->locations;
}
