#include "region.hpp"
#include "stdio.h"

bool Region::contain(double x, double y) {
	return	(this->getMinX() <= x) &&
			(x <= this->getMaxX()) &&
			(this->getMinY() <= y) &&
			(y <= this->getMaxY());
}

bool Region::contain(Region region) {
	return	this->contain(region.getMinX(), region.getMinY()) &&
			this->contain(region.getMaxX(), region.getMaxY());
}

bool Region::isValid() {
	return this->width >= 0 && this->height >= 0;
}

bool Region::include(Region region) {
	return	this->contain(region.getMinX(), region.getMinY()) ||
			this->contain(region.getMinX(), region.getMaxY()) ||
			this->contain(region.getMaxX(), region.getMinY()) ||
			this->contain(region.getMaxX(), region.getMaxY());
}

void Region::dump() {
	printf("center(%f, %f), size(%f, %f)\n", this->x, this->y, this->width, this->height);
}

Region Region::partition(enum partition p, double x, double y) {
	double centerX, centerY, width, height;
	double w = (this->width / 2.0);
	double h = (this->height / 2.0);
	double dx = x - this->x;
	double dy = y - this->y;
	
	if ( this->contain(x, y) ) {
		switch (p) {
			case kNEPartition:
			width = w - dx;
			height = h - dy;
			centerX = x + (width / 2.0);
			centerY = y + (height / 2.0);
			break;
			case kNWPartition:
			width = w + dx;
			height = h + dy;
			centerX = x - (width / 2.0);
			centerY = y + (height / 2.0);
			break;
			case kSEPartition:
			width = w - dx;
			height = h + dy;
			centerX = x + (width / 2.0);
			centerY = y - (height / 2.0);
			break;
			case kSWPartition:
			width = w + dx;
			height = h + dy;
			centerX = x - (width / 2.0);
			centerY = y - (height / 2.0);
			break;
		}
	} else {
		return Region(0,0,-1,-1);
	}
	
	return Region(centerX, centerY, width, height);
}

double Region::getMinX() {
	return this->x - (this->width / 2.0);
}

double Region::getMaxX() {
	return this->x + (this->width / 2.0);
}

double Region::getMinY() {
	return this->y - (this->height / 2.0);
}

double Region::getMaxY() {
	return this->y + (this->height / 2.0);
}

//	Initialize & deconstruct
Region::Region() {
	
}

Region::Region(double x, double y, double width, double height) {
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;
}

Region::Region(const Region &region) {
	this->x = region.x;
	this->y = region.y;
	this->width = region.width;
	this->height = region.height;
}

Region::~Region() {
	
}

/*
int main (int argc, char const *argv[])
{
	Region reg = Region(0,0,2,2);
	for (int i = 0; i < 4; i++) {
		reg.partition((enum partition)i, 1.5, 0).dump();
	}
	reg.dump();
	
	return 0;
}
*/