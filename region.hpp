#ifndef REGION_H
#define REGION_H

enum partition {
	kNWPartition = 0,
	kNEPartition = 1,
	kSWPartition = 2,
	kSEPartition = 3,
};

class Region {

//	Functions
public:
	//	Initialization & deconstructer
	Region();
	Region(double x, double y, double w, double h);
	Region(const Region &region);
	~Region();
	
	//	actions
	Region partition(enum partition p, double x, double y);	//	partition this into 4 parts. separation center is (x,y)
	bool contain(Region region);		//	return (this contains region)
	bool contain(double x, double y);	//	special version: region.width & height = 0
	bool include(Region region);		//	contain parts of the region
	bool isValid();						//	validate region (whether size is - or not)
	void dump();						//	print variables
	double getMinX();
	double getMaxX();
	double getMinY();
	double getMaxY();
	
//	Variables
public:
	double x;		//	center.x
	double y;		//	center.y
	double width;	//	rectangular.width
	double height;	//	rectangular.height

};	

#endif REGION_H
