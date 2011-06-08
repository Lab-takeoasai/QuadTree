#include "quadtree.hpp"


#include "stdio.h"
#include "math.h"

#include "region.hpp"
#include "location.hpp"



template <class T> QuadTree<T>::QuadTree(Region region, int depth) {
    this->x = 0.0;
	this->y = 0.0;
    this->region = new Region(region);
	this->trees[0] = NULL;
	this->trees[1] = NULL;
	this->trees[2] = NULL;
	this->trees[3] = NULL;
	this->objects = new std::vector<T *>();
	this->depth = depth;
}

template <class T> QuadTree<T>::~QuadTree() {
	delete this->region;
	delete this->objects;
}

template <class T> void QuadTree<T>::dump() {
	printf("<%p> %d: p = (%f, %f), %s, size = %d, region ", this, this->depth, this->x, this->y, (this->isLeaf() ? "leaf" : "edge"), (int)this->objects->size());
	this->region->dump();
	for ( int i = 0; i < 4; i++ ) {
		QuadTree *tree = this->trees[i];
		if ( tree != NULL )
			tree->dump();
	}
}

template <class T> std::vector<T *> QuadTree<T>::getObjects() {
	
	//	if leaf, return this.objects
	if ( this->isLeaf() ) {
		return std::vector<T *>(*this->objects);
	}
	
	//	if not leaf, gather objects of the subtrees
	std::vector<T *> objects = std::vector<T *>();
	for ( int i = 0; i < 4; i++ ) {
		if ( this->trees[i] != NULL ) {
			std::vector<T *> ret = this->trees[i]->getObjects();
			for ( unsigned int j = 0; j < ret.size(); j++ ) {
				objects.push_back(ret[j]);
			}
		}
	}
	return objects;
}

template <class T> bool QuadTree<T>::isEqualRegionTo(T *object) {
    static const double M = 180.0 / (M_PI * 6378150.0); //  1m
    return fabs(this->x - object->x) <= M && fabs(this->y - object->y) <= M;
}

template <class T> T *QuadTree<T>::findFirstObjectInRegion(Region region) {
    if ( this->isLeaf() ) {
        if ( region.contain(this->x, this->y) ) {
            return this->objects->at(0);
        }
    } else {
        for ( int i = 0; i < 4; i++ ) {
			//	null check & graph cut
			if ( this->trees[i] != NULL && (this->trees[i]->region->include(region) || region.include(*this->trees[i]->region)) ) {
				return this->trees[i]->findFirstObjectInRegion(region);
			}
		}
    }
    return NULL;
}

template <class T> std::vector< QuadTree<T>* > QuadTree<T>::findRegion(Region region) {
    
	std::vector< QuadTree<T>* > trees = std::vector< QuadTree<T>* >();
	
	//	region is bigger than this.region
	if ( region.contain(*this->region) ) {	
		trees.push_back(this);
		return trees;
        
        //	if leaf, check region contains (this.x, y)
	} else if ( this->isLeaf() ) {
		if ( region.contain(this->x, this->y) ) {
			trees.push_back(this);
		}
		return trees;
		
        //	if not leaf, gather trees that region contains
	} else {
		for ( int i = 0; i < 4; i++ ) {
			//	null check & graph cut
			if ( this->trees[i] != NULL && (this->trees[i]->region->include(region) || region.include(*this->trees[i]->region)) ) {
				std::vector< QuadTree<T>* > ret = this->trees[i]->findRegion(region);
				for ( unsigned int j = 0; j < ret.size(); j++ ) {
					trees.push_back(ret[j]);
				}
			}
		}
	}
	
	return trees;
}

template <class T> bool QuadTree<T>::hasObjects() {
    return ( this->objects->size() == 1 && this->isLeaf() ) || !this->isLeaf();
}

template <class T> void QuadTree<T>::add(T *object) {
	if ( this->isLeaf() ) {
		if ( !this->hasObjects() ) {	//	first time
			this->x = object->x;
			this->y = object->y;
			this->objects->push_back(object);
		} else {	//	
			if ( this->isEqualRegionTo(object) ) {
				this->objects->push_back(object);
			} else {
				//	partition region & put objects into the splited regions
                
				Region parts[4];
				parts[0] = this->region->partition(kNWPartition, this->region->x, this->region->y);
				parts[1] = this->region->partition(kNEPartition, this->region->x, this->region->y);
				parts[2] = this->region->partition(kSWPartition, this->region->x, this->region->y);
				parts[3] = this->region->partition(kSEPartition, this->region->x, this->region->y);
				this->objects->push_back(object);
				for ( unsigned int i = 0; i < this->objects->size(); i++ ) {
					T *obj = (*this->objects)[i];
					for ( int i = 0; i < 4; i++ ) {
						if ( parts[i].contain(obj->x, obj->y) ) {
							if ( this->trees[i] == NULL ) {
								this->trees[i] = new QuadTree(parts[i], this->depth+1);
							}
							this->trees[i]->add(obj);
							break;
						}
					}
				}
				this->objects->clear();
			}
		}
        
        //	is not Leaf
	} else {
		Region parts[4];
		parts[0] = this->region->partition(kNWPartition, this->region->x, this->region->y);
		parts[1] = this->region->partition(kNEPartition, this->region->x, this->region->y);
		parts[2] = this->region->partition(kSWPartition, this->region->x, this->region->y);
		parts[3] = this->region->partition(kSEPartition, this->region->x, this->region->y);
		for ( int i = 0; i < 4; i++ ) {
			if ( parts[i].contain(object->x, object->y) ) {
                if ( this->trees[i] == NULL ) {
                    this->trees[i] = new QuadTree(parts[i], this->depth+1);
                }
				this->trees[i]->add(object);
				break;
			}
		}
	}
}

template <class T> bool QuadTree<T>::isLeaf() {
    return (this->trees[0] == NULL) && (this->trees[1] == NULL) && (this->trees[2] == NULL) && (this->trees[3] == NULL);
}


template class QuadTree<Location>;



