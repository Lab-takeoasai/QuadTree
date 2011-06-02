//. exif.java
//. K.Kimura(Programmer K) @ IBM Software Group, Japan.
//	Exif.hpp
//	Complied into c++ by Takeo Asai, Ikeuchi Lab

#include <string>
#include <sstream>
#include <fstream>

class ExifJPEG {
public:
	ExifJPEG(std::string filename);
	double getLatitude();	//	lazy evaluation
	double getLongitude();	
        double getX();
        double getY();
private:
	void calculate();
private:
	std::string filename;
	bool isCalculated;
	double latitude;
	double longitude;
};

template <class T> std::string toString(T n) { 
	std::ostringstream ss;
	ss << n;
	return ss.str();
}

template <class T> double toDouble(T n) { 
	std::istringstream ss;
	double f;
	ss.str(toString(n));
	ss >> f;
	return f;
}
