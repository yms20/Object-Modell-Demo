#ifndef _H_KOMMSTAR
#define _H_KOMMSTAR
#include "object.h"
class KommStar : public Object
{
public:
       GLuint stripes;
       GLfloat rad;
       
       // Constructor
       KommStar(GLuint sides, GLfloat r) : Object()
       {
           stripes = sides ;
           rad = r;      
       }
      GLfloat dim[2];
      void draw();      
      
};
#endif
