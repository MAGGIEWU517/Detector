/**
 * @file convexthull.cpp
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

using namespace std;

/** uses a sorting algorithm of your choice (must be fully implemented by you)
  * to sort the points in v to satisfy the following criteria:
  * 1. v[0] must contain the point with the smallest y-coordinate.
  *      If multiple points have the same smallest y-coordinate, v[0]
  *      must contain the one among those with the smallest x-coordinate.
  * 2. The remaining indices i contain the points, sorted in increasing order
  *      by the angle that the point forms with v[0] and the x-axis. THat is,
  * 	one of the legs of the angle is represened by the line through v[0] and
  *	v[i], and the other is the x-axis.
  **/
void sortByAngle(vector<Point>& v){
	//check if v is a null vector
	if(v.empty()){
		return;
	}
	//step1:find the leftmost point with smallest y-coordinator.
	SMLYswitch(v);
 

	//step2:sort vector v in increasing order by the angle
	
	for(unsigned i = 2; i < v.size(); i++){
		Point temp = v[i];

		double ang = angleOfTwoPoints(v[0],v[i]);
		int pos = i;
    //shuffle all sorted points with angle > ang
    while(pos > 1 && angleOfTwoPoints(v[0],v[pos-1]) > ang){
      v[pos] = v[pos-1];
      pos--;
    }
		v[pos] = temp;
	}


}

/**determines whether a path from p1 to p2 to p3 describes a counterclockwise turn
  *return true if polar angle from p1 to p3 is bigger than polar angle from p1 to p2. 
  **/ 	
bool ccw(Point p1, Point p2, Point p3){
  double check = (p2.x - p1.x)*(p3.y - p1.y) - (p2.y - p1.y)*(p3.x - p1.x);

  return check > 0;
}

/** returns a vector of points representing the convex hull of v
  * if c is the vector representing the convex hull, then c[k], c[k+1]
  * is an edge in the convex hull, for all k in 0 to n-1, where n is the
  * number of points in the hull. c[n-1],c[0] is also an edge in the hull.
  * The returned vector should be a subset of v
  *Input: v - a vector of points in arbitrary order
  **/
vector<Point> getConvexHull(vector<Point>& v){
	Stack convexhull;
   //order vector v
  
	//check v is not empty 
  //if size of v is smaller than 3, we will have a point(size=1) or line segment(size=2) or a plane(size=3)
  //impossible for clockwise rotation occurring, just return v
	if(v.empty()|| v.size() <= 3){
		return v;
	}

 sortByAngle(v);
    //else, insert convex hull points into convexhull
    // first, insert v[0], v[1] and v[2] which must be convexhull
    convexhull.push(v[0]);
    convexhull.push(v[1]);

    
   
   
    //if ccw from v[i], v[i+1], v[i+2], insert them into convexhull
    //else insert v[i], v[i+2]into convexhull where i start at 1
    for(unsigned i= 2; i < v.size();i++){
      while(!ccw(Second(convexhull), convexhull.peek(),v[i])){
      convexhull.pop();
      }
      convexhull.push(v[i]);
      }

    if(ccw(Second(convexhull), convexhull.peek(),v[0])== false){
      convexhull.pop();
      }

    
    Stack cp;
    while(convexhull.isEmpty() == false){
      cp.push(convexhull.pop());
    }
    vector<Point> convex;
    while(cp.isEmpty() == false){
      convex.push_back(cp.pop());
    }

    return convex;

}


//=========================================
// Helper functions


/**   Given a vector v, find the smallest point with smallest y coordinate
  *      If multiple points have the same smallest y-coordinate, 
  *      return the point
  *      with the smallest x-coordinate.
  *      searching thought v, find the smllst point and switch poisition with v[0];
  *      if vector v is empty, nothing happens.
  **/
void SMLYswitch(vector<Point>& v){
	if(v.empty()){
		return;
	}

	Point smllst;

	smllst = v[0];
	double smlly = v[0].y;
    int min = 0;
	for(unsigned i = 1; i < v.size(); i++){
		if((v[i].y) < smlly || (v[i].y == smlly && v[i].x < v[min].x)){
			smlly = v[i].y;
			min = i;
		}
	}
   //find the smllst point and switch poisition with v[0];
    smllst = v[min];
    Point temp = v[0];
	  v[0] = smllst;
	  v[min] = temp;
  

}
/**
  * return the angle between two points
  **/
double angleOfTwoPoints(Point p1, Point p2){
  double pi = 3.1415926;

  if(p1.y > p2.y){
    double cosrate = ((p1.x) - (p2.x))/sqrt(pow(((p1.y) - (p2.y)),2)+pow(((p1.x) - (p2.x)),2));
    return acos(cosrate)+ pi;
  }else if(p1.y < p2.y){
    double cosrate = ((p2.x) - (p1.x))/sqrt(pow(((p1.y) - (p2.y)),2)+pow(((p1.x) - (p2.x)),2));
	  return acos(cosrate);
    }else{
      return 0;
    }
}
Point Second(Stack S){
  Point top = S.peek();
  S.pop();
  Point second = S.peek();
  S.push(top);
  return second;
}
