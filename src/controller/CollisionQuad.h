/*
 * CollisionQuad.h
 *
 *  Created on: Feb 5, 2010
 *      Author: johannes
 */

#ifndef COLLISIONQUAD_H_
#define COLLISIONQUAD_H_
#include <GL/glut.h>
#include <cmath>
#include "../objs/object.h"
#include "BoundingRect.h"
#include "../misc/Text.h"
#include "Scene.h"
#include <vector>
#define CHILDREN_MAX 2
using namespace std;
class CollisionQuad {
public:
	static  int color   ;
	Text text;
	unsigned int maxObjCount ;
	vector < unsigned int > scene_index;
	BoundingRect * bound;
	CollisionQuad*   children[CHILDREN_MAX];
	int childrenTos ;
	Scene * scene;
	GLfloat last_calc_time;

	CollisionQuad(Scene * s)
	{
		scene = s;
		bound = scene->boundingRect;
		childrenTos = 0;
		CollisionQuad::color ++;
		maxObjCount = 6;
		last_calc_time = 0;
		buildTree(0);
	}
	void draw()
	{
		if (scene_index.size() > 0)
		{
			/*
		text.setPos3f(bound->pos[0] + bound->dim[0],
				bound->pos[1]+ bound->dim[1],
				bound->pos[2]- bound->dim[2]);
		char t[20];
		sprintf(t,"Has %d",scene_index.size());
		text.text = t;
		text.draw();
		*/
		bound->draw();
		//printf("I draw ! have children %d\n",childrenTos );
		}

		for (int i = 0 ; i < scene_index.size(); i ++)
		{
			scene->objs[scene_index[i]]->draw();
			glBegin(GL_LINES);
				glVertex3f(scene->objs[scene_index[i]]->pos[0] ,
						bound->pos[1] - bound->dim[1],
						scene->objs[scene_index[i]]->pos[2] );
				glVertex3fv(scene->objs[scene_index[i]]->pos );
			glEnd();
		}
		for (int i = 0 ; i < childrenTos; i ++)
			children[i]->draw();
	}

	void buildTree(GLfloat time ){
			deleteChildren();
			BoundingRect * quads[2];
			int objCount[2] = {0};

		// Laufe durch die Quadranten und zaehle die Dinger
			quads[0]  = bound->getHalf(0);
			quads[1]  = bound->getHalf(1);
			for (int i = 0 ; i < scene_index.size() ; i ++)
			{
				/*
				 *
				printf("scene_index %d val %d isInner(0) = %d  isInner(1) = %d\n",
										i,
										scene_index[i],
										quads[0]->isInner( scene->objs[scene_index[i]]->pos ),
										quads[1]->isInner( scene->objs[scene_index[i]]->pos )
										);
				 */
				if (quads[0]->isInner( scene->objs[scene_index[i]]->pos ) )
				{
					objCount[0] ++;
				}else
				if (quads[1]->isInner(scene->objs[scene_index[i]]->pos ) )
					{
						objCount[1] ++;
					}
			/*	else
					printf("is in keinem Quadranten %.1f %.1f %.1f, lol\n",
							scene->objs[scene_index[i]]->pos[0],
							scene->objs[scene_index[i]]->pos[1],
							scene->objs[scene_index[i]]->pos[2]
							);
				*/
			}
			/*
			printf("Quadrant 0  %d Quadrant 1 %d \n",
					objCount[0],
					objCount[1]
					      );
*/

			// WEnn in einem Quadrant mehr als 4 sind
			// erzeuge neues Collision Quad
			for (int j = 0 ; j<2 ; j ++)
			{
				if (objCount[j] >= 5)
				{
					CollisionQuad* newQuad = new CollisionQuad(scene);
					newQuad->bound = quads[j];
					newQuad->last_calc_time = last_calc_time;
					for (int i = 0 ; i < scene_index.size() ; i ++)
					{

						if (quads[j]->isInner( scene->objs[scene_index[i]]->pos ) )
						{
							newQuad->scene_index.push_back(scene_index[i]);
							//printf("psuhed back\n");
						}
					}
					for (int i = 0 ; i <  scene_index.size()  ; i ++)
					{

						if (quads[j]->isInner( scene->objs[scene_index[i]]->pos ) )
						{
							scene_index.erase(scene_index.begin() + i);
							i--;
						}
					}
					//newQuad->buildTree(time);
					children[childrenTos++] = (newQuad);
				} else
					delete (quads[j]);
			}
	}

	void checkCollision(GLfloat deltaT){
		for (int i = 0 ; i < scene_index.size(); i ++)
		{
			Object * a =  scene->objs[scene_index[i]];
			for (int j = 0 ; j < scene_index.size(); j ++)
			{
				if (i !=j ){
					Object * b =  scene->objs[scene_index[j]];
					if (a->boundingSphere->collides(b->boundingSphere)
					    &&	(a->pos[0] != b->pos[0]
						||  a->pos[1] != b->pos[1]
						||  a->pos[2] != b->pos[2]))
				{
/*
	*/
							// mttelpunkt beider Kugeln (TODO ohne radius)
						GLfloat p[3] =  {a->force[0],
										a->force[1],
										a->force[2]};


						// Normale der Ebene
						GLfloat n[3] =  {(a->pos[0] - b->pos[0]),
										(a->pos[1] - b->pos[1]),
										(a->pos[2] - b->pos[2])};

						GLfloat distN = sqrt( n[0] * n[0] +
											 n[1] * n[1] +
											 n[2] * n[2] );

						/*
						n[0] /= distN;
						n[1] /= distN;
						n[2] /= distN;
						// Richtungsvvector der kraft oder Accel oder speed je nach dem
						GLfloat pAufA[3] =  {(p[0] + a->force[0]),
											(p[1] + a->force[1]),
											(p[2] + a->force[2])};

						GLfloat distP = sqrt( p[0] * p[0 ] +
											 p[1] * p[1 ] +
											 p[2] * p[2 ] );
*/

						GLfloat t = -(n[0]  + n[1] + n[2]+n[0] *p[0] +  n[1]*p[1] + n[2]*p[2]) /( n[0]* n[0]+ n[1]*n[1]+n[2]*n[2] );

						printf("t : %f \n",t);
						for (int k = 0 ; k < 3 ; k ++)
							a->force[k] =  p[k] + 2* t *n[k]  ;

						for (int k = 0 ; k < 3 ; k ++)
						{
							n[k] = b->pos[k] - a->pos[k];
							p[k] = b->force[k];
						}


						t =  -(n[0]  + n[1] + n[2]+n[0] *p[0] +  n[1]*p[1] + n[2]*p[2]) /( n[0]* n[0]+ n[1]*n[1]+n[2]*n[2] );

						for (int k = 0 ; k < 3 ; k ++)
							b->force[k] =  p[k] + 2* t *n[k]  ;



						a->setPos3f(a->pos[0] - a->accel[0]*deltaT/1000,
									a->pos[1] - a->accel[1]*deltaT/1000,
									a->pos[2] - a->accel[2]*deltaT/1000);
						b->setPos3f(b->pos[0] - b->accel[0]*deltaT/1000,
									b->pos[1] - b->accel[1]*deltaT/1000,
									b->pos[2] - b->accel[2]*deltaT/1000);
					}
				}
			}

		}
	}

	void calc(GLfloat time)
	{
		GLfloat deltaT= (time - last_calc_time);
		//updateBound();
		if(scene_index.size() > 0 || childrenTos)
		{
			buildTree(last_calc_time);

			for (int i = 0 ; i < childrenTos; i ++)
				children[i]->calc(time);
		}


		for (int i = 0 ; i < scene_index.size(); i ++)
		{
			Object * o = scene->objs[scene_index[i]];
			o->setPos3f(o->pos[0] + o->accel[0] * deltaT /1000,
						o->pos[1] + o->accel[1] * deltaT /1000,
						o->pos[2] + o->accel[2] * deltaT /1000);

		}
			checkCollision(deltaT);
		//	printf("Debug %f \n",deltaT);
		last_calc_time = time;
	}


	void deleteChildren()
	{
		for (int i = 0 ; i < childrenTos; i ++)
				delete children[i];
		childrenTos = 0 ;
	}


	void updateBound(){
		GLfloat min[3];
		GLfloat max[3];
		scene->minmax(min,max);
		/*
		 */
		bound->setPos( 	(min[0] + max[0])/2,
								(min[1] + max[1])/2,
								(min[2] + max[2])/2 );
		bound->setDim( 	 (max[0]-min[0])/2 ,
								(max[1]-min[1])/2 ,
								(max[2]-min[2])/2 );
	}

	virtual ~CollisionQuad(){
		deleteChildren();
		delete bound;

	}
};
#endif /* COLLISIONQUAD_H_ */
