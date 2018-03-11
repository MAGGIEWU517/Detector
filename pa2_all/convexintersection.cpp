/**
 * @file convextintersection.cpp
 * Implementation of convexhull class using Graham scan algorithm, PA2
 */

#include <iostream>
#include <cmath>
#include <cstdlib>
#include <vector>

#include "cs221util/PNG.h"
#include "cs221util/HSLAPixel.h"
#include "point.h"
#include "stack.h"
#include "convexhull.h"
#include "convexintersection.h"

using namespace std;

/** determines whether a point p1 is inside or outside
  * of a line segment defined by sp1 and sp2
  * sp1 and sp2 should be consistently provided
  * from the convex hull algorithm such that the edges
  * are listed in a CCW direction
  * p1 belongs to the subject polygon
  * sp1 and sp2 belong to the clipping polygon
  **/
bool inside(Point p1, Point sp1, Point sp2){
	//connect p1 sp1 and sp2
	// we find that if p1 is inside sp1 and sp2, we will have ccw from p1 to sp1 to sp2
	// if p1 not inside, we will have "turn right" from p1 to sp1 to sp2
	return ccw(sp1, sp2, p1);	
}

/** computes the point of intersection between the line segment
  * defined by s1 and s2, and the infinite line defined by
  * i1 and i2.
  * Assume that this will only be called when the intersection exists.
  **/
Point computeIntersection(Point s1, Point s2, Point i1, Point i2){
  double x1 = s1.x;
  double x2 = s2.x;
  double x3 = i1.x;
  double x4 = i2.x;

  double y1 = s1.y;
  double y2 = s2.y;
  double y3 = i1.y;
  double y4 = i2.y;

  double numx = (x1*y2 - y1*x2) * (x3-x4) -(x1-x2) * (x3*y4 - y3*x4);
  double denx = (x1-x2) * (y3-y4) - (y1-y2) * (x3-x4);
  double x = numx/denx;

  double numy = (x1*y2 - y1*x2) * (y3-y4) -(y1-y2) * (x3*y4 - y3*x4);
  double deny = (x1-x2) * (y3-y4) - (y1-y2) * (x3-x4);
  double y = numy/deny;

  return Point(x,y);
}


/** returns a vector containing a sequence of points defining
  * the intersection of two convex polygons poly1 and poly2
  * Inputs: poly1 and poly2 - sequences of points defining the
  *                           borders of convex polygons
  **/
vector<Point> getConvexIntersection(vector<Point>& poly1, vector<Point>& poly2){
  vector<Point> intersection;
  if(poly1.empty()|| poly2.empty()){
    return intersection;
  }
  if(poly1.size()<3|| poly2.size()<3){
    return intersection;
    cout<<"Poly size < 3, so no intersection area exists"<<endl;
  }
  
 
  Point cp1 = poly1[poly1.size()-1];
  vector<Point> input;

  intersection = poly2;
  for(unsigned i = 0; i < poly1.size(); i++) {
    Point cp2 = poly1[i];
    input = intersection;
    intersection.clear();

    Point s = input[input.size()- 1]; //last on the input vector
     
    for (unsigned j=0;j<input.size(); j++) {
      Point e = input[j];
     
      if(inside(e, cp1, cp2)){
        intersection.push_back(e);
        if(!inside(s,cp1,cp2)){
          intersection.push_back(computeIntersection(e,s,cp1,cp2));
        }else{
          intersection.push_back(s); 
        }
      }else if(inside(s, cp1, cp2)){
        intersection.push_back(s);
        intersection.push_back(computeIntersection(e,s,cp1,cp2)); 
    } 
     s = e;
    }
  cp1 = cp2;
  sortByAngle(intersection);
}
  return intersection;
}
 

// You may add some of your own useful functions here,
// BUT DO NOT MODIFY ANY OF THE FUNCTIONS ABOVE
