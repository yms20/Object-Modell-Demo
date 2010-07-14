#ifndef BEE_H_
#define BEE_H_

#include "object.h"
#include <math.h>
class Bee: public Object
{
public:
	GLfloat localtime;
	
	GLfloat r;
	GLfloat h;
	GLfloat hmax;
	GLfloat rot;
	GLfloat size;
	
	GLfloat O[3];
	
	
	Bee();
	Bee(GLfloat o[3]);
	void bee(GLfloat size);
	void setPath();
	
	void draw();
	void calc(float time);
	virtual ~Bee();
	virtual Object *  clone(){ return new Bee();}
};

#endif /*BEE_H_*/
