#include "Bee.h"

Bee::Bee() : Object()
{
	O[0] = 0;
	O[1] = 0;
	O[2] = 0;

	hmax = 10;
	r = 60;
	size = 4;
}

Bee::~Bee()
{
}

// Schwarz Gelb gestreifte Kugel, doe mit z in z richtung gezerrt werden kann
void kugel(float r, float z){
	float  u,v ;
	int ctr =0 ;
	float step = 8;
	GLfloat p[3];
//	glBegin(GL_LINE_LOOP);
		for (v = -M_PI/2; v <= M_PI/2 + M_PI/step/2 ; v+= M_PI/step) {
	ctr ++;
	glNormal3fv(p);
	glVertex3fv(p);
			if (ctr %2 ){
				glColor3f(1,1,0);
			} else
			glColor3f(0,0,0);

	glBegin(GL_QUAD_STRIP);
	for (u = 0; u <= 2*M_PI + M_PI/step/2 ; u+= M_PI/step) {

			p[0]  = cos(u) * cos(v) * r;
			p[1]  = sin(u) * cos(v) * r;
			p[2]  = sin(v)  * (r+ z) ;
			glNormal3fv(p);
			glVertex3fv(p);
			if (ctr %2 ){
				glColor3f(1,1,0);
			} else
			glColor3f(0,0,0);

			p[0]  = cos(u  ) * cos(v + (M_PI/step) ) * r;
			p[1]  = sin(u  ) * cos(v + M_PI/step) * r;
			p[2]  = sin(v + M_PI/step)  * (r+ z) ;
			glNormal3fv(p);
			glVertex3fv(p);
		}
	glEnd();

	}
}

void ellipse(float r, float z){
	//fascht wie die kugel nur kaum y
	float  u,v ;
	float step = 10;
	GLfloat p[3];
	glBegin(GL_LINE_LOOP);
	for (u = 0; u < 2*M_PI; u+= M_PI/step) {
		for (v = -M_PI/2; v < M_PI/2; v+= M_PI/step) {

			p[0]  = cos(u) * cos(v) * r;
			p[1]  = sin(u) * cos(v) * r/10;
			p[2]  = sin(v)  * (r+ z) ;

			glVertex3fv(p);

		}

	}
	glEnd();
}


void Bee::bee(GLfloat size){

	glColor3f(1,0,0);
	glPointSize(3);

	//Bauch
	kugel(1*size,  0.5*size );
	//Koerper
	glTranslatef(0,0,2*size );
	kugel(0.6*size, 0 );
	glTranslatef(0,0,-2*size );

	glColor3f(1,1,1);

	// Fluegel verschieben zum Koerper
	glTranslatef(0,0,2*size );

	glRotatef(60*sin(localtime*localtime/10.0),0,0,1);
	glTranslatef(2.5*size,0,0 );
	glRotatef(90,0,1,0);
	ellipse(1*size,1*size);
	glRotatef(-90,0,1,0);

	glTranslatef(-2.5*size,0,0 );
	glRotatef(-60*sin(localtime*localtime/10.0),0,0,1);


	glRotatef(-60*sin(localtime*localtime/10.0),0,0,1);
	glTranslatef(-2.5*size,0,0 );
	glRotatef(90,0,1,0);
	ellipse(1*size,1*size);
	glRotatef(-90,0,1,0);

	glTranslatef(2.5*size,0,0 );
	glRotatef(60*sin(localtime*localtime/10.0),0,0,1);

	// Ende der Fluegel
	glTranslatef(0,0,-2*size );

	// Kopf
	glTranslatef(0,0,3.5*size );
	glRotatef(45,1,0,0);
	kugel(0.8*size,0.2*size);
	glRotatef(-45,1,0,0);
	glTranslatef(0,0,-3.5*size );
}

void Bee::calc(float time){
	localtime = time;

	h = hmax/2 + hmax/2 * sin (localtime/1000.0);

	rot = 2 *M_PI/36 *  (localtime/1000);
}

void Bee::draw(){
	beginDraw();
		glTranslatef(O[0],O[1],O[2]);

		glRotatef(-rot * 36/2*M_PI,0,1,0);
		glTranslatef(r,h,0);
		bee(size);
		glTranslatef(-r,-h,0);
		glRotatef(rot * 36/2*M_PI,0,1,0);
		glTranslatef(-O[0],-O[1],-O[2]);
	endDraw();
}
