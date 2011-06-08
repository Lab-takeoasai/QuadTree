#include "location.hpp"
#include "ladybug.hpp"
#include "stdlib.h"

//	from http://d.hatena.ne.jp/sun-rise/20091010/1255136275
std::vector<std::string> split(std::string str, std::string delim) {
  std::vector<std::string> items;
  std::size_t dlm_idx;
  if(str.npos == (dlm_idx = str.find_first_of(delim))) {
    items.push_back(str.substr(0, dlm_idx));
  }
  while(str.npos != (dlm_idx = str.find_first_of(delim))) {
    if(str.npos == str.find_first_not_of(delim)) {
      break;
    }
    items.push_back(str.substr(0, dlm_idx));
    dlm_idx++;
    str = str.erase(0, dlm_idx);
    if(str.npos == str.find_first_of(delim) && "" != str) {
      items.push_back(str);
      break;
    }
  }
  return items;
}

void Location::dump() {
	if (this->isError) {
		printf("[ERROR]\n");
	} else {
		printf("[%d] seqid: %d, cycle: (%d, %d), size: %d gamma %f, gain %d, shutter %d, lat %f, lon %f, alt %f, time: %s\n", this->frame, this->seqid, this->cycleX, this->cycleY, this->size, this->gamma, this->gain, this->shutter, this->y, this->x, this->alt, this->time->c_str());
	}
}

Location::Location(double x, double y) {
    this->x = x;
    this->y = y;
}

Location::Location(LadyBug *ladybug, std::string line) {
	this->ladybug = ladybug;
	
	std::vector<std::string> hashes = split(line, ", ");
	if ( hashes[1] == "Dropped" ) {
		this->isError = true;
	} else {
		this->isError = false;
		this->frame = atoi(hashes[0].c_str());
		this->seqid = atoi(hashes[3].c_str());
		this->cycleX = atoi(hashes[6].c_str());
		this->cycleY = atoi(hashes[7].c_str());
		this->size = atoi(hashes[10].c_str());
		this->gamma = atof(hashes[13].c_str());
		this->gain = atoi(hashes[16].c_str());
		this->shutter = atoi(hashes[19].c_str());
		this->y = atof(hashes[22].c_str());
		this->x = atof(hashes[25].c_str());
		this->alt = atof(hashes[28].c_str());
		this->time = new std::string(hashes[31]);
	}
        //this->dump();
}

Location::~Location() {
	if ( !this->isError )
		delete this->time;
}
