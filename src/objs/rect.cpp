#include "rect.h"

void Rect::draw(){
    beginDraw();
    glBegin(GL_QUADS);
    glNormal3fv(normal);
    glTexCoord2f(0.0, 0.0);
    glVertex3f(-dim[0]/2,-dim[1]/2,0);
    glTexCoord2f(0.0,  texrepeat[1]* textureScale );
    glVertex3f(-dim[0]/2, dim[1]/2,0);
    glTexCoord2f(texrepeat[0] * textureScale, texrepeat[1] * textureScale);
    glVertex3f( dim[0]/2, dim[1]/2,0);
    glTexCoord2f( texrepeat[0] * textureScale, 0.0);
    glVertex3f( dim[0]/2,-dim[1]/2,0);


    glEnd();

    if (drawNormals)
    {
    	glLineWidth(3);
		glBegin(GL_LINES);
		glColor3f(1,1,1);
		glVertex3f(0,0,0);
		glColor3f(1,1,0);
		glVertex3fv(normal);
		glEnd();
    	glLineWidth(1);
    }
    endDraw();

}
Object * Rect::clone(){
	Rect * r = new Rect();
	for (int i = 0; i < 3 ; i ++)
	{
		r->force[i] = force[i];
		r->color[i] = color[i];
		r->speed[i] = speed[i];
		r->accel[i] = accel[i];
		r->rot[i] = rot[i];
		r->pos[i] = pos[i];
	}
		r->dim[0] = dim[0];
		r->dim[1] = dim[1];
	r->color[3] = color[3];
	r->textureOn = textureOn;
	r->tex = tex;
	r->materialOn = materialOn;
	r->drawForces = drawForces;
	r->last_calc_time = last_calc_time;

	return r;
}
void Rect::calc(GLfloat time)
{

}
