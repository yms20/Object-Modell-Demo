/*
 * Light.h
 *
 *  Created on: Dec 4, 2009
 *      Author: johannes
 */

#ifndef LIGHT_H_
#define LIGHT_H_

#include "object.h"

class Light : public Object {
private:
	static int id_ctr ;
public:
	int id ;

	GLfloat  ambient[4] ;// = { 0.0f, 0.0f, 0.0f, 1.0f };
	GLfloat  diffuse[4] ;// = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat  specular[4];// = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat  position[4];// position[3] == 0 then directional

	// Spotlight Properties
	GLboolean isSpotLight ;
	GLfloat direction[3];
	GLfloat cutoff; // Cutoff Angle
	GLfloat exponent; // abschwaechung nach ausse
	GLfloat kc; // Reichweite Constant
	GLfloat kl; // Reichweite Linear
	GLfloat kq; // Reichweite Quadratisch

	GLfloat isEnabled;

	void construct();
	void init();
	Light();
	Light(GLfloat r,GLfloat g,GLfloat b,GLfloat a);

	// Iherited MEthods
	virtual void draw();
	virtual void calc(GLfloat time);
	virtual Object *  clone(){ return new Light();}


	//Setters
	void setPosition(GLfloat x,GLfloat y,GLfloat z);
	void setAmbient (GLfloat r,GLfloat g,GLfloat b,GLfloat a);
	void setDiffuse (GLfloat r,GLfloat g,GLfloat b,GLfloat a);
	void setSpecular(GLfloat r,GLfloat g,GLfloat b,GLfloat a);

	void spotLight(GLfloat dirX, GLfloat dirY, GLfloat dirZ,
				   GLfloat cutoffAngle, GLfloat exponent,
				   GLfloat kC, GLfloat kL,GLfloat kQ);

	void enable();
	void disable();

	virtual ~Light();
};

#endif /* LIGHT_H_ */
