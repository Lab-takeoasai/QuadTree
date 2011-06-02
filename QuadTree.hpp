#include "stdio.h"
#include <vector>

//	TODO: speedup

enum partition {
	kNWPartition = 0,
	kNEPartition = 1,
	kSWPartition = 2,
	kSEPartition = 3,
};

class Region {
public:
	Region(double x, double y, double r) {
		this->x = x; this->y = y; this->r = r;
	}
	Region(const Region &reg) {
		this->x = reg.x; this->y = reg.y; this->r = reg.r;
	}
	bool contain(double x, double y);
	bool contain(Region reg);
	Region partition(enum partition p);
	~Region() {
	};
private:
	double x;
	double y;
	double r;
};

template <class T> class QuadTree {
public:
	QuadTree(T *object, Region reg) {
		this->isLeaf = true;
		std::vector<T *> objects;
		objects.push_back(object);
		this->objects = objects;
		this->region = new Region(reg);
		this->trees[0] = this->trees[1] = this->trees[2] = this->trees[3] = NULL;
	}
	void insert(T *object);
	std::vector<QuadTree *> searchRegion(Region reg);
	~QuadTree() {
		delete this->region;
	}
public:
	std::vector<T *> objects;
private:
	enum partition getRegion(T *object);
private:
	bool isLeaf;
	Region *region;
	QuadTree *trees[4];
};
