/*
 * BezierCurveLong.h
 *
 *  Created on: Mar 27, 2010
 *      Author: johannes
 */

#ifndef BEZIERCURVELONG_H_
#define BEZIERCURVELONG_H_
#include "BezierCurve.h"
#include "SegRing.h"
#include "Ball.h"
/*
 * This Class Implenents the fact that a BezierCure of any
 * Grade can be represented by a chain of 3rd Grade Beziers
 */
class BezierCurveLong : public Object{
public:

	/*
	 * Holds BezierCurvs of 3rd Grade
	 */
	std::vector <BezierCurve *> curves ;
	GLint grade;
	SegRing * runner;
	GLfloat t;
	BezierCurveLong(){
		runner = new SegRing();
		grade = 0;
		last_calc_time = 0 ;
	}
	void add(GLfloat x,GLfloat y,GLfloat z){
		if (grade == 0)
		{
			curves.push_back(new BezierCurve());
		}
		if (grade < 3){
			curves[0]->addPoint3f(x,y,z);
		}else		// If the curve is defined through more than 3 controll points
		{			// We add a new Curve to our stack with first Point = last point
					// of the previous curve,  3rd and last point is the new point
					// the 2dn point is more tricky, though it is a point mirror of the
					// middle point of the previous curve at the point of the starting
					// point at ths curve.
			BezierCurve * pre = curves[grade -3];
			BezierCurve * newPoint = new BezierCurve();

			// The Middle Point is Tricky
			GLfloat toMirror[3] = {pre->controllPoints[1][0],
									pre->controllPoints[1][1],
									pre->controllPoints[1][2]};
			GLfloat mirror[3] = {pre->controllPoints[2][0],
								pre->controllPoints[2][1],
								pre->controllPoints[2][2]};

			GLfloat result[3];

			for (int i = 0; i < 3; ++i) {
				result[i] = mirror[i] - ( toMirror[i] - mirror[i]);
			}

			newPoint->addPoint3fv(pre->controllPoints[2]);
			newPoint->addPoint3fv(result);
			newPoint->addPoint3f(x,y,z);

			curves.push_back(newPoint);
		}

		grade ++ ;
	}

	/*
	 * This Method closes The bezier Cure to a smooth loop
	 */
	void closeToLoop(){
		if (grade < 3){


		}else
		{
			BezierCurve * pre = curves[0];
			BezierCurve * newPoint = new BezierCurve();

			// The Middle Point is Tricky
			GLfloat second[3] = {pre->controllPoints[1][0],
									pre->controllPoints[1][1],
									pre->controllPoints[1][2]};
			GLfloat fisrt[3] = {pre->controllPoints[0][0],
								pre->controllPoints[0][1],
								pre->controllPoints[0][2]};

			GLfloat result[3];

			for (int i = 0; i < 3; ++i) {
				result[i] = fisrt[i] - ( second[i] - fisrt[i]);
			}

			newPoint->addPoint3fv(curves[grade -3]->controllPoints[2]);
			newPoint->addPoint3fv(result);
			newPoint->addPoint3fv(fisrt);

			curves.push_back(newPoint);
		}

		grade ++ ;
	}

	void f(GLfloat t,GLfloat x[3])
	{
		// t: 0..1
		int tt = t;
		t = t - tt;
		GLfloat parts = 1.0/curves.size();
		int part = t * (curves.size() ) ;
		printf("t %f parts %f part %d\n",t,parts,part);
		GLfloat subT =  (t- parts * part )* curves.size();
		curves[part]->f(subT,x);
	}
	void f(GLfloat x[3])
	{
		// t: 0..1
		GLfloat parts = 1.0/curves.size();
		int part = t * (curves.size() ) ;
		//printf("t %f parts %f part %d\n",t,parts,part);
		GLfloat subT =  (t- parts * part )* curves.size();
		curves[part]->f(subT,x);
	}

	void draw(){
		for (int i = 0 ; i <= grade -3 ; i ++)
		{
			curves[i]->draw();
		}

		//SegRing * b = new SegRing();
		f(runner->pos);
		//b->calc(0);
		runner->draw();
	}

	void calc(GLfloat t){
		GLfloat deltaT = t - last_calc_time;
		if (this->t < 1 && this->t + deltaT/10000 < 1)
			this->t +=deltaT/10000 ;
		else
			this->t = 0;
		for (int i = 0 ; i <= grade -3 ; i ++)
		{
			curves[i]->calc(0);
			curves[i]->calc(5000);
		}

		runner->calc(t);
		runner->setColor3fv(runner->pos);
		last_calc_time = t ;
	}

	virtual Object *  clone(){ return new BezierCurveLong();}

	virtual ~BezierCurveLong();
};

#endif /* BEZIERCURVELONG_H_ */
