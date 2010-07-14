/*
 * Particle.cpp
 *
 *  Created on: Jan 10, 2010
 *      Author: johannes
 */

#include "Particle.h"
#include "Ball.h"

Particle::Particle() {

	last_calc_time = 0;
	this->pos[0] = 0;
	this->pos[1] = 2;
	this->pos[2] = 0;

	this->dir[0] = 5;
	this->dir[1] = 5;
	this->dir[2] = 0;

	this->lifetime = 10000;
	this->speed = 1;
	Ball * b =  new Ball(5,1,1,1);
	b->xRes = 5;
	b->yRes = 5;
	this->modell = b;
}

Particle::Particle(	Object * Modell,
					GLfloat pos[3],
					GLfloat dir[3],
					GLfloat speet,
					GLfloat lifetime)
{
	last_calc_time = 0;
	this->pos[0] = pos[0];
	this->pos[1] = pos[1];
	this->pos[2] = pos[2];

	this->dir[0] = dir[0];
	this->dir[1] = dir[1];
	this->dir[2] = dir[2];

	this->lifetime = lifetime;
	this->speed = speet;
	this->modell = Modell;

}

void Particle::calc(GLfloat time)
{
	modell->calc(time);
	GLfloat deltaTime = time - last_calc_time;
	for (int k = 0 ; k < 3 ; k++)
	{
		pos[k] += speed *  dir[k] *deltaTime/1000.0;
	}



	// Update Modell position
		modell->setPos3fv(pos);


	last_calc_time = time;
}

void Particle::draw()
{
	this->modell->draw();
}

Particle::~Particle() {
	delete(modell);
	free (modell);
	//free (children);
	free (tex);
}
