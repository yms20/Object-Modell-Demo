/*
 * Ball.h
 *
 *  Created on: Jan 6, 2010
 *      Author: johannes
 */

#ifndef BALL_H_
#define BALL_H_
#include "object.h"

class Ball : public Object {
public:
	GLUquadricObj * q;
	GLfloat radius;
	GLint xRes;
	GLint yRes;
	Ball();
	Ball(GLfloat radius, GLfloat r,GLfloat g,GLfloat b );

	// Inherted from Object
	void draw();
	virtual void calc(GLfloat time);
	virtual Object *  clone(){ return new Ball(radius,color[0],color[1],color[2]);}

	virtual ~Ball();
};

#endif /* BALL_H_ */
