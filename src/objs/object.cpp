#include "object.h"

// Constructor
Object::Object()
{
	// tos = 0;
	  // next = NULL;
	  for (int k = 0 ; k < 3 ; k ++)
	  {
	   color[k] = 1;
	   pos[k] = 0;
	   rot[k] = 0;

	   //Physics
	   force[k] = 0;
	   speed[k] = 0;
	   accel[k] = 0;
	  }
	  color[3] = 1;
	  mass= 0;
	  drawForces = false;
	  lightOn = false;
	  textureOn = false;
	  materialOn = false;
	  drawBoundings = false;
	  cullFace = false;
	  cullFaceMode = GL_FRONT;
	  shadeOn = false;
	  drawNormals = false;

	  last_calc_time = 0;
}

void Object::beginDraw()
{
    //glPushMatrix();
    glTranslatef(pos[0],pos[1],pos[2]);
    glRotatef(rot[0],1,0,0);
    glRotatef(rot[1],0,1,0);
    glRotatef(rot[2],0,0,1);

    // Normals ar drawn red to green
    if (drawNormals )
    {
    	//for (int i = 0; i < normals->size(); i++)
    	{

			GLfloat  n[3];
		//	n[0]= normals->[i]->[0];
			//n[1]= normals[i][1];
		//	n[2]= normals[i][2];
			glBegin(GL_LINE);
			glColor3f(1,0,0);
			glVertex3fv(pos);
			glColor3f(0,1,0);
			glVertex3fv(n);
			glEnd();

		}
    }

    if (textureOn)
    {
    	//glDisable(GL_BLEND);
       glColor4fv(color);
       tex->enable();
    }else
    {
    	if(shadeOn)
    		glEnable(GL_BLEND);
    	tex->disable();
       glColor4fv(color);
    }

    if (cullFace)
    {

    	glEnable(GL_CULL_FACE);
    	glCullFace(cullFaceMode);
    }
}

void Object::add(Object * o)
{
     children.push_back(o);
  //   tos++;
     /*
     if (next != NULL)
     {
              Object * tmp = next;
              while (tmp->next != NULL)
              {
                    tmp = tmp->next;
              }
              tmp->next  = o;
     }else
     next = o;
     */
 }

void Object::endDraw()
{

	   if (cullFace)
	    	glDisable(GL_CULL_FACE);

    if (textureOn)
    {
       tex->disable();
    }else
    {
    	if(shadeOn)
    		glDisable(GL_BLEND);

    }

    // if (tos > 0 )
     {
     for (unsigned int i = 0 ; i < children.size()  ; i ++)
         children[i]->draw();
     }
     /*
     if (next != NULL)
     {
              Object * tmp = next;
              while (tmp != NULL)
              {
                    tmp->draw();
                    tmp = tmp->next;
              }

     }
*/

     if(drawBoundings)
     {
    	 if (boundingSphere)
    	 {
    		 boundingSphere->draw();
    	 }
     }

     if (drawForces)
     {
    	 //Force (Blue) (Left)
    	 //glTranslatef(-10,0,0);
    	 glColor3f(1,0,1);
		 glBegin(GL_LINES);
			 glVertex3f(0,0,0);
			 glVertex3fv(force);
    	 glEnd();

    	 //Speed (Yellow)(Right)
    	// glTranslatef(20,0,0);
    	 glColor3f(1,1,0);
		 glBegin(GL_LINES);
			 glVertex3f(0,0,0);
			 glVertex3fv(speed);
    	 glEnd();
    	// glTranslatef(-10,0,0);
     }

    glRotatef(-rot[2],0,0,1);
    glRotatef(-rot[1],0,1,0);
    glRotatef(-rot[0],1,0,0);
    glTranslatef(-pos[0],-pos[1],-pos[2]);

    //glPopMatrix();
}

void Object::setTexture( char * file)
{
    textureOn = true;
    tex = new Texture(file);
}
void Object::setTexture( Texture * tex)
{
    textureOn = true;
    this->tex = tex;
}
// Object Math

GLfloat Object::distanceTo(Object * o)
{
	GLfloat delta[3];
	if (o != 0)
	{
		for (int i = 0 ; i < 3 ; i ++)
			delta[i] = pos[i] - o->pos[i];

		return sqrt(delta[0] * delta[0] +
				delta[1] * delta[1] +
				delta[2] * delta[2]);
	}
	return 0;
}

void Object::setColor3f(GLfloat r, GLfloat g, GLfloat b)
{
	color[0] = r;
	color[1] = g;
	color[2] = b;

}
void Object::setColor3fv(GLfloat * c)
{
	color[0] = c[0];
	color[1] = c[1];
	color[2] = c[2];
}
void Object::setPos3f(GLfloat x, GLfloat y, GLfloat z)
{
	if (boundingSphere !=0 )
	{
		//boundingSphere->setPos3f(x,y,z);
	}
	pos[0] = x;
	pos[1] = y;
	pos[2] = z;

}
void Object::setPos3fv(GLfloat * c)
{
	pos[0] = c[0];
	pos[1] = c[1];
	pos[2] = c[2];
}
Object::~Object()
{
	if (textureOn)
		delete (tex);
	  children.clear();


}

