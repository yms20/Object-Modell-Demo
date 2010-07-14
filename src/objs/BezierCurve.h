/*
 * BezierCurve.h
 *
 *  Created on: Feb 2, 2010
 *      Author: johannes
 */

#ifndef BEZIERCURVE_H_
#define BEZIERCURVE_H_
#include "object.h"
#include <vector>

class BezierCurve : public Object{
public:
	BezierCurve();
	virtual ~BezierCurve();

	unsigned int grade ;
	float t;
	std::vector< GLfloat * >  controllPoints;
	GLfloat * tmp[3] ;
	// Add xyz Point to the Bezier Curve
	void addPoint3fv(GLfloat p[3]);
	//Add xy Point to the Bezier Curve
	void addPoint2fv(GLfloat p[2]);

	// Add xyz Point to the Bezier Curve
	void addPoint3f (GLfloat x,GLfloat y, GLfloat z);
	//Add xy Point to the Bezier Curve
	void addPoint2f(GLfloat x,GLfloat y);
	void extendArrayByOne();

	GLfloat* drawLevel(float t, unsigned int og,unsigned int ug,GLfloat result[3],bool draw);

	void f(GLfloat t, GLfloat x[3]);

	//Inherited Methods from Object
	 virtual void draw();
	 virtual void calc(GLfloat time);
	 virtual Object *  clone(){ return new BezierCurve();}

};

#endif /* BEZIERCURVE_H_ */
