/*
 *  Particle.h
 *  emptyExample
 *
 *  Created by satoshi okami on 12/01/15.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef __PARTICLE__
#define __PARTICLE__

#include "Agent.h"
#include <iostream.h>
#include "utils.h"
#include <GLUT/GLUT.h>


class Particle : public Agent
{
	public: float radius;
	public: int band;
	public: int rand;
	public: bool isMusicPlaying;
	
	public: Particle(int _gen, ofVec3f _position, ofVec3f _velocity) : Agent(_gen)
	{
		position = _position;
		velocity = _velocity;
		
		radius = ofRandom(10, 50 - (gen - 1) * 10);
		band = 0;
		seedMaterialColor();
		isMusicPlaying = false;
		
		
		
		mass = 1;
		maxForce = 20.0f;
		maxSpeed = 20.0f;
		wanderDistance = 1;
		wanderRadius = 3;
		
		maxTrailSize = 10;
		age = 0.0f;
		agePer = 1.0f;
		lifeSpan = (float)radius;
		genThreshold = 4;
		splitVelocityThreshold = 10.0f;
	}
	
	public: void update()
	{
		Agent::update();
		
		if (isMusicPlaying) aging(0.2);
		else aging(5);

	}
	
	public: void seedBand(int max)
	{
		if (band < 1 || band > max)
		{
			band = (int)(ofRandomuf() * max * 0.5);
		}
	}
	
	public: void seedMaterialColor()
	{
		rand = (int)(ofRandomuf() * 4);
	}
	
	public: void draw()
	{
		GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
		GLfloat mat_ambient[] = { 0.7, 0.7, 0.7, 1.0 };
		GLfloat mat_ambient_color[] = { 0.8, 0.8, 0.2, 1.0 };
		GLfloat mat_diffuse[] = { 0.1, 0.5, 0.8, 1.0 };
		GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
		GLfloat no_shininess[] = { 0.0 };
		GLfloat low_shininess[] = { 5.0 };
		GLfloat high_shininess[] = { 100.0 };
		GLfloat mat_emission[] = {0.3, 0.2, 0.2, 0.0};
		
		
		
		glPushMatrix();
		glEnable(GL_LIGHTING);
		glEnable(GL_LIGHT0);
		glTranslatef(position.x, position.y, position.z);
		
		if (rand == 0) {
		glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
		glMaterialfv(GL_FRONT, GL_SPECULAR, no_mat);
		glMaterialfv(GL_FRONT, GL_SHININESS, no_shininess);
		glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission);
		}
		if (rand == 1) {
		glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient_color);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
		glMaterialfv(GL_FRONT, GL_SPECULAR, no_mat);
		glMaterialfv(GL_FRONT, GL_SHININESS, no_shininess);
		glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission);
		}
		if (rand == 2) {
		glMaterialfv(GL_FRONT, GL_AMBIENT, no_mat);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
		glMaterialfv(GL_FRONT, GL_SPECULAR, no_mat);
		glMaterialfv(GL_FRONT, GL_SHININESS, no_shininess);
		glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission);
		}
		if (rand == 3) {
		glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient_color);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
		glMaterialfv(GL_FRONT, GL_SPECULAR, no_mat);
		glMaterialfv(GL_FRONT, GL_SHININESS, no_shininess);
		glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
		}
		glCallList((int)(radius * agePer));
		glDisable(GL_LIGHT0);
		glDisable(GL_LIGHTING);
		glPopMatrix();
	}
};


#endif __PARTICLE__