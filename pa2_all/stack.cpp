/**
 * @file stack.cpp
 * Implementation of stack class , PA2
 */

#include <iostream>
#include <cmath>
#include <cstdlib>
#include <vector>

#include "cs221util/PNG.h"
#include "cs221util/HSLAPixel.h"
#include "point.h"
#include "stack.h"

using namespace std;


    /**
      * returns true if the stack is empty, false otherwise
      **/
    bool Stack::isEmpty(){
    	return st.empty();
    }

    /** returns the top element of the stack
      * returns a default (0,0) point if stack is empty
      **/
    Point Stack::peek(){
    	Point deftpt = Point(0,0);

    	if(isEmpty()){
    		return deftpt;
    	}else{
    		return st.back();
    	}
    }
    /** 
      * returns number of elements in the stack
    **/
    int Stack::size(){
    	return st.size();
    }


    /** mutators
      * adds an item to the top of the stack
      **/
    void Stack::push(Point p){
    	st.push_back(p);
    }

    /** removes and returns the top element of the stack
      * returns a default (0,0) point if stack is empty
      **/
    Point Stack::pop(){
    	Point deftpt = Point(0,0);
    	Point top;
    	if(isEmpty()){
    		return deftpt;
    	}else{
    		top = st.back();
    		st.pop_back();
            return top;
    	}

    }
