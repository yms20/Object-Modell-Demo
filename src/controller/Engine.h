/*
 * Engine.h
 *
 *  Created on: Feb 4, 2010
 *      Author: johannes
 */

#ifndef ENGINE_H_
#define ENGINE_H_
#include <GL/glut.h>
#include "Scene.h"

class Engine {
public:
	// Attributes
	Scene * scene;

	virtual void draw() = 0;
	virtual void calc(GLfloat time) = 0;
	Engine();
	virtual ~Engine();
};

#endif /* ENGINE_H_ */
