//
//  main.cpp
//  quadtree_debug
//
//  Created by 浅井 岳大 on 11/06/07.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include <iostream>
#include <vector>
#include <sys/time.h>

#include "quadtree.hpp"
#include "location.hpp"
#include "region.hpp"
#include "ladybug.hpp"

double gettimeofday_sec()
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return tv.tv_sec + (double)tv.tv_usec*1e-6;
}

int main (int argc, const char * argv[])
{
    if (false) {
        double t0, t1, t2, t3;
        
        t0 = gettimeofday_sec();
        
        int width = 200;
        int height = 200;
        int n = 2000000;
        //  n= 2 millionで12secほどaddにかかる( nlogn ) 
        QuadTree<Location> *tree = new QuadTree<Location>(Region(0,0,width,height));
        for ( int i = 0; i < n; i++ ) {
            double x = width * ((double)(rand() % n) - (n/2.0)) / n;
            double y = height * ((double)(rand() % n) - (n/2.0)) / n;
            Location *l = new Location(x,y);
            tree->add(l);
        }
        t1 = gettimeofday_sec();
        
        int count = 0;
        std::vector<QuadTree<Location> *> foundTree = tree->findRegion(Region(70,-30,1,1));
        for ( int i = 0 ; i < foundTree.size(); i++ ) {
            count += foundTree[i]->getObjects().size();
        }
        t2 = gettimeofday_sec();
        
        Location *l = tree->findFirstObjectInRegion(Region(700, 45.23, 1, 0.4));
        t3 = gettimeofday_sec();
        
        printf("get all objects -> %d\n", (int)tree->getObjects().size());
        printf("find region objects - > %d\n", count);
        if ( l != NULL ) {
            printf("find first (%f, %f)\n", l->x, l->y);
        }
        
        printf("%d add time: %g\n", n, t1-t0);
        printf("findRegion time: %g\n", t2-t1);
        printf("findFirst time: %g\n", t3-t2);
    }
    
    
    //  findFirst() test
    if (true) {
        int m = 20;
        int n = 20;
        QuadTree<Location> *tree = new QuadTree<Location>(Region(140,40, m, n));
        LadyBug *ladybug = new LadyBug("", "/Users/asai/Desktop/gps.txt");
        std::vector<Location *> *locs = ladybug->getLocations();
        for ( unsigned int i = 0; i < locs->size(); i++ ) {
            if ( !locs->at(i)->isError ) {
                tree->add(locs->at(i));
            }
        }
        tree->dump();
        
        for ( int i = 0; i < m; i++ ) {
            for ( int j = 0; j < n; j++ ) {
                Region r = Region(140 - m/2 + i, 40 - n/2 + j, 2, 2);
                Location *l = tree->findFirstObjectInRegion(r);
                if ( l != NULL ) {
                    printf("found!");
                    r.dump();
                } else {
                    int count = 0;
                    std::vector<QuadTree<Location> *> foundTree = tree->findRegion(r);
                    for ( int k = 0 ; k < foundTree.size(); k++ ) {
                        count += foundTree[k]->getObjects().size();
                    }
                    printf("not found but %d found by getObjects()\n", count);
                }
                
            }
        }
    }
    
    
    return 0;
}

