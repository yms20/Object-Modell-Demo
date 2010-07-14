#ifndef _H_CUBE_ARRAY
#define _H_CUBE_ATTAY
#include "object.h"
class CubeArray : public Object
{
public:
       GLint dim[2];
       GLfloat t ; // animations Varaible
       // Constructor
       CubeArray(int dimx, int dimy) : Object(){
             t = 0;
        dim[0] = dimx;
        dim[1] = dimy;
      }
      GLfloat size;
      void draw();
      virtual void calc(GLfloat time);

};
#endif
