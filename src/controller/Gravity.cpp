/*
 * Gravity.cpp
 *
 *  Created on: Jan 7, 2010
 *      Author: johannes
 */

#include "Gravity.h"

Gravity::Gravity() {
last_calc_time = 0;
}

void Gravity::calc(GLfloat time)
{
	GLfloat deltaTime = time - last_calc_time;

	if (scene != 0)
	for (GLuint i = 0 ; i < scene->tos ; i ++)
	{
		Object* o = scene->objs[i];
		if (o != 0 && o->mass > 0)
		{
			GLfloat mass = o->mass;
			GLfloat gravF = mass * - P_G;

			o->force[1] += gravF;

			o->force[0] = 5000;

			for (int k = 0 ; k < 3; k ++)
				o->accel[k] = o->force[k] / mass;
			for (int k = 0 ; k < 3; k ++)
				o->speed[k] += o->accel[k] * deltaTime/1000;
			for (int k = 0 ; k < 3; k ++)
				o->pos[k] += o->speed[k] ;

			if (o->pos[1] < -200)
			{
				o->force[0] = 0;
				o->force[1] = 0;
				o->speed[0] = 0;
				o->speed[1] = 0;
				o->pos[0] = 0;
				o->pos[1] = 200;
			}
		}
	}
	last_calc_time = time;
}

Gravity::~Gravity() {
}
