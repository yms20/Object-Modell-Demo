#include <SDL/SDL.h>
#include <GL/freeglut.h>
#ifndef _H_OBJECT
#define _H_OBJECT

#define P_G 9.81
#include <cmath>
#include <vector>
#include "../controller/BoundingSphere.h"
#include "../files/texture.h"
class Object
{

    public:
           std::vector < Object * >  children;
           //GLuint tos;
           Texture  * tex;
           GLfloat pos[3]; // x,y,z Axis
           GLfloat rot[3]; // x,y,z Axis Rotation
           GLfloat color[4];
           GLboolean lightOn;
           GLboolean textureOn;
           GLboolean materialOn;
           GLboolean cullFace;
           GLboolean shadeOn;

           GLint cullFaceMode;

           // Collet The Normals if Object has any
           // They can be shown by draNormals Switch
           GLboolean drawNormals;

           // Physicss Section
           GLboolean drawForces;
           GLboolean drawBoundings;
           BoundingSphere * boundingSphere;
           GLfloat mass ;
           GLfloat speed[3];
           GLfloat accel[3];
           GLfloat force[3];
           GLfloat last_calc_time;

		   Object();
		   virtual ~Object();
           // Math Section
           GLfloat distanceTo(Object * o);
           void invertForce();

           // Abstract Methods
           virtual  void draw() = 0;
           virtual  void calc(GLfloat time) = 0;
           virtual  Object * clone() = 0;
           //Managenet Methods
           void add(Object * o);
           void setColor3fv(GLfloat * c);
           void setColor3f(GLfloat r, GLfloat g, GLfloat b);

           void setPos3fv(GLfloat * p);
           void setPos3f(GLfloat x, GLfloat y, GLfloat z);

           void  beginDraw();
           void  endDraw();
           void  setTexture( char * file);
           void  setTexture( Texture * tex);

           // InputHanding
           virtual void keyPressed(GLint key){}
           virtual void specialKeyPressed(GLint key){}

};
#endif
