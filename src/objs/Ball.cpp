/*
 * Ball.cpp
 *
 *  Created on: Jan 6, 2010
 *      Author: johannes
 */

#include "Ball.h"


void Ball::draw()
{
	beginDraw();


		if (q == 0 )
			q = gluNewQuadric();
			glColor3fv(color);
			glutSolidSphere(radius, xRes,yRes);

	endDraw();
}

void Ball::calc(GLfloat time)
{
	if (boundingSphere)
	{
		boundingSphere->setPos3fv(pos);
		boundingSphere->radius = radius;
	}
}

Ball::Ball(GLfloat radius, GLfloat r,GLfloat g,GLfloat b ) : Object() {
	this->radius=radius;
	setColor3f(r,g,b);
	xRes = 16;
	yRes = 16;

	boundingSphere = new BoundingSphere();
	mass = 100 ; // kg
	radius = 1;
}
Ball::Ball()
{
	boundingSphere = new BoundingSphere();
	drawForces = true;
	mass = 100 ; // kg
	radius = 1;
	setColor3f(200/255.0,30/255.0,200/255.0);
	xRes = 16;
	yRes = 16;

}

Ball::~Ball() {
}
