#include <vector>
#include "region.hpp"

//	class T must implement. public x, y: double
template <class T> class QuadTree {

//	Functions
public:
	//	Initialize & deconstructer
        QuadTree(Region region);
        QuadTree(Region region, int depth);
	~QuadTree();

	//	actions
	void add(T *object);			//	add object
	//	void remove(T *object);		//	not implemented
	std::vector<T *> getObjects();	//	get objects recursively
	std::vector< QuadTree<T>* > findRegion(Region region);	//	find trees in region
	bool isLeaf();
	bool isEqualRegionTo(T *object);
	void dump();
private:
	
//	Variables
private:
        QuadTree *trees[4];
	std::vector<T *> *objects;
	Region *region;
	double x;
	double y;
	int depth;
};
