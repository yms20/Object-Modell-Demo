/*
 * SegRing.h
 *
 *  Created on: Mar 27, 2010
 *      Author: johannes
 */

#ifndef SEGRING_H_
#define SEGRING_H_
#include "object.h"
class SegRing : public Object{
public:
	SegRing();
	virtual ~SegRing();
	GLfloat r1,r2;
	GLint segs;
	GLfloat space; // 0 .. 1
	GLfloat ** verts;
	GLboolean initing;
	int n;

		void init();
		void drawVertexArray();
		void drawImmidiate();
	//Inherited Methods from Object
	 virtual void draw();
	 virtual void calc(GLfloat time);
	 virtual Object *  clone(){ return new SegRing();}
};

#endif /* SEGRING_H_ */
