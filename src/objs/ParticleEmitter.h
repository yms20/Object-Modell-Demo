/*
 * ParticleEmitter.h
 *
 *  Created on: Jan 10, 2010
 *      Author: johannes
 */

#ifndef PARTICLEEMITTER_H_
#define PARTICLEEMITTER_H_
#include "Ball.h"
#include "object.h"
#include "Particle.h"
#include <vector>
#define MAX_PARTICLES 1000

class ParticleEmitter : public Object{
public:
	ParticleEmitter();
	virtual ~ParticleEmitter();

	std::vector <Particle *  >  particles;//[MAX_PARTICLES];
	std::vector <Object *  >  ammo;// Objects that are shot;
	std::vector <GLfloat  >  ammo_chance;// chances for indexd ammo between 0 .. 1 (should sum up to 1);
	GLboolean emitting;
	GLfloat frequency;

	GLfloat dir[3]; // Vector of direction
	GLint derivation ; // Kugel Kegel abweichung

	// Particle Enities
	GLfloat lifeTime;
	GLfloat speed;
	GLfloat speed_derrivation; // In percent



	void init();
	void startEmitting();
	void stopEmitting();

	void addAmmo(Object * o);

	void addParticle(Particle * newparticle);

	void removeParticle(GLint id);

	//Inherited Methods from Object
	 virtual void draw();
	 virtual void calc(GLfloat time);
	 virtual Object *  clone(){ return new ParticleEmitter();}
};

#endif /* PARTICLEEMITTER_H_ */
