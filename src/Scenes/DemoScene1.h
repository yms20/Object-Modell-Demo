/*
 * DemoScene1.h
 *
 *  Created on: Mar 28, 2010
 *      Author: johannes
 */

#ifndef DEMOSCENE1_H_
#define DEMOSCENE1_H_
#include "../controller/Scene.h"
#include "../objs/SegRing.h"
#include "../objs/rect.h"
#include "../objs/ParticleEmitter.h"
#include "../objs/BezierCurveLong.h"
#include "../objs/newnet.h"
#include "../objs/Light.h"
#include "../objs/cube.h"
#include "../objs/SkySkraper.h"
#include <vector>

class DemoScene1 : public Scene {
public:

	//Objects
	SegRing * atom;
	Rect * floor;
	Rect * top;
	Rect * left;
	Rect * right;
	Rect * back;
	ParticleEmitter * pe;
	BezierCurveLong bc;
	NewNet * nn;

	std::vector <SkySkraper *> city;
	std::vector <GLfloat> cityMaxHeight;

	// Light
	Light * scLight1;

	SkySkraper * skysracer;

	DemoScene1();
	void init();
	void draw();
	void calc(GLfloat time);
	virtual ~DemoScene1();

};

#endif /* DEMOSCENE1_H_ */
