
#ifndef SCENE_H_
#define SCENE_H_

#define MAX_OBJS 400
#include "../objs/object.h"
#include "BoundingRect.h"
//class Engine ;

class Scene {
public:
	Object * objs[MAX_OBJS];
	GLuint tos;
	BoundingRect * boundingRect;
	virtual void draw();
	virtual void calc(GLfloat time);
	/*
	 * TODO Add an init/deinit Scene or enable/disable Scene Mecanism
	 * Special regards to Light and everythig that has to do with the
	 * opengl State machine
	 */
	void updateBounds();
	void minmax(GLfloat  min[3],GLfloat max[3]);

	void add(Object * o);
	Object * remove(GLint index);
	bool remove(Object * o );

	// Input Handling
	virtual void keyPressed(GLint key);
	virtual void specialKeyPressed(GLint key);

	Scene();
	virtual ~Scene();
};

#endif /* SCENE_H_ */
