#ifndef _H_NET
#define _H_NET
#include "object.h"
class Net : public Object
{
  public:
    
    static const GLint xcnt = 30;
    static const GLint ycnt = 30;
    float verts[xcnt][ycnt][3];
    
    
    Net();
      GLfloat size;
      void draw();  
      void calc(float t);
      virtual Object *  clone(){ return new Net();}
};
#endif
