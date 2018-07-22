/*
 *  Planet.h
 *  emptyExample
 *
 *  Created by satoshi okami on 12/01/16.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef __PLANET__
#define __PLANET__

#include "Particle.h"
#include <iostream.h>


class Planet : public Agent
{
	public: float radius;
	public: float gravity;
	
	
	public: Planet(int _gen, ofVec3f _position, ofVec3f _velocity) : Agent(_gen)
	{
		position = _position;
		velocity = _velocity;
		
		radius = 200;
		gravity = 10;
		
		age = 0.0f;
		agePer = 1.0f;
		lifeSpan = (float)radius;
		genThreshold = 4;
		splitVelocityThreshold = 10.0f;
	}
	
	public: void update()
	{
		Agent::update();
		
		aging(5);
	}
};


#endif __PLANET__