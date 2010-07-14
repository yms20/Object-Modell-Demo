/*
 * Camera.h
 *
 *  Created on: Apr 1, 2010
 *      Author: johannes
 */

#ifndef CAMERA_H_
#define CAMERA_H_
#include <GL/glut.h>

class Camera {
public:
	GLfloat pos[3];
	GLint angle[2]; // XY and  XZ
	GLfloat dir[3]; // A normal Vector poining to view direction
	GLfloat upVector[3];

	GLfloat cleraColor[3];
	static GLint id_ctr;
	GLint id;
	GLfloat fov;
	GLfloat ratio;
	GLint viewport[2];

	// Camera cam be Targeted
	GLboolean targeted;
	GLfloat target[3];


	// First Person
	GLfloat speed;

	void moveForward()
	{
		pos[0] += dir[0]*speed;
		pos[1] += dir[1]*speed;
		pos[2] += dir[2]*speed;
	}

	void moveBackward()
	{
		pos[0] -= dir[0]*speed;
		pos[1] -= dir[1]*speed;
		pos[2] -= dir[2]*speed;
	}

	void strafLeft()
	{
		pos[0] += dir[2]*speed;
	   pos[2] += -dir[0]*speed;

	}
	void strafRight()
	{
		pos[0] += -dir[2]*speed;
	   pos[2] += dir[0]*speed;
	}


	// Misc Init and Render
	void save();
	void load();
	void render();

	Camera();
	virtual ~Camera();
};

#endif /* CAMERA_H_ */
