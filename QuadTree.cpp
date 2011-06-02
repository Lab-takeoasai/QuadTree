#include "QuadTree.hpp"

Region Region::partition(enum partition p) {
	double d = (r / 2.0);
	double x = 0.0, y = 0.0;
	switch (p) {
		case kNWPartition:
		x = (this->x)+d;	y = (this->y)+d;
		break;
		case kNEPartition:
		x = (this->x)-d;	y = (this->y)+d;
		break;
		case kSWPartition:
		x = (this->x)+d;	y = (this->y)-d;
		break;
		case kSEPartition:
		x = (this->x)-d;	y = (this->y)-d;
		break;
	}
	return Region(x, y, d);
}

bool Region::contain(double x, double y) {
	double d = this->r;
	return (x >= this->x-d) && (x < this->x+d) && (y >= this->y-d) && (y < this->y+d);
}

bool Region::contain(Region reg) {
	double d = this->r;
	return (reg.x >= this->x-d) && (reg.x < this->x+d) && (reg.y >= this->y-d) && (reg.y < this->y+d);
}

template <class T> enum partition QuadTree<T>::getRegion(T *object) {
	Region *reg = this->region;
	double x = object->getX(), y = object->getY();
	
	if ( reg->partition(kNWPartition).contain(x, y) )
		return kNWPartition;
	if ( reg->partition(kNEPartition).contain(x, y) )
		return kNEPartition;
	if ( reg->partition(kSWPartition).contain(x, y) )
		return kSWPartition;
	return kSEPartition;
}

//	g++ -O3, i3 3.2GH 4GB, 1000000times => 4.16sec, 10000000times => x
template <class T> void QuadTree<T>::insert(T *object) {
	if ( this->isLeaf ) {
		//	this->objects[i].getX() & getY() are same.
		if ( this->objects[0]->getX() == object->getX() && object->getY() == this->objects[0]->getY() ) {	//	same (x,y) pair
			this->objects.push_back(object);
		} else {
			for ( unsigned int i = 0; i < this->objects.size(); i++ ) {
				enum partition p = this->getRegion(this->objects[i]);
				if ( this->trees[p] == NULL ) {
					this->trees[p] = new QuadTree<T>(this->objects[i], this->region->partition(p));	//	this called first time of this loop
				} else {
					this->trees[p]->insert(this->objects[i]);
				}
			}
			this->objects.clear();
			this->isLeaf = false;
		}
	}
	
	enum partition p = this->getRegion(object);
	if ( this->trees[p] == NULL ) {
		this->trees[p] = new QuadTree<T>(object, this->region->partition(p));
	} else {
		this->trees[p]->insert(object);
	}
}

//	g++ -O3, i3 3.2GH 4GB, 1000000times => 6.72sec(including insert 4.16sec)
template <class T> std::vector< QuadTree<T>* > QuadTree<T>::searchRegion(Region reg) {
	//	this->objects[i].getX() & getY() are same.
	if ( this->isLeaf && reg.contain(this->objects[0]->getX(), this->objects[0]->getY()) ) {
		std::vector< QuadTree<T>* > trees;
		trees.push_back(this);
		return trees;
	}
	
	std::vector< QuadTree<T>* > trees;
	
	if ( this->trees[kNWPartition] != NULL ) {
		std::vector< QuadTree<T>* > nws = this->trees[kNWPartition]->searchRegion(reg);
		for ( unsigned int i = 0; i < nws.size(); i++ ) {
			trees.push_back(nws[i]);
		}
	}
	if ( this->trees[kNEPartition] != NULL ) {
		std::vector< QuadTree<T>* > nes = this->trees[kNEPartition]->searchRegion(reg);
		for ( unsigned int i = 0; i < nes.size(); i++ ) {
			trees.push_back(nes[i]);
		}
	}
	if ( this->trees[kSWPartition] != NULL ) {
		std::vector< QuadTree<T>* > sws = this->trees[kSWPartition]->searchRegion(reg);
		for ( unsigned int i = 0; i < sws.size(); i++ ) {
			trees.push_back(sws[i]);
		}
	}
	if ( this->trees[kSEPartition] != NULL ) {
		std::vector< QuadTree<T>* > ses = this->trees[kSEPartition]->searchRegion(reg);
		for ( unsigned int i = 0; i < ses.size(); i++ ) {
			trees.push_back(ses[i]);
		}
	}
	return trees;
}






/*

class Point {
public:
	Point(const Point &p) {
		this->x = p.x;	this->y = p.y;
	}
	Point(double x, double y) {
		this->x = x;	this->y = y;
	}
	Point() {
		
	}
	double getX() {
		return x;
	}
	double getY() {
		return y;
	}
	double x;
	double y;
};
int main (int argc, char const *argv[])
{
	Point *p = new Point(50,50);
	Region searchReg = Region(50,50,5.1);
	QuadTree<Point> *tree = new QuadTree<Point>(p, Region(50,50,50000000));
	
	for ( int i = 0; i < 1000000; i++ ) {
		double x = (double)(rand()) / rand();
		double y = (double)(rand()) / rand();
		Point *p = new Point(x+45, y+45);
//		printf("insert (%f, %f)\n", p->x, p->y);
		tree->insert(p);
	}
	
	std::vector< QuadTree<Point>* > results = tree->searchRegion(searchReg);
	for ( unsigned int i = 0; i < results.size(); i++ ) {
	//	printf("[%d] x: %f, y: %f\n", results[i]->objects.size(),results[i]->objects[0]->x, results[i]->objects[0]->y);
	}
	printf("size() %d\n", (int)results.size());
	
	return 0;
}
*/