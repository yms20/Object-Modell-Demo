/*
 * DemoScene1.cpp
 *
 *  Created on: Mar 28, 2010
 *      Author: johannes
 */

#include "DemoScene1.h"
#include "../objs/Bee.h"

DemoScene1::DemoScene1()
{
	init();
}
void DemoScene1::init()
{
	atom = new SegRing();
	atom->segs = 1;
	atom->space = 0;
	atom->setPos3f(0,0,10);
	add(atom);

	floor = new Rect();
	floor->setTexture("./Resources/Pix/4922.jpg");
	floor->dim[0] = 500;
	floor->dim[1] = 500;
	floor->rot[0] = 90;
	floor->texrepeat[0] = floor->texrepeat[1] = 5;
	floor->setPos3f(0,-250,0);
	add(floor);

	top = new Rect();
	top->dim[0] = 500;
	top->dim[1] = 500;
	top->rot[0] = 90;
	top->setColor3f(0.4,0.4,0.4);
	top->setPos3f(0,250,0);
	add(top);

	left = new Rect();
	left->dim[0] = 500;
	left->dim[1] = 500;
	left->rot[1] = 90;
	left->setColor3f(0.3,0.3,0.3);
	left->setPos3f(250,0,0);
	add(left);

	right = new Rect();
	right->dim[0] = 500;
	right->dim[1] = 500;
	right->rot[1] = 90;
	right->setColor3f(0.3,0.3,0.3);
	right->setPos3f(-250,0,0);
	add(right);

	// Light
	scLight1 = new Light(0.3,0.1,0.1,0);
	scLight1->setPos3f(0,0,-200);
	scLight1->enable();
	add(scLight1);


	pe = new ParticleEmitter();
	pe->frequency = 5000;
	pe->lifeTime = 1500;
	pe->speed  = 1000;
	pe->addAmmo(new Ball());
	pe->addAmmo(new Ball(1,0,1,0));
	pe->addAmmo(new Ball(1,0,0,1));
	//pe->addAmmo(new Bee());
	add(pe);


	bc.add(-100,0,- 200);
	bc.add(0,0,0);
	bc.add(100,0,0);
	bc.add(-100,0,100);
	bc.add(0,0,0);
	bc.add(100,0,0);
	bc.closeToLoop();

	nn = new NewNet();
	nn->cullFace = true;
	nn->setPos3f(0,0,120);
	nn->cullFaceMode = GL_BACK ;
	nn->setColor3f(1,0,0);
//	add(nn);

	Texture * t = new Texture("./Resources/Pix/skyscraper.jpg");

	// City


	for (int i = 0 ; i < 49; i ++)
	{
		SkySkraper * house = new SkySkraper();
		house->setSideTexture(t);
		house->base[0] = 20;
		house->base[1] = 20;
		house->height = 0;
		for (int j = 0; j < 4; j++) {
			Rect * r = house->getSide(j);
			r->textureScale = 0.05;
		}
		house->setPos3f( -140 + house->base[0]* 2* (i%7) ,
							-250 + house->height,
							-140 + (i / 7)  * house->base[1] * 2 );
		city.push_back(house);
		//add(city[i]);
	}

	GLfloat height;
	for (int i = 0 ; i < city.size(); i ++)
	{
		height = rand() % 150 + 1;
		cityMaxHeight.push_back(height);
	}

	skysracer = new SkySkraper();
	skysracer->setSideTexture(t);
	skysracer->setPos3f(-10,-5,5);
	add(skysracer);

}

void DemoScene1::calc(GLfloat time)
{
	static GLfloat last_calc_time = time;
	GLfloat delta = time - last_calc_time;

	GLfloat maxGrowthDurration = 10000 ; // ms
	GLfloat maxHouseHeight = 10 ;

	for (int i = 0; i < city.size(); ++i) {
		if (city[i]->height < cityMaxHeight[i])
		{
			city[i]->height +=  delta / maxGrowthDurration;
			//city[i]->pos[1] = city[i]->dim[1] / 2;
			//city[i]->calc(time);


		}
	}


	for (unsigned int i = 0 ; i < tos ; i ++)
	{
		Object * o = objs[i];
		o->calc(time);
	}



	bc.calc(time);
	atom->rot[2] ++;
	atom->rot[1] ++;
	atom->rot[0] ++;
	nn->verts[69][30][2] =50* sin(time/100);
	//bc.f(nn->verts[30][30]);
	nn->calc(time);

	GLfloat oldPePos[3] = {pe->pos[0],pe->pos[1],pe->pos[2] };
//	bc.f(pe->pos);

	for (int k = 0; k < 3; ++k) {
		pe->dir[k] = (pe->pos[k] - oldPePos[k])* 10;
	}


	//pe->pos[2] -= 200;
	bc.f(atom->pos);

}
void DemoScene1::draw()
{
	Scene::draw();
	for ( int i  = 0;  i < city.size() ; ++ i) {
		//city[i]->draw();
	}
	//bc.draw();
}

DemoScene1::~DemoScene1() {
	// TODO Auto-generated destructor stub
}
