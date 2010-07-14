/*
 * SkySkraper.h
 *
 *  Created on: Apr 1, 2010
 *      Author: johannes
 */
#include "object.h"
#include "rect.h"
#ifndef SKYSKRAPER_H_
#define SKYSKRAPER_H_

class SkySkraper : public Object{
public:
	Rect * front, * left, * right, * back, * top;
	GLfloat height;
	GLfloat base[2]; // Basement Plate;
	SkySkraper()
	{
		height = 10;
		base[0] = 2; // x
		base[1] = 2; // z

		front = new Rect();
		add(front);

		back = new Rect();
		add(back);

		left = new Rect();
		add(left);

		right = new Rect();
		add(right);

		top = new Rect();
		add(top);

		init();
	}

	void init()
	{
		front->dim[0] = base[0];
		front->dim[1] = height;
		front->setColor3f(1,1,1);
		front->setPos3f(0,height/2, - base[1]/2);

		back->dim[0] = base[0];
		back->dim[1] = height;
		back->rot[1] = 180;
		back->setColor3f(1,1,1);
		back->setPos3f(0,height/2,  base[1]/2);

		left->dim[0] = base[1];
		left->dim[1] = height;
		left->rot[1] = 270;
		left->setColor3f(1,1,1);
		left->setPos3f(  base[0]/2 ,height/2,  0);


		right->dim[0] = base[1];
		right->dim[1] = height;
		right->rot[1] = 90;
		right->setColor3f(1,1,1);
		right->setPos3f(  - base[0]/2 ,height/2,  0);



		top->dim[0] = base[0];
		top->dim[1] = base[1];
		top->rot[0] = 90;
		top->setPos3f(0,height,0);
		top->setColor3f(1,0,0);

	}
	void setSideTexture(Texture * t){
		front->setTexture(t);
		back->setTexture(t);
		left->setTexture(t);
		right->setTexture(t);
	}

	Rect * getSide(GLint n){
		Rect * returner;
		switch (n)
		{
		case 0 : returner =  front; break;
		case 1 : returner =  back; break;
		case 2 : returner =  left; break;
		case 3 : returner =  right; break;
		case 4 : returner =  top; break;
		}
		return returner;
	}


	virtual ~SkySkraper();

	//Inherited from Object
    virtual void draw();
    virtual void calc(GLfloat time);
    virtual Object *  clone(){ return new SkySkraper();}
};

#endif /* SKYSKRAPER_H_ */
