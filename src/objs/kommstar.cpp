#include "kommstar.h"
#include <cmath>
void KommStar::draw(){

    GLfloat delta = M_PI /stripes;
    GLuint c = 0;
    beginDraw();
    glBegin(GL_TRIANGLES);
    glNormal3f(0,0,-1);
    for(float t = - M_PI ; t < M_PI ; t+=delta, c++)
    {
              if (c %3 == 0)
                 glVertex3f(0,0,0);
              else
                  glVertex3f(rad * sin(t), rad * cos(t),0);
    }
    
    glEnd();
    endDraw();   

}
