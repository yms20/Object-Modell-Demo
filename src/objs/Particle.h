/*
 * Particel.h
 *
 *  Created on: Jan 10, 2010
 *      Author: johannes
 */

#ifndef PARTICLE_H_
#define PARTICLE_H_
#include "object.h"
class Particle : public Object {
public:
	Particle();
	virtual ~Particle();
	Particle(	Object * Modell,
				GLfloat pos[3],
				GLfloat dir[3],
				GLfloat speet,
				GLfloat lifetime);

	Object * modell; // The 3D Object that represents the Verices

	GLfloat birth; // ms
	GLfloat lifetime ; // ms
	GLfloat speed;

	GLfloat dir[3]; // Movement Vector Normalized


	//Inherited Methods from Object
	 virtual void draw();
	 virtual void calc(GLfloat time);
	 virtual Object *  clone(){ return new Particle();}
};

#endif /* PARTICEL_H_ */
