#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define ESCAPE 27

int window; 
float xrot, yrot, zrot;

GLfloat LightAmbient[]=  { 0.5f, 0.5f, 0.5f, 1.0f };
GLfloat LightDiffuse[]=  { 0.2f, 0.2f, 0.2f, 1.0f };
GLfloat LightPosition[]= { 5.0f, 5.0f, 5.0f, 1.0f };

void InitGL(int Width, int Height)
{
    glClearColor(0.13f, 0.13f, 0.13f, 0.0f);
    glClearDepth(1.0);
    glDepthFunc(GL_LESS);
    glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
    glShadeModel(GL_SMOOTH);
    //glBlendFunc(GL_SRC_ALPHA,GL_ONE);
	glLightfv(GL_LIGHT1, GL_AMBIENT, LightAmbient);
	glLightfv(GL_LIGHT1, GL_POSITION,LightPosition);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, LightDiffuse);
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
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glColor4f(1.0f,0.0f,0.0f,0.25f);
    glLoadIdentity();

    glTranslatef(0.0f,0.0f,-5.0f);
    
    glRotatef(xrot,0.001f,0.0f,0.0f);
    glRotatef(yrot,0.0f,0.001f,0.0f);
    glRotatef(zrot,0.0f,0.0f,0.001f);

	glBegin(GL_TRIANGLES);
		glColor4f(0.0f,1.0f,1.0f,1.0f);
		glVertex3f(0.0f, 0.0f,  -1.0f);
		glVertex3f(0.5f, -0.5f,  0.0f);
		glVertex3f(0.5f, 0.5f,  0.0f);

		glColor4f(1.0f,1.0f,0.0f,1.0f);
		glVertex3f(0.0f, 0.0f,  -1.0f);
		glVertex3f(-0.5f, -0.5f,  0.0f);
		glVertex3f(-0.5f, 0.5f,  0.0f);

		glNormal3f(1.0f, 1.0f, 0.0f);
		glColor4f(0.0f,1.0f,0.0f,1.0f);
		glVertex3f(0.0f, 0.0f,  -1.0f);
		glVertex3f(-0.5f, -0.5f,  0.0f);
		glVertex3f(0.5f, -0.5f,  0.0f);

		glColor4f(1.0f,0.0f,0.0f,1.0f);
		glVertex3f(0.0f, 0.0f,  -1.0f);
		glVertex3f(-0.5f, 0.5f,  0.0f);
		glVertex3f(0.5f, 0.5f,  0.0f);

	glEnd();

	glBegin(GL_QUADS);

		glColor4f(0.5f,0.0f,0.5f,1.0f);
		glVertex3f(0.25f, 0.25f ,0.5f);
		glVertex3f(-0.25f, 0.25f ,0.5f);
		glVertex3f(-0.25f, -0.25f ,0.5f);
		glVertex3f(0.25f, -0.25f ,0.5f);

		glColor4f(1.0f,0.0f,0.0f,1.0f);
		glVertex3f(0.25f, -0.25f ,0.5f);
		glColor4f(0.0f,1.0f,0.0f,1.0f);
		glVertex3f(0.25f, 0.25f ,0.5f);
		glColor4f(0.0f,1.0f,1.0f,1.0f);
		glVertex3f(0.50f, 0.50f ,0.0f);
		glColor4f(1.0f,1.0f,0.0f,1.0f);
		glVertex3f(0.50f, -0.50f ,0.0f);

		glColor4f(0.0f,0.5f,0.0f,1.0f);
		glVertex3f(-0.25f, -0.25f ,0.5f);
		glVertex3f(0.25f, -0.25f ,0.5f);
		glVertex3f(0.50f, -0.50f ,0.0f);
		glVertex3f(-0.50f, -0.50f ,0.0f);

		glColor4f(1.0f,0.0f,0.0f,1.0f);
		glVertex3f(-0.25f, -0.25f ,0.5f);
		glColor4f(0.0f,1.0f,0.0f,1.0f);
		glVertex3f(-0.25f, 0.25f ,0.5f);
		glColor4f(0.0f,1.0f,1.0f,1.0f);
		glVertex3f(-0.50f, 0.50f ,0.0f);
		glColor4f(1.0f,1.0f,0.0f,1.0f);
		glVertex3f(-0.50f, -0.50f ,0.0f);

		glColor4f(0.0f,1.0f,0.0f,1.0f);
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
    window = glutCreateWindow("Jeff Molofee's GL Code Tutorial ... NeHe '99");  
    glutDisplayFunc(&DrawGLScene);  
    glutFullScreen();
    glutIdleFunc(&DrawGLScene);
    glutReshapeFunc(&ReSizeGLScene);
    glutKeyboardFunc(&keyPressed);
    InitGL(1024, 768);
    glutMainLoop();  
    return 1;
}

