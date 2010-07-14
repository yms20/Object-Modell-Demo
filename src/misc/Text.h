/*
 * Text.h
 *
 *  Created on: Feb 6, 2010
 *      Author: johannes
 */

#ifndef TEXT_H_
#define TEXT_H_
#include <string>
#include "../objs/object.h"
#   define  GLUT_STROKE_ROMAN               ((void *) &glutStrokeRoman)
#   define  GLUT_STROKE_MONO_ROMAN          ((void *) &glutStrokeMonoRoman)
#   define  GLUT_BITMAP_9_BY_15             ((void *) &glutBitmap9By15)
#   define  GLUT_BITMAP_8_BY_13             ((void *) &glutBitmap8By13)
#   define  GLUT_BITMAP_TIMES_ROMAN_10      ((void *) &glutBitmapTimesRoman10)
#   define  GLUT_BITMAP_TIMES_ROMAN_24      ((void *) &glutBitmapTimesRoman24)
#   define  GLUT_BITMAP_HELVETICA_10        ((void *) &glutBitmapHelvetica10)
#   define  GLUT_BITMAP_HELVETICA_12        ((void *) &glutBitmapHelvetica12)
#   define  GLUT_BITMAP_HELVETICA_18        ((void *) &glutBitmapHelvetica18)

using namespace std;

class Text :public Object
{
public:
	Text(){
		font = GLUT_BITMAP_HELVETICA_18;
		size = 24;
	}


	string text;
	void * font;
	GLint size;

	void draw()
	{
		drawString(text.c_str());
	}
	// Inherited Methods
	void calc(GLfloat time )
	{

	}

	virtual Object *  clone(){ return new Text();}

	void drawString(const char *str)
	{
	    glPushAttrib(GL_LIGHTING_BIT | GL_CURRENT_BIT); // lighting and color mask
	    glDisable(GL_LIGHTING);     // need to disable lighting for proper text color
	    glDisable(GL_TEXTURE_2D);

	    glColor4fv(color);          // set text color
	    glRasterPos3fv(pos);        // place text position

	    // loop all characters in the string
	    while(*str)
	    {
	        glutBitmapCharacter(font, *str);
	        ++str;
	    }

	    glEnable(GL_TEXTURE_2D);
	    glEnable(GL_LIGHTING);
	    glPopAttrib();
	}
	virtual ~Text();
};

#endif /* TEXT_H_ */
