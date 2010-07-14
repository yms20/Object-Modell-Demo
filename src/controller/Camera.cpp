/*
 * Camera.cpp
 *
 *  Created on: Apr 1, 2010
 *      Author: johannes
 */

#include "Camera.h"
#include <stdio.h>
#include <math.h>
Camera::Camera() {
	cleraColor[0] = 0;
	cleraColor[1] = 0;
	cleraColor[2] = 0;
	speed = 10;
	fov = 45;
	ratio = 16/9.0;
}

Camera::~Camera() {
	// TODO Auto-generated destructor stub
}

void Camera::render()
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    dir[0] = sin(angle[1]*M_PI/180) ; // XZ
    dir[1] = angle[0] /180.0;	// XY
    dir[2] = cos(angle[1]*M_PI/180);  //XZ

    gluPerspective( fov, ratio, 1.0, 10000.0 );
    gluLookAt (pos[0], pos[1], pos[2] , /* position of eye */
    		pos[0] + dir[0] , pos[1] + dir[1]  ,pos[2] + dir[2], /* at, where pointing at */
              0.0, 1.0, 0.0); /* up vector of the camera */

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity() ;
}

void Camera::save()
{
	FILE * cam = fopen("./cam.txt","w+");

	fprintf(cam,"%f %f %f \n ",
			pos[0],
			pos[1],
			pos[2]);

	fprintf(cam,"%d %d \n",
			angle[0],
			angle[1]);

	fflush(cam);
	fclose(cam);
}

void Camera::load()
{
	FILE * cam = fopen("cam.txt","r");

	fscanf(cam,"%f",&pos[0]);
	fscanf(cam,"%f",&pos[1]);
	fscanf(cam,"%f",&pos[2]);

	fscanf(cam,"%d",&angle[0]); // XY
	fscanf(cam,"%d",&angle[1]); //XZ

//	fscanf(cam,"%f",&x);
//	fscanf(cam,"%f",&y);
//	fscanf(cam,"%f",&z);

	printf("x %f y %f z %f \n xy %d xz %d \n  ",
				pos[0],
				pos[1],
				pos[2],
				angle[0],
				angle[1]);

	fclose(cam);
	//setView();
}
