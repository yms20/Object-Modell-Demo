#include "net.h"
#include <math.h>

   // Constructor
       Net::Net() : Object(){
       
	   for (int i = 0 ; i < ycnt ; i ++)
	  for (int j = 0 ; j < xcnt ; j ++)
	  {
            verts[j][i][0] = (j-xcnt/2)*6 ; 
	    verts[j][i][1] = (i-ycnt/2)*5 ;
	    verts[j][i][2] = 0;
	  }
      }
void Net::draw()
{
  
  glColor3f(1,0,0);
  glPointSize(3);

  
  for (int i = 0 ; i < ycnt ; i ++)
  for (int j = 0 ; j < xcnt ; j ++)
  {
     static GLUquadricObj * q;
   if (q == 0 )
    q = gluNewQuadric();
    glTranslatef(verts[j][i][0],verts[j][i][1],verts[j][i][2]);
      gluSphere(q,2,16,10); // h, subdiv,subdiv
      glTranslatef(-verts[j][i][0],-verts[j][i][1],-verts[j][i][2]);
  }

  glColor3f(0,1,0);
  glPointSize(1);
  
  glBegin(GL_LINES);
  
  for (int i = 1 ; i < ycnt - 1 ; i ++)
  for (int j = 1 ; j < xcnt - 1 ; j ++)
  {
    glVertex3fv(verts[j][i]);
    glVertex3fv(verts[j+1][i]);
    
    glVertex3fv(verts[j][i]);
    glVertex3fv(verts[j][i+1]);
    
    glVertex3fv(verts[j][i]);
    glVertex3fv(verts[j-1][i]);
    
    glVertex3fv(verts[j][i]);
    glVertex3fv(verts[j][i-1]);
  }
glEnd();
}


void Net::calc(float t){
 
  //    |
  //  ------
  //    |
  // Punkt hat 4 verbindungen
  // entfernung zu verbindungsPunkten ist kraft 
  
  //if (((int)(t/100 ))% 2 ==  0)
  {
    
  //  verts[1][1][0] = 0.5;
  //  verts[1][1][1] = 0.5;
   float  newverts[xcnt][ycnt][3];
    
      for (int i = 1 ; i < ycnt - 1 ; i ++)
    for (int j = 1 ; j < xcnt - 1 ; j ++)
    {
      float x = verts[j][i][0];
      float y = verts[j][i][1];
      float z = verts[j][i][2];
      float newx, newy, newz;
       newx =  ( verts[j+1][i][0]-x) + ( verts[j-1][i][0]-x )+
	       ( verts[j][i+1][0]-x) + ( verts[j][i-1][0]-x )  ;
		      
      newy =  ( verts[j+1][i][1]-y) + ( verts[j-1][i][1]-y )+
	       ( verts[j][i+1][1]-y) + (verts[j][i-1][1]-y);
	       
      newz =  ( verts[j+1][i][2]-z) + ( verts[j-1][i][2]-z )+
	       ( verts[j][i+1][2]-z) + (verts[j][i-1][2]-z);
	       
	if (newx != 0 && newy != 0 && newz != 0)
	{
	float leng = sqrt(newx* newx + newy*newy);       
	//printf("%d,%d leng %f newx %f newy %f\n",i,j,leng,newx,newy);	  
		//newx = newx / leng;
	      //newy = newy / leng;
	printf("%d,%d leng %f newx %f newy %f\n",i,j,leng,newx,newy);
	}
      newverts[j][i][0] = x+ newx/5.0 ;
      newverts[j][i][1] = y+ newy/5.0 ;
      newverts[j][i][2] = z+ newz/5.0 ;
    }
    
    for (int i = 1 ; i < ycnt - 1 ; i ++)
    for (int j = 1 ; j < xcnt - 1 ; j ++)
    {
      verts[j][i][0] = newverts[j][i][0];
      verts[j][i][1] = newverts[j][i][1];
      verts[j][i][2] = newverts[j][i][2];
    }
  }
}