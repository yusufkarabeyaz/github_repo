#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<gl\glut.h>
#include<gl\GL.h>
#include<gl\GLU.h>
#include<algorithm>
#include<map>
#include<iostream>
#include "SOIL/SOIL.h"
 
 
#define pi 3.14159265358979323846
using namespace std;
#define SunSize 0.2
#define EarthSize 0.035
#define MarsSize 0.037

GLfloat xRot, yRot, zRot,x=-1.0,y,z;

float angle[4];
GLUquadricObj*sphere;


GLfloat SpeedX = 0.1;
GLfloat year = 0.0; //degrees
GLfloat day = 0.0;
GLfloat moonAroundEarth = 0.0;
GLfloat moonItsSelf = 0.0;
GLfloat EarthOrbitRadius = 1.0;
GLfloat MoonOrbitRadius = 0.1;
GLfloat daySpeed = 2.0 * SpeedX;
GLfloat DaysPerYear =360;
GLfloat yearSpeed = DaysPerYear / 360.0 * daySpeed * SpeedX;
GLfloat moonAroundEarthSpeed = 1 * SpeedX;
GLfloat moonItsSelfSpeed = .5 * SpeedX;

GLint LoadGLTexture(const char *filename, int width, int height)
{
    GLuint _texture;
    // filename = "/Users/gurelerceis/Documents/XCodeWorkspace/Ders2/SOIL/img_test.bmp"
    
    _texture = SOIL_load_OGL_texture // load an image file directly as a new OpenGL texture 
	(
     filename,
     SOIL_LOAD_AUTO,
     SOIL_CREATE_NEW_ID,
     SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT 
     );
    
    // check for an error during the load process 
    if(_texture == 0)
    {
	    printf( "SOIL loading error: '%s'\n", SOIL_last_result() );
    }
	
    
    glBindTexture(GL_TEXTURE_2D, _texture); // select our current texture
   // glGenerateMipmap(GL_TEXTURE_2D);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);  
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);  // texture should tile
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    return _texture;
}

void LoadTexture(GLint texture)
{
	
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);


}
typedef struct Planet
{
 GLfloat DaysPerYear,OrbitR,Size;
 GLfloat Clx,Cly,Clz;
 GLfloat yearSpeed ,day,year;
 GLint texture;
 
} Planet;

Planet Earth={365,0.7,EarthSize,
    0.0,0.5,0.6
	,0.0,0.0,0.0};
Planet Mars ={686,0.9,MarsSize,
    0.8,0.2,0.2,   //color 
    0.0 , 0.0 , 0.0};

void SpeedGen()
{
 
 Earth.yearSpeed=Earth.DaysPerYear / 360.0 * daySpeed * SpeedX;
 Mars.yearSpeed= Mars.DaysPerYear / 360.0 * daySpeed *0.5* SpeedX*2;
 
 
}
 
 
void PlacePlanet(Planet x)
{
	
	glEnable(GL_TEXTURE_2D);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);


	//glRotated(90,1,0,0);
 glRotatef(x.year,0,1.0,0);
 glTranslatef(x.OrbitR,0.0,0.0);

 glPushMatrix();
  glRotatef(x.day,0.25,1.0,0.0);
  glColor3f(x.Clx,x.Cly,x.Clz);
 
      GLUquadric* quadric = gluNewQuadric();
    gluQuadricNormals(quadric, GLU_SMOOTH);
	LoadTexture(x.texture);
	gluSphere(quadric,x.Size,20,20);  //Draw earth
  //Draw earth rotation axis
 
 glPopMatrix();
 


}
 
void RenderScene()
{
	

 glPushMatrix();
  gluLookAt( 0.0,5.0, 4,
     0.0 ,0.0 ,0.0,
     0.0 , 1.0, 0.0);
  glColor3f(1.0,1.0,0.6);

  GLfloat light_pos[] = {0.0,9.5,0.0, 1.0};
glLightfv(GL_LIGHT0, GL_POSITION, light_pos); 
GLfloat ambient[] = {0.7,0.7,0.7};
glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
GLfloat specular[] = {1.0,1.0,1.0};
glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
//GLfloat diffuse[] = {1.0,1.0,1.0};
//glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);


  
  glutSolidSphere(SunSize,50,50);
  
  //glPushMatrix();
  
   glPushMatrix();
    PlacePlanet(Earth);
	glTranslatef(0.1,0.0,0);
	glRotated(120,1.0,1.0,1.0);
	gluSphere(sphere,0.01, 50, 50);
	
   glPopMatrix();

   glPushMatrix();
		PlacePlanet(Mars);
		glPushMatrix();
			glTranslatef(0.1,0.0,0);
			glRotated(120,1.0,1.0,1.0);
			gluSphere(sphere,0.01, 50, 50);
		glPopMatrix();
	
		glPushMatrix();
			glTranslatef(0.15,0.0,0);
			glRotated(0,1.0,1.0,1.0);
			gluSphere(sphere,0.01, 50, 50);
		glPopMatrix();
   glPopMatrix();
  glPopMatrix();
 //glutSwapBuffers();
  
 
}
void Display()
{
glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

 RenderScene();
 glFlush();
 glutSwapBuffers();
 
}
 
void Reshape(int x,int y)
{
 if(y==0 ) return;
 glMatrixMode(GL_PROJECTION);
 glLoadIdentity();
 gluPerspective(40.0,(GLdouble)x/(GLdouble)y,1.5,20.0);
 glMatrixMode(GL_MODELVIEW);
 glViewport(0,0,x,y);
 Display();
 
}
 
void Idle()
{
 
 Mars.day += daySpeed;
 Mars.year += Mars.yearSpeed;
  
 Earth.day += daySpeed;
 Earth.year += Earth.yearSpeed;
  
 
 Display();
 
}
void Init(void)
{
	
	Earth.texture=LoadGLTexture("earthmap.jpg",1440,720);
 glEnable(GL_LIGHTING);
 glEnable(GL_LIGHT0);	
 glClearColor(0.0,0.0,0.0,0.0);
 //glClearDepth(30.0);
// glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
 glMatrixMode(GL_MODELVIEW);
 glLoadIdentity();
 sphere = gluNewQuadric();

}
 
int main(int argc, char **argv)
{
 // Initialize GLUT
	
    
    GLenum type;
    
 SpeedGen();
 
 glutInit( &argc, argv);
    type = GLUT_RGB;
	type |= GLUT_DOUBLE;
	type |= GLUT_DEPTH;
    type |= GLUT_MULTISAMPLE;
	glutInitDisplayMode(type);
	glutInitWindowSize(1024,768);
    // Creating a Window with rendring
    glutCreateWindow("Solar System");
	glEnable(GL_DEPTH_TEST);
 

 //Functions
 Init();
 glutDisplayFunc(Display);
 glutReshapeFunc(Reshape);
 glutIdleFunc(Idle);
 glutMainLoop();
 
 return 0;
}