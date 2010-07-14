/*
 * BoundingSphere.h
 *
 *  Created on: Feb 4, 2010
 *      Author: johannes
 */

#ifndef BOUNDINGSPHERE_H_
#define BOUNDINGSPHERE_H_
#include <GL/glut.h>
#include <cmath>
class BoundingSphere {
public:
	GLfloat radius;
	GLfloat pos[3];

	BoundingSphere();

	void draw(){
		glutWireSphere(radius,8,8);
	}

	void setPos3fv(GLfloat * p){
		setPos3f(p[0],p[1],p[2]);
	}


	bool collides(BoundingSphere * bs){
		float deltaR = radius + bs->radius;
		if (bs != this)
		{
			if (bs->pos[0] == pos[0] &&
				bs->pos[1] == pos[1] &&
				bs->pos[2] == pos[2] )
				return true;

			if (distanceTo(bs) <= deltaR)
				return true;
			else
				return false;
		}
		return false;
	}

	GLfloat distanceTo(BoundingSphere * bs){
		GLfloat delta[3] =
				{pos[0] - bs->pos[0],
				 pos[1] - bs->pos[1],
				 pos[2] - bs->pos[2]};
		GLfloat deltaLeng =
			delta[0] * delta[0] +
			delta[1] * delta[1] +
			delta[2] * delta[2];
		if (deltaLeng > 0)
			return sqrt(deltaLeng);
		else
			return -1;
	}

	void setPos3f(GLfloat x,GLfloat y,GLfloat z){
		pos[0] =x;
		pos[1] =y;
		pos[2] =z;
	}
	virtual ~BoundingSphere();
};

#endif /* BOUNDINGSPHERE_H_ */
