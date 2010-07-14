#ifndef _H_CUBE
#define _H_CUBE
#include "object.h"
class Cube : public Object
{
public:
       // Constructor
       Cube(GLfloat s) : Object()
       {
       size = s;
       for (int k = 0; k < 3; ++k) {
		   dim[k] = s/2;
		   textureWrap[k] = 1;
       }

      }

      // Attributes
      GLfloat dim[3];
      GLfloat textureWrap[3];
      GLfloat size;
      void drawBox(GLfloat size, GLenum type);

      //Inherited from Object
      virtual void draw();
      virtual void calc(GLfloat time);
      virtual Object *  clone(){ return new Cube(size);}
};
#endif
