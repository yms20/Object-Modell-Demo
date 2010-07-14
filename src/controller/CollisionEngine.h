/*
 * CollisionEngine.h
 *
 *  Created on: Feb 4, 2010
 *      Author: johannes
 */

#ifndef COLLISIONENGINE_H_
#define COLLISIONENGINE_H_

#include "Engine.h"
#include "CollisionQuad.h"

class CollisionEngine : public Engine{
public:
	// Attributes
CollisionQuad * quads;
	// Methods
	CollisionEngine(Scene * s)
	{
		scene = s;
		quads = new CollisionQuad(s);
		init();
	}
	void init(){
		//printf("Collision Engine Init Scene with  %d \n",scene->tos);
		quads->scene_index.clear();
		for (int i = 0 ; i < scene->tos ; i ++)
		{
			quads->scene_index.push_back(i);
		}
		//printf("Quad has %d elements\n",quads->scene_index.size());
		//quads->buildTree(0);
	}

	Object * collides(Object * test_object){


		for (int i =0 ; i < scene->tos ; i ++)
		{
			Object * o = scene->objs[i];
			if (o != test_object)
			{
				if ( o->boundingSphere->collides(test_object->boundingSphere) )
					return o;
			}
		}
		return 0;
	}

	void draw(){
		quads->draw();
	}


// Inherited MEthods from Engine
void calc(GLfloat time)
{
	static GLfloat last_calc_time;
	GLfloat deltaT = time - last_calc_time;

	for (int i =0 ; i < scene->tos ; i ++)
	{
		Object * o = scene->objs[i];
		for (int k =0; k< 3; k++)
		{
			o->force[k] *= 0.99;
			o->force[k] += -o->pos[k]/100;
			o->accel[k] = o->force[k] / o->mass;
		}


			/*
		Object * theOther;
		if (  !(theOther = collides( o ))    )
		{

		o->setPos3f(o->pos[0] +( o->accel[0] * deltaT) /1000,
					o->pos[1] + (o->accel[1] * deltaT ) /1000,
					o->pos[2] + (o->accel[2] * deltaT) /1000);

		} else
		{
			o->setPos3f(-(o->pos[0] + o->accel[0] * deltaT/1000),
						-(o->pos[1] + o->accel[1] * deltaT/1000),
						-(o->pos[2] + o->accel[2] * deltaT/1000));
			for (int k =0; k< 3; k++)
				o->force[k] *= -1;
		 	theOther->setPos3f(theOther->pos[0] + theOther->force[0] * -deltaT/1000,
								theOther->pos[1] + theOther->force[1] * -deltaT/1000,
								theOther->pos[2] + theOther->force[2] * -deltaT/1000);
			GLfloat oldf[3];
			for (int k =0; k< 3; k++)
			{
				oldf[k] = o->force[k];
				o->force[k] =   (  o->pos[k] - theOther->pos[k] ) *deltaT/1000 - o->pos[k]*deltaT/1000 ;
			//	theOther->force[k] =  (  theOther->pos[k] - o->pos[k] )*deltaT/1000 - theOther->pos[k]*deltaT/1000 ;
			}
			//delete(scene->remove(i));
		}
		 */
	}
	init();
	quads->calc(time);
last_calc_time = time;
}

~CollisionEngine() ;
};

#endif /* COLLISIONENGINE_H_ */
