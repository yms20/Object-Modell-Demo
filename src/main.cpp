#include <iostream>
#include <sstream>
#include <string>
#include <iomanip>
#include <cstdlib>
#include <GL/freeglut.h>
#include <GL/gl.h>
//#include <GL/glext.h>
#include <cmath>
#include <string.h>
#include <stdio.h>

#include <sys/types.h>
#include <dirent.h>



#include "./files/Lib3dsObject.h"
//#include "glext.h"
#include "controller/SceneController.h"
#include "controller/Camera.h"
SceneController * sc;

using namespace std;
int Light::id_ctr = 0;
int CollisionQuad::color = 0;
int Camera::id_ctr = 0;

//Camera
Camera camera;

// Statics
static int slices = 16;
static int stacks = 16;
static GLfloat theta = 0;
static float view[3] = {0,0,-150}; //  x,y,z
static GLint        windowW ;
static GLint        windowH ;
static double t ;
int mouseX;
int mouseY;
float x,y,z;
GLboolean mouseLeftDown = false;
GLboolean mouseRightDown = false;
int cameraAngleXZ  = 0;
int cameraAngleXY  = 0;
float camPosX = 0;
float camPosY = 0;
float camPosZ = -100;

// For drawing frame rate
static Text text;
void *font = GLUT_BITMAP_8_BY_13;

// Prototypes
void lightAndMat();
static void resize(int width, int height);
static void display(void);
static void key(unsigned char key, int x, int y);
void processSpecialKeys(int key, int x, int y);
static void idle(void);
void mouseCB(int button, int stat, int x, int y);
void mouseMotionCB(int x, int y);
void showFPS();
void calc();
void setView();
void timer(int dumm);


/* Program entry point */

//Objects
Lib3dsObject * l3ds ;

void initScene1(){
	srand(time(NULL));
	sc = new SceneController();
	l3ds = new Lib3dsObject("./Resources/3dsObjects/yms.3ds");
	Scene * modell = new Scene();
	modell->add(l3ds);
	sc->addScene(modell);

}


int main(int argc, char *argv[])
{

    printf("Beginning Programm \n");

    glutInit(&argc, argv);
    glutInitWindowSize(640,480);
    glutInitWindowPosition(10,10);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

    glutCreateWindow("Objects Demo");
    glutTimerFunc(20,timer,20);
    glutReshapeFunc(resize);
    glutDisplayFunc(display);
    glutKeyboardFunc(key);
    glutSpecialFunc(processSpecialKeys);
        glutMouseFunc(mouseCB);
    glutMotionFunc(mouseMotionCB);
    glutIdleFunc(idle);
    glClearColor(0,0,0,1);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    //glEnable(GL_SHADE_MODEL);
    glShadeModel(GL_SMOOTH);
    // Transparency
   // glEnable(GL_BLEND); //Enable alpha blending
    //glBlendFunc(GL_SRC_ALPHA,GL_ONE);		// Blending Function For Translucency Based On Source Alpha Value ( NEW )
    //glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); //Set the blend function

    lightAndMat();
    initScene1();

    //readCamera();
    camera.load();

    glutMainLoop();

    return 1;
}

/* GLUT callback Handlers */

static void resize(int width, int height)
{
       windowW = width;
       windowH = height;
    const float ar = (float) width / (float) height;
    glViewport(0, 0, width, height);
setView();
}

static void display(void)
{
    const double a = t*90.0;

    camera.render();

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glColor3d(1,0,0);

  //  l3ds->draw();
    sc->draw();

    static GLUquadricObj * q;
    if (q == 0 )
    		q = gluNewQuadric();
    showFPS();
    //text.draw();
    glutSwapBuffers();
}

void calc()
{
	t = glutGet(GLUT_ELAPSED_TIME) ;
	sc->calc(t);

}
void timer(int dumm)
{
     glutTimerFunc(20,timer,0);
     theta += 0.1;
     calc();
     glutPostRedisplay();
}

void setView()
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

z = cos(cameraAngleXZ*M_PI/180);
x = sin(cameraAngleXZ*M_PI/180) ;
y = cameraAngleXY /180.0;
    gluPerspective( 45.0, 16/9.0, 1.0, 10000.0 );
    gluLookAt (camPosX, camPosY,camPosZ , /* position of eye */
              camPosX + x , camPosY + y  ,camPosZ + z, /* at, where pointing at */
              0.0, 1.0, 0.0); /* up vector of the camera */

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity() ;

}



static void key(unsigned char key, int x1, int y1)
{
	printf("Normal Key   %c\n",key);
    sc->keyPressed(key);
    switch (key)
    {
		case 27 :
		case 'q':  	camera.save();
					//saveCamera();
					exit(0);
		break;
		case 'r' : camPosY += 10; setView();   break;
		case 'f' : camPosY -= 10; setView();   break;
		case 'w' : camera.moveForward();	   break;
		case 's' : camera.moveBackward(); 	   break;
		case 'a' : camera.strafLeft();  	   break;
		case 'd' : camera.strafRight();		   break;

    }

    glutPostRedisplay();
}

void processSpecialKeys(int key, int x, int y)
{
	printf("Special Key   %c\n",key);
    sc->specialKeyPressed(key);
	switch (key)
	{


		//	case GLUT_KEY_LEFT : cameraAngleXZ += 3; setView(); break;
		//	case GLUT_KEY_RIGHT : cameraAngleXZ -= 3; setView();break;
		//	case GLUT_KEY_UP	: cameraAngleXY += 3; setView();break;
		//	case GLUT_KEY_DOWN : cameraAngleXY -= 3; setView();break;

		case GLUT_KEY_F1 :
				cameraAngleXZ = 0;
				cameraAngleXY = 0;
				camPosX = 0;
				camPosY = 0;
				camPosZ =-100;
				setView();break;
		case GLUT_KEY_F2 :
				cameraAngleXZ = 0;
				cameraAngleXY = 0;
				camPosX = 0;
				camPosY = 0;
				camPosZ = 0;
				setView();break;
	}

    glutPostRedisplay();
}

static void idle(void)
{
	//calc();
    glutPostRedisplay();
}

const GLfloat light_ambient[]  = { 0.0f, 0.0f, 0.0f, 1.0f };
const GLfloat light_diffuse[]  = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_position[] = { 5.0f, 0.0f, -1.0f, 0.0f };

const GLfloat mat_ambient[]    = { 0.7f, 0.7f, 0.7f, 1.0f };
const GLfloat mat_diffuse[]    = { 0.8f, 0.8f, 0.8f, 1.0f };
const GLfloat mat_specular[]   = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat high_shininess[] = { 100.0f };





void drawString(const char *str, int x, int y, float color[4], void *font)
{
    glPushAttrib(GL_LIGHTING_BIT | GL_CURRENT_BIT); // lighting and color mask
    glDisable(GL_LIGHTING);     // need to disable lighting for proper text color
    glDisable(GL_TEXTURE_2D);

    glColor4fv(color);          // set text color
    glRasterPos2i(x, y);        // place text position

    // loop all characters in the string
    while(*str)
    {
        glutBitmapCharacter(font, *str);
        ++str;
    }

    glEnable(GL_TEXTURE_2D);
    glEnable(GL_LIGHTING);
    glPopAttrib();
}
///////////////////////////////////////////////////////////////////////////////
// display frame rates
///////////////////////////////////////////////////////////////////////////////
void showFPS()
{

    static Timer timer;
    static int count = 0;

    static stringstream ss;
    double elapsedTime;

    // backup current model-view matrix
    glPushMatrix();                     // save current modelview matrix
    glLoadIdentity();                   // reset modelview matrix

    // set to 2D orthogonal projection
    glMatrixMode(GL_PROJECTION);        // switch to projection matrix
    glPushMatrix();                     // save current projection matrix
    glLoadIdentity();                   // reset projection matrix
    gluOrtho2D(0, windowW, 0, windowH); // set to orthogonal projection

    float color[4] = {1, 1, 0, 1};

    // update fps every second
    elapsedTime = timer.getElapsedTime();
    if(elapsedTime < 1.0)
    {
        ++count;
    }
    else
    {
        ss.str("");
	ss << "T: "<< fixed << t << " ";
        ss << fixed << setprecision(1);
        ss << (count / elapsedTime) << " FPS" << ends; // update fps string
        ss << std::resetiosflags(std::ios_base::fixed | std::ios_base::floatfield);
        count = 0;                      // reset counter
        timer.start();                  // restart timer
    }
    text.text = ss.str();
    text.setPos3f(windowW-205, windowH-14,0);
    text.draw();

    //drawString(ss.str().c_str(), windowW-205, windowH-14, color, font);

    // restore projection matrix
    glPopMatrix();                      // restore to previous projection matrix

    // restore modelview matrix
    glMatrixMode(GL_MODELVIEW);         // switch to modelview matrix
    glPopMatrix();                      // restore to previous modelview matrix
}

void mouseCB(int button, int state, int x, int y)
{
    mouseX = x;
    mouseY = y;
static bool once = true;

    if(button == GLUT_LEFT_BUTTON)
    {
        if(state == GLUT_DOWN)
        {
            mouseLeftDown = true;
        }
        else if(state == GLUT_UP)
            mouseLeftDown = false;
    }

    else if(button == GLUT_RIGHT_BUTTON)
    {
      if(state == GLUT_DOWN)
        {
            mouseRightDown = true;
            if (once)
            {
            //	bc->addPoint2f(x,y);
            	once = false;
            }
        }
        else if(state == GLUT_UP)
        {
            mouseRightDown = false;
            once = true;
        }
    }

}


void mouseMotionCB(int x, int y)
{
    if(mouseLeftDown)
    {
        cameraAngleXZ -= (x - mouseX);
        if (cameraAngleXY - (y - mouseY) > -500
        	&&cameraAngleXY - (y - mouseY)< 500	)
        cameraAngleXY -= (y - mouseY);
        cameraAngleXZ %= 360;
            //setView();

        camera.angle[0] -= (y - mouseY);
        camera.angle[1] -= (x - mouseX);
        camera.angle[1] %= 360;
        camera.render();

        mouseX = x;
        mouseY = y;
    }
    if(mouseRightDown)
    {
	//n->verts[10][10][0] -= (x - mouseX);
	//n->verts[10][10][2] -= (y - mouseY);

	//nn->verts[nn->xcnt/2][nn->ycnt/2][0] -= (x - mouseX);
	//nn->verts[nn->xcnt/2][nn->ycnt/2][2] -= (y - mouseY);

	mouseX = x;
        mouseY = y;
    }
}



void lightAndMat()
{


//     glEnable(GL_LIGHT0);
    glEnable(GL_NORMALIZE);
   glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING);

/*
    glLightfv(GL_LIGHT0, GL_AMBIENT,  light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE,  light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
*/

    glMaterialfv(GL_FRONT, GL_AMBIENT,   mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE,   mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR,  mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);

}

#ifdef WIN32
int WINAPI WinMain (HINSTANCE hInstance,
                    HINSTANCE hPrevInstance,
                    LPSTR lpCmdLine,
                    int iCmdShow)
{
    char * args[1];
    args[0] = "Gaga";
    main(1,args);

}
#endif
