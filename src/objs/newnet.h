#ifndef _H_NEWNET
#define _H_NEWNET
#include "object.h"
class NewNet : public Object
{
  public:
    int drawForces,drawBalls,drawNetz,drawPoly ;
    float daempfung ;
    static const GLint xcnt = 70;
    static const GLint ycnt = 70;
    GLfloat verts[xcnt][ycnt][3];
    GLfloat force[xcnt][ycnt][3];


       // Constructor
      NewNet() : Object(){

	init();

      }
      void init(){
	drawForces = 0;
	drawNetz = 0;
	drawPoly = 1;
	drawBalls = 0;
	daempfung = 0.128;
         for (int i = 0 ; i < ycnt ; i ++)
	  for (int j = 0 ; j < xcnt ; j ++)
	  {
        verts[j][i][0] = (j-xcnt/2.0) *9;
	    verts[j][i][1] = (i-ycnt/2.0) *8;
	    verts[j][i][2] = 0;

	    force[j][i][0] = 0;
	    force[j][i][1] = 0;
	    force[j][i][2] = 0;


	  }
      }
      GLfloat size;
      void calcNormal(int j, int i);
      void drawNormal(int j, int i);

      //Inherrited
      void draw();
      void calc(float t);
      virtual Object *  clone(){ return new NewNet();}

};
#endif
