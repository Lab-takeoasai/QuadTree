#include <vector>
#include <string>

class Location;
class LadyBug {
public:
	LadyBug(std::string pgrFile, std::string gpsFile);
	~LadyBug();
        std::vector<Location *> getLocations();
private:
	std::string *pgrFile;
	std::vector<Location *> *locations;
};
