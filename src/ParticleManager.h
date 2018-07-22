/*
 *  ParticleManager.h
 *  emptyExample
 *
 *  Created by satoshi okami on 12/01/15.
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef __PARTICLEMANAGER__
#define __PARTICLEMANAGER__

#include "Particle.h"
#include "Planet.h"
#include "utils.h"
#include <iostream.h>


class ParticleManager
{
	public: vector<Particle> particles;
	public: vector<Planet> planets;
	public: vector<int> bands;
	public: bool isMusicPlaying;
	
	
	
	public: ParticleManager()
	{
		isMusicPlaying = false;
		
		ofVec3f position(0, 0, 0);
		ofVec3f velocity(0, 0, 0);
		createPlanet(1, position, velocity);
		
	}
	
	public: void emit(float emitNum)
	{
		int gen = 1;
		
		for (int i = 0; i < emitNum; i++)
		{
			ofVec3f position(0, 0, 0);
			ofVec3f randVec = utils::getRandVec() * 20 * (1 - log(gen));
			
			createParticle(gen, randVec, position);
		}
	}
	
	protected: void createParticle(const int gen, const ofVec3f _position, const ofVec3f _velocity)
	{
		Particle p(gen, _position, _velocity);
		particles.push_back(p);
	}
	
	protected: void createPlanet(const int gen, const ofVec3f _position, const ofVec3f _velocity)
	{
		planets.push_back(Planet(gen, _position, _velocity));
	}
	
	public: void update()
	{
		int size = particles.size();
		vector<Particle> tmp1;
		vector<Particle> tmp2;
		
		
		if (size > 0)
		{
			// サウンド情報取得
			float *fftValues = ofSoundGetSpectrum(size);
			float normalizedValues[size];
			float avg = 0;
			float max = 0;
			
			if (size > 0)
			{
				for (int i = 0; i < size; i++)
				{
					if (fftValues[i] > max) max = fftValues[i];
				}
				
				for (int i = 0; i < size; i++)
				{
					normalizedValues[i] = fftValues[i] / max;
					
					avg += normalizedValues[i];
				}
				
				avg /= size;
			}
			
			// 配列が可変で変化するのでバンドもそれにともなって修正する
			for (int i = 0; i < size; i++)
			{
				Particle& p = particles[i];
				p.seedBand(particles.size());
			}
			
			// パーティクル更新
			float threshold = 0.9f;
			ofVec3f force;
			ofVec3f crossVec;
			crossVec.set(0, 1, 0);
			crossVec.rotate(ofGetFrameNum(), 0, ofGetFrameNum() * 0.5);
			ofVec3f tangentVec;
			
			for (int i = 0; i < size; i++)
			{
				Particle& p = particles[i];
				
				if (p.isDead()) continue;
				
				p.isMusicPlaying = isMusicPlaying;
				
				if(normalizedValues[p.band] > threshold)
				{
					ofVec3f randVec = utils::getRandVec();
					randVec.normalize();
					randVec *= normalizedValues[p.band] * 100;
					p.addForce(randVec);
				}
				
				if (max > threshold)
				{
					p.seedMaterialColor();
				}
				
				// 重力足す
				for (int j = 0; j < planets.size(); j++)
				{
					ofVec3f norm = (p.position - planets[j].position);
					norm.normalize();
					norm *= planets[j].radius;
					p.arrive(ofVec3f(0, 0, 0));
					//p.arrive(norm);
				}
				
				force.set(p.position - planets[0].position);
				force.normalize();
				force *= max * 300;
				tangentVec = force.crossed(crossVec);
				//tangentVec = crossVec;
				tangentVec.normalize();
				tangentVec *= max * 1000;
				force += tangentVec;
				
				p.addForce(force);
				
				ofVec3f randVec = utils::getRandVec();
				randVec.normalize();
				randVec *= max * 1000;
				p.addForce(randVec);
				//cout << randVec << " " << randVec.length() << endl;
				
				p.update();
				
				
				
				
				if (p.isSplited())
				{
					
				}
				
				
				tmp1.push_back(p);
			}
			
			particles.swap(tmp1);
			
			
			
		}
	}
	
	public: void draw()
	{
		for (int i = 0; i < particles.size(); i++)
		{
			Particle& p = particles[i];
			p.draw();
		}
	}
	
};


#endif __PARTICLEMANAGER__