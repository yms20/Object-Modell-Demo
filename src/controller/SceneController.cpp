/*
 * SceneController.cpp
 *
 *  Created on: Mar 18, 2010
 *      Author: johannes
 */

#include "SceneController.h"



void SceneController::initScene(){

	// AlteGLobals
	Gallery * gallerie;
	Net * n = new Net();
	Bee * bee = new Bee();
	Light * l1 = new Light(.2,.1,.1,0) ;
	Light * l2 = new Light(0,0.2,0,0) ;
	Light * l3 = new Light(0,0,0.2,0) ;
	Light * gallerieLight = new Light(0.6,0.6,0.6,0.1);
	BezierCurve * bc = new BezierCurve();
	Gravity grav;
	CollisionEngine * ce;


	// TestScene
	Scene * s_test = new Scene();
	//s_test->add(new SegRing());
	//addScene(s_test);

	DemoScene1 * ds1 = new DemoScene1();
	addScene(ds1);

	// Scene 0
	Scene * s0 = new Scene();
	Rect * title = new Rect();
	title->setTexture("./Resources/Pix/omtest.jpg");
	//title->setColor3f(1,1,1);
	title->dim[0]= 100;
	title->dim[1]= 100;
	title->setPos3f(0,0,10);
	s0->add(title);
    s0->add(l1);
	//addScene(s0);

	//Scene 1 (Water)
	Scene * s1 = new Scene();
	NewNet * nn = new NewNet();
	s1->add(nn);
    nn->pos[0] = 0;
	nn->pos[1] = 0;
	nn->pos[2] = 0;
    nn->rot[0] = 90;
    l3->pos[0] =0;
    l3->pos[1] =50;
    l3->pos[2] =0;

    s1->add(bee);
    s1->add(l1);
    s1->add(l2);
    s1->add(l3);

    addScene(s1);

	// Scene 2 (Gravity)
	Scene * s2 = new Scene();
	grav.scene = s2;
	s2->add(new Ball());
	Rect * rect = new Rect();
	rect->dim[0] =500;
	rect->dim[1] = 500;

	//rect->setTexture("./Resources/Pix/test.jpg");
	rect->rot[0] = 90;
	Rect * transR1 = new Rect();

	transR1->color[0] = 1;
	transR1->color[1] = 0;
	transR1->color[2] = 0;
	transR1->color[3] = 0.5;
	transR1->dim[0]= 100;
	transR1->dim[1]= 50;

	Rect * transR2 = new Rect();

	transR2->color[0] = 0;
	transR2->color[1] = 0;
	transR2->color[2] = 1;
	transR2->color[3] = 0.5;
	transR2->dim[0]= 50;
	transR2->dim[1]= 50;
	transR2->pos[2] = 20;

	s2->add(transR2);
	s2->add(transR1);
	s2->add(rect);
	s2->add(l1);
	s2->add(l2);
	s2->add(l3);
  //  addScene(s2);

	// Scene 3 (Partile System)
	Scene * s3 = new Scene();
	//scene[3].add(new Particle());
	ParticleEmitter * emitter =new ParticleEmitter();
	s3->add(emitter);
    addScene(s3);


	// Scene 4 (Bilder)
	Scene * s4 = new Scene();
	Directory *d= new Directory();
	 d->openDirectory("./Resources/Pix");
	//  d->openDirectory("/home/johannes/BIlder/090526 Kletter Tag2 Grillen Wohnheim");
	// d->openDirectory("/home/johannes/BIlder/Hochzeit Anna und Mike 1.8.09");
	gallerie =new Gallery(d);
	s4->add(gallerie);
	gallerieLight->pos[0] = -200;
	gallerieLight->pos[1] = 200;
	s4->add(gallerieLight);
    addScene(s4);


	// Szene 5 (Bezier Curve)
	Scene * s5 = new Scene();
	GLfloat point[3] = {0,0,0};
	//bc->addPoint2f(point);
	bc->addPoint2f(10,-10);
	bc->addPoint3f(-20,25,25);
	bc->addPoint3f(20,25,25);
	bc->addPoint2f(-10,-10);

	// The long bc
	BezierCurveLong * bcl = new BezierCurveLong();
	bcl->add(10,0,2);
	bcl->add(100,19,0);
	bcl->add(10,10,4);
	bcl->add(10,30,0);
	bcl->add(10,-10,0);
	bcl->add(100,19,6);
	bcl->add(10,10,0);
	bcl->add(10,30,0);
	bcl->add(10,-10,3);
//	bcl->add(-10,-10,0);
	bcl->closeToLoop();

	//bcl->add(0,10,0);
	s5->add(bcl);
//	s5->add(bc);
	addScene(s5);


	// Scene 6 (Collision & Physics)
	Scene * s6 = new Scene();
	GLint Rad = 10;
	for (GLfloat alpha = -M_PI ; alpha <= M_PI; alpha += M_PI/50.0)
	{
		GLfloat size = 1+ (rand()%Rad/2)/10.0 ;
		Ball * pb1 =new Ball(size,
							rand()%100/100.0,
							rand()%100/100.0,
							rand()%100/100.0);
		//pb1->drawBoundings = true;
		//pb1->drawForces = true;
		pb1->mass = size;
		pb1->setPos3f(Rad *(rand()%(Rad-1)) *cos(alpha),
						Rad *(rand()%(Rad-1)) *sin(alpha),
						Rad *(rand()%(Rad-1)) *cos(alpha));

		for (int k  = 0 ; k < 3 ; k ++)
			pb1->force[k] = -pb1->pos[(k ) % 3]/10;
		s6->add(pb1);

	}

	/*
	Ball * b1 = new Ball(5,1,0,0);
	b1->setPos3f(-10,5,1.5);
	b1->mass = 5;
	b1->force[0] = - b1->pos[0];
	b1->force[1] = - b1->pos[1];
	b1->force[2] = - b1->pos[2];
	b1->drawForces = 1;
	scene[6].add(b1);
	b1 = new Ball(5,0,1,0);
	b1->mass = 5;
	b1->setPos3f(10,10,0);
	b1->force[0] = - b1->pos[0];
	b1->force[1] = - b1->pos[1];
	b1->force[2] = - b1->pos[2];
	b1->drawForces = 1;
	scene[6].add(b1);
	 */
	ce = new CollisionEngine(s6);
    addScene(s6);


	// Scene 7 FileBrowser
	Scene * s7 = new Scene();
	s7->add(new FileBrowser());
    addScene(s7);



}
SceneController::~SceneController() {
	// TODO Auto-generated destructor stub
}
