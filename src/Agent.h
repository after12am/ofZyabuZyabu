/*
 *  Agent.h
 *  emptyExample
 *
 *  Created by satoshi okami on 12/01/15.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef __AGENT__
#define __AGENT__

#include "SteeredVehicle.h"


/*
	behave waiting, splitting and dead
 */
class Agent : public SteeredVehicle
{
	protected: int gen;
	protected: float age;
	protected: float agePer;
	protected: float lifeSpan;
	public: int genThreshold;
	public: float splitVelocityThreshold;
	
	
	
	
	public: Agent(int _gen) : SteeredVehicle()
	{
		gen = _gen;
		age = 0.0f;
		agePer = 1.0f;
		lifeSpan = 10.0f;
		genThreshold = 4;
		splitVelocityThreshold = 10.0f;
	}
	
	public: void update()
	{
		SteeredVehicle::update();
	}
	
	public: void aging(float v)
	{
		age += v;
		
		if (isDead()) agePer = 0.0f;
		else agePer = 1.0 - (float)age / lifeSpan;
	}
	
	public: bool isDead()
	{
		return (age > lifeSpan);
	}
	
	public: bool isSplited()
	{
		return (bool)(gen < genThreshold && velocity.length() > splitVelocityThreshold);
	}
};


#endif __AGENT__