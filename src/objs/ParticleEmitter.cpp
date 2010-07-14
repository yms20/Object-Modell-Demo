/*
 * ParticleEmitter.cpp
 *
 *  Created on: Jan 10, 2010
 *      Author: johannes
 */

#include "ParticleEmitter.h"
#include "Bee.h"
#include "cube.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
ParticleEmitter::ParticleEmitter() {
	frequency = 100 ; // herz = 1/s
	last_calc_time = 0 ;
	derivation =  90;
	speed = 1;
	lifeTime = 1000;
	dir [0] = 5;
//	addAmmo(new Ball());
}

ParticleEmitter::~ParticleEmitter() {


	//delete particles;
	//free ( particles);
}

void ParticleEmitter::addParticle(Particle * newparticle)
{
	newparticle->birth = last_calc_time;
	newparticle->setPos3fv(pos);
	particles.push_back(newparticle);
	//tos ++;
}
void ParticleEmitter::draw()
{
	beginDraw();

	// Draw the Derivation Sphere
/*
	 GLfloat alpha = derivation * M_PI/180.0; //xy
	 GLfloat beta = derivation/2 * M_PI/180.0; //xz
	 GLfloat speed = 10;
	 GLfloat abw[3];

	 glBegin(GL_LINES);
		 for (int   a = 0 ; a < derivation ; a ++) // 0 bis 2 Pi
			 for (int   b = 0 ; b < derivation/2 ; b ++) // 0 bis PI
			 {
				 glVertex3f(0,0,0);

				 abw[0] = speed * sin(b/180.0 *M_PI ) * cos (a/180.0*M_PI );
				 abw[1] = speed * sin(b/180.0*M_PI ) * sin (a/180.0*M_PI );
				 abw[2] = speed * cos(b/180.0*M_PI );
				 glVertex3fv(abw);
			 }
	 glEnd();
*/

	endDraw();
	for (unsigned int i = 0 ; i < particles.size() ; i++)
	{
		particles[i]->draw();
		float x = particles[i]->pos[0];
		float y = particles[i]->pos[1];
		float z = particles[i]->pos[2];
	}
}
/*
 *
void ParticleEmitter::removeParticle(GLint index)
{
	//delete (particles[index]);
	for (int i = index + 1; i < tos  ; i++)
		particles[i-1] = particles[i];

	tos--;

}
 */

void ParticleEmitter::addAmmo(Object * o)
{
	ammo.push_back(o);
}

void ParticleEmitter::calc(GLfloat time)
{
	static 	GLfloat freq_cnt = 0;
	GLfloat deltaTime = time - last_calc_time;
	freq_cnt +=deltaTime;
 if (freq_cnt > (1000.0/ frequency) )
 {
/*
 *

	 Particle * p = new Particle();

	 int choose = rand() % 7 ;
	 switch(choose){
	 case 0 :
	 case 1 :
	 case 2 :
	 case 3 :
	 case 4 :
		 delete (p->modell);
		 p->modell = new Cube(10);
		 p->modell->setColor3f((choose/4.0),4.0/(choose+1),choose%3/3.0);
		 break;


	 case 5 :
	 case 6 :
	//	 ParticleEmitter * e = new ParticleEmitter();
	//	e->frequency = 5;
	//	 p->lifetime = 2500;
	//	 delete (p->modell);
	//	 p->modell = e;

	 break;
	 }
 */

	 GLfloat alpha = rand()%derivation * M_PI/180.0; //xy
	 GLfloat beta = rand()%derivation/2 * M_PI/180.0; //xz
	 GLfloat speed = 50;
	 GLfloat abw[3];
	 abw[0] =  sin(beta) * cos (alpha);
 	 abw[1] =  sin(beta) * sin (alpha);
     abw[2] =  cos (beta);


     for (int k = 0 ; k < 3 ; k ++)
		 abw[k] = dir[k] + abw[k];

     GLfloat leng = sqrt(abw[0]*abw[0] +abw[1]*abw[1] +abw[2]*abw[2] );
	if (leng > 0)
	{
		 for (int k = 0 ; k < 3 ; k ++)
			 abw[k] /= leng;
	}

	 //addParticle(p);
if(ammo.size())
{

	 GLint rnd = rand()%(ammo.size()) ;
	 addParticle(new Particle(ammo[rnd]->clone(),pos,abw,speed,lifeTime));
}
	 freq_cnt -= (1000.0/ frequency);
 }

	// Clean dead Particles
	for (unsigned int i = 0 ; i < particles.size() ; i++){
		Particle * p = particles[i];
		if ((p->birth + p->lifetime )< time)
		{
			particles.erase( particles.begin() +i);

		}
	}

	// Call Calc for the still active Particles
	for (unsigned int i = 0 ; i < particles.size() ; i++)
	{
		particles[i]->calc(time- particles[i]->birth );
	}

	last_calc_time = time;
}
