/*
 * Scene.cpp
 *
 *  Created on: Dec 4, 2009
 *      Author: johannes
 */

#include "Scene.h"

Scene::Scene() {
	tos = 0;
	boundingRect = new BoundingRect();
}

Scene::~Scene() {
}

void Scene::add(Object * o )
{
	if(tos < MAX_OBJS -1 )
	objs[tos++] = o ;

}
Object * Scene::remove(GLint index)
{
	Object * deleted;
	if (index < tos)
	{
		//Save deleted
		deleted = objs[index];
		// close the gap in the array
		for (int i = index ; i < tos - 1; i++)
		{
			objs[i] = objs[i+1];
		}
		//decrement stack size
		tos--;
	}

	return deleted;
}

void Scene::updateBounds(){
	GLfloat min[3];
	GLfloat max[3];
	minmax(min,max);


	/*
	 */
	boundingRect->setPos( 	(min[0] + max[0])/2,
							(min[1] + max[1])/2,
							(min[2] + max[2])/2 );
	boundingRect->setDim( 	 (max[0]-min[0])/2 ,
							(max[1]-min[1])/2 ,
							(max[2]-min[2])/2 );

}
void Scene::minmax(GLfloat  min[3], GLfloat max[3]){

	if (tos > 0)
	{
		max[0] = objs[0]->pos[0] ;
		max[1] = objs[0]->pos[1];
		max[2] = objs[0]->pos[2];
		min[0] = objs[0]->pos[0];
		min[1] = objs[0]->pos[1];
		min[2] = objs[0]->pos[2];

		for (int i = 0 ; i < tos ; i ++)
		{
			Object * o = objs[i];
			for (int k = 0 ; k < 3 ; k++)
			{
				if (max[k] <= o->pos[k])
					max[k] = o->pos[k];

				if (min[k] >= o->pos[k])
					min[k] = o->pos[k];
			}

		}
	}
	else {
		min[0] = max[0] =  0;
		min[1] = max[1] =  0;
		min[2] = max[2] =  0;
	}
}


void Scene::calc(GLfloat time)
{
	updateBounds();
	for (GLint i = 0; i < tos ; i++)
	{
		objs[i]->calc(time);
	}
}
void Scene::draw()
{
	boundingRect->draw();

	for (GLint i = 0; i < tos ; i++)
	{
		objs[i]->draw();
	}
}

void Scene::keyPressed(GLint key)
{
	for (GLint i = 0; i < tos ; i++)
	{
		objs[i]->keyPressed(key);
	}
}
void Scene::specialKeyPressed(GLint key)
{
	for (GLint i = 0; i < tos ; i++)
	{
		objs[i]->specialKeyPressed(key);
	}
}

