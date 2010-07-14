#include "newnet.h"
#include <math.h>
void NewNet::draw()
{
  beginDraw();
  glColor4f(1,0,0,0);
  glPointSize(3);

  // Draw Balls
  if (drawBalls)
    for (int i = 0 ; i < ycnt ; i ++)
      for (int j = 0 ; j < xcnt ; j ++)
      {
	static GLUquadricObj * q;
      if (q == 0 )
	q = gluNewQuadric();
	glTranslatef(verts[j][i][0],verts[j][i][1],verts[j][i][2]);
	glColor3f(0,1,1);
	  gluSphere(q,2,6,6); // h, subdiv,subdiv
	  glTranslatef(-verts[j][i][0],-verts[j][i][1],-verts[j][i][2]);
      }



  //Draw Netz
  if(drawNetz)
  {
    glPointSize(1);
    glBegin(GL_LINES);

    for (int i = 1 ; i < ycnt - 1 ; i ++)
    for (int j = 1 ; j < xcnt - 1 ; j ++)
    {
      glColor3f(0,1,0);
      glVertex3fv(verts[j][i]);
      glVertex3fv(verts[j+1][i]);

      glVertex3fv(verts[j][i]);
      glVertex3fv(verts[j][i+1]);

      glVertex3fv(verts[j][i]);
      glVertex3fv(verts[j-1][i]);

      glVertex3fv(verts[j][i]);
      glVertex3fv(verts[j][i-1]);

      if(drawForces)
      {
	glColor3f(1,0,0);
	glVertex3fv(verts[j][i]);
	glVertex3f(verts[j][i][0] +force[j][i][0],
		  verts[j][i][1] +force[j][i][1],
		  verts[j][i][2] +force[j][i][2]);
      }
    }
    glEnd();
  }
	// Draw poly
	if (drawPoly)
	{
		glColor4fv(color);
		glBegin(GL_TRIANGLES);
		for (int i =  1; i < ycnt -1 ; i ++)
		  for (int j = 1 ; j < xcnt -1 ; j ++)
		  {


			calcNormal(j,i);
			glVertex3fv(verts[j][i]); //0
			calcNormal(j,i+1);
			glVertex3fv(verts[j][i+1]); //1
			calcNormal(j+1,i);
			glVertex3fv(verts[j+1][i]); //3

			glVertex3fv(verts[j+1][i]); //3
			//calcNormal(j+1,i);
			glVertex3fv(verts[j][i+1]);  //1
			//calcNormal(j,i+1);
			glVertex3fv(verts[j+1][i+1]); //2
			//calcNormal(j+1,i+1);
		   // drawNormal(j,i);
			//drawNormal(j,i+1);
		   // drawNormal(j+1,i);
			//drawNormal(j+1,i+1);
		   // drawNormal(j,i+1);
		   // drawNormal(j+1,i);

		  }

		glEnd();
	} // end if draw poly
  endDraw();
}


void NewNet::drawNormal(int j, int i)
{

	   float x = verts[j][i][0];
	   float y = verts[j][i][1];
	   float z = verts[j][i][2];


	  int xs[] = {-1,0,1,1, 1, 0,-1,-1};
	  int ys[] = {1 ,1,1,0,-1,-1,-1,0};

	  float n1=0,n2=0,n3=0;

	  for (int t =0; t<8; t++){


	    float a1 = verts[j + xs[t] ][i + ys[t] ][0]-x;
	    float a2 = verts[j + xs[t] ][i + ys[t] ][1]-y;
	    float a3 = verts[j + xs[t] ][i + ys[t] ][2]-z;

	    float b1 = verts[j + xs[(t+1)%8] ][i + ys[(t+1)%8] ][0]-x;
	    float b2 = verts[j + xs[(t+1)%8] ][i + ys[(t+1)%8] ][1]-y;
	    float b3 = verts[j + xs[(t+1)%8] ][i + ys[(t+1)%8] ][2]-z;

	    float nx = a2*b3 - a3*b2;
	    float ny = a3*b1 - a1*b3;
	    float nz = a1*b2 - a2*b1;

	    n1+=nx;
	    n2+=ny;
	    n3+=nz;


	  }
	  float leng = sqrt(n1*n1 + n2*n2+ n3*n3);
	  n1/=leng;
	  n2/=leng;
	  n3/=leng;

	    //draw Normals

	    glColor3f(1,1,1);
	    glBegin(GL_LINES);
	    glVertex3f(x,y,z);
	    glVertex3f(x+n1,y+n2,+n3);
	    glEnd();
}

void NewNet::calcNormal(int j, int i)
{

   float x = verts[j][i][0];
   float y = verts[j][i][1];
   float z = verts[j][i][2];


  int xs[] = {-1,0,1,1, 1, 0,-1,-1};
  int ys[] = {1 ,1,1,0,-1,-1,-1,0};

  float n1=0,n2=0,n3=0;

  for (int t =0; t<8; t++){


    float a1 = verts[j + xs[t] ][i + ys[t] ][0]-x;
    float a2 = verts[j + xs[t] ][i + ys[t] ][1]-y;
    float a3 = verts[j + xs[t] ][i + ys[t] ][2]-z;

    float b1 = verts[j + xs[(t+1)%8] ][i + ys[(t+1)%8] ][0]-x;
    float b2 = verts[j + xs[(t+1)%8] ][i + ys[(t+1)%8] ][1]-y;
    float b3 = verts[j + xs[(t+1)%8] ][i + ys[(t+1)%8] ][2]-z;

    float nx = a2*b3 - a3*b2;
    float ny = a3*b1 - a1*b3;
    float nz = a1*b2 - a2*b1;

    n1+=nx;
    n2+=ny;
    n3+=nz;


  }
  float leng = sqrt(n1*n1 + n2*n2+ n3*n3);
  //n1/=leng;
  //n2/=leng;
  //n3/=leng;


  glNormal3f(n1,n2,n3);
}

void NewNet::calc(float t){

	GLfloat deltaT = (t- last_calc_time) / 1000;
  //    |
  //  ------
  //    |
  // Punkt hat 4 verbindungen
  // Punkt hat eine Kraft in die er seine position
  // bein naechsten durchlauf aendert
  //

  //if (((int)(t/100 ))% 2 ==  0)
  {

  //  verts[1][1][0] = 0.5;
  //  verts[1][1][1] = 0.5;
   float  newforce[xcnt][ycnt][3];

      for (int i = 1 ; i < ycnt - 1 ; i ++)
    for (int j = 1 ; j < xcnt - 1 ; j ++)
    {
      //Pos
      float x = verts[j][i][0];
      float y = verts[j][i][1];
      float z = verts[j][i][2];
      // Force
      float fx = force[j][i][0];
      float fy = force[j][i][1];
      float fz = force[j][i][2];

      float newfx, newfy, newfz;

      for(int dj = -1 ; dj <= 1 ; dj ++)
      for(int di = -1 ; di <= 1 ; di ++)
     // if ((dj !=  di ) )
     if (!(dj == di && dj == 0))
      {
		  // Ein nachbar
		// Aenderungen der Eingenkraft enstehen nur dich abstand
		// dh wechselwirkung

		float px = verts[j+dj][i+di][0];
		float py = verts[j+dj][i+di][1];
		float pz = verts[j+dj][i+di][2];

		float fnx = force[j+dj][i+di][0];
		float fny = force[j+dj][i+di][1];
		float fnz = force[j+dj][i+di][2];

		float fnD = sqrt(fnx* fnx + fny*fny + fnz * fnz);

		if (fnD > 1)
		{
			fnx= fnx / fnD ;
			fny= fny /fnD ;
			fnz= fnz /fnD ;
		}
		//Vektor zum nachbarn
		float dx = px - x;
		float dy = py - y;
		float dz = pz - z;

		// Entfernung zum nachbarn
		float dist = sqrt(dx* dx + dy*dy + dz * dz);

		//Falls Entfernung Groesser 1 entsteht anziehung
		// Hier fehlt noch das abziehen des normalabstands von 1
	/*
	*/
		if (dist > 1)
		{
			//if (dist < 100)
			{
			  fx += ((dist-1)/4 * dx/dist );
			  fy += ((dist-1)/4 * dy/dist );
			  fz += ((dist-1)/4 * dz/dist );

			}
		}else
		if (dist < 1)
		{
		  fx -= ((1-dist)/4 * dx/dist );
		  fy -= ((1-dist)/4 * dy/dist) ;
		  fz -= ((1-dist)/4 * dz/dist );
		}else if (dist == 1)
		{
		  printf ("%f %f %f\n",fx,fy,fz);

		}




      } // Nachbar loop

      // normalize the Force

      float leng = sqrt(fx*fx+ fy*fy+fz*fz);
      if (leng > 0)
      {
      newforce[j][i][0] = fx  ;//leng;
      newforce[j][i][1] = fy  ;//leng;
      newforce[j][i][2] = fz  ;//leng;
      }
    }

    for (int i = 1 ; i < ycnt - 1 ; i ++)
    for (int j = 1 ; j < xcnt - 1 ; j ++)
    {
    	force[j][i][0] = newforce[j][i][0] ;// * daempfung ;
        force[j][i][1] = newforce[j][i][1] ;//* daempfung ;
        force[j][i][2] = newforce[j][i][2] ;//* daempfung ;
/*

    	force[j][i][0] += (newforce[j][i][0] - force[j][i][0])  *daempfung;
        force[j][i][1] += (newforce[j][i][1] - force[j][i][1])  *daempfung ;
        force[j][i][2] += (newforce[j][i][2] - force[j][i][2]) *daempfung ;
 */



      verts[j][i][0] += force[j][i][0]*daempfung ;//*deltaT;
      verts[j][i][1] += force[j][i][1]*daempfung ;//*deltaT;
      verts[j][i][2] += force[j][i][2]*daempfung ;//*deltaT;
    }
  }


  last_calc_time = t;
}
