#include "cubearray.h"
#include "cube.h"
#include  <cmath>
void CubeArray::draw(){

     unsigned char * b;
     if (textureOn)
     {
          b = (unsigned char *) (tex->image->pixels);
     }

    beginDraw();
        for (int i = -dim[0]/2 ; i < dim[0]/2 ; i++)
        for (int j = -dim[1]/2 ; j < dim[1]/2 ; j++)
        {
        float abstand = 2;

        float f = 10 * sin (3*(t + i)* M_PI/180.0);
        float xf =        50*  0.5+0.5*sin((t+j)/100.0);
        glTranslatef(abstand*i,abstand*j,f+xf);

        if(textureOn){
              static int ypix = 400;
              static int xpix = 100;
              int pos = ((dim[1]/2 + j) * tex->image->w
                      +  (dim[0]/2 + i) )*3;
              glColor3f(b[pos+0]/255.0,
                        b[pos+1]/255.0,
                        b[pos+2]/255.0);
        }else
        {
        glColor3f(0.5+0.5*cos(f/10),
                  0.5+0.5*sin((t+j)/100.0),
                  0.5+0.5*sin((t*j)/100.0));
        }
        Cube(1.5+f/20).draw();


        glTranslatef(abstand*-i,abstand*-j,-(f+xf));
        }
    /*
    glBegin(GL_QUADS);
    glNormal3f(0,0,-1);
    glTexCoord2f(0.0, 0.0);
    glVertex3f(-dim[0]/2,-dim[1]/2,0);
    glTexCoord2f(0.0, 1.0);
    glVertex3f(-dim[0]/2, dim[1]/2,0);
    glTexCoord2f(1.0, 1.0);
    glVertex3f( dim[0]/2, dim[1]/2,0);
    glTexCoord2f(1.0, 0.0);
    glVertex3f( dim[0]/2,-dim[1]/2,0);
    glEnd();
    */
    endDraw();

}
void CubeArray::calc(GLfloat time){}
