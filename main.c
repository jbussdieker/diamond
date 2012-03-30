#ifdef __APPLE__
	#include <OpenGL/gl.h>
	#include <OpenGL/glu.h>
	#include <GLUT/glut.h>
#else
	#include <GL/glut.h>
	#include <GL/gl.h>
	#include <GL/glu.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define ESCAPE 27

int window; 
float xrot, yrot, zrot;

GLfloat LightAmbient[]=  { 0.2f, 0.2f, 0.2f, 1.0f };
GLfloat LightDiffuse[]=  { 0.5f, 0.5f, 0.5f, 1.0f };
GLfloat LightPosition[]= { 2.0f, 2.0f, 5.0f, 1.0f };
GLfloat LightColor[]= { 0.6f, 0.6f, 0.6f };

typedef struct
 {
  float x,y,z;
 }stVec;

stVec CalcNormal(stVec v1, stVec v2, stVec v3)
 {
  double v1x,v1y,v1z,v2x,v2y,v2z;
  double nx,ny,nz;
  double vLen;
 
  stVec Result;
 
  // Calculate vectors
  v1x = v1.x - v2.x;
  v1y = v1.y - v2.y;
  v1z = v1.z - v2.z;
 
  v2x = v2.x - v3.x;
  v2y = v2.y - v3.y;
  v2z = v2.z - v3.z;
 
  // Get cross product of vectors
  nx = (v1y * v2z) - (v1z * v2y);
  ny = (v1z * v2x) - (v1x * v2z);
  nz = (v1x * v2y) - (v1y * v2x);
 
  // Normalise final vector
  vLen = sqrt( (nx * nx) + (ny * ny) + (nz * nz) );
 
  Result.x = (float)(nx / vLen);
  Result.y = (float)(ny / vLen);
  Result.z = (float)(nz / vLen);
 
  return Result;
 }

void InitGL(int Width, int Height)
{
    glClearColor(0.13f, 0.13f, 0.13f, 0.0f);
    glClearDepth(1.0);
    glDepthFunc(GL_LESS);
    glEnable(GL_DEPTH_TEST);
	//glEnable(GL_BLEND);
    glShadeModel(GL_SMOOTH);
    glBlendFunc(GL_SRC_ALPHA,GL_ONE);
	glLightfv(GL_LIGHT1, GL_AMBIENT, LightAmbient);
	glLightfv(GL_LIGHT1, GL_POSITION,LightPosition);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, LightDiffuse);
	//glLightfv(GL_LIGHT1, GL_SPECULAR, LightColor);
	glEnable(GL_LIGHT1);
	glEnable(GL_LIGHTING);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0f,(GLfloat)Width/(GLfloat)Height,0.1f,100.0f);
    glMatrixMode(GL_MODELVIEW);
}

void ReSizeGLScene(int Width, int Height)
{
    if (Height==0)
	Height=1;
    glViewport(0, 0, Width, Height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluPerspective(45.0f,(GLfloat)Width/(GLfloat)Height,0.1f,100.0f);
    glMatrixMode(GL_MODELVIEW);
}

void DrawGLScene()
{
	stVec p1,p2,p3,Norm;

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glColor4f(1.0f,0.0f,0.0f,0.25f);
    glLoadIdentity();

    glTranslatef(0.0f,0.0f,-5.0f);
    
    glRotatef(xrot,0.1f,0.1f,0.0f);
    glRotatef(yrot,0.0f,0.001f,0.0f);
    glRotatef(zrot,0.0f,0.0f,0.001f);

	//glMaterialfv(GL_FRONT, GL_AMBIENT, LightColor);
	//glMaterialfv(GL_FRONT, GL_SPECULAR, LightColor);
	
	//glutSolidTeapot(0.2f);

	glBegin(GL_TRIANGLES);
		// Calc the top face normal
		p3.x= 0.0f; p3.y= 0.0f; p3.z= -1.0f;
		p2.x= 0.5f; p2.y= -0.5f; p2.z= 0.0f;
		p1.x= 0.5f; p1.y= 0.5f; p1.z= 0.0f;
		Norm=CalcNormal(p1,p2,p3);
		glNormal3f(Norm.x,Norm.y,Norm.z);
		//glColor4f(0.0f,1.0f,1.0f,1.0f);
		glVertex3f(0.0f, 0.0f,  -1.0f);
		glVertex3f(0.5f, -0.5f,  0.0f);
		glVertex3f(0.5f, 0.5f,  0.0f);

		// Calc the top face normal
		p1.x= 0.0f; p1.y= 0.0f; p1.z= -1.0f;
		p2.x= -0.5f; p2.y= -0.5f; p2.z= 0.0f;
		p3.x= -0.5f; p3.y= 0.5f; p3.z= 0.0f;
		Norm=CalcNormal(p1,p2,p3);
		glNormal3f(Norm.x,Norm.y,Norm.z);
		//glColor4f(1.0f,1.0f,0.0f,1.0f);
		glVertex3f(0.0f, 0.0f,  -1.0f);
		glVertex3f(-0.5f, -0.5f,  0.0f);
		glVertex3f(-0.5f, 0.5f,  0.0f);

		// Calc the top face normal
		p3.x= 0.0f; p3.y= 0.0f; p3.z= -1.0f;
		p2.x= -0.5f; p2.y= -0.5f; p2.z= 0.0f;
		p1.x= 0.5f; p1.y= -0.5f; p1.z= 0.0f;
		Norm=CalcNormal(p1,p2,p3);
		glNormal3f(Norm.x,Norm.y,Norm.z);
		//glColor4f(0.0f,1.0f,0.0f,1.0f);
		glVertex3f(0.0f, 0.0f,  -1.0f);
		glVertex3f(-0.5f, -0.5f,  0.0f);
		glVertex3f(0.5f, -0.5f,  0.0f);

		// Calc the top face normal
		p1.x= 0.0f; p1.y= 0.0f; p1.z= -1.0f;
		p2.x= -0.5f; p2.y= 0.5f; p2.z= 0.0f;
		p3.x= 0.5f; p3.y= 0.5f; p3.z= 0.0f;
		Norm=CalcNormal(p1,p2,p3);
		glNormal3f(Norm.x,Norm.y,Norm.z);
		//glColor4f(1.0f,0.0f,0.0f,1.0f);
		glVertex3f(0.0f, 0.0f,  -1.0f);
		glVertex3f(-0.5f, 0.5f,  0.0f);
		glVertex3f(0.5f, 0.5f,  0.0f);

	glEnd();

	glBegin(GL_QUADS);

		// Calc the top face normal
		p1.x= 0.25f; p1.y= 0.25f; p1.z= 0.5f;
		p2.x= -0.25f; p2.y= 0.25f; p2.z= 0.5f;
		p3.x= -0.25f; p3.y= -0.25f; p3.z= 0.5f;
		Norm=CalcNormal(p1,p2,p3);
		glNormal3f(Norm.x,Norm.y,Norm.z);
		glVertex3f(0.25f, 0.25f ,0.5f);
		glVertex3f(-0.25f, 0.25f ,0.5f);
		glVertex3f(-0.25f, -0.25f ,0.5f);
		glVertex3f(0.25f, -0.25f ,0.5f);

		// Calc the top face normal
		p3.x= 0.25f; p3.y= -0.25f; p3.z= 0.5f;
		p2.x= 0.25f; p2.y= 0.25f; p2.z= 0.5f;
		p1.x= 0.50f; p1.y= 0.50f; p1.z= 0.0f;
		Norm=CalcNormal(p1,p2,p3);
		glNormal3f(Norm.x,Norm.y,Norm.z);
		glVertex3f(0.25f, -0.25f ,0.5f);
		glVertex3f(0.25f, 0.25f ,0.5f);
		glVertex3f(0.50f, 0.50f ,0.0f);
		glVertex3f(0.50f, -0.50f ,0.0f);

		// Calc the top face normal
		p3.x= -0.25f; p3.y= -0.25f; p3.z= 0.5f;
		p2.x= 0.25f; p2.y= -0.25f; p2.z= 0.5f;
		p1.x= 0.50f; p1.y= -0.50f; p1.z= 0.0f;
		Norm=CalcNormal(p1,p2,p3);
		glNormal3f(Norm.x,Norm.y,Norm.z);
		glVertex3f(-0.25f, -0.25f ,0.5f);
		glVertex3f(0.25f, -0.25f ,0.5f);
		glVertex3f(0.50f, -0.50f ,0.0f);
		glVertex3f(-0.50f, -0.50f ,0.0f);

		// Calc the top face normal
		p1.x= -0.25f; p1.y= -0.25f; p1.z= 0.5f;
		p2.x= -0.25f; p2.y= 0.25f; p2.z= 0.5f;
		p3.x= -0.50f; p3.y= 0.50f; p3.z= 0.0f;
		Norm=CalcNormal(p1,p2,p3);
		glNormal3f(Norm.x,Norm.y,Norm.z);
		glVertex3f(-0.25f, -0.25f ,0.5f);
		glVertex3f(-0.25f, 0.25f ,0.5f);
		glVertex3f(-0.50f, 0.50f ,0.0f);
		glVertex3f(-0.50f, -0.50f ,0.0f);

		// Calc the top face normal
		p1.x= -0.25f; p1.y= 0.25f; p1.z= 0.5f;
		p2.x= 0.25f; p2.y= 0.25f; p2.z= 0.5f;
		p3.x= 0.50f; p3.y= 0.50f; p3.z= 0.0f;
		Norm=CalcNormal(p1,p2,p3);
		glNormal3f(Norm.x,Norm.y,Norm.z);
		glVertex3f(-0.25f, 0.25f ,0.5f);
		glVertex3f(0.25f, 0.25f ,0.5f);
		glVertex3f(0.50f, 0.50f ,0.0f);
		glVertex3f(-0.50f, 0.50f ,0.0f);
	glEnd();

    xrot+=0.01f;
    yrot+=0.01f;
    zrot+=0.01f;

    glutSwapBuffers();
}

void keyPressed(unsigned char key, int x, int y) 
{
    usleep(100);

    if (key == ESCAPE) { 
		glutDestroyWindow(window); 
		exit(0);                   
    }
}

int main(int argc, char **argv) 
{  
    glutInit(&argc, argv);  
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_ALPHA | GLUT_DEPTH);  
    glutInitWindowSize(640, 480);  
    glutInitWindowPosition(0, 0);  
    window = glutCreateWindow("Diamond");  
    glutDisplayFunc(&DrawGLScene);  
    glutFullScreen();
    glutIdleFunc(&DrawGLScene);
    glutReshapeFunc(&ReSizeGLScene);
    glutKeyboardFunc(&keyPressed);
    InitGL(1024, 768);
    glutMainLoop();  
    return 1;
}

