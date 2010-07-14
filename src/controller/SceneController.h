/*
 * SceneController.h
 *
 *  Created on: Mar 18, 2010
 *      Author: johannes
 */

#ifndef SCENECONTROLLER_H_
#define SCENECONTROLLER_H_
#include <vector>
#include "Scene.h"
#include "../files/Directory.h"
#include "../objs/rect.h"
#include "../objs/kommstar.h"
#include "../objs/cube.h"
#include "../objs/cubearray.h"
#include "../objs/net.h"
#include "../objs/newnet.h"
#include "../objs/Bee.h"
#include "../objs/ParticleEmitter.h"
#include "../objs/Particle.h"
#include "../objs/Ball.h"
#include "../objs/Light.h"
#include "../objs/SegRing.h"
#include "../Timer.h"
#include "./Gravity.h"
#include "./CollisionEngine.h"
#include "../objs/BezierCurve.h"
#include "../objs/BezierCurveLong.h"
#include "../Gallery.h"
#include "../FileBrowser.h"
#include "../Scenes/DemoScene1.h"
using namespace std;
class SceneController {
public:

	vector<Scene*> scene;
	int selectedSecen;


	SceneController(){
		selectedSecen = 1;

		initScene();

	}

	void initScene();

	void addScene(Scene * s){
		scene.push_back(s);
	}
	void calc(GLfloat time){
		if (selectedSecen >= 0)
		scene[selectedSecen]->calc(time);

	}
	void draw(){
		if (selectedSecen >= 0)
			scene[selectedSecen]->draw();
	}

	void keyPressed(GLint key){
		// Handle Scene Switching Keys
		if (key >= '0' && key < ('0'+ scene.size())  && key < '9')
		{
		printf("SceneController KeyPressed %c %d\n",key,key);
			selectedSecen =  key - '0';
		}
		else
		{
		if (selectedSecen >= 0)
			scene[selectedSecen]->keyPressed(key);
		}

	}
	void specialKeyPressed(GLint key)
	{
		printf("Scene Controller Special Key pressed\n");
		// Handle Scene Switching Keys
		if (selectedSecen >= 0)
			scene[selectedSecen]->specialKeyPressed(key);

	}
	virtual ~SceneController();
};

#endif /* SCENECONTROLLER_H_ */
