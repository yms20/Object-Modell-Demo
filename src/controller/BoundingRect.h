/*
 * BoundingRect.h
 *
 *  Created on: Feb 5, 2010
 *      Author: johannes
 */

#ifndef BOUNDINGRECT_H_
#define BOUNDINGRECT_H_
#include <GL/glut.h>
#include <cmath>
#include "../misc/Text.h"
#include <stdio.h>
// Bounding Rectangle cant be rotated in the R^3
class BoundingRect {
public:

	GLfloat dim[3]; // Half Lenght of the Three axis
	GLfloat pos[3]; // The Middel

	enum{up_right_back =0  , up_left_back, up_left_front , up_right_front,
        lower_right_back , lower_left_back, lower_left_front , lower_right_front};
	/**
	 * REturs a Bounding Reckt Of onhe eights the size of itself,
	 * enum {up right back , up left back, up left front , up right front,
	 *      lower right back , lower left back, lower left front , lower right front}
	 */
	BoundingRect * getQuadrant(int index)
	{
		BoundingRect *result = new BoundingRect();
		GLfloat deltaPos[3];


		switch (index)
		{
		case up_right_back :
			deltaPos[0] = dim[0]/2;
			deltaPos[1] = dim[1]/2;
			deltaPos[2] = dim[2]/2;
			break;
		case up_left_back:
			deltaPos[0] = -dim[0]/2;
			deltaPos[1] = dim[1]/2;
			deltaPos[2] = dim[2]/2;
			break;
		case up_left_front:
			deltaPos[0] = -dim[0]/2;
			deltaPos[1] = dim[1]/2;
			deltaPos[2] = -dim[2]/2;
			break;
		case up_right_front :
			deltaPos[0] = dim[0]/2;
			deltaPos[1] = dim[1]/2;
			deltaPos[2] = -dim[2]/2;
			break;
		case lower_right_back :
			deltaPos[0] = dim[0]/2;
			deltaPos[1] = -dim[1]/2;
			deltaPos[2] = dim[2]/2;
			break;
		case lower_left_back:
			deltaPos[0] = -dim[0]/2;
			deltaPos[1] = -dim[1]/2;
			deltaPos[2] = dim[2]/2;
			break;
		case lower_left_front :
			deltaPos[0] = -dim[0]/2;
			deltaPos[1] = -dim[1]/2;
			deltaPos[2] = -dim[2]/2;
			break;
		case lower_right_front:
			deltaPos[0] = dim[0]/2;
			deltaPos[1] = -dim[1]/2;
			deltaPos[2] = -dim[2]/2;
			break;

		default : break;
		}

		for (int k = 0 ; k < 3 ; k++)
		{
			result->pos[k] = pos[k] + deltaPos[k];
			result->dim[k] = dim[k]/2;
		}
		return result;
	}

	/**
	 * Halbiert den Quader entlang der laengsten dimension
	 * parm  n entscheide ob die eine oder die andere Haelhtfe
	 * zurueckgegeben wird n = 1 oder n = -1;
	 */

	BoundingRect * getHalf(int n){
		BoundingRect* result = new BoundingRect();
		int qsw = 1;
		if (n == 1)
			qsw = -1;
		for (int k = 0 ; k < 3; k ++)
		{
			result->pos[k] = pos[k];
			result->dim[k] = dim[k];
		}

		float maximal = max(max(dim[0],dim[1]),dim[2]);

		if (maximal == dim[0])
		{
			result->pos[0] = pos[0] + qsw* (dim[0]/2);
			result->dim[0] = dim[0]/2;
		}else if (maximal == dim[1])
		{
			result->pos[1] = pos[1] +  qsw* (dim[1]/2);
			result->dim[1] = dim[1]/2;

		}else if (maximal == dim[2])
		{
			result->pos[2] = pos[2] +  qsw* (dim[2]/2);
			result->dim[2] = dim[2]/2;

		}else
			printf("bullshit\n");

		return result;
	}

	int isInQuadrant(GLfloat point[3])
	{
		if (isInner(point))
		{
			for (int i = 0 ; i <= 8 ; i++)
			{
				BoundingRect * quadrant = getQuadrant(i);
				if (quadrant->isInner(point)){
					delete(quadrant);
					return i;
				}
				delete(quadrant);
			}
		}else return -1;
	}
	float min(float a , float b)
	{
		if (a <= b) return a;
		else return b;
	}
	float max(float a , float b)
	{
		if (a >= b) return a;
		else return b;
	}

	bool isInner(GLfloat point[3])
	{
		GLfloat deltaVec[3] ;
		GLfloat lengthToMiddle = 0 ;
		GLfloat lengtDimension = 0;
		for (int k = 0 ; k < 3 ; k++)
		{
			deltaVec[k] = pos[k] - point[k];
			lengthToMiddle += deltaVec[k] *deltaVec[k];
			lengtDimension += dim[k] * dim[k];
		}

		// Wenn der Punkt innerhalb einer Sphaere liegt
		//if (lengtDimension < lengthToMiddle)
		{
			if (point[0] >= (min(pos[0] - dim[0],pos[0] + dim[0] ))&&
				point[0] <= (max(pos[0] - dim[0],pos[0] + dim[0] ))&&
				point[1] >= (min(pos[1] - dim[1],pos[1] + dim[1] ))&&
				point[1] <= (max(pos[1] - dim[1],pos[1] + dim[1] ))&&
				point[2] >= (min(pos[2] - dim[2],pos[2] + dim[2] ))&&
				point[2] <= (max(pos[2] - dim[2],pos[2] + dim[2] )))
					return 1;
			else
				return 0;
		}
		return -1;
	}

	void draw(){

		/*
		Text t;
		char str[25];
		sprintf(str,"%.1f %.1f %.1f",pos[0],pos[1],pos[2]);
		t.text = str;
		t.setPos3fv(pos);
		t.draw();
		*/
	    glDisable(GL_LIGHTING);     // need to disable lighting for proper text color
	    glDisable(GL_TEXTURE_2D);
		glColor3f(1,1,1);
		glTranslatef(pos[0],pos[1],pos[2]);
		glBegin(GL_LINES);

		glVertex3f(dim[0],dim[1],dim[2]);
		glVertex3f(-dim[0],dim[1],dim[2]);

		glVertex3f(dim[0],dim[1],dim[2]);
		glVertex3f(dim[0],-dim[1],dim[2]);

		glVertex3f(dim[0],dim[1],dim[2]);
		glVertex3f(dim[0],dim[1],-dim[2]);

		glVertex3f(-dim[0],-dim[1],-dim[2]);
		glVertex3f(dim[0],-dim[1],-dim[2]);

		glVertex3f(-dim[0],-dim[1],-dim[2]);
		glVertex3f(-dim[0],dim[1],-dim[2]);

		glVertex3f(-dim[0],-dim[1],-dim[2]);
		glVertex3f(-dim[0],-dim[1],dim[2]);


		glVertex3f(-dim[0],dim[1],-dim[2]);
		glVertex3f(-dim[0],dim[1],dim[2]);

		glVertex3f(-dim[0],dim[1],-dim[2]);
		glVertex3f(dim[0],dim[1],-dim[2]);


		glVertex3f(-dim[0],-dim[1],dim[2]);
		glVertex3f(-dim[0],dim[1],dim[2]);

		glVertex3f(-dim[0],-dim[1],dim[2]);
		glVertex3f(dim[0],-dim[1],dim[2]);



		glVertex3f(dim[0],-dim[1],-dim[2]);
		glVertex3f(dim[0],dim[1],-dim[2]);

		glVertex3f(dim[0],-dim[1],-dim[2]);
		glVertex3f(dim[0],-dim[1],dim[2]);

		glEnd();
		glTranslatef(-pos[0],-pos[1],-pos[2]);
	    glEnable(GL_TEXTURE_2D);
	    glEnable(GL_LIGHTING);
	}
	BoundingRect();
	void setDim(GLfloat dx,GLfloat dy,GLfloat dz){
		dim[0] = dx;
		dim[1] = dy;
		dim[2] = dz;
	}

	void setPos(GLfloat x,GLfloat y,GLfloat z)
	{
		pos[0] = x;
		pos[1] = y;
		pos[2] = z;
	}
	virtual ~BoundingRect(){
	}
};

#endif /* BOUNDINGRECT_H_ */
