/*
 * SegRing.cpp
 *
 *  Created on: Mar 27, 2010
 *      Author: johannes
 */

#include "SegRing.h"
#include <malloc.h>
SegRing::SegRing() {

	r1 = 10;
	r2 = 30;
	verts = 0;
	segs = 3;
	space = 0.5;
	//init();
	setPos3f(0,0,0);
	setColor3f(0,0,1);
}
void SegRing::init(){
	initing = true;
	float u= 0,res = M_PI / 32;
	n= 0;
	int seg =0;
	// Count the Vertexes We will need for the Vertex array;
	for (u = ((M_PI * 2)/ segs)  *  seg; u <  ((M_PI * 2)/ segs)  *  seg + ((M_PI * 2)/ segs) * (1-space); u +=res)
	{
		n+=3;
		n+=3;
	}

	// Memort Allocation
	if (verts != 0)		free( verts);
	verts = (GLfloat **) malloc (n * sizeof (GLfloat * ) * segs );
	for (seg = 0; seg < segs; seg++)
		verts[seg] = (GLfloat *) malloc (n * sizeof (GLfloat ) * 3 );

	// Fill the Vertexarray
	for (seg = 0 ; seg < segs ; seg ++ )
	{
	n = 0 ;
	//	glBegin(GL_QUAD_STRIP);
		for (u = ((M_PI * 2)/ segs)  *  seg; u <  ((M_PI * 2)/ segs)  *  seg + ((M_PI * 2)/ segs) * (1-space); u +=res)
		{

			verts[seg][n++] = r1 * sin(u);
			verts[seg][n++] = r1 * cos(u);
			verts[seg][n++] = 0;

			verts[seg][n++] = r2 * sin(u);
			verts[seg][n++] = r2 * cos(u);
			verts[seg][n++] = 0;
		//	glVertex3f(r1 * sin(u),r1 * cos(u),0);
			//glVertex3f(r2 * sin(u),r2 * cos(u),0);
		}
	//	glEnd();
	}


	initing = false;
}

void SegRing::drawImmidiate()
{
	int seg;
	float u,res = M_PI / 32;
	for (seg = 0 ; seg < segs ; seg ++ )
	{

		glBegin(GL_QUAD_STRIP);
		for (u = ((M_PI * 2)/ segs)  *  seg; u <  ((M_PI * 2)/ segs)  *  seg + ((M_PI * 2)/ segs) * (1-space); u +=res)
		{
			glVertex3f(r1 * sin(u),r1 * cos(u),0);
			glVertex3f(r2 * sin(u),r2 * cos(u),0);
		}
		glEnd();
	}
}

void SegRing::drawVertexArray(){
	if (!initing)
	{

		glColor3f(1,0,0);

		int seg;
		for (seg = 0; seg < segs; seg++)
		{
		glEnableClientState(GL_VERTEX_ARRAY);
			glVertexPointer(3, GL_FLOAT, 0, verts[seg]);
			glDrawArrays(GL_QUAD_STRIP, 0, n);
		glDisableClientState(GL_VERTEX_ARRAY);
		}

	}
}

void SegRing::draw()
{
	beginDraw();
	drawImmidiate();
	endDraw();
}

void SegRing::calc(GLfloat time){

	//rot[2] = rot[2] + 1;

	//r1 = 15  +10 * sin(time/1000);
	//init();
}

SegRing::~SegRing() {
	// TODO Auto-generated destructor stub
}
