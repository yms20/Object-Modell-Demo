#ifndef _H_RECT
#define _H_RECT
#include "object.h"
class Rect : public Object
{
public:
      GLfloat dim[2];
      GLfloat texrepeat[2];
   	  GLfloat textureScale;

   	  GLboolean drawNormals;
  	  GLfloat   normal[3];

      // Constructor
      Rect() : Object(){

    	   texrepeat[0] = 1;
    	   texrepeat[1] = 1;
    	   textureScale = 1;
    	// normals = new std::vector< GLfloat[3] >();
    	   drawNormals = true;
    	   normal[0] =0 ;
    	   normal[1] = 0;
    	   normal[2] = -1;
    	  // normals.push_back(normal);
      }

      //Inherrited Methods
      void draw();
      void calc(GLfloat time);
      virtual Object *  clone();
};
#endif
