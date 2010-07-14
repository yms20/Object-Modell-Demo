/*
 * Light.cpp
 *
 *  Created on: Dec 4, 2009
 *      Author: johannes
 */

#include "Light.h"

void Light::construct(){
	id = id_ctr ++;
	isSpotLight = false;
	isEnabled = false;
	setPosition(0,0,0);
	init();

}
Light::Light() {
	construct();
}
Light::Light(GLfloat r,GLfloat g, GLfloat b, GLfloat a) : Object(){

	setAmbient(r ,g ,b ,a  );
	setDiffuse(r,g,b,a);
	setSpecular(r,g,b,a);

	construct();

}

void Light::init(){
	if(isEnabled)
	{

		glEnable(GL_LIGHT0 + id);
		//glEnable(GL_NORMALIZE);
		//glEnable(GL_COLOR_MATERIAL);
		//glEnable(GL_LIGHTING);

		glLightfv(GL_LIGHT0 + id, GL_AMBIENT,  ambient);
		glLightfv(GL_LIGHT0 + id, GL_DIFFUSE,  diffuse);
		glLightfv(GL_LIGHT0 + id, GL_SPECULAR, specular);
		glLightfv(GL_LIGHT0 + id, GL_POSITION, position);


		// Spotlight
		if (isSpotLight)
		{
			glLightfv(GL_LIGHT0 + id, GL_SPOT_CUTOFF, &cutoff);
			glLightfv(GL_LIGHT0 + id, GL_SPOT_DIRECTION, direction);
			// Abschwaechung nach aussen
			glLightfv(GL_LIGHT0 + id, GL_SPOT_EXPONENT, &exponent);
			// abschwaechuns anteile
			glLightfv(GL_LIGHT0 + id, GL_CONSTANT_ATTENUATION,&kc);
			glLightfv(GL_LIGHT0 + id,GL_LINEAR_ATTENUATION,&kl);
			glLightfv(GL_LIGHT0 + id,GL_QUADRATIC_ATTENUATION,&kq);
		}
	}
	else
	{
		glDisable(GL_LIGHT0 + id);
	}

}
void Light::setPosition(GLfloat x,GLfloat y,GLfloat z){
	position[0] = x;
	position[1] = y;
	position[2] = z;
	// Pointlight
	position[3] = 1;

}
void Light::setAmbient (GLfloat r,GLfloat g,GLfloat b,GLfloat a){
	ambient[0] = r;
	ambient[1] = g;
	ambient[2] = b;
	ambient[3] = a;

}
void Light::setDiffuse (GLfloat r,GLfloat g,GLfloat b,GLfloat a){

	diffuse[0] = r;
	diffuse[1] = g;
	diffuse[2] = b;
	diffuse[3] = a;
}
void Light::setSpecular(GLfloat r,GLfloat g,GLfloat b,GLfloat a){
	specular[0] = r;
	specular[1] = g;
	specular[2] = b;
	specular[3] = a;
}


void Light::spotLight(GLfloat dirX, GLfloat dirY, GLfloat dirZ,
				      GLfloat cutoffAngle,GLfloat exponent,
			          GLfloat kC, GLfloat kL,GLfloat kQ){

	position[3] = 0;
	isSpotLight = true;

	direction[0] = dirX;
	direction[1] = dirY;
	direction[2] = dirZ;
	cutoff = cutoffAngle;
	kc = kC;
	kl = kL;
	kq = kQ;

	//Reinit Light
	init();

}
void Light::enable()
{
	isEnabled = true;
	init();
}
void Light::disable()
{
	isEnabled = false;
	init();
}

Light::~Light() {
}

void Light::draw()
{

beginDraw();
	static GLUquadricObj * q;
	if (q == 0 )
		q = gluNewQuadric();
	// TODO : Waer schoen wenn der Zylinder in die richtige Richtung zeigt
	//glRotatef(direction)
	glColor3f(ambient[0],ambient[1],ambient[2]);

	if (isSpotLight)
		glutSolidCone(2,3, 8,8);
	else
		glutSolidSphere(2, 8,8);

endDraw();
}
void Light::calc(GLfloat time)
{
	for (int k = 0 ; k < 3 ;k++)
		position[k] = pos[k];
	init();

}
