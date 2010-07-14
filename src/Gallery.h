/*
 * Gallery.h
 *
 *  Created on: Jan 12, 2010
 *      Author: johannes
 */

#ifndef GALLERY_H_
#define GALLERY_H_
#include "files/Directory.h"
#include "files/texture.h"
#include "objs/rect.h"
#include "objs/object.h"

class Gallery : public Object {


	struct threadTexture{
		Texture * tex;
		int arraypos;
		int w;
		int h;
	};

	int texturePipe[2];
public:

	Directory * directory;

	int picture_count;
	int selected;
	Rect * plane ;


	Texture * * texture ;
	Rect * * mirror ;
	Rect * * canvas ;
	GLfloat  cHeight ; // width of canvas
	GLboolean animation ;
	GLfloat flipTime;
	GLfloat animationStart;
	int nextSelected;

	void prev();
	void next();

	void loadTextures();
	void initCanvas();
	Gallery(Directory * dir);
	Gallery(){};
	virtual ~Gallery();

	// Inherted from Object
	void draw();
	void calc(GLfloat time);
	virtual Object *  clone(){ return new Gallery();}

	  // InputHanding
	   virtual void keyPressed(GLint key);
	   virtual void specialKeyPressed(GLint key);
};

#endif /* GALLERY_H_ */
