/*
 *  glutils.h
 *  emptyExample
 *
 *  Created by satoshi okami on 12/01/13.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef __UTILS__
#define __UTILS__

#include "ofVec3f.h"


class utils {
	
	//--------------------------------------------------------------
	public: static ofVec3f getRandVec()
	{
		ofVec3f vec;
		
		float a1 = (float)(ofRandom(0, 360) * PI / 180);
		float a2 = (float)(ofRandomuf() * 2 * PI);
		
		vec.x = (float)(sin(a1) * cos(a2));
		vec.y = (float)(sin(a1) * sin(a2));
		vec.z = (float)(cos(a1));
		
		return vec;
	}
};



#endif __UTILS__