/*
 * Gravity.h
 *
 *  Created on: Jan 7, 2010
 *      Author: johannes
 */

#ifndef GRAVITY_H_
#define GRAVITY_H_

#include "../objs/object.h"
#include "Scene.h"

class Gravity {
public:
	Scene * scene ; // Scene hold objs to calc Gravitiy

	GLfloat last_calc_time;

	void calc(GLfloat time);
	Gravity();
	virtual ~Gravity();
};

#endif /* GRAVITY_H_ */
