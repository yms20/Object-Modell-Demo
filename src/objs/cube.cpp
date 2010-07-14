#include "cube.h"


 void Cube::drawBox(GLfloat size, GLenum type)
{
  static GLfloat n[6][3] =
  {
    {-1.0, 0.0, 0.0},
    {0.0, 1.0, 0.0},
    {1.0, 0.0, 0.0},
    {0.0, -1.0, 0.0},
    {0.0, 0.0, 1.0},
    {0.0, 0.0, -1.0}
  };
  static GLint faces[6][4] =
  {
    {0, 1, 2, 3},
    {3, 2, 6, 7},
    {7, 6, 5, 4},
    {4, 5, 1, 0},
    {5, 6, 2, 1},
    {7, 4, 0, 3}
  };
  GLfloat v[8][3];
  GLint i;

  // right
  v[0][0] = v[1][0] = v[2][0] = v[3][0] = -dim[0]/2 ;
  // left
  v[4][0] = v[5][0] = v[6][0] = v[7][0] = dim[0]/2 ;
  // Bottom
  v[0][1] = v[1][1] = v[4][1] = v[5][1] = -dim[1]/2 ;
  // TOp
  v[2][1] = v[3][1] = v[6][1] = v[7][1] = dim[1]/2 ;
  // Front?
  v[0][2] = v[3][2] = v[4][2] = v[7][2] = -dim[2]/2 ;
  //Back
  v[1][2] = v[2][2] = v[5][2] = v[6][2] = dim[2]/2 ;

  for (i = 5; i >= 0; i--) {
    glBegin(type);
    glNormal3fv(&n[i][0]);
    glTexCoord2f(0.0, 0.0);
    glVertex3fv(&v[faces[i][0]][0]);
    glTexCoord2f(0.0, textureWrap[1]);
    glVertex3fv(&v[faces[i][1]][0]);
    glTexCoord2f(textureWrap[0], textureWrap[1]);
    glVertex3fv(&v[faces[i][2]][0]);
    glTexCoord2f(textureWrap[0], 0.0);
    glVertex3fv(&v[faces[i][3]][0]);
    glEnd();
  }
}


void Cube::draw(){
    beginDraw();

    drawBox(size, GL_QUADS);

    endDraw();

}
void Cube::calc(GLfloat time){}
