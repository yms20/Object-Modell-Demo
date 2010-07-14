#ifndef _H_TEXTURE
#define _H_TEXTURE

#include <stdlib.h>
#include <SDL/SDL.h>
#include <GL/freeglut.h>
#include <SDL/SDL_image.h>
#include <string>
#include <stdio.h>


using namespace std;

class Texture{

      public:
      GLint height;
      GLint width;
      SDL_Surface  *image;
      GLuint textureID;
      string fileName;
      GLfloat texRepeatValue;

      Texture(char * file){

    	  fileName = file;
            // loadImageLQ(file);
		  //loadImage(file);
    	  magickLoad();
    	  printf("Tex ID %u\n",textureID);
	   }

      void loadImage(char * filename);
      void loadImageLQ( char * filename);
      void magickLoad();
      void unload();
      void enable() ;
      void disable();
};

#endif
