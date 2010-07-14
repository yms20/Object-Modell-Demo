/*
 * Gallery.cpp
 *
 *  Created on: Jan 12, 2010
 *      Author: johannes
 */

#include "Gallery.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/unistd.h>
Gallery::Gallery(Directory * dir ) {
	cHeight = 100;
	directory = dir;
	loadTextures();
	nextSelected = selected = 0;
	initCanvas();
	plane = new Rect();
	plane->dim[0] = 2000;
	plane->dim[1] = 2000;
	plane->rot[0] = 90;
	plane->color[0] = 0.2;
	plane->color[1] = 0.2;
	plane->color[2] = 0.2;
	plane->color[3] = 0.1;
}

void Gallery::next()
{
	nextSelected = (nextSelected + 1) % picture_count;
	animationStart = last_calc_time;
	animation = true;

}
void Gallery::prev()
{
	if (selected == 0)
		nextSelected  = picture_count - 1 ;
	else
		nextSelected = nextSelected - 1 ;

	animationStart = last_calc_time;
	animation = true;
}

void Gallery::calc(GLfloat time)
{
	GLfloat deltaTime = time - last_calc_time;
	GLfloat animationProgres;
	GLfloat animationDuration = 2000; // ms


	//close(texturePipe[1]); // Close Pipe for Reading
	//struct threadTexture t;
	//int n = read(texturePipe[0],&t,sizeof( t));
	//printf("n= %d \n",n);
	//texture[t.arraypos] =  t.tex ;
	//printf("Read From Pipe ! %d  %d %d \n",t.arraypos,t.w, t.h);

	initCanvas();


		if (animation)
		{
			animationProgres = (time - animationStart) / animationDuration;
			if (animationProgres >= 1)
			{
				animation = false;
				selected = nextSelected;
				animationProgres = 1;
			}
		}

	for (int i = 0 ; i < picture_count; i ++)
	{
		GLfloat ar = texture[i]->width / (float)texture[i]->height ;
		GLfloat height = cHeight ;
		GLfloat width = height * ar;

		GLfloat posX = ( width  + (selected - i) * 100);
		GLfloat posZ;
		GLfloat rotY;
		GLfloat t = animationProgres;
		if (i == selected) // Mitte
		{
			posX= 0;
			rotY= 0;
			posZ= -100;

			if (animation)
			{
				if (nextSelected > selected){

					posX=  (width + (nextSelected - i) * 100) * t;
					rotY =  (1-t) * 0 + 30 * t;
					posZ= (1-t)* -100 + 0 * t;
				}
				else if (nextSelected < selected)
				{
					posX=  ( -( width + ( i -nextSelected) * 100 ) * t);
					rotY =  (1-t) * 0 + 120 * t;
					posZ= (1-t)* -100 + 0 * t;

				}
				else
				{
					posX= 0;
					rotY= 0;
					posZ= -100;

				}
			}

		}else if (i < selected){  // Links

			if (i == nextSelected)
			{
				GLfloat akt = (width  +  (selected - i)  * 100);
				GLfloat nex = 0;
				posX=   (1-t) * akt + t * nex;
				rotY= (1-t) * 30;
				posZ= -100 * t;

				//go to middle
			}else {
				GLfloat akt = (width  +  (selected - i)  * 100);
				GLfloat nex = (width  +  (nextSelected - i)  * 100);

				posX=   (1-t) * akt + t * nex;
				posZ= 0;
				rotY= 30;
			}



		} else   // Rechts
		{
			if (i == nextSelected)
			{
				GLfloat akt = -(width  +  (i - selected )  * 100);
				GLfloat nex = 0;
				posX=   (1-t) * akt + t * nex;
				rotY= (1-t) * 120;
				posZ= -100 * t;
						//go to middle
			 }else {
				GLfloat akt = -(width  +  ( i - selected )  * 100);
				GLfloat nex = -(width  +  ( i- nextSelected )  * 100);

				posX=   (1-t) * akt + t * nex;
				posZ= 0;
				rotY= 120;
			}

		}

		canvas[i]->pos[0]= posX;
		canvas[i]->pos[2]= posZ ; // -100;
		canvas[i]->rot[1]= rotY;

		mirror[i]->pos[0] = canvas[i]->pos[0];
		mirror[i]->pos[1] = - canvas[i]->dim[1]/2;
		mirror[i]->pos[2] = canvas[i]->pos[2];
		mirror[i]->rot[1] = - canvas[i]->rot[1];
		mirror[i]->rot[0] = 180;
	}

	last_calc_time = time;
}

void Gallery::loadTextures()
{

	// Creakte a Texture Pipe for sending the Folowing Texture to the Father prgramm Memory
	pipe(texturePipe);


	// Fork The Process for Loading the Textures once the Program has started
	int pid = 1;
	//pid = fork();

	if (pid == 0 ) // Child
	{
		close(texturePipe[0]);  // Close for reading

		if (directory != 0 )
			{
				int cnt ;
				char ** files = directory->findFiles("jpg",&cnt);
				picture_count = cnt;
				texture = (Texture * * )malloc( sizeof(Texture) * cnt);

				for (int i = 0 ; i < cnt ; i++)
				{
					struct threadTexture t;

					char  file_path[2048];
					sprintf(file_path,"%s/%s",directory->path,files[i]);
					// texture[i]
					        t.tex = new Texture(file_path);
					        t.arraypos = i;
					        t.w = t.tex->width;
					        t.h = t.tex->height;

					        write(texturePipe[1],&t,sizeof(t)  );

						printf("%d size  %d \n",i, sizeof(texture[i]));
				}

				_exit(0) ;
			}
	}
	else // Main Process
	{
		if (directory != 0 )
		{
			int cnt ;
			char ** files = directory->findFiles("jpg",&cnt);
			picture_count = cnt;
			texture = (Texture * * )malloc( sizeof(Texture) * cnt);

			for (int i = 0 ; i < cnt ; i++)
			{
				char  file_path[2048];
				sprintf(file_path,"%s/%s",directory->path,files[i]);
				texture[i] = new Texture("./Resources/Pix/dummy.bmp");
			}

		}

	}
}

void Gallery::initCanvas()
{
	mirror = (Rect * * ) malloc (sizeof(Rect) * picture_count);
	canvas = (Rect * * ) malloc (sizeof(Rect) * picture_count);

	for (int i = 0 ; i < picture_count; i ++)
	{

		canvas[i] = new Rect();
		canvas[i]->textureOn = true;
		canvas[i]->tex = texture[i];
		GLfloat ar = texture[i]->width / (float)texture[i]->height ;
		GLfloat height = cHeight;
		//GLfloat height = width / ar;
		GLfloat width = ar * height;

		canvas[i]->dim[0]= width ; // texture[i]->width/10.0;
		canvas[i]->dim[1]= height ; //texture[i]->height/10.0;

		if (i == selected)
		{

			canvas[i]->rot[1]= 0;
			canvas[i]->pos[0]= 0;
			canvas[i]->pos[1]= canvas[i]->dim[1]/2;
			canvas[i]->pos[2]= -100;
		}else if (i < selected){

			canvas[i]->rot[1]= 30;
			canvas[i]->rot[2]= 180;
			canvas[i]->pos[0]=   (width  + (selected - i) * 100);
			canvas[i]->pos[1]= canvas[i]->dim[1]/2;
			canvas[i]->pos[2]= 0;

		} else
		{
			canvas[i]->rot[1]= 120;
			canvas[i]->rot[2]= 180;
			canvas[i]->pos[0]=  -(  width + (picture_count - i) * 100 );
			canvas[i]->pos[1]= canvas[i]->dim[1]/2;
			canvas[i]->pos[2]= 0;

		}


		mirror[i] = (Rect*)canvas[i]->clone();
		mirror[i]->color[0] = 0.2;
		mirror[i]->color[1] = 0.2;
		mirror[i]->color[2] = 0.2;
		mirror[i]->color[3] = 1;
		mirror[i]->rot[1] = - canvas[i]->rot[1];
		mirror[i]->rot[0] = 180;
		mirror[i]->pos[1] = - canvas[i]->dim[1]/2;

	}

}

void Gallery::keyPressed(GLint key)
{

}
void Gallery::specialKeyPressed(GLint key)
{

}

void Gallery::draw(){

	for (int i = 0 ; i < picture_count; i ++)
	{
		mirror[i]->draw();
		canvas[i]->draw();
	}
	plane->draw();
}

Gallery::~Gallery() {
	// TODO Auto-generated destructor stub
}
