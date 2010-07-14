/*
 * BezierCurve.cpp
 *
 *  Created on: Feb 2, 2010
 *      Author: johannes
 */

#include "BezierCurve.h"
#include "Ball.h"
#include <stdio.h>
BezierCurve::BezierCurve() {

	grade = 0;
	t= 0.5 ;
}

void BezierCurve::extendArrayByOne(){

	// tmp= (GLfloat **)malloc(this->grade +1 * sizeof(GLfloat));

	for (unsigned int i = 0 ; i < grade  ; i ++)
	{
		tmp[i] = (GLfloat *) malloc (sizeof(GLfloat) *3);
		tmp[i][0] = controllPoints[i][0];
		tmp[i][1] = controllPoints[i][1];
		tmp[i][2] = controllPoints[i][2];
	}

//	tmp = new GLfloat[grade][3]; // [grade] = (GLfloat *) malloc (sizeof(GLfloat) *3);
	//free (controllPoints);
	//controllPoints = tmp;5
	/*

	controllPoints = (GLfloat **)malloc( (this->grade +1) * sizeof(GLfloat));

	for (unsigned int i = 0 ; i < grade ; i ++)
	{
		controllPoints[i] = (GLfloat *) malloc (sizeof(GLfloat) *3);
		controllPoints[i][0] = tmp[i][0];
		controllPoints[i][1] = tmp[i][1];
		controllPoints[i][2] = tmp[i][2];
	}
	controllPoints[grade] = (GLfloat *) malloc (sizeof(GLfloat) *3);
	*/
}
void BezierCurve::addPoint3f(GLfloat x,GLfloat y, GLfloat z)
{
	//extendArrayByOne();
	GLfloat * p = (GLfloat *) malloc(sizeof(GLfloat) * 3);
	controllPoints.push_back( p);
	controllPoints[grade][0] = x;
	controllPoints[grade][1] = y;
	controllPoints[grade][2] = z;
	//GLfloat tmp[3] = {x,y,z};

	grade ++;
}

void BezierCurve::addPoint2f(GLfloat x,GLfloat y)
{
	addPoint3f(x,y,0);
}

void BezierCurve::addPoint3fv(GLfloat p[3])
{
	addPoint3f(p[0],p[1],p[2]);
}
void BezierCurve::addPoint2fv(GLfloat p[2])
{
	addPoint2f(p[0],p[1]);
}


void BezierCurve::calc(GLfloat time ){
	float deltaTime =time - last_calc_time;
	if (t < 1 )
		t += deltaTime/5000;
	else
		t = 0 ;

	last_calc_time = time;
}
void BezierCurve::draw(){
	// Draw th Points
	static Ball b;

	glPointSize(5);
	glColor3f(0,0,1);


	 // drawLevel(this->t,grade-1,0,b.pos,true);
	  glColor3f(1,1,1);
	  glBegin(GL_LINES);

	  for (float t = 0 ; t < this->t ; t+= this->t/100)
	  {
		  GLfloat p1[3];
		  GLfloat p2[3];
		  drawLevel(t,grade-1,0,p1,false);
		  drawLevel(t+this->t/100,grade-1,0,p2,false);
		  glVertex3fv(p1);
		  glVertex3fv(p2);
	  }

	  glEnd();

	b.radius = 1;

	b.draw();
}

GLfloat* BezierCurve::drawLevel(float t,unsigned int og,unsigned int ug,GLfloat result[3],bool draw)
{
	static Ball red;
	static Ball green;

	if (og < 0 || ug < 0)
		printf("error og %d ug %d",og,ug);

	if (og == ug)
	{
		result[0] = controllPoints[og][0];
		result[1] = controllPoints[og][1];
		result[2] = controllPoints[og][2];
		return 0 ;
	}

	GLfloat links[3];
	drawLevel(t,og-1,ug,links,draw);

	GLfloat rechts[3] ;
	drawLevel(t,og,ug+1,rechts,draw);

	if (draw)
	{

		glColor3f(0,0,1);
		glBegin(GL_LINES);
		glVertex3fv(links);
		glVertex3fv(rechts);
		glEnd();
		red.setPos3fv(links);
		green.setPos3fv(rechts);

		red.setColor3f(1,0,0);
		red.draw();
		green.setColor3f(0,1,0);
		green.draw();

	}
	 result[0] =links[0]  * (1-t) + rechts[0]  * (t);
	 result[1] =links[1]  * (1-t) + rechts[1]  * (t);
	 result[2] =links[2]  * (1-t) + rechts[2]  * (t);
	 return 0;
}

void BezierCurve::f(GLfloat t, GLfloat x[3])
{
	drawLevel(t,grade - 1, 0 ,x, false);
}

BezierCurve::~BezierCurve() {
	// TODO Auto-generated destructor stub
}
