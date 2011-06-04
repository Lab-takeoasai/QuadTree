#include <string>

class LadyBug;
class Location {
public:
	Location(LadyBug *ladybug, std::string line);
	~Location();
	void dump();
	
public:
	double x;
	double y;
	
	int frame;
	int seqid;
	int cycleX;
	int cycleY;
	int size;
	double gamma;
	int gain;
	int shutter;
	double alt;
	std::string *time;
	
	
	LadyBug *ladybug;
private:
	bool isError;
};
